#include "Session.h"

#include <QDir>
#include <QFile>
#include <QProcessEnvironment>
#include <QtDebug>

#include "ShellCommand.h"

namespace Konsole {

int Session::s_lastSessionId = 0;

Session::Session(QObject* parent)
    : QObject(parent)
    , m_shellProcess(new Pty(this))
    , m_addToUtmp(false)
    , m_flowControl(true)
    , m_autoClose(true)
    , m_monitorActivity(false)
    , m_monitorSilence(false)
    , m_notifiedActivity(false)
    , m_silenceSeconds(10)
    , m_monitorTimer(new QTimer(this))
    , m_sessionId(++s_lastSessionId)
{
    m_monitorTimer->setSingleShot(true);
    connect(m_monitorTimer, &QTimer::timeout, this, &Session::monitorTimerDone);

    m_shellProcess->setUtf8Mode(true);
    connect(m_shellProcess, &Pty::receivedData, this, &Session::handlePtyData);
    connect(m_shellProcess, qOverload<int, QProcess::ExitStatus>(&Pty::finished),
            this, &Session::handleProcessFinished);
}

Session::~Session() = default;

int Session::sessionId() const
{
    return m_sessionId;
}

int Session::processId() const
{
    return m_shellProcess != nullptr ? static_cast<int>(m_shellProcess->processId()) : 0;
}

void Session::setProgram(const QString& program)
{
    m_program = ShellCommand::expand(program);
}

void Session::setArguments(const QStringList& arguments)
{
    m_arguments = ShellCommand::expand(arguments);
}

void Session::setInitialWorkingDirectory(const QString& dir)
{
    m_initialWorkingDir = ShellCommand::expand(dir);
}

void Session::setEnvironment(const QStringList& environment)
{
    m_environment = environment;
}

QString Session::program() const
{
    return m_program;
}

QStringList Session::arguments() const
{
    return m_arguments;
}

QString Session::initialWorkingDirectory() const
{
    return m_initialWorkingDir;
}

QStringList Session::environment() const
{
    return m_environment;
}

void Session::setAddToUtmp(bool enabled)
{
    m_addToUtmp = enabled;
}

bool Session::addToUtmp() const
{
    return m_addToUtmp;
}

void Session::setFlowControlEnabled(bool enabled)
{
    m_flowControl = enabled;
    if (m_shellProcess != nullptr) {
        m_shellProcess->setFlowControlEnabled(enabled);
        emit flowControlStateChanged(m_shellProcess->flowControlEnabled());
    }
}

bool Session::flowControlEnabled() const
{
    return m_shellProcess != nullptr ? m_shellProcess->flowControlEnabled() : m_flowControl;
}

void Session::setMonitorActivity(bool monitor)
{
    m_monitorActivity = monitor;
    if (!monitor) {
        m_notifiedActivity = false;
    }
}

void Session::setMonitorSilence(bool monitor)
{
    m_monitorSilence = monitor;
    if (!monitor) {
        m_monitorTimer->stop();
    } else {
        restartSilenceTimer();
    }
}

void Session::setSilenceSeconds(int seconds)
{
    m_silenceSeconds = seconds;
    if (m_monitorSilence) {
        restartSilenceTimer();
    }
}

void Session::setAutoClose(bool enabled)
{
    m_autoClose = enabled;
}

bool Session::autoClose() const
{
    return m_autoClose;
}

void Session::setSize(const QSize& size)
{
    if (!size.isValid() || size == m_reportedSize) {
        return;
    }

    m_reportedSize = size;
    if (m_shellProcess != nullptr) {
        m_shellProcess->setWindowSize(size.height(), size.width());
    }
}

QSize Session::size() const
{
    return m_reportedSize;
}

bool Session::isRunning() const
{
    return m_shellProcess != nullptr && m_shellProcess->state() == QProcess::Running;
}

void Session::run()
{
    ensureProcess();
    applyProcessEnvironment();

    QString exec = resolveProgram();
    QString argsTmp = m_arguments.join(QLatin1Char(' ')).trimmed();
    QStringList programArguments;
    programArguments << exec;
    if (!argsTmp.isEmpty()) {
        programArguments << m_arguments;
    }

    QString workingDirectory = m_initialWorkingDir;
    if (workingDirectory.isEmpty()) {
        workingDirectory = QDir::currentPath();
    }
    m_shellProcess->setWorkingDirectory(workingDirectory);

    m_shellProcess->setFlowControlEnabled(m_flowControl);

    QStringList env = m_environment;
    if (!env.contains(QLatin1String("COLORFGBG"))) {
        env << QLatin1String("COLORFGBG=0;15");
    }

    const int result = m_shellProcess->start(exec,
                                             programArguments,
                                             env,
                                             0,
                                             m_addToUtmp);

    if (result < 0) {
        qWarning() << "Failed to start program" << exec;
        emit flowControlStateChanged(m_shellProcess->flowControlEnabled());
        return;
    }

    m_shellProcess->setWriteable(false);
    restartSilenceTimer();
    emit flowControlStateChanged(m_shellProcess->flowControlEnabled());
}

void Session::close()
{
    if (m_shellProcess == nullptr) {
        return;
    }

    m_monitorTimer->stop();
    m_shellProcess->closePty();
    m_shellProcess->kill();
}

void Session::sendText(const QString& text)
{
    sendBytes(text.toUtf8());
}

void Session::sendBytes(const QByteArray& bytes)
{
    if (m_shellProcess == nullptr || bytes.isEmpty()) {
        return;
    }

    m_shellProcess->sendData(bytes.constData(), bytes.size());
}

void Session::handlePtyData(const char* data, int length)
{
    if (length <= 0) {
        return;
    }

    QByteArray bytes(data, length);
    emit rawDataReceived(bytes);
    emit receivedData(QString::fromUtf8(bytes));

    if (m_monitorActivity && !m_notifiedActivity) {
        m_notifiedActivity = true;
        emit activityDetected();
    }

    if (m_monitorSilence) {
        restartSilenceTimer();
    }
}

void Session::handleProcessFinished(int exitCode, QProcess::ExitStatus status)
{
    Q_UNUSED(status);
    m_monitorTimer->stop();

    emit finishedWithCode(exitCode);
    emit finished();

    if (m_autoClose) {
        close();
    }
}

void Session::monitorTimerDone()
{
    if (m_monitorSilence) {
        emit silenceDetected();
    }
    m_notifiedActivity = false;
}

void Session::restartSilenceTimer()
{
    if (!m_monitorSilence) {
        return;
    }
    m_monitorTimer->start(m_silenceSeconds * 1000);
}

void Session::ensureProcess()
{
    if (m_shellProcess != nullptr) {
        return;
    }

    m_shellProcess = new Pty(this);
    m_shellProcess->setUtf8Mode(true);
    connect(m_shellProcess, &Pty::receivedData, this, &Session::handlePtyData);
    connect(m_shellProcess, qOverload<int, QProcess::ExitStatus>(&Pty::finished),
            this, &Session::handleProcessFinished);
}

void Session::applyProcessEnvironment()
{
    if (!m_environment.isEmpty()) {
        return;
    }

    m_environment = QProcessEnvironment::systemEnvironment().toStringList();
    if (!m_environment.contains(QLatin1String("TERM="))) {
        m_environment << QLatin1String("TERM=xterm-256color");
    }
}

QString Session::resolveProgram() const
{
    QString exec = QString::fromLocal8Bit(QFile::encodeName(m_program));
    const QString defaultShell = QLatin1String("/bin/sh");

    if (exec.startsWith(QLatin1Char('/')) || exec.isEmpty()) {
        QFile executable(exec);
        if (exec.isEmpty() || !executable.exists()) {
            exec = QString::fromLocal8Bit(qgetenv("SHELL"));
        }
        executable.setFileName(exec);
        if (exec.isEmpty() || !executable.exists()) {
            qWarning() << "Falling back to" << defaultShell;
            exec = defaultShell;
        }
    }

    return exec;
}

} // namespace Konsole
