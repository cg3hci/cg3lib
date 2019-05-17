/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LOAD_SAVE_PLY_H
#define CG3_LOAD_SAVE_PLY_H

#include "load_save.h"

namespace cg3 {
/*
 * Load
 */
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(
		const std::string& filename,
		std::list<T>& coords,
		std::list<V>& faces,
		io::MeshType& meshType,
		int& modality = internal::dummyInt,
		std::list<C>& verticesNormals = internal::dummyListDouble,
		std::list<Color>& verticesColors = internal::dummyListColor,
		std::list<Color>& faceColors = internal::dummyListColor,
		std::list<W>& faceSizes = internal::dummyListUnsignedInt);

#ifdef CG3_WITH_EIGEN
template <typename T, typename V>
bool loadTriangleMeshFromPly(
		const std::string& filename,
		Eigen::PlainObjectBase<T>& coords,
		Eigen::PlainObjectBase<V>& triangles);

template <typename T, typename V, typename C = double, typename W = float, typename X = float>
bool loadTriangleMeshFromPly(
		const std::string& filename,
		Eigen::PlainObjectBase<T>& coords,
		Eigen::PlainObjectBase<V>& triangles,
		int& modality,
		Eigen::PlainObjectBase<C>& verticesNormals,
		Eigen::PlainObjectBase<W>& verticesColors,
		Eigen::PlainObjectBase<X>& triangleColors);
#endif

/*
 * Save
 */
template <typename A, typename B, typename C = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnPly(
		const std::string &filename,
		size_t nVertices,
		size_t nTriangles,
		const A vertices[],
		const B faces[],
		io::MeshType meshType = io::TRIANGLE_MESH,
		int modality = 0,
		const C verticesNormals[] = internal::dummyVectorDouble.data(),
		io::ColorMode colorMod = io::RGB,
		const T verticesColors[] = internal::dummyVectorFloat.data(),
		const V triangleColors[] = internal::dummyVectorFloat.data(),
		const W polygonSizes[] = internal::dummyVectorUnsignedInt.data());

} //namespace cg3

#include "load_save_ply.tpp"

#endif // CG3_LOAD_SAVE_PLY_H
