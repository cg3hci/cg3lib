/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_BOOLEANS_H
#define CG3_LIBIGL_BOOLEANS_H

#ifdef  CG3_CGAL_DEFINED

#include <cg3/meshes/eigenmesh/eigenmesh.h>
#include <igl/copyleft/cgal/CSGTree.h>
#include "internal/booleans_algorithms.h"

namespace cg3 {
namespace libigl {

typedef igl::copyleft::cgal::CSGTree CSGTree;

/* Conversions */
CSGTree eigenMeshToCSGTree(const SimpleEigenMesh& m);
SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree& tree);

/* Intersection */
void intersection(CSGTree& result, const CSGTree& m1, const CSGTree& m2);
void intersection(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
void intersection(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
CSGTree intersection(const CSGTree& m1, const CSGTree& m2);
SimpleEigenMesh intersection(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
EigenMesh intersection(const EigenMesh& m1, const EigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);

/* Difference */
void difference(CSGTree& result, const CSGTree& m1, const CSGTree& m2);
void difference(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
void difference(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
CSGTree difference(const CSGTree& m1, const CSGTree& m2);
SimpleEigenMesh difference(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
EigenMesh difference(const EigenMesh& m1, const EigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);

/* Union */
void union_(CSGTree& result, const CSGTree& m1, const CSGTree& m2);
void union_(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
void union_(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
CSGTree union_(const CSGTree& m1, const CSGTree& m2);
SimpleEigenMesh union_(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);
EigenMesh union_(const EigenMesh& m1, const EigenMesh& m2, std::vector<uint>& birthFaces = internal::dummyVector);

} //namespace cg3::libigl
} //namespace cg3

#endif //CG3_CGAL_DEFINED

#ifndef CG3_STATIC
#define CG3_LIBIGL_BOOLEANS_CPP "booleans.cpp"
#include CG3_LIBIGL_BOOLEANS_CPP
#undef CG3_LIBIGL_BOOLEANS_CPP
#endif //CG3_STATIC

#endif // CG3_LIBIGL_BOOLEANS_H
