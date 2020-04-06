/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "curvature.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief Get principal curvature
 * @param m Input mesh
 * @param minDirection Minimum principal curvature direction for each vertex
 * @param maxDirection Minimum principal curvature direction for each vertex
 * @param minValue Minimum principal curvature magnitude for each vertex
 * @param maxValue Maximum principal curvature magnitude for each vertex
 * @param nRing Controls the size of the neighbourhood used, 1 = average edge length
 */
CG3_INLINE void vertexCurvature(
        const SimpleEigenMesh& m,
        std::vector<Vec3d>& minDirection,
        std::vector<Vec3d>& maxDirection,
        std::vector<double>& minValue,
        std::vector<double>& maxValue,
        const unsigned int nRing)
{
    return internal::EigenMeshLibIglAlgorithms::vertexCurvature(
                m,
                minDirection,
                maxDirection,
                minValue,
                maxValue,
                nRing);

    assert(minValue.size() == maxValue.size());
    assert(minDirection.size() == maxDirection.size());
}

/**
 * @ingroup cg3libigl
 * @brief Get mean curvature
 * @param m Input mesh
 * @param nRing Controls the size of the neighbourhood used, 1 = average edge length
 * @return Mean curvature for each vertex
 */
CG3_INLINE std::vector<double> meanVertexCurvature(
        const SimpleEigenMesh& m,
        const unsigned int nRing)
{
    std::vector<Vec3d> minDirection;
    std::vector<Vec3d> maxDirection;
    std::vector<double> minValue;
    std::vector<double> maxValue;

    vertexCurvature(m, minDirection, maxDirection, minValue, maxValue, nRing);

    return meanVertexCurvature(minValue, maxValue);
}

/**
 * @ingroup cg3libigl
 * @brief Get mean curvature (with precalculated magnitudes)
 * @param m Input mesh
 * @param minValue Minimum principal curvature magnitude for each vertex
 * @param maxValue Maximum principal curvature magnitude for each vertex
 * @return Mean curvature for each vertex
 */
CG3_INLINE std::vector<double> meanVertexCurvature(
        const std::vector<double>& minValue,
        const std::vector<double>& maxValue)
{
    assert(minValue.size() == maxValue.size());

    std::vector<double> meanCurvature(minValue.size());

    for (size_t i = 0; i < meanCurvature.size(); ++i) {
        meanCurvature[i] = (minValue[i] + maxValue[i]) / 2.0;
    }

    return meanCurvature;
}


/**
 * @ingroup cg3libigl
 * @brief Get gaussian curvature
 * @param m Input mesh
 * @param nRing Controls the size of the neighbourhood used, 1 = average edge length
 * @return Mean curvature for each vertex
 */
CG3_INLINE std::vector<double> gaussianVertexCurvature(
        const SimpleEigenMesh& m,
        const unsigned int nRing)
{
    std::vector<Vec3d> minDirection;
    std::vector<Vec3d> maxDirection;
    std::vector<double> minValue;
    std::vector<double> maxValue;

    vertexCurvature(m, minDirection, maxDirection, minValue, maxValue, nRing);

    return gaussianVertexCurvature(minValue, maxValue);
}

/**
 * @ingroup cg3libigl
 * @brief Get gaussian curvature (with precalculated magnitudes)
 * @param m Input mesh
 * @param minValue Minimum principal curvature magnitude for each vertex
 * @param maxValue Maximum principal curvature magnitude for each vertex
 * @return Mean curvature for each vertex
 */
CG3_INLINE std::vector<double> gaussianVertexCurvature(
        const std::vector<double>& minValue,
        const std::vector<double>& maxValue)
{
    assert(minValue.size() == maxValue.size());

    std::vector<double> gaussianCurvature(minValue.size());

    for (size_t i = 0; i < gaussianCurvature.size(); ++i) {
        gaussianCurvature[i] = minValue[i] * maxValue[i];
    }

    return gaussianCurvature;
}



} //namespace cg3::libigl
} //namespace cg3


