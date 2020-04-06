/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_CURVATURE_H
#define CG3_LIBIGL_CURVATURE_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {
namespace libigl {

void vertexCurvature(
        const SimpleEigenMesh& m,
        std::vector<Vec3d>& minDirection,
        std::vector<Vec3d>& maxDirection,
        std::vector<double>& minValue,
        std::vector<double>& maxValue,
        const unsigned int nRing = 5);

std::vector<double> meanVertexCurvature(
        const SimpleEigenMesh& m,
        const unsigned int nRing = 5);

std::vector<double> meanVertexCurvature(
        const std::vector<double>& minValue,
        const std::vector<double>& maxValue);

std::vector<double> gaussianVertexCurvature(
        const SimpleEigenMesh& m,
        const unsigned int nRing = 5);

std::vector<double> gaussianVertexCurvature(
        const std::vector<double>& minValue,
        const std::vector<double>& maxValue);

} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LIBIGL_CURVATURE_CPP "curvature.cpp"
#include CG3_LIBIGL_CURVATURE_CPP
#undef CG3_LIBIGL_CURVATURE_CPP
#endif //CG3_STATIC

#endif // CG3_LIBIGL_CURVATURE_H
