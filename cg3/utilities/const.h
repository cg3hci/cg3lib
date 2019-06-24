/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CONST_H
#define CG3_CONST_H

#include "../geometry/bounding_box3.h"
#include "../utilities/color.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief CG3_EPSILON
 */
static const double CG3_EPSILON = 1e-6;
static const double EPSILON = 1e-6;

/**
 * @ingroup cg3core
 * @brief AXIS
 */
static const std::array<Vec3d, 6> AXIS
{
    Vec3d( 1, 0, 0),
    Vec3d( 0, 1, 0),
    Vec3d( 0, 0 ,1),
    Vec3d(-1, 0, 0),
    Vec3d( 0,-1, 0),
    Vec3d( 0, 0,-1),
};

static const cg3::BoundingBox3 unitBoundingBox(
        cg3::Point3d(-1,-1,-1),
        cg3::Point3d( 1, 1, 1));

static const cg3::Vec3d X_AXIS(1, 0, 0);
static const cg3::Vec3d Y_AXIS(0, 1, 0);
static const cg3::Vec3d Z_AXIS(0, 0, 1);

/**
 * @ingroup cg3core
 * @brief PASTEL_COLORS
 */
static const std::vector<Color> PASTEL_COLORS =
{
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

static const cg3::Color RED(255,0,0);
static const cg3::Color GREEN(0,255,0);
static const cg3::Color BLUE(0,0,255);
static const cg3::Color YELLOW(255,255,0);
static const cg3::Color CYAN(0,255,255);
static const cg3::Color MAGENTA(255,0,255);
static const cg3::Color WHITE(255,255,255);
static const cg3::Color BLACK(0,0,0);
static const cg3::Color GREY(128,128,128);

} //namespace cg3

#endif // CONST_H
