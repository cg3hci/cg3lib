/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CGAL_HOLE_FILLING_H
#define CG3_CGAL_HOLE_FILLING_H

#include "polyhedron.h"

#ifdef CGAL_EIGEN3_ENABLED
namespace cg3 {
namespace cgal {

void holeFillingFileOff(const std::string& input, const std::string& output);

void holeFilling(Polyhedron& poly);
void holeFillingTriangulation(cgal::Polyhedron& poly);

void holeFilling(Dcel & d);

SimpleEigenMesh holeFilling(const SimpleEigenMesh& d);
SimpleEigenMesh holeFillingTriangulation(const SimpleEigenMesh& poly);

} //namespace cg3::cgal
} //namespace cg3
#endif //CGAL_EIGEN3_ENABLED

#ifndef CG3_STATIC
#define CG3_CGAL_HOLE_FILLING_CPP "hole_filling.cpp"
#include CG3_CGAL_HOLE_FILLING_CPP
#undef BOUNDINGBOX2_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_HOLE_FILLING_H
