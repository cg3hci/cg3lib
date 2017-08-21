#ifndef CG3_SYSTEM_H
#define CG3_SYSTEM_H

#include <string>

namespace cg3 {

bool fileExists(const std::string& filename);

std::string executeCommand(const std::string& cmd);

std::string executeCommand(const char* cmd);

}

#include "system.cpp"

#endif // CG3_SYSTEM_H
