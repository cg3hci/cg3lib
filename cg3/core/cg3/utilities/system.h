/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SYSTEM_H
#define CG3_SYSTEM_H

#include <string>

namespace cg3 {

bool fileExists(const std::string& filename);

std::string executeCommand(const std::string& cmd);

std::string executeCommand(const char* cmd);

}

#include "system.tpp"

#endif // CG3_SYSTEM_H
