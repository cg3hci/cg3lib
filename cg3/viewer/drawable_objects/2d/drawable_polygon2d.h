/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLEPOLYGON2D_H
#define CG3_DRAWABLEPOLYGON2D_H

#include <cg3/geometry/2d/polygon2d.h>
#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/utilities/color.h>

namespace cg3 {

class DrawablePolygon2D : public Polygon2D, public DrawableObject
{
public:
    DrawablePolygon2D();

    void setPointColor(const cg3::Color& value);
    void setSegmentColor(const cg3::Color& value);
    void setPointSize(int value);
    void setSegmentSize(int value);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

protected:
    cg3::Color pointColor;
    cg3::Color segmentColor;
    int pointSize;
    int segmentSize;
};

} //namespace cg3

#endif // CG3_DRAWABLEPOLYGON2D_H
