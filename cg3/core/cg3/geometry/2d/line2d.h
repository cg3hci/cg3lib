/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef LINE2D_H
#define LINE2D_H

#include "point2d.h"

namespace cg3 {

/**
 * @brief The Line2D class
 *
 * It models a 2D line coded in the form y = mx + q.
 * Vertical lines are stored with m = std::numeric_limits<double>::infinity() and q = the x coordinate of the line.
 */
class Line2D : public SerializableObject{
    public:
        Line2D();
        Line2D(double m, double q);
        Line2D(const Point2Dd& p1, const Point2Dd& p2);
        Line2D(double m, const Point2Dd& p);
        double m() const;
        double q() const;

        double yValue(double x) const;
        double xValue(double y) const;

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    private:
        double _m;
        double _q;
};

}

#endif // LINE2D_H
