/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "drawable_bounding_box2d.h"

#include "../../renderable_objects/2d/renderable_objects2d.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

DrawableBoundingBox2D::DrawableBoundingBox2D() : BoundingBox2D(), pointSize(2), pointColor(), edgeWidth(1), edgeColor() {
}

DrawableBoundingBox2D::DrawableBoundingBox2D(const BoundingBox2D& b) : BoundingBox2D(b), pointSize(2), pointColor(), edgeWidth(1), edgeColor() {
}

DrawableBoundingBox2D::DrawableBoundingBox2D(const Point2Dd& min, const Point2Dd& max) : DrawableBoundingBox2D(BoundingBox2D(min, max))
{
}

void DrawableBoundingBox2D::draw() const {
    drawEdges();
    drawPoints();
}

Pointd DrawableBoundingBox2D::sceneCenter() const {
    Point2Dd c = center();
    return Pointd(c.x(), c.y(), 0);
}

double DrawableBoundingBox2D::sceneRadius() const {
    return diag();
}

void DrawableBoundingBox2D::setEdgeColor(const QColor& c) {
    edgeColor = c;
}

void DrawableBoundingBox2D::setPointColor(const QColor& c) {
    pointColor = c;
}

void DrawableBoundingBox2D::setEdgeWidth(int w) {
    edgeWidth = w;
}

void DrawableBoundingBox2D::setPointSize(int s) {
    pointSize = s;
}

void DrawableBoundingBox2D::drawEdges() const {
    viewer::drawLine2D(Point2Dd(min().x(), min().y()), Point2Dd(max().x(), min().y()), edgeColor, edgeWidth);
    viewer::drawLine2D(Point2Dd(max().x(), min().y()), Point2Dd(max().x(), max().y()), edgeColor, edgeWidth);
    viewer::drawLine2D(Point2Dd(max().x(), max().y()), Point2Dd(min().x(), max().y()), edgeColor, edgeWidth);
    viewer::drawLine2D(Point2Dd(min().x(), max().y()), Point2Dd(min().x(), min().y()), edgeColor, edgeWidth);
}

void DrawableBoundingBox2D::drawPoints() const {
    viewer::drawPoint2D(minCoord, pointColor, pointSize);
    viewer::drawPoint2D(cg3::Point2Dd(minCoord.x(), maxCoord.y()), pointColor, pointSize);
    viewer::drawPoint2D(cg3::Point2Dd(maxCoord.x(), minCoord.y()), pointColor, pointSize);
    viewer::drawPoint2D(maxCoord, pointColor, pointSize);
}

}
