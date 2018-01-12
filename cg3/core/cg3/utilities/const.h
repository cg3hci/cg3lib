/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CONST_H
#define CG3_CONST_H

#include "../geometry/point.h"
#include "../utilities/color.h"

namespace cg3 {

static const double CG3_EPSILON = 1e-6;

static const std::array<Vec3, 6> AXIS {
    Vec3( 1, 0, 0),
    Vec3( 0, 1, 0),
    Vec3( 0, 0 ,1),
    Vec3(-1, 0, 0),
    Vec3( 0,-1, 0),
    Vec3( 0, 0,-1),
};

static const std::vector<Color> PASTEL_COLORS = {
    Color(182, 215, 168), //
    Color(159, 197, 232), //
    Color(234, 153, 153), //
    Color(255, 229, 153), //
    Color(162, 196, 201), //
    Color(213, 166, 189), //
    Color(164, 194, 244), //
    Color(221, 126, 107), //
    Color(249, 203, 156), //
    Color(180, 167, 214) //
};


}

#endif // CONST_H
