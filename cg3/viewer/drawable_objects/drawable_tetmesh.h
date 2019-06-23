/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CINOLIB_DRAWABLETETMESH_H
#define CG3_CINOLIB_DRAWABLETETMESH_H

#include <cg3/viewer/interfaces/drawable_object.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wreturn-type"
#include <cinolib/meshes/drawable_tetmesh.h>
#pragma GCC diagnostic pop

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
    Point3d sceneCenter() const;
    double sceneRadius() const;
};

} //namespace cg3::cino
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CINOLIB_DRAWABLETETMESH_CPP "drawable_tetmesh.cpp"
#include CG3_CINOLIB_DRAWABLETETMESH_CPP
#undef CG3_CINOLIB_DRAWABLETETMESH_CPP
#endif //CG3_STATIC

#endif // CG3_CINOLIB_DRAWABLETETMESH_H
