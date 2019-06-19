/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "ply.h"

namespace cg3 {
namespace ply {

namespace internal {

template<typename T>
void writeChar(std::ofstream& file, T p, bool bin, bool isColor)
{
	if (isColor && !std::is_integral<T>::value) p*= 255;
	char tmp = p;
	if (bin) file.write((const char*)&tmp, 1);
	else file << (int)p << " "; //cast necessary to not print the ascii char
}

template<typename T>
void writeUChar(std::ofstream& file, T p, bool bin, bool isColor)
{
	if (isColor && !std::is_integral<T>::value) p*= 255;
	unsigned char tmp = p;
	if (bin) file.write((const char*)&tmp, 1);
	else file << (unsigned int)p << " "; //cast necessary to not print the ascii char
}

template<typename T>
void writeShort(std::ofstream& file, T p, bool bin, bool isColor)
{
	if (isColor && !std::is_integral<T>::value) p*= 255;
	short tmp = p;
	if (bin) file.write((const char*)&tmp, 2);
	else file << tmp << " ";
}

template<typename T>
void writeUShort(std::ofstream& file, T p, bool bin, bool isColor)
{
	if (isColor && !std::is_integral<T>::value) p*= 255;
	unsigned short tmp = p;
	if (bin) file.write((const char*)&tmp, 2);
	else file << tmp << " ";
}

template<typename T>
void writeInt(std::ofstream& file, T p, bool bin, bool isColor)
{
	if (isColor && !std::is_integral<T>::value) p*= 255;
	int tmp = p;
	if (bin) file.write((const char*)&tmp, 4);
	else file << tmp << " ";
}

template<typename T>
void writeUInt(std::ofstream& file, T p, bool bin, bool isColor)
{
	if (isColor && !std::is_integral<T>::value) p*= 255;
	unsigned int tmp = p;
	if (bin) file.write((const char*)&tmp, 4);
	else file << tmp << " ";
}

template<typename T>
void writeFloat(std::ofstream& file, const T& p, bool bin, bool isColor)
{
	float tmp = p;
	if (isColor && std::is_integral<T>::value) tmp/= 255;
	if (bin) file.write((const char*)&tmp, 4);
	else file << tmp << " ";
}

template<typename T>
void writeDouble(std::ofstream& file, const T& p, bool bin, bool isColor)
{
	double tmp = p;
	if (isColor && std::is_integral<T>::value) tmp/= 255;
	if (bin) file.write((const char*)&tmp, 8);
	else file << tmp << " ";
}

template<typename T>
void writeProperty(std::ofstream& file, const T& p, PropertyType type, bool bin, bool isColor)
{
	switch (type) {
		case CHAR:
			writeChar(file, p, bin, isColor); break;
		case UCHAR:
			writeUChar(file, p, bin, isColor); break;
		case SHORT:
			writeShort(file, p, bin, isColor); break;
		case USHORT:
			writeUShort(file, p, bin, isColor); break;
		case INT:
			writeInt(file, p, bin, isColor); break;
		case UINT:
			writeUInt(file, p, bin, isColor); break;
		case FLOAT:
			writeFloat(file, p, bin, isColor); break;
		case DOUBLE:
			writeDouble(file, p, bin, isColor); break;
		default:
			assert(0);
	}
}

template<typename T>
T readChar(std::ifstream& file)
{
	char c;
	file.read(&c, 1);
	return (T)c;
}

template<typename T>
T readUChar(std::ifstream& file)
{
	unsigned char c;
	file.read((char*)&c, 1);
	return (T)c;
}

template<typename T>
T readShort(std::ifstream& file)
{
	short c;
	file.read((char*)&c, 2);
	return (T)c;
}

template<typename T>
T readUShort(std::ifstream& file)
{
	unsigned short c;
	file.read((char*)&c, 2);
	return (T)c;
}

template<typename T>
T readInt(std::ifstream& file)
{
	int c;
	file.read((char*)&c, 4);
	return (T)c;
}

template<typename T>
T readUInt(std::ifstream& file)
{
	unsigned int c;
	file.read((char*)&c, 4);
	return (T)c;
}

template<typename T>
T readFloat(std::ifstream& file, bool isColor)
{
	float c;
	file.read((char*)&c, 4);
	if (isColor)
		return (T)(c *255);
	return (T)c;
}

template<typename T>
T readDouble(std::ifstream& file, bool isColor)
{
	double c;
	file.read((char*)&c, 8);
	if (isColor)
		return (T)(c *255);
	return (T)c;
}

template<typename T>
T readProperty(std::ifstream& file, PropertyType type, bool isColor)
{
	T p;
	switch (type) {
		case CHAR:
			p = readChar<T>(file); break;
		case UCHAR:
			p = readUChar<T>(file); break;
		case SHORT:
			p = readShort<T>(file); break;
		case USHORT:
			p = readUShort<T>(file); break;
		case INT:
			p = readInt<T>(file); break;
		case UINT:
			p = readUInt<T>(file); break;
		case FLOAT:
			p = readFloat<T>(file, isColor); break;
		case DOUBLE:
			p = readDouble<T>(file, isColor); break;
		default:
			assert(0);
			p = 0;
	}
	//if I read a color that must be returned as a float or double
	if (isColor && !std::is_integral<T>::value)
		p = (float) p / 255.0;
	return p;
}

template<typename T>
T readProperty(cg3::Tokenizer::iterator& token, PropertyType type, bool isColor)
{
	T p;
	switch (type) {
		case CHAR:
		case UCHAR:
		case SHORT:
		case USHORT:
		case INT:
		case UINT:
			p = std::stoi(*token++); break;
		case FLOAT:
		case DOUBLE:
			if (isColor){
				p = std::stod(*token++)*255;
			}
			else {
				p = std::stod(*token++);
			}
			break;
		default:
			assert(0);
			p = 0;
	}
	//if I read a color that must be returned as a float or double
	if (isColor && !std::is_integral<T>::value)
		p = (float) p / 255.0;
	return p;
}

inline bool nextLine(std::ifstream& file, cg3::Tokenizer& tokenizer)
{
	std::string line;
	do {
		bool error = ! std::getline(file, line);
		if (error)
			return false;
		tokenizer = cg3::Tokenizer(line, ' ');
	} while(tokenizer.begin() == tokenizer.end());
	return true;
}

template <typename T>
T colorValue(int value){
	if (std::is_integral<T>::value)
		return value;
	else
		return T(value) / 255.0;
}

template <typename T>
T colorValue(double value){
	if (std::is_integral<T>::value)
		return value * 255.0;
	else
		return value;
}

template <typename T>
T colorValue(cg3::Tokenizer::iterator& token, PropertyType type)
{
	if (type < 6) //integer format
		return colorValue<T>(std::stoi(*token++));
	else
		return colorValue<T>(std::stod(*token++));
}

} //namespace cg3::ply::internal
} //namespace cg3::ply
} //namespace cg3
