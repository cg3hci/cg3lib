/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "consolestream.h"
#include <iostream>

#include <cg3/utilities/const.h>

ConsoleStream::ConsoleStream(std::ostream &stream, QTextEdit* text_edit)
    :std::basic_streambuf<char>()
    ,m_stream(stream)


{
    this->log_window = text_edit;
    this->m_old_buf = stream.rdbuf();

    stream.rdbuf(this);

}

ConsoleStream::~ConsoleStream()
{
    this->m_stream.rdbuf(this->m_old_buf);
}

void ConsoleStream::registerConsoleMessageHandler()
{
    qInstallMessageHandler(consoleMessageHandler);
}


void ConsoleStream::consoleMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {
    /**
      * @todo
      */
    CG3_SUPPRESS_WARNING(type);
    std::cerr << msg.toStdString().c_str();
}

std::streamsize ConsoleStream::xsputn(const char *p, std::streamsize n) {
    /**
      * @todo
      */
    CG3_SUPPRESS_WARNING(n);
    log_window->append(p);
    log_window->update();
    return log_window->toPlainText().size();
}
