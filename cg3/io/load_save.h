/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LOAD_SAVE_H
#define CG3_LOAD_SAVE_H

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

template <typename T>
Color colorFromArray(
		size_t baseIndex,
		const T arrayColors[],
		io::ColorMode colorMod);

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
		io::ColorMode colorMod)
{
	Color c;
	if (std::is_same<T, int>::value ||
			std::is_same<T, unsigned int>::value ||
			std::is_same<T, char>::value ||
			std::is_same<T, unsigned char>::value) {
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

#endif // LOAD_SAVE_H
