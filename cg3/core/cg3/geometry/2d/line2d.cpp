/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "line2d.h"

namespace cg3 {

/**
 * @brief Empty constructor, initializes the m and q components of the line to zero.
 */
Line2D::Line2D() :
    _m(0),
    _q(0)
{
}

Line2D::Line2D(double m, double q) :
    _m(m),
    _q(q)
{
}

Line2D::Line2D(const Point2Dd& p1, const Point2Dd& p2)
{
    double det = p2.x() - p1.x();
    if (det != 0) {
        _m = (p2.y() - p1.y()) / det;
        _q = p1.y() - _m*p1.x();
    }
    else {
        _m = std::numeric_limits<double>::infinity();
        _q = p1.x();
    }
}

Line2D::Line2D(const Segment2Dd& s) :
    Line2D(s.p1(), s.p2())
{
}

Line2D::Line2D(double m, const Point2Dd& p) : _m(m)
{
    _q = p.y() - m*p.x();
}

/**
 * @brief Returns the m coefficient of the line.
 * @return the m coefficient of the line. Returns std::numeric_limits<double>::infinity() if the line is a vertical line.
 */
double Line2D::m() const
{
    return _m;
}

/**
 * @brief Returns the m coefficient of the line.
 * @return te q coefficient of the line. Returns the x coordinate if the line is a vertical line.
 */
double Line2D::q() const
{
    return _q;
}

double Line2D::yValue(double x) const
{
    if (_m == std::numeric_limits<double>::infinity())
        return _m;
    return _m*x + _q;
}

double Line2D::xValue(double y) const
{
    if (_m == std::numeric_limits<double>::infinity())
        return _q;
    return (y-_q)/_m;
}

Point2Dd Line2D::intersection(const Line2D& l) const
{
    if (_m != l._m){
        if (_m == std::numeric_limits<double>::infinity()){
            return Point2Dd(_q, l.yValue(_q));
        }
        if (l._m == std::numeric_limits<double>::infinity()){
            return Point2Dd(l._q, yValue(l._q));
        }
        return Point2Dd(
                    (l._q - _q) / (_m - l._m),
                    (_m*l._q - l._m*_q) / (_m - l._m));
    }
    return Point2Dd();
}

void Line2D::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Line2D", binaryFile, _m, _q);
}

void Line2D::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Line2D", binaryFile, _m, _q);
}

} //namespace cg3
