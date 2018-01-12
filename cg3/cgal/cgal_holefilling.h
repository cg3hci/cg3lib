/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_HOLEFILLING_H
#define CG3_CGAL_HOLEFILLING_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/triangulate_hole.h>

#include "cgal_polyhedron.h"

#ifdef DCEL_DEFINED
#include <dcel/dcel.h>
#endif

#include <fstream>

#ifdef CGAL_EIGEN3_ENABLED

namespace cg3 {

namespace cgal {
    namespace holeFilling {

        typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
        typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;
        typedef Polyhedron::Halfedge_handle    Halfedge_handle;
        typedef Polyhedron::Facet_handle       Facet_handle;
        typedef Polyhedron::Vertex_handle      Vertex_handle;

        void holeFillingFileOff(const std::string& input, const std::string& output);
        void holeFilling(Polyhedron& poly);

        #ifdef CG3_DCEL_DEFINED
        void holeFilling(Dcel & d);
        #endif
    }
}

}
#endif

#endif // CG3_CGAL_HOLEFILLING_H
