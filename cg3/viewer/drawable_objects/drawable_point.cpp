/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_point.h"
#include "../opengl_objects/opengl_objects.h"

namespace cg3 {

DrawablePoint::DrawablePoint(double x, double y, double z, Color c, int size) :
    Pointd(x, y, z), color(c), size(size)
{
}

void DrawablePoint::draw() const
{
    opengl::drawPoint(*this, color, size);
}

Pointd DrawablePoint::sceneCenter() const
{
    return *this;
}

double DrawablePoint::sceneRadius() const
{
    return -1;
}

} //namespace cg3
