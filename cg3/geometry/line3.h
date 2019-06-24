/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#ifndef CG3_LINE3_H
#define CG3_LINE3_H

#include "point3.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief The Line class
 */
class Line3 : public SerializableObject
{
public:
	Line3();
	Line3(const Point3d& p0, const Vec3d& dir);
    const Vec3d& dir() const;
    const Point3d& startingPoint() const;

    bool pointLiesOnLine(const Point3d &p) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    Point3d p0;
    Vec3d _dir;
};

} //namespace cg3

//hash specialization
namespace std {

template <>
struct hash<cg3::Line3> {
	size_t operator()(const cg3::Line3& k) const;
};

} //namespace std

#ifndef CG3_STATIC
#define CG3_LINE3_CPP "line3.cpp"
#include CG3_LINE3_CPP
#undef CG3_LINE3_CPP
#endif

#endif // LINE3_H
