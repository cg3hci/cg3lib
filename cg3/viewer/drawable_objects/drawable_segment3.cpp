/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_segment3.h"

#include "../opengl_objects/opengl_objects3.h"

namespace cg3 {

DrawableSegment3::DrawableSegment3() :
    Segment3d(),
    color(0,0,0),
    width(0)
{
}

DrawableSegment3::DrawableSegment3(
        const Point3d &p1,
        const Point3d &p2,
        Color c,
        int width) :
    Segment3d(p1, p2),
    color(c),
    width(width)
{
}

void DrawableSegment3::draw() const
{
    cg3::opengl::drawLine3(_p1, _p2, color, width);
}

Point3d DrawableSegment3::sceneCenter() const
{
    return (_p1 + _p2)/2;
}

double DrawableSegment3::sceneRadius() const
{
    return length() / 2;
}

} //namespace cg3
