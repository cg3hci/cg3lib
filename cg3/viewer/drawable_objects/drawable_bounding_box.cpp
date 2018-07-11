/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "drawable_bounding_box.h"

#include "../opengl_objects/opengl_objects.h"


namespace cg3 {

DrawableBoundingBox::DrawableBoundingBox() :
    BoundingBox(),
    edgeWidth(1),
    edgeColor()
{
}

DrawableBoundingBox::DrawableBoundingBox(const BoundingBox& bb) :
    BoundingBox(bb),
    edgeWidth(1),
    edgeColor()
{
}

DrawableBoundingBox::DrawableBoundingBox(const Pointd& min, const Pointd& max) :
    DrawableBoundingBox(BoundingBox(min, max))
{
}

void DrawableBoundingBox::draw() const
{
    opengl::drawBox(_min, _max, edgeColor, edgeWidth);
}

Pointd DrawableBoundingBox::sceneCenter() const
{
    return center();
}

double DrawableBoundingBox::sceneRadius() const
{
    return diag() / 2;
}

void DrawableBoundingBox::setEdgeColor(const QColor& c)
{
    edgeColor = c;
}

void DrawableBoundingBox::setEdgeWidth(int w)
{
    edgeWidth = w;
}

} //namespace cg3
