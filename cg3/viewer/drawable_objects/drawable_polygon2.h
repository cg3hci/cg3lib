/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_POLYGON2_H
#define CG3_DRAWABLE_POLYGON2_H

#include <cg3/geometry/polygon2.h>
#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/utilities/color.h>

namespace cg3 {

class DrawablePolygon2 : public Polygon2, public DrawableObject
{
public:
	DrawablePolygon2();

    void setPointColor(const cg3::Color& value);
    void setSegmentColor(const cg3::Color& value);
    void setPointSize(int value);
    void setSegmentSize(int value);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    cg3::Color pointColor;
    cg3::Color segmentColor;
    int pointSize;
    int segmentSize;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_POLYGON2_CPP "drawable_polygon2.cpp"
#include CG3_DRAWABLE_POLYGON2_CPP
#undef CG3_DRAWABLE_POLYGON2_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_POLYGON2_H
