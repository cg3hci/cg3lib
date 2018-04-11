/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_segment2d.h"

namespace cg3 {

DrawableSegment2D::DrawableSegment2D() :
    Segment2Dd(),
    color(),
    width(2)
{
}

DrawableSegment2D::DrawableSegment2D(const Segment2Dd &s) :
    Segment2Dd(s),
    color(),
    width(2)
{
}

DrawableSegment2D::DrawableSegment2D(const Point2Dd &p1, const Point2Dd &p2) :
    Segment2Dd(p1, p2),
    color(),
    width(2)
{
}

void DrawableSegment2D::draw() const
{
    cg3::opengl::drawLine2D(p1, p2, color, width);
}

Pointd DrawableSegment2D::sceneCenter() const
{
    Point2Dd p = (p1 + p2)/2;
    return Pointd(p.x(), p.y(), 0);
}

double DrawableSegment2D::sceneRadius() const
{
    return p1.dist(p2) / 2;
}

void DrawableSegment2D::setColor(const QColor& c)
{
    color = c;
}

void DrawableSegment2D::setWidth(int w)
{
    width = w;
}

} //namespace cg3
