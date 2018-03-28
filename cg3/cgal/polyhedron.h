/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_CGAL_POLYHEDRON_H
#define CG3_CGAL_POLYHEDRON_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

namespace cg3 {
namespace cgal {

typedef CGAL::Polyhedron_3<CGAL::Exact_predicates_inexact_constructions_kernel> Polyhedron;

#ifdef  CG3_DCEL_DEFINED
namespace internal {

static std::map<const Dcel::Vertex*, int> dummyVertexMap;
static std::map<const Dcel::Face*, int> dummyFaceMap;

} //namespace cg3::cgal::internal

Polyhedron getPolyhedronFromDcel(const Dcel& dcel,
        std::map<const Dcel::Vertex*, int>& vertexMap = internal::dummyVertexMap,
        std::map<const Dcel::Face*, int>& faceMap = internal::dummyFaceMap);

Dcel getDcelFromPolyhedron(const Polyhedron& poly);
#endif

#ifdef  CG3_EIGENMESH_DEFINED
Polyhedron getPolyhedronFromEigenMesh(const SimpleEigenMesh& mesh);
#endif

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_POLYHEDRON_H
