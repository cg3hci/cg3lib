/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_TOKENIZER_H
#define CG3_TOKENIZER_H

#include <string>
#include <vector>

namespace cg3 {

class Tokenizer {
    public:
        Tokenizer();
        Tokenizer(const char* string, char separator);
        Tokenizer(const std::string& string, char separator);

        typedef std::vector<std::string>::iterator iterator;

        iterator begin();
        iterator end();

        unsigned long int size()const ;

    private:
        void split();
        const char* string;
        char separator;
        std::vector<std::string> splitted;

};

}

#include "tokenizer.tpp"

#endif // CG3_TOKENIZER_H
