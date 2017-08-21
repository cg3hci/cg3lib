#ifndef CONSOLESTREAM_H
#define CONSOLESTREAM_H

#include <streambuf>
#include <QTextEdit>

class ConsoleStream : public std::basic_streambuf<char>
{

public:
    ConsoleStream(std::ostream &stream, QTextEdit* text_edit);

    virtual ~ConsoleStream();
    static void registerConsoleMessageHandler();

private:

    static void consoleMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg);

protected:


    // Diese Funktion wird aufgerufen wenn std::endl im Stream erscheint
    virtual int_type overflow(int_type v)
        {
            if (v == '\n')
            {
                log_window->append("");
            }
            return v;
        }

    virtual std::streamsize xsputn(const char *p, std::streamsize n);

private:

    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    QTextEdit* log_window;

};

#endif // CONSOLESTREAM_H
