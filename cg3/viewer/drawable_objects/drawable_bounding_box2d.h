/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_DRAWABLE_BOUNDINGBOX2D_H
#define CG3_DRAWABLE_BOUNDINGBOX2D_H

#include <cg3/geometry/2d/bounding_box2d.h>
#include <cg3/utilities/color.h>
#include "../interfaces/drawable_object.h"

namespace cg3 {

class DrawableBoundingBox2D : public BoundingBox2D, public DrawableObject
{
    public:
        DrawableBoundingBox2D(double thirdCoord = 0);
        DrawableBoundingBox2D(const BoundingBox2D& b, double thirdCoord = 0);
        DrawableBoundingBox2D(const Point2Dd& min, const Point2Dd& max, double thirdCoord = 0);


        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;

    private:

        void drawEdges() const;
        void drawPoints() const;

        int pointSize;
        Color colorPoint;
        int edgeWidth;
        Color colorEdge;

        double thirdCoord;
};

}

#endif // CG3_DRAWABLE_BOUNDINGBOX2D_H
