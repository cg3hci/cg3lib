/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "ply_header.h"
#include "../utilities/tokenizer.h"

namespace cg3 {
namespace internal {

PlyHeader::PlyHeader() :
	_format(UNKNOWN),
	isValid(false)
{
}

PlyHeader::PlyHeader(PlyHeader::Format f, const PlyHeader::Element &vElement, const PlyHeader::Element fElement) :
	_format(f),
	isValid(true)
{
	elements.push_back(vElement);
	elements.push_back(fElement);
}

PlyHeader::PlyHeader(std::ifstream &file) :
	_format(UNKNOWN),
	isValid(false)
{
	if (file.is_open()){
		std::string line;
		std::getline(file,line);
		if (line.compare(0, 3, "ply") == 0){
			bool error, first = true;
			std::string headerLine;
			do {
				Element element;
				error = !(std::getline(file,line));
				if (!error){
					cg3::Tokenizer spaceTokenizer(line, ' ');
					if (spaceTokenizer.begin() == spaceTokenizer.end()) continue;
					cg3::Tokenizer::iterator token = spaceTokenizer.begin();
					headerLine = *token;
					if (headerLine == "element") { //new type of element read
						if (!first){ //last element finished, save it
							elements.push_back(element);
						}
						element = readElement(spaceTokenizer);
						first = false;
					}
					else if (headerLine == "property"){
						Property p = readProperty(spaceTokenizer);
						if (p.name != unknown)
							element.properties.push_back(p);
					}
				}
			} while (!error && headerLine != "end_header");
			isValid = !error && hasVertexAndFaceElements();
		}
	}
}

void PlyHeader::clear()
{
	_format = UNKNOWN;
	elements.clear();
	isValid = false;
}

bool PlyHeader::errorWhileLoading() const
{
	return !isValid;
}

bool PlyHeader::hasVertexAndFaceElements() const
{
	bool vertex = false, face = false;
	for (const Element& e : elements) {
		if (e.type == VERTEX){
			bool xb = false, yb = false, zb = false;
			for (const Property& p : e.properties) {
				if (p.name == x)
					xb = true;
				if (p.name == y)
					yb = true;
				if (p.name == z)
					zb = true;
			}
			if (xb && yb && zb)
				vertex = true;
		}
		if (e.type == FACE){
			for (const Property& p : e.properties) {
				if (p.name == vertex_indices)
					face = true;
			}
		}
	}
	return vertex && face;
}

PlyHeader::Format PlyHeader::format() const
{
	return _format;
}

void PlyHeader::addElement(const PlyHeader::Element &e)
{
	elements.push_back(e);
}

void PlyHeader::setFormat(PlyHeader::Format f)
{
	_format = f;
}

PlyHeader::iterator PlyHeader::begin() const
{
	return elements.begin();
}

PlyHeader::iterator PlyHeader::end() const
{
	return elements.end();
}

PlyHeader::Element PlyHeader::readElement(const Tokenizer &lineTokenizer) const
{
	Element e;
	cg3::Tokenizer::iterator token = lineTokenizer.begin();
	std::string s = *(++token);
	if (s == "vertex"){
		e.type = VERTEX;
		e.numberElements = std::stoi(*(++token));
	}
	else if (s == "face"){
		e.type = FACE;
		e.numberElements = std::stoi(*(++token));
	}
	else
		e.type = OTHER;
	return e;
}

PlyHeader::Property PlyHeader::readProperty(const cg3::Tokenizer& lineTokenizer) const
{
	Property p;
	cg3::Tokenizer::iterator token = lineTokenizer.begin();
	std::string type = *(++token);

	if (type == "list"){
		p.list = true;
		std::string typeSize = *(++token);
		std::string typeData = *(++token);
		std::string name = *(++token);
		p.listSizeType = stringToType(typeSize);
		p.type = stringToType(typeData);
		p.name = stringToListName(name);
	}
	else {
		p.list = false;
		std::string name =*(++token);
		p.type = stringToType(type);
		p.name = stringToName(name);
	}

	return p;
}

PlyHeader::PropertyName PlyHeader::stringToName(const std::string& name) const
{
	PropertyName pn = unknown;
	if (name == "x") pn = x;
	if (name == "y") pn = y;
	if (name == "z") pn = z;
	if (name == "nx") pn = nx;
	if (name == "ny") pn = ny;
	if (name == "nz") pn = nz;
	if (name == "red") pn = red;
	if (name == "green") pn = green;
	if (name == "blue") pn = blue;
	if (name == "alpha") pn = alpha;
	return pn;
}

PlyHeader::PropertyName PlyHeader::stringToListName(const std::string &name) const
{
	PropertyName pn = unknown;
	if (name == "vertex_indices") pn = vertex_indices;
	return pn;
}

PlyHeader::PropertyType PlyHeader::stringToType(const std::string &type) const
{
	PropertyType pt = UCHAR;
	if (type == "char") pt = CHAR;
	if (type == "uchar") pt = UCHAR;
	if (type == "short") pt = SHORT;
	if (type == "ushort") pt = USHORT;
	if (type == "int") pt = INT;
	if (type == "uint") pt = UINT;
	if (type == "float") pt = FLOAT;
	if (type == "double") pt = DOUBLE;
	return pt;
}

} //namespace cg3::internal
} //namespace cg3
