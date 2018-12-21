/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "delaunaytriangulation.h"

namespace cg3 {
namespace cgal {

DelaunayTriangulation::DelaunayTriangulation()
{

}

void DelaunayTriangulation::pushPoint(const Pointd& p)
{
    triangulation.insert(CGALPoint(p.x(), p.y(), p.z()));

}

}
}
