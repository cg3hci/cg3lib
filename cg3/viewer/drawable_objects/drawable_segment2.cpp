/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_segment2.h"

namespace cg3 {

CG3_INLINE DrawableSegment2::DrawableSegment2() :
    Segment2d(),
    color(),
    width(2)
{
}

CG3_INLINE DrawableSegment2::DrawableSegment2(const Segment2d &s) :
    Segment2d(s),
    color(),
    width(2)
{
}

CG3_INLINE DrawableSegment2::DrawableSegment2(const Point2d &p1, const Point2d &p2) :
    Segment2d(p1, p2),
    color(),
    width(2)
{
}

CG3_INLINE void DrawableSegment2::draw() const
{
    cg3::opengl::drawLine2(_p1, _p2, color, width);
}

CG3_INLINE Point3d DrawableSegment2::sceneCenter() const
{
    Point2d p = (_p1 + _p2)/2;
    return Point3d(p.x(), p.y(), 0);
}

CG3_INLINE double DrawableSegment2::sceneRadius() const
{
    return _p1.dist(_p2) / 2;
}

CG3_INLINE void DrawableSegment2::setColor(const QColor& c)
{
    color = c;
}

CG3_INLINE void DrawableSegment2::setWidth(int w)
{
    width = w;
}

} //namespace cg3
