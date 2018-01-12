/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CONSOLESTREAM_H
#define CG3_CONSOLESTREAM_H

#include <streambuf>
#include <QTextEdit>

namespace cg3 {

namespace viewer {

/**
 * @brief The ConsoleStream class
 * @link https://stackoverflow.com/questions/9211298/redirect-stdcout-to-qtextedit
 */
class ConsoleStream : public std::basic_streambuf<char> {

public:
    ConsoleStream(std::ostream &stream, std::ostream &stream2, QTextEdit* text_edit);
    virtual ~ConsoleStream();

    static void registerConsoleMessageHandler();


protected:
    virtual int_type overflow(int_type v);
    virtual std::streamsize xsputn(const char *p, std::streamsize n);

private:
    static void consoleMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg);

    std::ostream& stream;
    std::ostream& stream2;
    std::streambuf *oldBuffer;
    std::streambuf *oldBuffer2;
    QTextEdit* textEdit;

};

}

}

#include "consolestream.tpp"

#endif // CG3_CONSOLESTREAM_H
