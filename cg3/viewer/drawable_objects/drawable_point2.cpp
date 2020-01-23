/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_point2.h"
#include "../opengl_objects/opengl_objects2.h"

namespace cg3 {

CG3_INLINE DrawablePoint2::DrawablePoint2(double x, double y, Color c, unsigned int size) :
    Point2d(x, y), color(c), size(size)
{
}

CG3_INLINE void DrawablePoint2::draw() const
{
    opengl::drawPoint2(*this, color, static_cast<int>(size));
}

CG3_INLINE Point3d DrawablePoint2::sceneCenter() const
{
    return Point3d(x(), y(), 0);
}

CG3_INLINE double DrawablePoint2::sceneRadius() const
{
    return -1;
}

} //namespace cg3
