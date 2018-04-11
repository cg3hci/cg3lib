/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_TRIANGLE_H
#define CG3_DRAWABLE_TRIANGLE_H

#include <cg3/geometry/triangle.h>
#include <cg3/utilities/color.h>

#include "../interfaces/drawable_object.h"

namespace cg3 {

class DrawableTriangle : public Triangle3Dd, public DrawableObject
{
public:
    DrawableTriangle();
    DrawableTriangle(
            const Pointd& p1,
            const Pointd& p2,
            const Pointd& p3,
            Color c = Color(),
            unsigned int width = 3,
            bool fill = false);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

protected:
    Color color;
    unsigned int width;
    bool fill;
};

} //namespace cg3

#endif // CG3_DRAWABLE_TRIANGLE_H
