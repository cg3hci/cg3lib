/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CGAL_SDF_SEGMENTATION_H
#define CG3_CGAL_SDF_SEGMENTATION_H

#include <boost/version.hpp>

#if BOOST_VERSION > 106501

#include "polyhedron.h"

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/simpleeigenmesh.h>
#endif

namespace cg3 {
namespace cgal {

std::vector<int> skeletonSdfSegmentation(PolyhedronWithId& mesh);
std::vector<int> sdfSegmentation(const Polyhedron& mesh);

#ifdef  CG3_EIGENMESH_DEFINED
std::vector<int> sdfSegmentation(const SimpleEigenMesh& m);
std::vector<int> skeletonSdfSegmentation(const SimpleEigenMesh& m);
#endif

} //namespace cg3::cgal
} //namespace cg3

#endif //BOOST_VERSION

#ifndef CG3_STATIC
#define CG3_CGAL_SDF_SEGMENTATION_CPP "sdf_segmentation.cpp"
#include CG3_CGAL_SDF_SEGMENTATION_CPP
#undef CG3_CGAL_SDF_SEGMENTATION_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_SDF_SEGMENTATION_H
