/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PLY_EDGE_H
#define CG3_PLY_EDGE_H

#include "ply_header.h"
#include "../file_commons.h"
#include <cg3/utilities/tokenizer.h>
#include <fstream>

namespace cg3 {
namespace ply {

namespace internal {

template <typename A, typename B>
bool loadEdgesTxt(
		std::ifstream& file,
		const PlyHeader& header,
		A edges[], //container with push_back method
		io::FileColorMode colorMod ,
		B edgeColors[]);

template <typename A, typename B>
bool loadEdgesBin(
		std::ifstream& file,
		const PlyHeader& header,
		A edges[], //container with push_back method
		io::FileColorMode colorMod ,
		B edgeColors[]);

}

template <typename A, typename B>
void saveEdges(
		std::ofstream& file,
		const PlyHeader& header,
		const A edges[],
		io::FileColorMode colorMod ,
		const B edgeColors[]);

template <typename A, typename B>
bool loadEdges(
		std::ifstream& file,
		const PlyHeader& header,
		A edges[],
		io::FileColorMode colorMod,
		B edgeColors[]);

} //namespace cg3::ply
} //namespace cg3

#include "ply_edge.cpp"

#endif // CG3_PLY_EDGE_H
