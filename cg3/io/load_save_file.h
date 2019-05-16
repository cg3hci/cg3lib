/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LOAD_SAVE_FILE_H
#define CG3_LOAD_SAVE_FILE_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "../utilities/color.h"
#include <clocale>

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

namespace cg3 {

namespace internal {

static int dummyInt;

static std::vector<double> dummyVectorDouble;
static std::vector<float> dummyVectorFloat;
static std::vector<int> dummyVectorInt;
static std::vector<unsigned int> dummyVectorUnsignedInt;
static std::vector<Color> dummyVectorColor;

static std::list<int> dummyListInt;
static std::list<unsigned int> dummyListUnsignedInt;
static std::list<float> dummyListFloat;
static std::list<double> dummyListDouble;
static std::list<Color> dummyListColor;

#ifdef CG3_WITH_EIGEN
static Eigen::MatrixXf dummyEigenFloat;
static Eigen::MatrixXd dummyEigenDouble;
static Eigen::MatrixXi dummyEigenInt;
#endif

} //namespace cg3::internal

namespace io {

typedef enum {
    TRIANGLE_MESH,
    QUAD_MESH,
    POLYGON_MESH
} MeshType;
typedef enum {
    NORMAL_VERTICES =       0b000001,
    COLOR_VERTICES =        0b000010,
    COLOR_FACES =           0b000100
} FileMode;
typedef enum {
    RGB,
    RGBA
} ColorMode;

} //namespace cg3::io


namespace internal {

void manageObjFileColor(
        std::ofstream &fp,
        std::ofstream &fmtu,
        const Color &c,
        io::ColorMode colorMod,
        Color &actualColor,
        std::map<Color,
        std::string> &colors);

void manageObjFileNames(
        const std::string &objfilename,
        std::string& mtufilename,
        std::string& mtufilenopath);

bool loadMtlFile(
        const std::string &mtuFile,
        std::map<std::string, Color> &mapColors);

template <typename T>
Color colorFromArray(
        size_t baseIndex,
        const T arrayColors[],
        io::ColorMode colorMod);

} //namespace cg3::internal

/*
 * Save
 */
template <typename A, typename B, typename C = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnObj(
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

/*
 * Load
 */
///Obj
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromObj(
        const std::string &filename,
        std::list<T>& coords,
        std::list<V>& faces,
        io::MeshType& meshType,
        int& modality = internal::dummyInt,
        std::list<C>& verticesNormals = internal::dummyListDouble,
        std::list<Color>& verticesColors = internal::dummyListColor,
        std::list<Color>& faceColors = internal::dummyListColor,
        std::list<W>& faceSizes = internal::dummyListUnsignedInt);

template <typename T, typename V, typename C = double>
bool loadTriangleMeshFromObj(
        const std::string& filename,
        std::vector<T>& coords,
        std::vector<V>& triangles,
        int& modality = internal::dummyInt,
        std::vector<C>& verticesNormals = internal::dummyVectorDouble,
        std::vector<Color>& verticesColors = internal::dummyVectorColor,
        std::vector<Color>& triangleColors = internal::dummyVectorColor);

#ifdef CG3_WITH_EIGEN
template <typename T, typename V>
bool loadTriangleMeshFromObj(
        const std::string& filename,
        Eigen::PlainObjectBase<T>& coords,
        Eigen::PlainObjectBase<V>& triangles);

template <typename T, typename V, typename C = double, typename W = float, typename X = float>
bool loadTriangleMeshFromObj(
        const std::string& filename,
        Eigen::PlainObjectBase<T>& coords,
        Eigen::PlainObjectBase<V>& triangles,
        int& modality,
        Eigen::PlainObjectBase<C>& verticesNormals,
        Eigen::PlainObjectBase<W>& verticesColors,
        Eigen::PlainObjectBase<X>& triangleColors);
#endif

///Ply
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

} //namespace cg3

#include "load_save_file.tpp"

#endif // CG3_LOAD_SAVE_FILE_H
