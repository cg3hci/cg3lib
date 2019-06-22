/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "delaunay_triangulation3.h"

namespace cg3 {
namespace cgal {

CG3_INLINE DelaunayTriangulation3::DelaunayTriangulation3()
{
}

CG3_INLINE void DelaunayTriangulation3::pushPoint(const Point3d& p)
{
    triangulation.insert(CGALPoint(p.x(), p.y(), p.z()));
}

}
}
