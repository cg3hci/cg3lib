/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "system.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief fileExists
 * @param filename
 * @link https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
 * @return
 */
inline bool fileExists(const std::string& filename)
{
    std::ifstream infile(filename);
    return infile.good();

}

inline std::string executeCommand(const std::string& cmd)
{
    return executeCommand(cmd.c_str());
}

/**
 * @ingroup cg3core
 * @brief this function executes a command on the shell
 * @param[in] cmd: string containing the command
 * @return the output of the executed command
 * @link https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
 */
inline std::string executeCommand(const char* cmd)
{
    std::string result;
    executeCommand(cmd, result);
    return result;
}

/**
 * @ingroup cg3core
 * @brief this function executes a command on the shell
 * @param[in] cmd: string containing the command
 * @param[out] output: the output of the executed command
 * @return true if the command exited successfully, false otherwise
 * @link https://stackoverflow.com/questions/52164723/how-to-execute-a-command-and-get-return-code-stdout-and-stderr-of-command-in-c
 */
inline bool executeCommand(const std::string& cmd, std::string& output)
{
    return executeCommand(cmd.c_str(), output);
}

/**
 * @ingroup cg3core
 * @brief this function executes a command on the shell
 * @param[in] cmd: string containing the command
 * @param[out] output: the output of the executed command
 * @return true if the command exited successfully, false otherwise
 * @link https://stackoverflow.com/questions/52164723/how-to-execute-a-command-and-get-return-code-stdout-and-stderr-of-command-in-c
 */
inline bool executeCommand(const char* cmd, std::string& output)
{
    auto pipe = popen(cmd, "r");
    if (!pipe) return false;
    char buffer[128];
    output = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr)
            output += buffer;
    }
    auto rc = pclose(pipe);

    return rc == EXIT_SUCCESS;
}

} //namespace cg3
