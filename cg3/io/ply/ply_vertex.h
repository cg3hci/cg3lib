/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PLY_VERTEX_H
#define CG3_PLY_VERTEX_H

#include "ply_header.h"
#include "../file_commons.h"
#include <fstream>

namespace cg3 {
namespace ply {

namespace internal {

template <typename A, typename B, typename C>
bool loadVerticesTxt(
		std::ifstream& file,
		const PlyHeader& header,
		A vertices[],
		B vertexNormals[],
		io::FileColorMode colorMod ,
		C vertexColors[]);

template <typename A, typename B, typename C>
bool loadVerticesBin(
		std::ifstream& file,
		const PlyHeader& header,
		A vertices[],
		B vertexNormals[],
		io::FileColorMode colorMod ,
		C vertexColors[]);

} //namespace cg3::ply::internal

template <typename A, typename B, typename C>
void saveVertices(
		std::ofstream& file,
		const PlyHeader& header,
		const A vertices[],
		const B vertexNormals[],
		io::FileColorMode colorMod ,
		const C vertexColors[]);

template <typename A, typename B, typename C>
bool loadVertices(
		std::ifstream& file,
		const PlyHeader& header,
		A vertices[],
		B vertexNormals[],
		io::FileColorMode colorMod ,
		C vertexColors[]);

} //namespace cg3::ply
} //namespace cg3

#include "ply_vertex.cpp"

#endif // CG3_PLY_VERTEX_H
