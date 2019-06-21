/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LOAD_SAVE_PLY_H
#define CG3_LOAD_SAVE_PLY_H

#include "file_commons.h"

namespace cg3 {
/*
 * Load
 */
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(
		const std::string& filename,
		std::vector<T>& coords,
		std::vector<V>& faces,
		io::FileMeshMode& modality = internal::dummyFileMeshMode,
		std::vector<C>& verticesNormals = internal::dummyListDouble,
		std::vector<Color>& verticesColors = internal::dummyVectorColor,
		std::vector<Color>& facesColors = internal::dummyVectorColor,
		std::vector<W>& faceSizes = internal::dummyVectorUnsignedInt);

template <template <typename... Args> class Con1, template <typename... Args> class Con2,
		  template <typename... Args> class Con3, template <typename... Args> class Con4,
		  template <typename... Args> class Con5, template <typename... Args> class Con6,
		  typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(
		const std::string& filename,
		std::vector<T>& coords,
		std::vector<V>& faces,
		io::FileMeshMode& modality = internal::dummyFileMeshMode,
		std::vector<C>& verticesNormals = internal::dummyListDouble,
		std::vector<Color>& verticesColors = internal::dummyVectorColor,
		std::vector<Color>& facesColors = internal::dummyVectorColor,
		std::vector<W>& faceSizes = internal::dummyVectorUnsignedInt);

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
		io::FileMeshMode &modality,
		Eigen::PlainObjectBase<C>& verticesNormals,
		Eigen::PlainObjectBase<W>& verticesColors,
		Eigen::PlainObjectBase<X>& triangleColors);
#endif

/*
 * Save
 */
template <typename A, typename B, typename C = double, typename D = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnPly(
		const std::string &filename,
		size_t nVertices,
		size_t nFaces,
		const A vertices[],
		const B faces[],
		bool binary = true,
		io::FileMeshMode meshType = internal::dummyConstFileMeshMode,
		const C verticesNormals[] = internal::dummyVectorDouble.data(),
		const D facesNormals[] = internal::dummyVectorDouble.data(),
		io::FileColorMode colorMod = io::RGB,
		const T verticesColors[] = internal::dummyVectorFloat.data(),
		const V faceColors[] = internal::dummyVectorFloat.data(),
		const W polygonSizes[] = internal::dummyVectorUnsignedInt.data());

} //namespace cg3

#include "load_save_ply.cpp"

#endif // CG3_LOAD_SAVE_PLY_H
