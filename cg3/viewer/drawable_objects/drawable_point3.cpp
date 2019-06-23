/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_point3.h"
#include "../opengl_objects/opengl_objects3.h"

namespace cg3 {

CG3_INLINE DrawablePoint3::DrawablePoint3(double x, double y, double z, Color c, int size) :
    Point3d(x, y, z), color(c), size(size)
{
}

CG3_INLINE void DrawablePoint3::draw() const
{
    opengl::drawPoint3(*this, color, size);
}

CG3_INLINE Point3d DrawablePoint3::sceneCenter() const
{
    return *this;
}

CG3_INLINE double DrawablePoint3::sceneRadius() const
{
    return -1;
}

} //namespace cg3
