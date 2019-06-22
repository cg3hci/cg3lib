/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_LIBIGL_DECIMATE_H
#define CG3_LIBIGL_DECIMATE_H

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {
namespace libigl {

SimpleEigenMesh decimateMesh(
        const SimpleEigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping);

SimpleEigenMesh decimateMesh(
        const SimpleEigenMesh& m,
        int numberDesiredFaces,
        std::vector<int> &mapping);

SimpleEigenMesh decimateMesh(
        const SimpleEigenMesh& m,
        int numberDesiredFaces);

EigenMesh decimateMesh(
        const EigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping);

EigenMesh decimateMesh(
        const EigenMesh& m,
        int numberDesiredFaces);

void decimateMesh(
        SimpleEigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping);

void decimateMesh(
        SimpleEigenMesh& m,
        int numberDesiredFaces);

void decimateMesh(
        EigenMesh& m,
        int numberDesiredFaces,
        Eigen::VectorXi &mapping);

void decimateMesh(
        EigenMesh& m,
        int numberDesiredFaces);

} //namespace cg3::libigl
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LIBIGL_DECIMATE_CPP "decimate.cpp"
#include CG3_LIBIGL_DECIMATE_CPP
#undef CG3_LIBIGL_DECIMATE_CPP
#endif //CG3_STATIC

#endif // CG3_LIBIGL_DECIMATE_H
