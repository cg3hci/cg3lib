/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_polygon2.h"

#include <cg3/viewer/opengl_objects/opengl_objects2.h>

namespace cg3 {

CG3_INLINE DrawablePolygon2::DrawablePolygon2() :
    pointColor(0,0,0),
    segmentColor(0,0,0),
    pointSize(3),
    segmentSize(1)
{
}

CG3_INLINE void DrawablePolygon2::setPointColor(const cg3::Color& value)
{
    pointColor = value;
}

CG3_INLINE void DrawablePolygon2::setSegmentColor(const cg3::Color& value)
{
    segmentColor = value;
}

CG3_INLINE void DrawablePolygon2::setPointSize(int value)
{
    pointSize = value;
}

CG3_INLINE void DrawablePolygon2::setSegmentSize(int value)
{
    segmentSize = value;
}

CG3_INLINE void DrawablePolygon2::draw() const
{
    if (pol.size() > 0){
        for (unsigned int i = 0; i < pol.size()-1; i++){
			cg3::opengl::drawPoint2(pol[i], pointColor, pointSize);
			cg3::opengl::drawLine2(pol[i], pol[i+1], segmentColor, segmentSize);
        }
		cg3::opengl::drawPoint2(pol[pol.size()-1], pointColor, pointSize);
		cg3::opengl::drawLine2(pol[pol.size()-1], pol[0], segmentColor, segmentSize);
    }
}

CG3_INLINE Point3d DrawablePolygon2::sceneCenter() const
{
    return cg3::Point3d(bb.center().x(), bb.center().y());
}

CG3_INLINE double DrawablePolygon2::sceneRadius() const
{
    return bb.diag() / 2;
}

} //namespace cg3
