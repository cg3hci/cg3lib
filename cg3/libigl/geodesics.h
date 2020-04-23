/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_GEODESICS_H
#define CG3_GEODESICS_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

#include <igl/heat_geodesics.h>

namespace cg3 {
namespace libigl {

typedef igl::HeatGeodesicsData<double> HeatGeodesicsData;

void exactGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices,
        const std::vector<unsigned int>& targetVertices,
        std::vector<double>& vertexGeodesics);

void exactGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices,
        std::vector<double>& vertexGeodesics);

std::vector<double> heatGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices);

std::vector<double> heatGeodesics(
        const HeatGeodesicsData& precomputedData,
        const std::vector<unsigned int>& sourceVertices);

void heatGeodesicsPrecomputeData(
        const SimpleEigenMesh& m,
        HeatGeodesicsData& precomputedData);


} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LIBIGL_GEODESICS_CPP "geodesics.cpp"
#include CG3_LIBIGL_GEODESICS_CPP
#undef CG3_LIBIGL_GEODESICS_CPP
#endif //CG3_STATIC

#endif // CG3_GEODESICS_H
