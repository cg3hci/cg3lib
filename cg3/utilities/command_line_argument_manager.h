/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_COMMAND_LINE_ARGUMENT_MANAGER_H
#define CG3_COMMAND_LINE_ARGUMENT_MANAGER_H

#include <map>
#include <vector>

namespace cg3 {

/**
 * @brief The CommandLineArgumentManager class manages a simple list of arguments
 * passed to the main.
 *
 * Manages the following cases:
 * ./mybin arg -arg --arg arg=value -arg=value --arg=value
 */
class CommandLineArgumentManager
{
public:
	CommandLineArgumentManager(int argc, char *argv[]);

	typedef std::map<std::string, std::string>::const_iterator iterator;

	bool exists(const std::string& arg) const;
	std::string value(const std::string& arg) const;

	iterator begin() const;
	iterator end() const;

	unsigned long int size() const ;
	const std::string& operator[](std::string& arg) const;
	const std::string& operator[](unsigned int i) const;

private:

	std::map<std::string, std::string> arguments;
	std::vector<std::string> orderedKeys;
};

}

#include "command_line_argument_manager.cpp"

#endif // CG3_COMMAND_LINE_ARGUMENT_MANAGER_H
