/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_EIGENMESH_H
#define CG3_DRAWABLE_EIGENMESH_H

#include <cg3/viewer/interfaces/drawable_mesh.h>
#include "cg3/meshes/eigenmesh/eigenmesh.h"

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableEigenMesh class
 */
class DrawableEigenMesh : public EigenMesh, public DrawableMesh
{
public:
    DrawableEigenMesh();
    DrawableEigenMesh(const SimpleEigenMesh &m);
    DrawableEigenMesh(const EigenMesh &m);
	DrawableEigenMesh(const char* filename);
    DrawableEigenMesh(const std::string &filename);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_EIGENMESH_CPP "drawable_eigenmesh.cpp"
#include CG3_DRAWABLE_EIGENMESH_CPP
#undef CG3_DRAWABLE_EIGENMESH_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_EIGENMESH_H
