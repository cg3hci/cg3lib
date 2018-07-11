/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_BOUNDING_BOX_H
#define CG3_DRAWABLE_BOUNDING_BOX_H

#include <cg3/geometry/bounding_box.h>
#include <cg3/utilities/color.h>
#include "../interfaces/drawable_object.h"

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableBoundingBox class
 *
 * DrawableObject which draws a Bounding Box.
 */
class DrawableBoundingBox : public BoundingBox, public DrawableObject
{
public:
    DrawableBoundingBox();
    DrawableBoundingBox(const BoundingBox& bb);
    DrawableBoundingBox(const Pointd& min, const Pointd& max);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setEdgeColor(const QColor& c);
    void setEdgeWidth(int w);

private:
    int edgeWidth;
    Color edgeColor;
};

} //namespace cg3

#endif // CG3_DRAWABLE_BOUNDING_BOX_H
