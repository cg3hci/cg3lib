/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_SEGMENT3_H
#define CG3_DRAWABLE_SEGMENT3_H

#include <cg3/geometry/segment3.h>
#include <cg3/utilities/color.h>

#include "../interfaces/drawable_object.h"

namespace cg3 {

class DrawableSegment3 : public Segment3d, public DrawableObject
{
public:
	DrawableSegment3();
	DrawableSegment3(
            const Point3d& _p1,
            const Point3d& _p2,
            Color c = Color(),
            int width = 3);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    Color color;
    unsigned int width;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_SEGMENT3_CPP "drawable_segment3.cpp"
#include CG3_DRAWABLE_SEGMENT3_CPP
#undef CG3_DRAWABLE_SEGMENT3_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_SEGMENT3_H
