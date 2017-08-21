#ifndef CG3_LOAD_SAVE_FILE_H
#define CG3_LOAD_SAVE_FILE_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <boost/tokenizer.hpp>
#include "../data_structures/color.h"
#include <clocale>

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

namespace cg3 {

namespace Common {
namespace Dummies {
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
bool saveMeshOnObj(const std::string &filename, size_t nVertices, size_t nTriangles, const A vertices[], const B faces[], MeshType meshType = TRIANGLE_MESH, int modality= 0, const C verticesNormals[] = Dummies::dummyVectorDouble.data(), ColorMode colorMod = RGB, const T verticesColors[] = Dummies::dummyVectorFloat.data(), const V triangleColors[] = Dummies::dummyVectorFloat.data(), const W polygonSizes[] = Dummies::dummyVectorUnsignedInt.data());

template <typename A, typename B, typename C = double, typename T = float, typename V = float, typename W = unsigned int>
bool saveMeshOnPly(const std::string &filename, size_t nVertices, size_t nTriangles, const A vertices[], const B faces[], MeshType meshType = TRIANGLE_MESH, int modality= 0, const C verticesNormals[] = Dummies::dummyVectorDouble.data(), ColorMode colorMod = RGB, const T verticesColors[] = Dummies::dummyVectorFloat.data(), const V triangleColors[] = Dummies::dummyVectorFloat.data(), const W polygonSizes[] = Dummies::dummyVectorUnsignedInt.data());

/**
     * Load
     */
///Obj
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromObj(const std::string &filename, std::list<T>& coords, std::list<V>& faces, MeshType &meshType, int &modality = Dummies::dummyInt, std::list<C> &verticesNormals = Dummies::dummyListDouble, std::list<Color> &verticesColors = Dummies::dummyListColor, std::list<Color> &faceColors = Dummies::dummyListColor, std::list<W> &faceSizes = Dummies::dummyListUnsignedInt);

template <typename T, typename V, typename C = double>
bool loadTriangleMeshFromObj(const std::string &filename, std::vector<T>& coords, std::vector<V>&triangles, int &modality = Dummies::dummyInt, std::vector<C> &verticesNormals = Dummies::dummyVectorDouble, std::vector<Color> &verticesColors = Dummies::dummyVectorColor, std::vector<Color> &triangleColors = Dummies::dummyVectorColor);

#ifdef CG3_WITH_EIGEN
template <typename T, typename V, int ...A>
bool loadTriangleMeshFromObj(const std::string &filename, Eigen::Matrix<T, A...>& coords, Eigen::Matrix<V, A...>&triangles);
template <typename T, typename V, typename C = double, typename W = float, typename X = float, int ...A>
bool loadTriangleMeshFromObj(const std::string &filename, Eigen::Matrix<T, A...>& coords, Eigen::Matrix<V, A...>&triangles, int &modality, Eigen::Matrix<C, A...> &verticesNormals, Eigen::Matrix<W, A...> &verticesColors, Eigen::Matrix<X, A...> &triangleColors);
#endif

///Ply
template <typename T, typename V, typename C = double, typename W = unsigned int>
bool loadMeshFromPly(const std::string &filename, std::list<T>& coords, std::list<V>& faces, MeshType &meshType, int &modality = Dummies::dummyInt, std::list<C> &verticesNormals = Dummies::dummyListDouble, std::list<Color> &verticesColors = Dummies::dummyListColor, std::list<Color> &faceColors = Dummies::dummyListColor, std::list<W> &faceSizes = Dummies::dummyListUnsignedInt);

#ifdef CG3_WITH_EIGEN
template <typename T, typename V, int ...A>
bool loadTriangleMeshFromPly(const std::string &filename, Eigen::Matrix<T, A...>& coords, Eigen::Matrix<V, A...>&triangles);
template <typename T, typename V, typename C = double, typename W = float, typename X = float, int ...A>
bool loadTriangleMeshFromPly(const std::string &filename, Eigen::Matrix<T, A...>& coords, Eigen::Matrix<V, A...>&triangles, int &modality, Eigen::Matrix<C, A...> &verticesNormals, Eigen::Matrix<W, A...> &verticesColors, Eigen::Matrix<X, A...> &triangleColors);
#endif

}

}

#include "load_save_file.cpp"

#endif // CG3_LOAD_SAVE_FILE_H
