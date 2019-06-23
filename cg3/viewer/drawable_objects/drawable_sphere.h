/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_SPHERE_H
#define CG3_DRAWABLE_SPHERE_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/sphere.h>
#include <cg3/utilities/color.h>

namespace cg3 {

class DrawableSphere : public Sphere, public DrawableObject
{
public:
    DrawableSphere();
    DrawableSphere(
            const Point3d& _center,
            double _radius,
            QColor color = QColor(128,128,128),
            int precision = 10);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    QColor color;
    int precision;

};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_SPHERE_CPP "drawable_sphere.cpp"
#include CG3_DRAWABLE_SPHERE_CPP
#undef CG3_DRAWABLE_SPHERE_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_SPHERE_H
