/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_FILE_COMMONS_H
#define CG3_FILE_COMMONS_H

#include <string>
#include <list>
#include <vector>
#include "../utilities/color.h"

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

namespace cg3 {
namespace io {

typedef enum {
	RGB,
	RGBA
} FileColorMode;

typedef enum {
	TRIANGLE_MESH,
	QUAD_MESH,
	POLYGON_MESH
} FileMeshType;

/**
 * @brief A simple class that allows to store
 * which properties has been loaded or are going
 * to be saved on a mesh file (obj, ply, ...)
 */
class FileMeshMode {
public:
    FileMeshMode() : mode(0), type(TRIANGLE_MESH){}
	FileMeshMode(FileMeshType ft, bool vn, bool vc, bool fn, bool fc, bool e = false, bool ec = false) :
		mode(0), type(ft)
	{
		if (vn) setVertexNormals();
		if (vc) setVertexColors();
		if (fn) setFaceNormals();
		if (fc) setFaceColors();
		if (e) setEdges();
		if (ec) setEdgeColors();
	}
    bool isTriangleMesh()   const {return type == TRIANGLE_MESH;}
    bool isQuadMesh()       const {return type == QUAD_MESH;}
    bool isPolygonMesh()    const {return type == POLYGON_MESH;}
    bool hasVertexNormals() const {return mode & VERTEX_NORMALS;}
    bool hasVertexColors()  const {return mode & VERTEX_COLORS;}
    bool hasFaceNormals()   const {return mode & FACE_NORMALS;}
    bool hasFaceColors()    const {return mode & FACE_COLORS;}
	bool hasEdges()         const {return mode & EDGES;}
	bool hasEdgeColors()    const {return mode & EDGE_COLORS;}

    void setTriangleMesh()  {type = TRIANGLE_MESH;}
    void setQuadMesh()      {type = QUAD_MESH;}
    void setPolygonMesh()   {type = POLYGON_MESH;}
    void setMeshType(FileMeshType t) {type = t;}
    void setVertexNormals() {mode |= VERTEX_NORMALS;}
    void setVertexColors()  {mode |= VERTEX_COLORS;}
    void setFaceNormals()   {mode |= FACE_NORMALS;}
    void setFaceColors()    {mode |= FACE_COLORS;}
	void setEdges()			{mode |= EDGES;}
	void setEdgeColors()	{mode |= EDGE_COLORS;}

    void reset() {mode = 0; type = TRIANGLE_MESH;}

private:
	typedef enum {
		VERTEX_NORMALS =		0b000001,
		VERTEX_COLORS =			0b000010,
		FACE_COLORS =			0b000100,
		FACE_NORMALS =			0b001000,
		EDGES =					0b010000,
		EDGE_COLORS =			0b100000
	} FMM;
	int mode;
	FileMeshType type;
};

} //namespace cg3::io

namespace internal {

//static int dummyInt;
static io::FileMeshMode dummyFileMeshMode;
static const io::FileMeshMode dummyConstFileMeshMode;

static std::vector<double> dummyVectorDouble;
static std::vector<float> dummyVectorFloat;
static std::vector<int> dummyVectorInt;
static std::vector<unsigned int> dummyVectorUnsignedInt;
static std::vector<Color> dummyVectorColor;
static std::vector<Color> dummyVectorColor2;
static std::vector<Color> dummyVectorColor3;

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

template <typename T>
Color colorFromArray(
		size_t baseIndex,
		const T arrayColors[],
		io::FileColorMode colorMod);

} //namespace cg3::internal
} //namespace cg3

/**
 * @brief Generates a cg3::Color starting from a C-style array of values.
 * @param baseIndex: the starting index where take the first value from the array
 * @param arrayColors: the array of values (allowed types: int, uint, char, uchar)
 * @param colorMod: color mode: RGB or RGBA
 * @return a cg3::Color
 */
template <typename T>
inline cg3::Color cg3::internal::colorFromArray(
		size_t baseIndex,
		const T arrayColors[],
		io::FileColorMode colorMod)
{
	Color c;
	if (std::is_integral<T>::value) {
		if (colorMod == io::RGB){
			c = Color(arrayColors[baseIndex],
					  arrayColors[baseIndex+1],
					  arrayColors[baseIndex+2]);
		}
		else{
			c = Color(arrayColors[baseIndex],
					  arrayColors[baseIndex+1],
					  arrayColors[baseIndex+2],
					  arrayColors[baseIndex+3]);
		}

	}
	else {
		if (colorMod == io::RGB){
			c = Color(arrayColors[baseIndex]*255,
					  arrayColors[baseIndex+1]*255,
					  arrayColors[baseIndex+2]*255);
		}
		else {
			c = Color(arrayColors[baseIndex]*255,
					  arrayColors[baseIndex+1]*255,
					  arrayColors[baseIndex+2]*255,
					  arrayColors[baseIndex+3]*255);
		}
	}
	return c;
}

#endif // CG3_FILE_COMMONS_H
