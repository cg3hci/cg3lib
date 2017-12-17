/**
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

namespace cg3 {

namespace libigl {

typedef igl::copyleft::cgal::CSGTree CSGTree;

CSGTree eigenMeshToCSGTree(const SimpleEigenMesh& m);
SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree& tree);

void intersection(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
void intersection(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
SimpleEigenMesh intersection(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
EigenMesh intersection(const EigenMesh &m1, const EigenMesh &m2);
void intersection(CSGTree& result, const CSGTree& m1, const SimpleEigenMesh& m2);
CSGTree intersection(const CSGTree& m1, const SimpleEigenMesh& m2);
void intersection(SimpleEigenMesh& result, const CSGTree& m1, const SimpleEigenMesh& m2);

void difference(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
void difference(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
SimpleEigenMesh difference(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
EigenMesh difference(const EigenMesh &m1, const EigenMesh &m2);
void difference(CSGTree& result, const CSGTree& m1, const SimpleEigenMesh& m2);
CSGTree difference(const CSGTree& m1, const SimpleEigenMesh& m2);


void union_(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
void union_(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
SimpleEigenMesh union_(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
EigenMesh union_(const EigenMesh &m1, const EigenMesh &m2);
void union_(CSGTree& result, const CSGTree& m1, const SimpleEigenMesh& m2);
CSGTree union_(const CSGTree& m1, const SimpleEigenMesh& m2);

}

}

#include "booleans.tpp"

#endif //CG3_CGAL_DEFINED


#endif // CG3_LIBIGL_BOOLEANS_H
