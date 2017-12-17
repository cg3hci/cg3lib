/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "drawable_bounding_box2d.h"

#include "../renderable_objects/renderable_objects.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

DrawableBoundingBox2D::DrawableBoundingBox2D(double thirdCoord) : BoundingBox2D(), pointSize(2), colorPoint(), edgeWidth(1), colorEdge(), thirdCoord(thirdCoord)
{
}

DrawableBoundingBox2D::DrawableBoundingBox2D(const BoundingBox2D& b, double thirdCoord) : BoundingBox2D(b), pointSize(2), colorPoint(), edgeWidth(1), colorEdge(), thirdCoord(thirdCoord)
{
}

DrawableBoundingBox2D::DrawableBoundingBox2D(const Point2Dd& min, const Point2Dd& max, double thirdCoord) : DrawableBoundingBox2D(BoundingBox2D(min, max), thirdCoord)
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
    viewer::drawLine(Pointd(min().x(), min().y(), thirdCoord), Pointd(max().x(), min().y(), thirdCoord), colorEdge, edgeWidth);
    viewer::drawLine(Pointd(max().x(), min().y(), thirdCoord), Pointd(max().x(), max().y(), thirdCoord), colorEdge, edgeWidth);
    viewer::drawLine(Pointd(max().x(), max().y(), thirdCoord), Pointd(min().x(), max().y(), thirdCoord), colorEdge, edgeWidth);
    viewer::drawLine(Pointd(min().x(), max().y(), thirdCoord), Pointd(min().x(), min().y(), thirdCoord), colorEdge, edgeWidth);
}

void DrawableBoundingBox2D::drawPoints() const {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(pointSize);
    glBegin(GL_POINTS);

    glColor3f(colorPoint.redF(), colorPoint.greenF(), colorPoint.blueF());

    glVertex3d(min().x(), min().y(), thirdCoord);
    glVertex3d(min().x(), max().y(), thirdCoord);
    glVertex3d(max().x(), min().y(), thirdCoord);
    glVertex3d(max().x(), max().y(), thirdCoord);

    glEnd();
}

}
