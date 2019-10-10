/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PLY_FACE_H
#define CG3_PLY_FACE_H

#include "ply_header.h"
#include "../file_commons.h"
#include <cg3/utilities/tokenizer.h>
#include <fstream>

namespace cg3 {
namespace ply {

namespace internal {

template <typename A, typename D>
void saveFaceIndices(
		std::ofstream& file,
		Property p,
		uint f,
		uint& startingIndex,
		const A faces[],
		const io::FileMeshMode& meshType,
		const D polygonSizes[],
		bool bin);


template <template <typename... Args> class Container, typename A, typename D>
bool loadFaceIndicesTxt(
		const cg3::Tokenizer& spaceTokenizer,
		cg3::Tokenizer::iterator& token,
		Property p,
		uint f,
		Container<A>& faces,
		D polygonSizes[]);

template <typename A, typename B, typename C, typename D>
bool loadFacesTxt(
		std::ifstream& file,
		const PlyHeader& header,
		A& faces, //container with push_back method
		io::FileMeshType& meshType,
		B faceNormals[],
		io::FileColorMode colorMod ,
		C faceColors[],
		D polygonSizes[]);

template <template <typename... Args> class Container, typename A, typename D>
bool loadFaceIndicesBin(
		std::ifstream& file,
		Property p,
		uint f,
		Container<A>& faces,
		D polygonSizes[]);

template <typename A, typename B, typename C, typename D>
bool loadFacesBin(
		std::ifstream& file,
		const PlyHeader& header,
		A& faces, //container with push_back method
		io::FileMeshType& meshType,
		B faceNormals[],
		io::FileColorMode colorMod ,
		C faceColors[],
		D polygonSizes[]);

} //namespace cg3::ply::internal

template <typename A, typename B, typename C, typename D>
void saveFaces(
		std::ofstream& file,
		const PlyHeader& header,
		const A faces[],
		io::FileMeshMode meshMode,
		const B faceNormals[],
		io::FileColorMode colorMod ,
		const C faceColors[],
		const D polygonSizes[]);

template <typename A, typename B, typename C, typename D>
bool loadFaces(
		std::ifstream& file,
		const PlyHeader& header,
		A& faces,
		io::FileMeshType& meshType,
		B faceNormals[],
		io::FileColorMode colorMod ,
		C faceColors[],
		D polygonSizes[]);

} //namespace cg3::ply
} //namespace cg3

#include "ply_face.cpp"

#endif // CG3_PLY_FACE_H
