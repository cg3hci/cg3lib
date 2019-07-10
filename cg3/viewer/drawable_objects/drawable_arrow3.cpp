/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_arrow3.h"
#include "../opengl_objects/opengl_objects3.h"
#include <cg3/io/serialize.h>

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

CG3_INLINE DrawableArrow3::DrawableArrow3()
{
}

DrawableArrow3::DrawableArrow3(
		const Point3d &a,
		const Point3d &b,
		double radius,
		QColor color,
		unsigned int slices,
		unsigned int stacks) :
	a(a),
	b(b),
	radius(radius),
	color(color),
	slices(slices),
	stacks(stacks)
{
}

CG3_INLINE void DrawableArrow3::draw() const
{
	cg3::opengl::drawArrow3(a, b, radius, color, slices, stacks);
}

CG3_INLINE Point3d DrawableArrow3::sceneCenter() const
{
	return (a+b) * 0.5;
}

CG3_INLINE double DrawableArrow3::sceneRadius() const
{
	return a.dist(b) * 0.5;
}

void DrawableArrow3::serialize(std::ofstream &binaryFile) const
{
	cg3::serializeObjectAttributes("cg3DrawableArrow3", binaryFile, a, b, radius, color, slices, stacks);
}

void DrawableArrow3::deserialize(std::ifstream &binaryFile)
{
	cg3::deserializeObjectAttributes("cg3DrawableArrow3", binaryFile, a, b, radius, color, slices, stacks);
}

}
