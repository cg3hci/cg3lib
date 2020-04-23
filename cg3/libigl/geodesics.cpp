/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "geodesics.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief Get exact geodesics given source and target vertices and faces
 * @param m Input mesh
 * @param sourceVertices Source vertices
 * @param targetVertices Target vertices
 * @param vertexGeodesics Output geodesics for each target vertex
 */
CG3_INLINE void exactGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices,
        const std::vector<unsigned int>& targetVertices,
        std::vector<double>& vertexGeodesics)
{
    return internal::EigenMeshLibIglAlgorithms::exactGeodesics(
                m,
                sourceVertices,
                targetVertices,
                vertexGeodesics);
}

/**
 * @ingroup cg3libigl
 * @brief Get exact geodesics given source vertices and faces (all elements are in the target)
 * @param m Input mesh
 * @param sourceVertices Source vertices
 * @param vertexGeodesics Output geodesics for each target vertex
 */
CG3_INLINE void exactGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices,
        std::vector<double>& vertexGeodesics)
{
    std::vector<unsigned int> targetVertices;

    targetVertices.resize(m.numberVertices());
    for (unsigned int i = 0; i < m.numberVertices(); i++) {
        targetVertices[i] = i;
    }

    return exactGeodesics(
                m,
                sourceVertices,
                targetVertices,
                vertexGeodesics);
}

/**
 * @ingroup cg3libigl
 * @brief Get heat geodesics approximation given source vertices
 * @param m Input mesh
 * @param sourceVertices Source vertices
 */
CG3_INLINE std::vector<double> heatGeodesics(
        const SimpleEigenMesh& m,
        const std::vector<unsigned int>& sourceVertices)
{
    HeatGeodesicsData precomputedData;

    heatGeodesicsPrecomputeData(
                m,
                precomputedData);

    return heatGeodesics(
                precomputedData,
                sourceVertices);
}

/**
 * @ingroup cg3libigl
 * @brief Get heat geodesics approximation given source vertices
 * @param precomputedData Precomputed heat geodesics data
 * @param sourceVertices Source vertices
 * @return Geodesic values per vertex
 */
CG3_INLINE std::vector<double> heatGeodesics(
        const HeatGeodesicsData& precomputedData,
        const std::vector<unsigned int>& sourceVertices)
{
    std::vector<double> geodesics;

    Eigen::VectorXi gamma;
    gamma.resize(sourceVertices.size());
    for (size_t i = 0; i < sourceVertices.size(); i++)
        gamma(i) = sourceVertices[i];

    Eigen::VectorXd D;

    igl::heat_geodesics_solve(precomputedData, gamma, D);

    geodesics.resize(D.size());
    for (int i = 0; i < D.size(); i++)
        geodesics[i] = D(i);

    return geodesics;
}

/**
 * @ingroup cg3libigl
 * @brief Get heat geodesics precomputed data
 * @param m Input mesh
 * @param precomputedData Output precomputed data
 */
CG3_INLINE void heatGeodesicsPrecomputeData(
        const SimpleEigenMesh& m,
        HeatGeodesicsData& precomputedData)
{
    internal::EigenMeshLibIglAlgorithms::heatGeodesicsPrecomputeData(
        m,
        precomputedData);
}


} //namespace cg3::libigl
} //namespace cg3


