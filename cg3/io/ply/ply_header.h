/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PLY_HEADER_H
#define CG3_PLY_HEADER_H

#include <vector>
#include <string>
#include <fstream>
#include "ply.h"

namespace cg3 {

class Tokenizer;

namespace ply {

/**
  @ingroup cg3core
 * @brief The PlyHeader class allows to manage the header of a ply file.
 *
 * Following the content of an header, a ply file can be loaded or
 * saved.
 */
class PlyHeader
{
public:
	PlyHeader();
	PlyHeader(ply::Format f, const ply::Element& vElement, const ply::Element fElement);
	PlyHeader(std::ifstream& file);
	void clear();

	bool errorWhileLoading() const;
	bool hasVertexAndFaceElements() const;
	ply::Format format() const;
	const std::list<ply::Property>& vertexProperties() const;
	const std::list<ply::Property>& faceProperties() const;
	uint numberVertices() const;
	uint numberFaces() const;
	void setNumberVertices(uint nV);
	void setNumberFaces(uint nF);
	io::FileMeshMode modality() const;
	void setModality(const io::FileMeshMode& mode, bool binary = true);
	std::string toString() const;

	void addElement(const ply::Element& e);
	void setFormat(ply::Format f);

	typedef std::vector<ply::Element>::const_iterator iterator;
	iterator begin() const;
	iterator end() const;


private:
	ply::Element readElement(const cg3::Tokenizer& lineTokenizer) const;
	ply::Property readProperty(const cg3::Tokenizer& lineTokenizer) const;
	ply::PropertyName stringToName(const std::string &name) const;
	ply::PropertyName stringToListName(const std::string &name) const;
	ply::PropertyType stringToType(const std::string &type) const;
	std::string nameToString(ply::PropertyName n) const;
	std::string typeToString(ply::PropertyType t) const;

	ply::Format _format;
	std::vector<ply::Element> elements;
	bool isValid;
	int v, f;
};

} //namespace cg3::ply
} //namespace cg3

#endif // CG3_PLY_HEADER_H
