#ifndef CG3_CONST_H
#define CG3_CONST_H

#include "../geometry/point.h"
#include "../data_structures/color.h"

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
