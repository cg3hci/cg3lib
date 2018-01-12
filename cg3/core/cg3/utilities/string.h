/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_STRING_H
#define CG3_STRING_H

#include <string>

namespace cg3 {

template <typename T>
std::string toStringWithPrecision(const T& value, unsigned int precision = 2);

void separateExtensionFromFilename(const std::string& fullname, std::string& rawname, std::string& extension);

void separateFilenameFromPath(const std::string& fullpath, std::string& path, std::string& filename);

}

#include "string.tpp"

#endif // CG3_STRING_H
