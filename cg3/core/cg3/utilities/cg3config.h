/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CG3CONFIG_H
#define CG3_CG3CONFIG_H

#ifndef __APPLE__
#include <experimental/filesystem>
#endif

namespace cg3 {
namespace internal {

//Config
//
#ifdef WIN32
const std::string configFolderDirectory = std::string(std::getenv("USERPROFILE")) + "\\AppData\\Roaming\\cg3lib\\";
#elif __APPLE__
const std::string configFolderDirectory = std::string("/Users/") + std::getenv("USER") + "/Library/Preferences/cg3lib/";
#elif __linux__
const std::string configFolderDirectory = std::string(std::getenv("HOME")) + "/.config/cg3lib/";
#endif

inline void initConfigFolder()
{
    #ifndef __APPLE__
    if (! std::experimental::filesystem::exists(configFolderDirectory.c_str()))
        std::experimental::filesystem::create_directory(configFolderDirectory.c_str());
    #else
    system((std::string("mkdir ") + configFolderDirectory).c_str());
    #endif
}


} //namespace cg3::internal
} //namespace cg3

#endif // CG3_CG3CONFIG_H
