/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_HOLEFILLING_H
#define CG3_CGAL_HOLEFILLING_H

#include "polyhedron.h"

#ifdef CGAL_EIGEN3_ENABLED
namespace cg3 {
namespace cgal {

void holeFillingFileOff(const std::string& input, const std::string& output);

void holeFilling(Polyhedron& poly);

#ifdef CG3_DCEL_DEFINED
void holeFilling(Dcel & d);
#endif

} //namespace cg3::cgal
} //namespace cg3
#endif

#endif // CG3_CGAL_HOLEFILLING_H
