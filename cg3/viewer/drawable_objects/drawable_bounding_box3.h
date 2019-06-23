/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_BOUNDING_BOX3_H
#define CG3_DRAWABLE_BOUNDING_BOX3_H

#include <cg3/geometry/bounding_box3.h>
#include <cg3/utilities/color.h>
#include "../interfaces/drawable_object.h"

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableBoundingBox class
 *
 * DrawableObject which draws a Bounding Box.
 */
class DrawableBoundingBox3 : public BoundingBox3, public DrawableObject
{
public:
	DrawableBoundingBox3();
	DrawableBoundingBox3(const BoundingBox3& bb);
	DrawableBoundingBox3(const Point3d& min, const Point3d& max);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

	void setEdgeColor(const QColor& c);
	void setEdgeWidth(int w);

protected:
	int edgeWidth;
	Color edgeColor;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_BOUNDING_BOX3_CPP "drawable_bounding_box3.cpp"
#include CG3_DRAWABLE_BOUNDING_BOX3_CPP
#undef CG3_DRAWABLE_BOUNDING_BOX3_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_BOUNDING_BOX3_H
