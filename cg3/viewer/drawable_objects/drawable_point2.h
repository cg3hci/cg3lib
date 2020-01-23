/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_POINT2_H
#define CG3_DRAWABLE_POINT2_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/point3.h>
#include <cg3/utilities/color.h>

#include "../interfaces/drawable_object.h"

namespace cg3 {

class DrawablePoint2 : public Point2d, public DrawableObject
{
public:
    DrawablePoint2(
            double x = 0,
            double y = 0,
            Color c = Color(),
            unsigned int size = 3);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    Color color;
    unsigned int size;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_POINT2_CPP "drawable_point2.cpp"
#include CG3_DRAWABLE_POINT2_CPP
#undef CG3_DRAWABLE_POINT2_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_POINT2_H
