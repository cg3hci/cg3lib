/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "decimate.h"

#include "internal/eigenmesh_libigl_algorithms.h"
#include <cg3/utilities/eigen.h>

namespace cg3 {
namespace libigl {

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @param mapping
 * @return
 */
CG3_INLINE SimpleEigenMesh decimateMesh(
        const SimpleEigenMesh &m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping)
{
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @param mapping
 * @return
 */
CG3_INLINE SimpleEigenMesh decimateMesh(
        const SimpleEigenMesh& m,
        int numberDesiredFaces,
        std::vector<int>& mapping)
{
    Eigen::VectorXi map;
    SimpleEigenMesh res = internal::EigenMeshLibIglAlgorithms::decimateMesh(
                              m,
                              numberDesiredFaces,
                              map);
    mapping = cg3::eigenVectorToStdVector(map);
    return res;
}


/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @return
 */
CG3_INLINE SimpleEigenMesh decimateMesh(const SimpleEigenMesh &m, int numberDesiredFaces)
{
    Eigen::VectorXi mapping;
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @param mapping
 * @return
 */
CG3_INLINE EigenMesh decimateMesh(
        const EigenMesh &m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping)
{
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @return
 */
CG3_INLINE EigenMesh decimateMesh(const EigenMesh &m, int numberDesiredFaces)
{
    Eigen::VectorXi mapping;
    return internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @param mapping
 */
CG3_INLINE void decimateMesh(
        SimpleEigenMesh &m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping)
{
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 */
CG3_INLINE void decimateMesh(SimpleEigenMesh &m, int numberDesiredFaces)
{
    Eigen::VectorXi mapping;
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 * @param mapping
 */
CG3_INLINE void decimateMesh(EigenMesh &m, int numberDesiredFaces, Eigen::VectorXi &mapping)
{
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

/**
 * @ingroup cg3libigl
 * @brief decimateMesh
 * @param m
 * @param numberDesiredFaces
 */
CG3_INLINE void decimateMesh(EigenMesh &m, int numberDesiredFaces)
{
    Eigen::VectorXi mapping;
    internal::EigenMeshLibIglAlgorithms::decimateMesh(m, numberDesiredFaces, mapping);
}

} //namespace cg3::libigl
} //namespace cg3


