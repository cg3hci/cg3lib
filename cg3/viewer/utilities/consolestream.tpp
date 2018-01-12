/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "consolestream.h"
#include <iostream>

#include <cg3/utilities/const.h>

namespace cg3 {

namespace viewer {

inline ConsoleStream::ConsoleStream(std::ostream &stream, std::ostream &stream2, QTextEdit* text_edit) : std::basic_streambuf<char>(), stream(stream), stream2(stream2) {
    textEdit = text_edit;
    oldBuffer = stream.rdbuf();
    oldBuffer2 = stream2.rdbuf();

    stream.rdbuf(this);
    stream2.rdbuf(this);

}

inline ConsoleStream::~ConsoleStream() {
    stream.rdbuf(this->oldBuffer);
    stream2.rdbuf(this->oldBuffer2);
}

inline void ConsoleStream::registerConsoleMessageHandler() {
    qInstallMessageHandler(consoleMessageHandler);
}

inline std::basic_streambuf<char>::int_type ConsoleStream::overflow(std::basic_streambuf<char>::int_type v) {
    if (v == '\n') {
        textEdit->append("");
    }
    return v;
}


inline void ConsoleStream::consoleMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {
    CG3_SUPPRESS_WARNING(type);
    std::cout << msg.toStdString().c_str();
}

inline std::streamsize ConsoleStream::xsputn(const char *p, std::streamsize n) {
    CG3_SUPPRESS_WARNING(n);
    textEdit->append(p);
    textEdit->update();
    return textEdit->toPlainText().size();
}

}

}
