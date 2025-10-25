#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QSocketNotifier>
#include <QTextStream>
#include <QMetaObject>
#include <QByteArray>
#include <QStringList>
#include <QSize>

#include "Session.h"

#include <csignal>
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>

using Konsole::Session;

namespace {
Session* g_session = nullptr;

void applyTerminalSize(Session* session)
{
    if (session == nullptr) {
        return;
    }

    struct winsize windowSize;
    if (::ioctl(STDIN_FILENO, TIOCGWINSZ, &windowSize) == 0 && windowSize.ws_col > 0 && windowSize.ws_row > 0) {
        session->setSize(QSize(windowSize.ws_col, windowSize.ws_row));
    } else {
        session->setSize(QSize(80, 24));
    }
}

void handleWindowResize(int)
{
    if (g_session == nullptr) {
        return;
    }

    Session* session = g_session;
    QMetaObject::invokeMethod(session, [session]() {
        applyTerminalSize(session);
    }, Qt::QueuedConnection);
}

class StdinForwarder : public QObject
{
public:
    explicit StdinForwarder(Session* session, QObject* parent = nullptr)
        : QObject(parent)
        , m_session(session)
    {
        m_notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
        QObject::connect(m_notifier, &QSocketNotifier::activated, this, [this](int) {
            forwardInput();
        });
    }

private:
    void forwardInput()
    {
        char buffer[4096];
        const ssize_t bytesRead = ::read(STDIN_FILENO, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            const QString text = QString::fromLocal8Bit(buffer, static_cast<int>(bytesRead));
            m_session->sendText(text);
        } else if (bytesRead == 0) {
            m_notifier->setEnabled(false);
        }
    }

    Session* m_session;
    QSocketNotifier* m_notifier = nullptr;
};
} // namespace

int main(int argc, char** argv)
{
    QCoreApplication application(argc, argv);

    const QStringList arguments = application.arguments();
    if (arguments.size() < 2) {
        QTextStream(stderr) << "Usage: " << arguments.first() << " <program> [args...]\n";
        return EXIT_FAILURE;
    }

    Session session;
    session.setProgram(arguments.at(1));
    if (arguments.size() > 2) {
        session.setArguments(arguments.mid(2));
    }
    session.setEnvironment(QProcessEnvironment::systemEnvironment().toStringList());

    g_session = &session;
    ::signal(SIGWINCH, handleWindowResize);
    applyTerminalSize(&session);

    QObject::connect(&session, &Session::receivedData, [](const QString& text) {
        const QByteArray data = text.toLocal8Bit();
        ::write(STDOUT_FILENO, data.constData(), static_cast<size_t>(data.size()));
    });
    QObject::connect(&session, &Session::finished, &application, &QCoreApplication::quit);

    StdinForwarder forwarder(&session);

    session.run();
    if (!session.isRunning()) {
        QTextStream(stderr) << "Failed to start program: " << arguments.at(1) << "\n";
        return EXIT_FAILURE;
    }

    return application.exec();
}
