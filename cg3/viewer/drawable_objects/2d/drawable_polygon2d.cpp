/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_polygon2d.h"

#include <cg3/viewer/opengl_objects/2d/opengl_objects2d.h>

namespace cg3 {

DrawablePolygon2D::DrawablePolygon2D() :
    pointColor(0,0,0),
    segmentColor(0,0,0),
    pointSize(3),
    segmentSize(1)
{
}

void DrawablePolygon2D::setPointColor(const cg3::Color& value)
{
    pointColor = value;
}

void DrawablePolygon2D::setSegmentColor(const cg3::Color& value)
{
    segmentColor = value;
}

void DrawablePolygon2D::setPointSize(int value)
{
    pointSize = value;
}

void DrawablePolygon2D::setSegmentSize(int value)
{
    segmentSize = value;
}

void DrawablePolygon2D::draw() const
{
    for (unsigned int i = 0; i < pol.size()-1; i++){
        cg3::opengl::drawPoint2D(pol[i], pointColor, pointSize);
        cg3::opengl::drawLine2D(pol[i], pol[i+1], segmentColor, segmentSize);
    }
    if (pol.size() > 0){
        cg3::opengl::drawPoint2D(pol[pol.size()-1], pointColor, pointSize);
        cg3::opengl::drawLine2D(pol[pol.size()-1], pol[0], segmentColor, segmentSize);
    }
}

Pointd DrawablePolygon2D::sceneCenter() const
{
    return cg3::Pointd(bb.center().x(), bb.center().y());
}

double DrawablePolygon2D::sceneRadius() const
{
    return bb.diag() / 2;
}

} //namespace cg3
