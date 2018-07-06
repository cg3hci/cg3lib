/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_SEGMENT_H
#define CG3_DRAWABLE_SEGMENT_H

#include <cg3/geometry/segment.h>
#include <cg3/utilities/color.h>

#include "../interfaces/drawable_object.h"

namespace cg3 {

class DrawableSegment : public Segment3Dd, public DrawableObject
{
public:
    DrawableSegment();
    DrawableSegment(
            const Pointd& _p1,
            const Pointd& _p2,
            Color c = Color(),
            int width = 3);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

protected:
    Color color;
    unsigned int width;
};

} //namespace cg3

#endif // CG3_DRAWABLE_SEGMENT_H
