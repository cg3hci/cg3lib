/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "console_stream.h"
#include <cg3/cg3lib.h>

namespace cg3 {
namespace viewer {
namespace internal {

CG3_INLINE CLogBuf::CLogBuf(QTextEdit* t)  : textEdit(t), coutOutPut(true)
{
}

CG3_INLINE CLogBuf::~CLogBuf()
{
    pubsync();
}

CG3_INLINE std::basic_stringbuf<char>::int_type CLogBuf::overflow(
        std::basic_stringbuf<char>::int_type v)
{
    if (v == '\n') {
        textEdit->append(mString.c_str());
        if (coutOutPut)
            std::cout << mString << "\n";
        mString.erase(mString.begin(), mString.end());
    }
    else
        mString += v;

    return v;
}

CG3_INLINE std::streamsize CLogBuf::xsputn(const char* p, std::streamsize n)
{
    mString.append(p, p + n);

    std::size_t pos = 0;
    while (pos != std::string::npos) {
        pos = mString.find('\n');
        if (pos != std::string::npos) {
            std::string tmp(mString.begin(), mString.begin() + pos);
            textEdit->append(tmp.c_str());
            if (coutOutPut)
                std::cout << tmp << "\n";
            mString.erase(mString.begin(), mString.begin() + pos + 1);
        }
    }
    return n;
}

CG3_INLINE void CLogBuf::setCoutOutput(bool b)
{
    coutOutPut = b;
}

} //namespace cg3::viewer::internal

CG3_INLINE ConsoleStream::ConsoleStream(QTextEdit* text_edit) :
    std::ostream(new internal::CLogBuf(text_edit))
{
    buf = (internal::CLogBuf*) rdbuf();
}

CG3_INLINE ConsoleStream::~ConsoleStream()
{
    delete rdbuf();
}

CG3_INLINE void ConsoleStream::setCoutOutput(bool b)
{
    buf->setCoutOutput(b);
}

} //namespace cg3::viewer
} //namespace cg3
