/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_BOUNDINGBOX2D_H
#define CG3_DRAWABLE_BOUNDINGBOX2D_H

#include <cg3/geometry/2d/bounding_box2d.h>
#include <cg3/utilities/color.h>
#include "../../interfaces/drawable_object.h"

namespace cg3 {

/**
 * @brief The DrawableBoundingBox2D class
 *
 * DrawableObject which draws a 2D Bounding Box.
 */
class DrawableBoundingBox2D : public BoundingBox2D, public DrawableObject {
    public:
        DrawableBoundingBox2D();
        DrawableBoundingBox2D(const BoundingBox2D& b);
        DrawableBoundingBox2D(const Point2Dd& min, const Point2Dd& max);


        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;

        void setEdgeColor(const QColor& c);
        void setPointColor(const QColor& c);
        void setEdgeWidth(int w);
        void setPointSize(int s);

    private:

        void drawEdges() const;
        void drawPoints() const;

        int pointSize;
        Color pointColor;
        int edgeWidth;
        Color edgeColor;
};

}

#endif // CG3_DRAWABLE_BOUNDINGBOX2D_H
