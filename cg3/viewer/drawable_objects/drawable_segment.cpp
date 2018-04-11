/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_segment.h"

#include "../opengl_objects/opengl_objects.h"

namespace cg3 {

DrawableSegment::DrawableSegment() :
    Segment3Dd(),
    color(0,0,0),
    width(0)
{
}

DrawableSegment::DrawableSegment(
        const Pointd &p1,
        const Pointd &p2,
        Color c,
        int width) :
    Segment3Dd(p1, p2),
    color(c),
    width(width)
{
}

void DrawableSegment::draw() const
{
    cg3::opengl::drawLine(p1, p2, color, width);
}

Pointd DrawableSegment::sceneCenter() const
{
    return (p1 + p2)/2;
}

double DrawableSegment::sceneRadius() const
{
    return length() / 2;
}

} //namespace cg3
