/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_SLICER_H
#define CG3_CGAL_SLICER_H

#include <cg3/geometry/point.h>

#include "surfacemesh.h"

namespace cg3 {

class Plane;

namespace cgal {

std::vector<std::vector<Pointd> > polylines(
        const std::string& inputOffFile,
        const Vec3& norm,
        double d);

std::vector<std::vector<Pointd> > polylines(
        const SurfaceMesh& mesh,
        const Vec3& norm,
        double d);

#ifdef CG3_DCEL_DEFINED
std::vector<std::vector<Pointd> > polylines(
        const Dcel& mesh,
        const cg3::Plane& p);

std::vector<std::vector<Pointd> > polylines(
        const Dcel& mesh,
        const Vec3& norm,
        double d);
    #endif

} //namespace cg3::cgal
} //namespace cg3


#endif // CG3_CGAL_SLICER_H
