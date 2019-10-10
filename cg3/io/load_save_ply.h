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
//with edges
template <typename T, typename V, typename E, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(
		const std::string& filename,
		std::vector<T>& coords,
		std::vector<V>& faces,
		std::vector<E>& edges,
		io::FileMeshMode& modality = internal::dummyFileMeshMode,
		std::vector<C>& vertexNormals = internal::dummyListDouble,
		std::vector<Color>& vertexColors = internal::dummyVectorColor,
		std::vector<Color>& faceColors = internal::dummyVectorColor2,
		std::vector<Color>& edgeColors = internal::dummyVectorColor2,
		std::vector<W>& faceSizes = internal::dummyVectorUnsignedInt);

//without edges
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(
		const std::string& filename,
		std::vector<T>& coords,
		std::vector<V>& faces,
		io::FileMeshMode& modality = internal::dummyFileMeshMode,
		std::vector<C>& vertexNormals = internal::dummyListDouble,
		std::vector<Color>& vertexColors = internal::dummyVectorColor,
		std::vector<Color>& faceColors = internal::dummyVectorColor2,
		std::vector<W>& faceSizes = internal::dummyVectorUnsignedInt);

template <template <class ... > class Con1, template <class ... > class Con2,
		  template <class ... > class Con3, template <class ... > class Con4,
		  template <class ... > class Con5, template <class ... > class Con6,
		  template <class ... > class Con7, template <class ... > class Con8,
		  class T, class V, class E, class C, class W,
		  class ... ArgsT, class ... ArgsV, class ... ArgsE, class ... ArgsC, class ... ArgsColor, class ... ArgsW>
bool loadMeshFromPly(
		const std::string& filename,
		Con1<T, ArgsT...>& coords,
		Con2<V, ArgsV...>& faces,
		Con3<E, ArgsE...>& edges,
		io::FileMeshMode& modality = internal::dummyFileMeshMode,
		Con4<C, ArgsC...>& vertexNormals = internal::dummyListDouble,
		Con5<Color, ArgsColor...>& vertexColors = internal::dummyVectorColor,
		Con6<Color, ArgsColor...>& faceColors = internal::dummyVectorColor2,
		Con7<Color, ArgsColor...>& edgeColors = internal::dummyVectorColor3,
		Con8<W, ArgsW...>& faceSizes = internal::dummyVectorUnsignedInt);

template <template <class ... > class Con1, template <class ... > class Con2,
          template <class ... > class Con3, template <class ... > class Con4,
          template <class ... > class Con5, template <class ... > class Con6,
          class T, class V, class C, class W,
          class ... ArgsT, class ... ArgsV, class ... ArgsC, class ... ArgsColor, class ... ArgsW>
bool loadMeshFromPly(
		const std::string& filename,
        Con1<T, ArgsT...>& coords,
        Con2<V, ArgsV...>& faces,
		io::FileMeshMode& modality = internal::dummyFileMeshMode,
		Con3<C, ArgsC...>& vertexNormals = internal::dummyListDouble,
		Con4<Color, ArgsColor...>& vertexColors = internal::dummyVectorColor,
		Con5<Color, ArgsColor...>& faceColors = internal::dummyVectorColor2,
        Con6<W, ArgsW...>& faceSizes = internal::dummyVectorUnsignedInt);

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
template <typename A, typename B, typename E, typename C = double, typename D = double, typename T = float, typename V = float, typename X = float, typename W = unsigned int>
bool saveMeshOnPly(
		const std::string &filename,
		size_t nVertices,
		size_t nFaces,
		size_t nEdges,
		const A vertices[],
		const B faces[],
		const E edges[],
		bool binary = true,
		io::FileMeshMode modality = internal::dummyConstFileMeshMode,
		const C verticesNormals[] = internal::dummyVectorDouble.data(),
		const D facesNormals[] = internal::dummyVectorDouble.data(),
		io::FileColorMode colorMod = io::RGB,
		const T verticesColors[] = internal::dummyVectorFloat.data(),
		const V faceColors[] = internal::dummyVectorFloat.data(),
		const X edgeColors[] = internal::dummyVectorFloat.data(),
		const W polygonSizes[] = internal::dummyVectorUnsignedInt.data());

template <typename A, typename B, typename C = double, typename D = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnPly(
		const std::string &filename,
		size_t nVertices,
		size_t nFaces,
		const A vertices[],
		const B faces[],
		bool binary = true,
		io::FileMeshMode modality = internal::dummyConstFileMeshMode,
		const C verticesNormals[] = internal::dummyVectorDouble.data(),
		const D facesNormals[] = internal::dummyVectorDouble.data(),
		io::FileColorMode colorMod = io::RGB,
		const T verticesColors[] = internal::dummyVectorFloat.data(),
		const V faceColors[] = internal::dummyVectorFloat.data(),
		const W polygonSizes[] = internal::dummyVectorUnsignedInt.data());

} //namespace cg3

#include "load_save_ply.cpp"

#endif // CG3_LOAD_SAVE_PLY_H
