/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CGAL_SKELETON_H
#define CG3_CGAL_SKELETON_H

#include "polyhedron.h"

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/simpleeigenmesh.h>
#endif

#include <CGAL/extract_mean_curvature_flow_skeleton.h>

namespace cg3 {
namespace cgal {

CGAL::Mean_curvature_flow_skeletonization<PolyhedronWithId>::Skeleton skeleton(const PolyhedronWithId& mesh);

#ifdef  CG3_EIGENMESH_DEFINED
std::vector<cg3::Point3d> skeleton(
        const SimpleEigenMesh& mesh,
        std::vector<std::vector<size_t>>& birthVertices,
        std::vector<std::vector<size_t>>& polylines);
#endif

} //namespace cg3::cgal
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CGAL_SKELETON_CPP "skeleton.cpp"
#include CG3_CGAL_SKELETON_CPP
#undef CG3_CGAL_SKELETON_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_SKELETON_H
