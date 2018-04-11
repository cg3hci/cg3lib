/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_RENDERABLE_OBJECTS_2D_H
#define CG3_RENDERABLE_OBJECTS_2D_H

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

#include <cg3/geometry/2d/point2d.h>
#include <cg3/utilities/color.h>

namespace cg3 {
namespace opengl {

void drawPoint2D(const Point2Dd& p, const Color& c, int size);

void drawLine2D(
        const Point2Dd&a,
        const Point2Dd& b,
        const Color& c,
        int width = 3);

void drawTriangle2D(
        const std::array<Point2Dd, 3>& arr,
        const Color& c,
        int width = 3,
        bool fill = false);

void drawTriangle2D(
        const Point2Dd& p1,
        const Point2Dd& p2,
        const Point2Dd& p3,
        const Color& c,
        int width = 3,
        bool fill = false);

void drawQuad2D(
        const std::array<Point2Dd, 4>& arr,
        const Color& c,
        int width = 3,
        bool fill = false);

void drawQuad2D(
        const Point2Dd& p1,
        const Point2Dd& p2,
        const Point2Dd& p3,
        const Point2Dd& p4,
        const Color& c,
        int width = 3,
        bool fill = false);

} //namespace cg3::opengl
} //namespace cg3

#include "opengl_objects2d.tpp"

#endif // CG3_RENDERABLE_OBJECTS2D_H
