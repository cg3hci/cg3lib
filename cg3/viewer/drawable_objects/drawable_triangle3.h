/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_TRIANGLE3_H
#define CG3_DRAWABLE_TRIANGLE3_H

#include <cg3/geometry/triangle3.h>
#include <cg3/utilities/color.h>

#include "../interfaces/drawable_object.h"

namespace cg3 {

class DrawableTriangle3 : public Triangle3d, public DrawableObject
{
public:
	DrawableTriangle3();
	DrawableTriangle3(
            const Point3d& p1,
            const Point3d& p2,
            const Point3d& p3,
            Color c = Color(),
            unsigned int width = 3,
            bool fill = false);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    Color color;
    unsigned int width;
    bool fill;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_TRIANGLE3_CPP "drawable_triangle3.cpp"
#include CG3_DRAWABLE_TRIANGLE3_CPP
#undef CG3_DRAWABLE_TRIANGLE3_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_TRIANGLE3_H
