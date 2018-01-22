/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "tokenizer.h"

namespace cg3 {

inline Tokenizer::Tokenizer() : string(""), separator('\0'){
}

inline Tokenizer::Tokenizer(const char* string, char separator) : string(string), separator(separator) {
    split();
}

inline Tokenizer::Tokenizer(const std::string& string, char separator) : string(string.c_str()), separator(separator) {
    split();
}

inline Tokenizer::iterator Tokenizer::begin() {
    return splitted.begin();
}

inline Tokenizer::iterator Tokenizer::end() {
    return splitted.end();
}

inline unsigned long Tokenizer::size() const {
    return (unsigned long) splitted.size();
}

/**
 * @brief Tokenizer::split
 * @link https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
 */
inline void Tokenizer::split() {
    const char* str = string;
    splitted.clear();
    if (*str != '\0'){
        do {
            const char *begin = str;
            while(*str != separator && *str)
                str++;
            if (begin != str)
                splitted.push_back(std::string(begin, str));
        } while ('\0' != *str++);
    }
}

}
