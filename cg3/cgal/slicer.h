/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_SLICER_H
#define CG3_CGAL_SLICER_H

#include <cg3/geometry/point3.h>

#include "surface_mesh.h"

namespace cg3 {

class Plane;

namespace cgal {

std::vector<std::vector<Point3d> > polylines(
        const std::string& inputOffFile,
        const Vec3d& norm,
        double d);

std::vector<std::vector<Point3d> > polylines(
        const SurfaceMesh& mesh,
        const Vec3d& norm,
        double d);

#ifdef CG3_DCEL_DEFINED
std::vector<std::vector<Point3d> > polylines(
        const Dcel& mesh,
        const cg3::Plane& p);

std::vector<std::vector<Point3d> > polylines(
        const Dcel& mesh,
        const Vec3d& norm,
        double d);
    #endif

} //namespace cg3::cgal
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CGAL_SLICER_CPP "slicer.cpp"
#include CG3_CGAL_SLICER_CPP
#undef CG3_CGAL_SLICER_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_SLICER_H
