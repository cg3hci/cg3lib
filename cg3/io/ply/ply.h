/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PLY_H
#define CG3_PLY_H

#include <list>
#include <fstream>
#include <assert.h>
#include <cg3/utilities/tokenizer.h>
#include "../file_commons.h"

namespace cg3 {
namespace ply {

typedef enum {ASCII, BINARY, UNKNOWN} Format;
typedef enum {VERTEX, FACE, EDGE, MATERIAL, OTHER} ElementType;
typedef enum {unknown = -1, x, y, z, nx, ny, nz, red, green, blue, alpha, vertex_indices, vertex1, vertex2} PropertyName;
typedef enum {CHAR, UCHAR, SHORT, USHORT, INT, UINT, FLOAT, DOUBLE} PropertyType;

struct Property {
	PropertyName name;
	PropertyType type;
	bool list;
	PropertyType listSizeType;
	std::string unknownPropwertyName;
};
struct Element {
	ElementType type;
	std::list<Property> properties;
	unsigned int numberElements;
};

namespace internal {

//write/bin

template<typename T>
void writeChar(std::ofstream& file, T p, bool bin = true, bool isColor = false);

template<typename T>
void writeUChar(std::ofstream& file, T p, bool bin = true, bool isColor = false);

template<typename T>
void writeShort(std::ofstream& file, T p, bool bin = true, bool isColor = false);

template<typename T>
void writeUShort(std::ofstream& file, T p, bool bin = true, bool isColor = false);

template<typename T>
void writeInt(std::ofstream& file, T p, bool bin = true, bool isColor = false);

template<typename T>
void writeUInt(std::ofstream& file, T p, bool bin = true, bool isColor = false);

template<typename T>
void writeFloat(std::ofstream& file, const T& p, bool bin = true, bool isColor = false);

template<typename T>
void writeDouble(std::ofstream& file, const T& p, bool bin = true, bool isColor = false);

template <typename T>
void writeProperty(std::ofstream& file, const T& p, PropertyType type, bool bin = true, bool isColor = false);

//read/bin

template<typename T>
T readChar(std::ifstream& file);

template<typename T>
T readUChar(std::ifstream& file);

template<typename T>
T readShort(std::ifstream& file);

template<typename T>
T readUShort(std::ifstream& file);

template<typename T>
T readInt(std::ifstream& file);

template<typename T>
T readUInt(std::ifstream& file);

template<typename T>
T readFloat(std::ifstream& file, bool isColor = false);

template<typename T>
T readDouble(std::ifstream& file, bool isColor = false);

template <typename T>
T readProperty(std::ifstream& file, PropertyType type, bool isColor = false);

//read/txt

template <typename T>
T readProperty(cg3::Tokenizer::iterator& token, PropertyType type, bool isColor = false);

inline bool nextLine(std::ifstream& file, cg3::Tokenizer& tokenizer);

//color management

template <typename T>
T colorValue(int value);

template <typename T>
T colorValue(double value);

template <typename T>
T colorValue(cg3::Tokenizer::iterator& token, PropertyType type);

} //namespace cg3::ply::internal

} //namespace cg3::ply
} //namespace cg3

#include "ply.cpp"

#endif // CG3_PLY_H
