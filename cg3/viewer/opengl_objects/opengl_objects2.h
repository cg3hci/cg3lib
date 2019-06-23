/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_OPENGL_OBJECTS2_H
#define CG3_OPENGL_OBJECTS2_H

#ifdef WIN32
#include "windows.h"
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cg3/geometry/point2.h>
#include <cg3/utilities/color.h>

namespace cg3 {
namespace opengl {

void drawPoint2(const Point2d& p, const Color& c, int size);

void drawLine2(
        const Point2d&a,
        const Point2d& b,
        const Color& c,
        int width = 3);

void drawTriangle2(
        const std::array<Point2d, 3>& arr,
        const Color& c,
        int width = 3,
        bool fill = false);

void drawTriangle2(
        const Point2d& p1,
        const Point2d& p2,
        const Point2d& p3,
        const Color& c,
        int width = 3,
        bool fill = false);

void drawQuad2(
        const std::array<Point2d, 4>& arr,
        const Color& c,
        int width = 3,
        bool fill = false);

void drawQuad2(
        const Point2d& p1,
        const Point2d& p2,
        const Point2d& p3,
        const Point2d& p4,
        const Color& c,
        int width = 3,
        bool fill = false);

} //namespace cg3::opengl
} //namespace cg3

#include "opengl_objects2.cpp"

#endif // CG3_OPENGL_OBJECTS2_H
