/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/exact_geodesic.h>
#include <igl/heat_geodesics.h>

namespace cg3 {
namespace libigl {
namespace internal {

/* ----- EXACT GEODESICS ----- */

/**
 * @ingroup cg3libigl
 * @brief Get exact geodesics given source and target vertices and faces
 * @param m Input mesh
 * @param sourceVertices Source vertices
 * @param targetVertices Target vertices
 * @param vertexGeodesics Output geodesics for each target vertex
 */
CG3_INLINE void EigenMeshLibIglAlgorithms::exactGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices,
        const std::vector<unsigned int>& targetVertices,
        std::vector<double>& vertexGeodesics)
{
    Eigen::MatrixXd V = m.V;
    Eigen::MatrixXi F = m.F;

    Eigen::VectorXi VS,FS,VT,FT;

    VS.resize(sourceVertices.size());
    for (size_t i = 0; i < sourceVertices.size(); i++)
        VS(i) = sourceVertices[i];
    VT.resize(targetVertices.size());
    for (size_t i = 0; i < targetVertices.size(); i++)
        VT(i) = targetVertices[i];

    Eigen::VectorXd d;

    igl::exact_geodesic(V,F,VS,FS,VT,FT,d);

    vertexGeodesics.resize(targetVertices.size());
    for (size_t i = 0; i < targetVertices.size(); i++)
        vertexGeodesics[i] = d(i);
}


/* ----- HEAT GEODESICS ----- */

CG3_INLINE void EigenMeshLibIglAlgorithms::heatGeodesicsPrecomputeData(
        const SimpleEigenMesh& m,
        igl::HeatGeodesicsData<double>& precomputedData)
{
    igl::heat_geodesics_precompute(m.V, m.F, precomputedData);
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3
