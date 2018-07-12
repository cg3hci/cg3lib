/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "console_stream.h"

namespace cg3 {
namespace viewer {
namespace internal {

CLogBuf::CLogBuf(QTextEdit* t)  : textEdit(t)
{
}

CLogBuf::~CLogBuf()
{
    pubsync();
}

std::basic_stringbuf<char>::int_type CLogBuf::overflow(
        std::basic_stringbuf<char>::int_type v)
{
    if (v == '\n') {
        textEdit->append(mString.c_str());
        std::cout << mString << "\n";
        mString.erase(mString.begin(), mString.end());
    }
    else
        mString += v;

    return v;
}

std::streamsize CLogBuf::xsputn(const char* p, std::streamsize n)
{
    mString.append(p, p + n);

    std::size_t pos = 0;
    while (pos != std::string::npos) {
        pos = mString.find('\n');
        if (pos != std::string::npos) {
            std::string tmp(mString.begin(), mString.begin() + pos);
            textEdit->append(tmp.c_str());
            std::cout << tmp << "\n";
            mString.erase(mString.begin(), mString.begin() + pos + 1);
        }
    }
    return n;
}

} //namespace cg3::viewer::internal

ConsoleStream::ConsoleStream(QTextEdit* text_edit) :
    std::ostream(new internal::CLogBuf(text_edit))
{
}

ConsoleStream::~ConsoleStream()
{
    delete rdbuf();
}

} //namespace cg3::viewer
} //namespace cg3
