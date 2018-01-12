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

namespace loadSave {
namespace dummies {
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
}


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



namespace ObjManager {
void manageColor(std::ofstream &fp, std::ofstream &fmtu, const Color &c, ColorMode colorMod, Color &actualColor, std::map<Color, std::string> &colors);
void manageFileNames(const std::string &objfilename, std::string& mtufilename, std::string& mtufilenopath);
bool loadMtlFile(const std::string &mtuFile, std::map<std::string, Color> &mapColors);
}

template <typename T>
Color getColor(size_t baseIndex, const T arrayColors[], ColorMode colorMod);

/**
     * Save
     */

template <typename A, typename B, typename C = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnObj(const std::string &filename, size_t nVertices, size_t nTriangles, const A vertices[], const B faces[], MeshType meshType = TRIANGLE_MESH, int modality= 0, const C verticesNormals[] = dummies::dummyVectorDouble.data(), ColorMode colorMod = RGB, const T verticesColors[] = dummies::dummyVectorFloat.data(), const V triangleColors[] = dummies::dummyVectorFloat.data(), const W polygonSizes[] = dummies::dummyVectorUnsignedInt.data());

template <typename A, typename B, typename C = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnPly(const std::string &filename, size_t nVertices, size_t nTriangles, const A vertices[], const B faces[], MeshType meshType = TRIANGLE_MESH, int modality= 0, const C verticesNormals[] = dummies::dummyVectorDouble.data(), ColorMode colorMod = RGB, const T verticesColors[] = dummies::dummyVectorFloat.data(), const V triangleColors[] = dummies::dummyVectorFloat.data(), const W polygonSizes[] = dummies::dummyVectorUnsignedInt.data());

/**
     * Load
     */
///Obj
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromObj(const std::string &filename, std::list<T>& coords, std::list<V>& faces, MeshType &meshType, int &modality = dummies::dummyInt, std::list<C> &verticesNormals = dummies::dummyListDouble, std::list<Color> &verticesColors = dummies::dummyListColor, std::list<Color> &faceColors = dummies::dummyListColor, std::list<W> &faceSizes = dummies::dummyListUnsignedInt);

template <typename T, typename V, typename C = double>
bool loadTriangleMeshFromObj(const std::string &filename, std::vector<T>& coords, std::vector<V>&triangles, int &modality = dummies::dummyInt, std::vector<C> &verticesNormals = dummies::dummyVectorDouble, std::vector<Color> &verticesColors = dummies::dummyVectorColor, std::vector<Color> &triangleColors = dummies::dummyVectorColor);

#ifdef CG3_WITH_EIGEN
template <typename T, typename V>
bool loadTriangleMeshFromObj(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles);
template <typename T, typename V, typename C = double, typename W = float, typename X = float>
bool loadTriangleMeshFromObj(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles, int &modality, Eigen::PlainObjectBase<C> &verticesNormals, Eigen::PlainObjectBase<W> &verticesColors, Eigen::PlainObjectBase<X> &triangleColors);
#endif

///Ply
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(const std::string &filename, std::list<T>& coords, std::list<V>& faces, MeshType &meshType, int &modality = dummies::dummyInt, std::list<C> &verticesNormals = dummies::dummyListDouble, std::list<Color> &verticesColors = dummies::dummyListColor, std::list<Color> &faceColors = dummies::dummyListColor, std::list<W> &faceSizes = dummies::dummyListUnsignedInt);

#ifdef CG3_WITH_EIGEN
template <typename T, typename V>
bool loadTriangleMeshFromPly(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles);
template <typename T, typename V, typename C = double, typename W = float, typename X = float>
bool loadTriangleMeshFromPly(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles, int &modality, Eigen::PlainObjectBase<C> &verticesNormals, Eigen::PlainObjectBase<W> &verticesColors, Eigen::PlainObjectBase<X> &triangleColors);
#endif

}

}

#include "load_save_file.tpp"

#endif // CG3_LOAD_SAVE_FILE_H
