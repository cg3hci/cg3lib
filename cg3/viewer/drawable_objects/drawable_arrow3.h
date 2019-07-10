/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_ARROW3_H
#define CG3_DRAWABLE_ARROW3_H

#include "../interfaces/drawable_object.h"
#include <cg3/io/serializable_object.h>
#include <cg3/utilities/color.h>

namespace cg3 {

class DrawableArrow3 : public DrawableObject, public SerializableObject
{
public:
	DrawableArrow3();
	DrawableArrow3(const Point3d& a,
				   const Point3d& b,
				   double radius,
				   QColor color = QColor(128,128,128),
				   unsigned int slices = 50,
				   unsigned int stacks = 10);

	// DrawableObject interface
	void draw() const;
	Point3d sceneCenter() const;
	double sceneRadius() const;

	// SerializableObject interface
	void serialize(std::ofstream &binaryFile) const;
	void deserialize(std::ifstream &binaryFile);

protected:
	cg3::Point3d a, b;
	double radius;
	QColor color;
	unsigned int slices;
	unsigned int stacks;
};

} //namesapce cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_ARROW3_CPP "drawable_arrow3.cpp"
#include CG3_DRAWABLE_ARROW3_CPP
#undef CG3_DRAWABLE_ARROW3_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_ARROW3_H
