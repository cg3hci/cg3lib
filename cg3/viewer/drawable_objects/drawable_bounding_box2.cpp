/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "drawable_bounding_box2.h"

#include "../opengl_objects/opengl_objects2.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

DrawableBoundingBox2::DrawableBoundingBox2() :
    BoundingBox2(),
    pointSize(2),
    pointColor(),
    edgeWidth(1),
    edgeColor()
{
}

DrawableBoundingBox2::DrawableBoundingBox2(const BoundingBox2& b) :
    BoundingBox2(b),
    pointSize(2),
    pointColor(),
    edgeWidth(1),
    edgeColor()
{
}

DrawableBoundingBox2::DrawableBoundingBox2(const Point2d& min, const Point2d& max) :
	DrawableBoundingBox2(BoundingBox2(min, max))
{
}

void DrawableBoundingBox2::draw() const
{
    drawEdges();
    drawPoints();
}

Point3d DrawableBoundingBox2::sceneCenter() const
{
    Point2d c = center();
    return Point3d(c.x(), c.y(), 0);
}

double DrawableBoundingBox2::sceneRadius() const
{
    return diag();
}

void DrawableBoundingBox2::setEdgeColor(const QColor& c)
{
    edgeColor = c;
}

void DrawableBoundingBox2::setPointColor(const QColor& c)
{
    pointColor = c;
}

void DrawableBoundingBox2::setEdgeWidth(int w)
{
    edgeWidth = w;
}

void DrawableBoundingBox2::setPointSize(int s)
{
    pointSize = s;
}

void DrawableBoundingBox2::drawEdges() const
{
	opengl::drawLine2(Point2d(min().x(), min().y()),
                       Point2d(max().x(), min().y()),
                       edgeColor,
                       edgeWidth);
	opengl::drawLine2(Point2d(max().x(), min().y()),
                       Point2d(max().x(), max().y()),
                       edgeColor,
                       edgeWidth);
	opengl::drawLine2(Point2d(max().x(), max().y()),
                       Point2d(min().x(), max().y()),
                       edgeColor,
                       edgeWidth);
	opengl::drawLine2(Point2d(min().x(), max().y()),
                       Point2d(min().x(), min().y()),
                       edgeColor,
                       edgeWidth);
}

void DrawableBoundingBox2::drawPoints() const
{
	opengl::drawPoint2(minCoord, pointColor, pointSize);
	opengl::drawPoint2(cg3::Point2d(minCoord.x(), maxCoord.y()), pointColor, pointSize);
	opengl::drawPoint2(cg3::Point2d(maxCoord.x(), minCoord.y()), pointColor, pointSize);
	opengl::drawPoint2(maxCoord, pointColor, pointSize);
}

} //namespace cg3
