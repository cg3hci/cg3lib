/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_CGAL_POLYHEDRON_H
#define CG3_CGAL_POLYHEDRON_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Simple_cartesian.h>

#include <cg3/meshes/dcel/dcel.h>
#include <cg3/meshes/eigenmesh/eigenmesh.h>


namespace cg3 {
class SimpleEigenMesh;

namespace cgal {

/**
 * @ingroup cg3cgal
 * @brief The Polyhedron class
 */
typedef CGAL::Polyhedron_3<CGAL::Exact_predicates_inexact_constructions_kernel> Polyhedron;
typedef CGAL::Polyhedron_3<CGAL::Simple_cartesian<double>, CGAL::Polyhedron_items_with_id_3> PolyhedronWithId;

namespace internal {

static std::map<const Dcel::Vertex*, int> dummyVertexMap;
static std::map<const Dcel::Face*, int> dummyFaceMap;

} //namespace cg3::cgal::internal

template<class P = Polyhedron>
P polyhedronFromDcel(const Dcel& dcel,
        std::map<const Dcel::Vertex*, int>& vertexMap = internal::dummyVertexMap,
        std::map<const Dcel::Face*, int>& faceMap = internal::dummyFaceMap);

template<class P = Polyhedron>
Dcel dcelFromPolyhedron(const P& poly);

template<class P = Polyhedron>
P polyhedronFromEigenMesh(const SimpleEigenMesh& mesh);
template<class P = Polyhedron>
SimpleEigenMesh eigenMeshFromPolyhedron(const P& poly);

} //namespace cg3::cgal
} //namespace cg3

#include "polyhedron.inl"

#endif // CG3_CGAL_POLYHEDRON_H
