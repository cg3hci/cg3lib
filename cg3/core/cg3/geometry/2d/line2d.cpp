/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "line2d.h"

namespace cg3 {

Line2D::Line2D() : _m(0), _q(0) {
}

Line2D::Line2D(double m, double q) : _m(m), _q(q) {
}

Line2D::Line2D(const Point2Dd& p1, const Point2Dd& p2) {
    double det = p2.x() - p1.x();
    if (det != 0) {
        _m = (p2.y() - p1.y()) / det;
        _q = p1.y() - _m*p1.x();
    }
    else {
        _m = std::numeric_limits<double>::infinity();
        _q = p1.x();
    }
    //
}

Line2D::Line2D(double m, const Point2Dd& p) : _m(m) {
    _q = p.y() - m*p.x();
}

/**
 * @brief Line2D::m
 * @return the m coefficient of the line. Returns std::numeric_limits<double>::infinity() if the line is a vertical line.
 */
double Line2D::m() const {
    return _m;
}

/**
 * @brief Line2D::q
 * @return te q coefficient of the line. Returns the x coordinate if the line is a vertical line.
 */
double Line2D::q() const {
    return _q;
}

double Line2D::yValue(double x) const {
    if (_m == std::numeric_limits<double>::infinity())
        return _m;
    return _m*x + _q;
}

double Line2D::xValue(double y) const {
    if (_m == std::numeric_limits<double>::infinity())
        return _q;
    return (y-_q)/_m;
}

void Line2D::serialize(std::ofstream& binaryFile) const {
    cg3::serializeObjectAttributes("cg3Line2D", binaryFile, _m, _q);
}

void Line2D::deserialize(std::ifstream& binaryFile) {
    cg3::deserializeObjectAttributes("cg3Line2D", binaryFile, _m, _q);
}

}
