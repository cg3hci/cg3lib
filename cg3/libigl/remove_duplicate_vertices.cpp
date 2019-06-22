/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "remove_duplicate_vertices.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief removeDuplicateVertices
 * @param input
 * @param epsilon
 */
CG3_INLINE void removeDuplicateVertices(SimpleEigenMesh &input, double epsilon)
{
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, epsilon);
}

/**
 * @ingroup cg3libigl
 * @brief removeDuplicateVertices
 * @param input
 * @param I
 * @param epsilon
 */
CG3_INLINE void removeDuplicateVertices(SimpleEigenMesh &input,
                                    Eigen::Matrix<int, Eigen::Dynamic, 1> &I,
                                    double epsilon)
{
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, I, epsilon);
}

/**
 * @ingroup cg3libigl
 * @brief removeDuplicateVertices
 * @param input
 * @param epsilon
 */
CG3_INLINE void removeDuplicateVertices(EigenMesh &input, double epsilon)
{
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, epsilon);
}

/**
 * @ingroup cg3libigl
 * @brief removeDuplicateVertices
 * @param input
 * @param I
 * @param epsilon
 */
CG3_INLINE void removeDuplicateVertices(
        EigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I,
        double epsilon)
{
    internal::EigenMeshLibIglAlgorithms::removeDuplicateVertices(input, I, epsilon);
}

} //namespace cg3::libigl
} //namespace cg3
