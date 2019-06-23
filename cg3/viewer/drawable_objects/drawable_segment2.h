/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_SEGMENT2_H
#define CG3_DRAWABLE_SEGMENT2_H

#include <cg3/geometry/segment2.h>
#include "../opengl_objects/opengl_objects2.h"
#include "../interfaces/drawable_object.h"

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableSegment2D class
 */
class DrawableSegment2 : public Segment2d, public DrawableObject
{
public:
	DrawableSegment2();
	DrawableSegment2(const Segment2d& s);
	DrawableSegment2(const Point2d& _p1, const Point2d& _p2);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

    void setColor(const QColor& c);
    void setWidth(int w);

protected:
    QColor color;
    int width;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_SEGMENT2_CPP "drawable_segment2.cpp"
#include CG3_DRAWABLE_SEGMENT2_CPP
#undef CG3_DRAWABLE_SEGMENT2_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_SEGMENT2_H
