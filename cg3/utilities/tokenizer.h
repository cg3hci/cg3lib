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

/**
 * @ingroup cg3core
 * @brief The Tokenizer class
 */
class Tokenizer
{
public:
    Tokenizer();
    Tokenizer(const char* string, char separator);
    Tokenizer(const std::string& string, char separator);

	typedef std::vector<std::string>::const_iterator iterator;

	iterator begin() const;
	iterator end() const;

	unsigned long int size() const ;
    const std::string& operator[](unsigned int i) const;

private:
    void split();
    const char* string;
    char separator;
    std::vector<std::string> splitted;
};

}

#include "tokenizer.cpp"

#endif // CG3_TOKENIZER_H
