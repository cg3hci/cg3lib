/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SERIALIZE_H
#define CG3_SERIALIZE_H

#include "serializable_object.h"

namespace cg3 {

//utilities functions for the serialization of an entire object by its attributes
template <typename... Args>
void serializeObjectAttributes(
        const std::string& s,
        std::ofstream& binaryFile,
        const Args&... args);

template <typename... Args>
void deserializeObjectAttributes(
        const std::string& s,
        std::ifstream& binaryFile,
        Args&... args);

template <typename... Args>
void serializeObjectAttributes(
        const std::string& s,
        const std::string& fileName,
        const Args&... args);

template <typename... Args>
void deserializeObjectAttributes(
        const std::string& s,
        const std::string& fileName,
        Args&... args);

// Manage File functions
std::streampos getFilePosition(std::ifstream& binaryFile);

void restoreFilePosition(std::ifstream& binaryFile, const std::streampos& position);

// serialize/deserialize functions
template <typename T>
void serialize(const T& obj,
               std::ofstream& binaryFile,
               typename std::enable_if<std::is_pointer<T>::value >::type* = 0);

template <typename T>
void serialize(const T& obj,
               std::ofstream& binaryFile,
               typename std::enable_if<!std::is_pointer<T>::value >::type* = 0);

template <typename T>
void deserialize(T& obj,
                 std::ifstream& binaryFile,
                 typename std::enable_if<std::is_pointer<T>::value >::type* = 0);

template <typename T>
void deserialize(T& obj,
                 std::ifstream& binaryFile,
                 typename std::enable_if<!std::is_pointer<T>::value >::type* = 0);

void serialize(const char * str, std::ofstream& binaryFile);

void serialize(const std::string& str, std::ofstream& binaryFile);

void deserialize(std::string& str, std::ifstream& binaryFile);

namespace internal {

template <typename T>
std::string typeName(bool specifyIfConst = true, bool specifyIfVolatile = true, bool specifyIfReference = true);

void serializeAttribute(std::ofstream& binaryFile);

template<typename T, typename... Args>
void serializeAttribute(std::ofstream& binaryFile, const T& t, const Args&... args);

void deserializeAttribute(std::ifstream& binaryFile);

template<typename T, typename... Args>
void deserializeAttribute(std::ifstream& binaryFile, T& t, Args&... args);

} //namespace cg3::internal
} //namespace cg3

#include "serialize_std.h"
#include "serialize_eigen.h"
#include "serialize_qt.h"

#include "serialize.cpp"

#include "serialize_std.cpp"
#include "serialize_eigen.cpp"
#include "serialize_qt.cpp"

#endif // CG3_SERIALIZE_H
