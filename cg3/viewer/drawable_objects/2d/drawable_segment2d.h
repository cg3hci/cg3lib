/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLESEGMENT2D_H
#define CG3_DRAWABLESEGMENT2D_H

#include <cg3/geometry/2d/segment2d.h>
#include "../../opengl_objects/2d/opengl_objects2d.h"
#include "../../interfaces/drawable_object.h"

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableSegment2D class
 */
class DrawableSegment2D : public Segment2Dd, public DrawableObject
{
public:
    DrawableSegment2D();
    DrawableSegment2D(const Segment2Dd& s);
    DrawableSegment2D(const Point2Dd& _p1, const Point2Dd& _p2);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setColor(const QColor& c);
    void setWidth(int w);

protected:
    QColor color;
    int width;
};

}

#endif // CG3_DRAWABLESEGMENT2D_H
