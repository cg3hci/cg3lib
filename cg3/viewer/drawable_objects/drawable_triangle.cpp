/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_triangle.h"
#include "../opengl_objects/opengl_objects.h"

namespace cg3 {

DrawableTriangle::DrawableTriangle() :
    Triangle3Dd(),
    color(0,0,0),
    width(3),
    fill(false)
{
}

DrawableTriangle::DrawableTriangle(
        const Pointd &p1,
        const Pointd &p2,
        const Pointd &p3,
        Color c,
        unsigned int width,
        bool fill) :
    Triangle3Dd(p1, p2, p3),
    color(c),
    width(width),
    fill(fill)
{
}

void DrawableTriangle::draw() const
{
    opengl::drawTriangle(_v1, _v2, _v3, color, width, fill);
}

Pointd DrawableTriangle::sceneCenter() const
{
    return barycenter();
}

double DrawableTriangle::sceneRadius() const
{
    return barycenter().dist(_v1);
}

} //namespace cg3
