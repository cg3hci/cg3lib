/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PLY_HEADER_H
#define CG3_PLY_HEADER_H

#include <list>
#include <string>
#include <fstream>


namespace cg3 {

class Tokenizer;

namespace internal {

class PlyHeader
{
public:
	typedef enum {ASCII, BINARY, UNKNOWN} Format;
	typedef enum {VERTEX, FACE, EDGE, MATERIAL, OTHER} ElementType;
	typedef enum {unknown = -1, x, y, z, nx, ny, nz, red, green, blue, alpha, vertex_indices} PropertyName;
	typedef enum {CHAR, UCHAR, SHORT, USHORT, INT, UINT, FLOAT, DOUBLE} PropertyType;

	struct Property {
		PropertyName name;
		PropertyType type;
		bool list;
		PropertyType listSizeType;
	};
	struct Element{
		ElementType type;
		std::list<Property> properties;
		unsigned int numberElements;
	};

	PlyHeader();
	PlyHeader(Format f, const Element& vElement, const Element fElement);
	PlyHeader(std::ifstream& file);
	void clear();

	bool errorWhileLoading() const;
	bool hasVertexAndFaceElements() const;
	Format format() const;

	void addElement(const Element& e);
	void setFormat(Format f);

	typedef std::list<Element>::const_iterator iterator;
	iterator begin() const;
	iterator end() const;


private:
	Element readElement(const cg3::Tokenizer& lineTokenizer) const;
	Property readProperty(const cg3::Tokenizer& lineTokenizer) const;
	PropertyName stringToName(const std::string &name) const;
	PropertyName stringToListName(const std::string &name) const;
	PropertyType stringToType(const std::string &type) const;

	Format _format;
	std::list<Element> elements;
	bool isValid;
};

} //namespace cg3::internal
} //namespace cg3

#endif // CG3_PLY_HEADER_H
