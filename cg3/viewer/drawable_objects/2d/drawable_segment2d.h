/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLESEGMENT2D_H
#define CG3_DRAWABLESEGMENT2D_H

#include <cg3/geometry/2d/segment2d.h>
#include "../../renderable_objects/2d/renderable_objects2d.h"
#include "../../interfaces/drawable_object.h"

namespace cg3 {

template <typename T>
class DrawableSegment2D : public Segment2D<T>, public DrawableObject{
    public:
        DrawableSegment2D();
        DrawableSegment2D(const Segment2D<T>& s);
        DrawableSegment2D(const Point2D<T>& p1, const Point2D<T>& p2);

        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;

        void setColor(const QColor& c);
        void setWidth(int w);

    protected:
        QColor color;
        int width;
};

typedef DrawableSegment2D<int> DrawableSegment2Di;
typedef DrawableSegment2D<float> DrawableSegment2Df;
typedef DrawableSegment2D<double> DrawableSegment2Dd;

}

#include "drawable_segment2d.tpp"

#endif // CG3_DRAWABLESEGMENT2D_H
