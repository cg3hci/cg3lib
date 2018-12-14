/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CINOLIB_DRAWABLETETMESH_H
#define CG3_CINOLIB_DRAWABLETETMESH_H

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cinolib/meshes/drawable_tetmesh.h>

namespace cg3 {
namespace cino {

class DrawableTetMesh : public DrawableObject, public cinolib::DrawableTetmesh<>
{
public:
    DrawableTetMesh();
    DrawableTetMesh(const std::string& s);

    // DrawableObject interface
    void draw() const;
    virtual void draw(const float f = 1.0) const;
    Pointd sceneCenter() const;
    double sceneRadius() const;
};

} //namespace cg3::cino
} //namespace cg3

#endif // CG3_CINOLIB_DRAWABLETETMESH_H
