/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_SLICER_H
#define CG3_CGAL_SLICER_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>
#include <cg3/geometry/plane.h>

#include "surfacemesh.h"

#include <CGAL/boost/graph/graph_traits_Surface_mesh.h>
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/Polygon_mesh_slicer.h>



namespace cg3 {

namespace cgal {

        std::vector<std::vector<Pointd> > getPolylines(const std::string& inputOffFile, const Vec3& norm, double d);
        std::vector<std::vector<Pointd> > getPolylines(const SurfaceMesh& mesh, const Vec3& norm, double d);
        #ifdef CG3_DCEL_DEFINED
        std::vector<std::vector<Pointd> > getPolylines(const Dcel& mesh, const cg3::Plane& p);
        std::vector<std::vector<Pointd> > getPolylines(const Dcel& mesh, const Vec3& norm, double d);
        #endif
}

}


#endif // CG3_CGAL_SLICER_H
