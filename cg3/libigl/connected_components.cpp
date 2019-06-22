/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "connected_components.h"

#include "internal/eigenmesh_libigl_algorithms.h"

/**
 * @ingroup cg3libigl
 * @brief cg3::libigl::getConnectedComponents
 * @param m
 * @return
 */
CG3_INLINE std::vector<cg3::SimpleEigenMesh> cg3::libigl::connectedComponents(
        const cg3::SimpleEigenMesh &m)
{
    return internal::EigenMeshLibIglAlgorithms::connectedComponents(m);
}
