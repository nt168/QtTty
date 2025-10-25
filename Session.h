/*
    Headless session wrapper extracted from QTermWidget's Session class.
    Preserves the original process/PTY management logic while omitting the
    GUI specific pieces such as TerminalDisplay wiring.
*/

#ifndef KONSOLE_HEADLESS_SESSION_H
#define KONSOLE_HEADLESS_SESSION_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QTimer>
#include <QSize>

#include "Pty.h"

namespace Konsole {

class Session : public QObject
{
    Q_OBJECT

public:
    explicit Session(QObject* parent = nullptr);
    ~Session() override;

    // Session identity -----------------------------------------------------
    int sessionId() const;
    int processId() const;

    // Command configuration ------------------------------------------------
    void setProgram(const QString& program);
    void setArguments(const QStringList& arguments);
    void setInitialWorkingDirectory(const QString& dir);
    void setEnvironment(const QStringList& environment);
    QString program() const;
    QStringList arguments() const;
    QString initialWorkingDirectory() const;
    QStringList environment() const;

    // Runtime control ------------------------------------------------------
    void setAddToUtmp(bool enabled);
    bool addToUtmp() const;
    void setFlowControlEnabled(bool enabled);
    bool flowControlEnabled() const;
    void setMonitorActivity(bool monitor);
    void setMonitorSilence(bool monitor);
    void setSilenceSeconds(int seconds);
    void setAutoClose(bool enabled);
    bool autoClose() const;

    void setSize(const QSize& size);
    QSize size() const;

    bool isRunning() const;
    void run();
    void close();

    // I/O ------------------------------------------------------------------
    void sendText(const QString& text);
    void sendBytes(const QByteArray& bytes);

signals:
    void receivedData(const QString& text);
    void rawDataReceived(const QByteArray& data);
    void finished();
    void finishedWithCode(int exitCode);
    void silenceDetected();
    void activityDetected();
    void flowControlStateChanged(bool enabled);

private slots:
    void handlePtyData(const char* data, int length);
    void handleProcessFinished(int exitCode, QProcess::ExitStatus status);
    void monitorTimerDone();

private:
    void restartSilenceTimer();
    void ensureProcess();
    void applyProcessEnvironment();
    QString resolveProgram() const;

    static int s_lastSessionId;

    Pty* m_shellProcess;
    QSize m_reportedSize;
    QString m_program;
    QStringList m_arguments;
    QStringList m_environment;
    QString m_initialWorkingDir;

    bool m_addToUtmp;
    bool m_flowControl;
    bool m_autoClose;
    bool m_monitorActivity;
    bool m_monitorSilence;
    bool m_notifiedActivity;
    int m_silenceSeconds;

    QTimer* m_monitorTimer;
    int m_sessionId;
};

} // namespace Konsole

#endif // KONSOLE_HEADLESS_SESSION_H
