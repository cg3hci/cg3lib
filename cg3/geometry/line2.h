/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LINE2_H
#define CG3_LINE2_H

#include "point2.h"
#include "segment2.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief The Line2D class
 *
 * It models a 2D line coded in the form y = mx + q.
 * Vertical lines are stored with m = std::numeric_limits<double>::infinity() and q = the x coordinate of the line.
 */
class Line2 : public SerializableObject
{
public:
	Line2();
	Line2(double m, double q);
	Line2(const Point2d& p1, const Point2d& p2);
	Line2(const Segment2d& s);
	Line2(double m, const Point2d& p);
    double m() const;
    double q() const;

    double yValue(double x) const;
    double xValue(double y) const;

	Point2d intersection(const cg3::Line2& l) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

private:
    double _m;
    double _q;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_LINE2_CPP "line2.cpp"
#include CG3_LINE2_CPP
#undef CG3_LINE2_CPP
#endif

#endif // CG3_LINE2_H
