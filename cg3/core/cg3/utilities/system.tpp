/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "system.h"

namespace cg3 {

/**
 * @brief fileExists
 * @param filename
 * @link https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
 * @return
 */
inline bool fileExists(const std::string& filename) {
    std::ifstream infile(filename);
    return infile.good();

}

inline std::string executeCommand(const std::string& cmd) {
    return executeCommand(cmd.c_str());
}

/**
 * \~English
 * @brief this function executes a command on the shell
 * @param[in] cmd: string containing the command
 * @return the output of the executed command
 * @link https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
 */
inline std::string executeCommand(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

}
