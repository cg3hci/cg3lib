/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_CYLINDER_H
#define CG3_DRAWABLE_CYLINDER_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/cylinder.h>
#include <cg3/utilities/color.h>

namespace cg3 {

class DrawableCylinder : public Cylinder, public DrawableObject
{
public:
    DrawableCylinder();
    DrawableCylinder(
            const Point3d& a,
            const Point3d& b,
            double _radius,
            QColor color = QColor(128,128,128),
            unsigned int slices = 50,
            unsigned int stacks = 10);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    QColor color;
    unsigned int slices;
    unsigned int stacks;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_CYLINDER_CPP "drawable_cylinder.cpp"
#include CG3_DRAWABLE_CYLINDER_CPP
#undef CG3_DRAWABLE_CYLINDER_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_CYLINDER_H
