/**
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

DrawableBoundingBox2D::DrawableBoundingBox2D() : BoundingBox2D(), pointSize(2), colorPoint(), edgeWidth(1), colorEdge() {
}

DrawableBoundingBox2D::DrawableBoundingBox2D(const BoundingBox2D& b) : BoundingBox2D(b), pointSize(2), colorPoint(), edgeWidth(1), colorEdge() {
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

void DrawableBoundingBox2D::drawEdges() const {
    viewer::drawLine2D(Point2Dd(min().x(), min().y()), Point2Dd(max().x(), min().y()), colorEdge, edgeWidth);
    viewer::drawLine2D(Point2Dd(max().x(), min().y()), Point2Dd(max().x(), max().y()), colorEdge, edgeWidth);
    viewer::drawLine2D(Point2Dd(max().x(), max().y()), Point2Dd(min().x(), max().y()), colorEdge, edgeWidth);
    viewer::drawLine2D(Point2Dd(min().x(), max().y()), Point2Dd(min().x(), min().y()), colorEdge, edgeWidth);
}

void DrawableBoundingBox2D::drawPoints() const {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(pointSize);
    glBegin(GL_POINTS);

    glColor3f(colorPoint.redF(), colorPoint.greenF(), colorPoint.blueF());

    glVertex2d(min().x(), min().y());
    glVertex2d(min().x(), max().y());
    glVertex2d(max().x(), min().y());
    glVertex2d(max().x(), max().y());

    glEnd();
}

}
