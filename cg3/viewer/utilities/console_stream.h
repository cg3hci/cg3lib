/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CONSOLE_STREAM_H
#define CG3_CONSOLE_STREAM_H

#include <iostream>
#include <streambuf>
#include <sstream>
#include <string>
#include <QPlainTextEdit>

namespace cg3 {
namespace viewer {
namespace internal {
class CLogBuf : public std::stringbuf
{
private:
    // or whatever you need for your application
    QTextEdit* textEdit;
    std::string mString;
public:
    CLogBuf(QTextEdit* t);
    ~CLogBuf();

    virtual int_type overflow(int_type v);
    virtual std::streamsize xsputn(const char *p, std::streamsize n);
};

} //namespace cg3::viewer::internal

/**
 * @brief The ConsoleStream class
 * @link https://stackoverflow.com/questions/4366904/custom-stream-to-method-in-c
 * @link https://stackoverflow.com/questions/12978973/unknown-ouput-with-qdebugstream-and-qtextedit
 */
class ConsoleStream : public std::ostream
{
public:
    ConsoleStream(QTextEdit* text_edit);
    ~ConsoleStream();
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_CONSOLE_STREAM_H
