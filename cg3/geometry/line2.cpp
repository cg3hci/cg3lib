/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "line2.h"

namespace cg3 {

/**
 * @brief Empty constructor, initializes the m and q components of the line to zero.
 */
CG3_INLINE Line2::Line2() :
    _m(0),
    _q(0)
{
}

CG3_INLINE Line2::Line2(double m, double q) :
    _m(m),
    _q(q)
{
}

CG3_INLINE Line2::Line2(const Point2d& p1, const Point2d& p2)
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

CG3_INLINE Line2::Line2(const Segment2d& s) :
    Line2(s.p1(), s.p2())
{
}

CG3_INLINE Line2::Line2(double m, const Point2d& p) : _m(m)
{
    _q = p.y() - m*p.x();
}

/**
 * @brief Returns the m coefficient of the line.
 * @return the m coefficient of the line. Returns std::numeric_limits<double>::infinity() if the line is a vertical line.
 */
CG3_INLINE double Line2::m() const
{
    return _m;
}

/**
 * @brief Returns the m coefficient of the line.
 * @return te q coefficient of the line. Returns the x coordinate if the line is a vertical line.
 */
CG3_INLINE double Line2::q() const
{
    return _q;
}

CG3_INLINE double Line2::yValue(double x) const
{
    if (_m == std::numeric_limits<double>::infinity())
        return _m;
    return _m*x + _q;
}

CG3_INLINE double Line2::xValue(double y) const
{
    if (_m == std::numeric_limits<double>::infinity())
        return _q;
    return (y-_q)/_m;
}

CG3_INLINE Point2d Line2::intersection(const Line2& l) const
{
    if (_m != l._m){
        if (_m == std::numeric_limits<double>::infinity()){
            return Point2d(_q, l.yValue(_q));
        }
        if (l._m == std::numeric_limits<double>::infinity()){
            return Point2d(l._q, yValue(l._q));
        }
        return Point2d(
                    (l._q - _q) / (_m - l._m),
                    (_m*l._q - l._m*_q) / (_m - l._m));
    }
    return Point2d();
}

CG3_INLINE void Line2::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Line2D", binaryFile, _m, _q);
}

CG3_INLINE void Line2::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Line2D", binaryFile, _m, _q);
}

} //namespace cg3
