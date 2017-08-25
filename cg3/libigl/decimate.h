#ifndef CG3_LIBIGL_DECIMATE_H
#define CG3_LIBIGL_DECIMATE_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

namespace libigl {

SimpleEigenMesh decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
SimpleEigenMesh decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces);

EigenMesh decimateMesh(const EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
EigenMesh decimateMesh(const EigenMesh& m, int numberDesiredFaces);

void decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
void decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces);

void decimateMesh(EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi &mapping);
void decimateMesh(EigenMesh& m, int numberDesiredFaces);

}

}

#include "decimate.ipp"

#endif // CG3_LIBIGL_DECIMATE_H
