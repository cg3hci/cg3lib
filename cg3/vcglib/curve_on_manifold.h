/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_VCGLIB_CURVE_ON_MANIFOLD_H
#define CG3_VCGLIB_CURVE_ON_MANIFOLD_H

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

namespace cg3 {
namespace vcglib {

#ifdef CG3_EIGENMESH_DEFINED

cg3::EigenMesh curveOnManifold(
        const cg3::EigenMesh& mesh,
		const std::vector<std::pair<cg3::Point3d,cg3::Point3d>>& edges,
		std::set<std::pair<cg3::Point3d, cg3::Point3d>>& newEdgesCoordinates,
        const int firstStepIterations = 30,
        const int secondStepIterations = 10,
        const double baryCentricThreshold = 0.05,
        bool fixBorders = true,
        bool fixCorners = false);


#endif

template <class TriangleEdgeMeshType>
bool curveOnManifold(
        TriangleEdgeMeshType& mesh,
        TriangleEdgeMeshType& edgeMesh,
        TriangleEdgeMeshType& resultMesh,
        const int firstStepIterations = 30,
        const int secondStepIterations = 10,
        const double baryCentricThreshold = 0.05,
        bool fixBorders = true,
        bool fixCorners = false);
}
}

#include "curve_on_manifold.cpp"

#endif // CURVE_ON_MANIFOLD_H
