/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "command_line_argument_manager.h"

namespace cg3{

inline CommandLineArgumentManager::CommandLineArgumentManager(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i){
		std::string arg = argv[i];
		std::string key;
		std::string value;

		std::size_t posEqual = arg.find('=');
		uint endValue = arg.size();
		if (posEqual != std::string::npos){ //no = in the argument makes value empty
			value = arg.substr(posEqual+1); //from pos+1 until the end
			endValue = posEqual;
		}
		uint j = 0;
		while (arg[j] == '-' && j<endValue)
			j++;
		if (j < endValue){
			key = arg.substr(j, endValue-j);
			if (!exists(key)){
				arguments[key] = value;
				orderedKeys.push_back(key);
			}
		}
	}
}

/**
 * @brief
 * @param arg: key argument
 * @return true if the given argument exists
 */
inline bool CommandLineArgumentManager::exists(const std::string& arg) const
{
	return arguments.find(arg) != arguments.end();
}

/**
 * @brief Returns the value associated to the given argument.
 *
 * If the argument has no value, it returns an empty string.
 * If the argument does not exists, it returns an empty string.
 * Please discriminate these two cases using the member function
 * CommandLineArgumentManager::exists.
 *
 * @param arg: key argument
 * @return the value associated to the given argument.
 */
inline std::string CommandLineArgumentManager::value(const std::string& arg) const
{
	if (!exists(arg)) return "";
	return arguments.at(arg);
}

inline CommandLineArgumentManager::iterator CommandLineArgumentManager::begin() const
{
	return arguments.begin();
}

inline CommandLineArgumentManager::iterator CommandLineArgumentManager::end() const
{
	return arguments.end();
}

inline unsigned long CommandLineArgumentManager::size() const
{
	return arguments.size();
}

inline const std::string& CommandLineArgumentManager::operator[](std::string& arg) const
{
	return arguments.at(arg);
}

inline const std::string& CommandLineArgumentManager::operator[](unsigned int i) const
{
	return orderedKeys[i];
}

} //namespace cg3
