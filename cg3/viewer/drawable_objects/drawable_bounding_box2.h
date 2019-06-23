/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_BOUNDING_BOX2_H
#define CG3_DRAWABLE_BOUNDING_BOX2_H

#include <cg3/geometry/bounding_box2.h>
#include <cg3/utilities/color.h>
#include "../interfaces/drawable_object.h"

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableBoundingBox2D class
 *
 * DrawableObject which draws a 2D Bounding Box.
 */
class DrawableBoundingBox2 : public BoundingBox2, public DrawableObject
{
public:
	DrawableBoundingBox2();
	DrawableBoundingBox2(const BoundingBox2& b);
	DrawableBoundingBox2(const Point2d& min, const Point2d& max);


    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

    void setEdgeColor(const QColor& c);
    void setPointColor(const QColor& c);
    void setEdgeWidth(int w);
    void setPointSize(int s);

private:

    void drawEdges() const;
    void drawPoints() const;

    int pointSize;
    Color pointColor;
    int edgeWidth;
    Color edgeColor;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_BOUNDING_BOX2_CPP "drawable_bounding_box2.cpp"
#include CG3_DRAWABLE_BOUNDING_BOX2_CPP
#undef CG3_DRAWABLE_BOUNDING_BOX2_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_BOUNDING_BOX2_H
