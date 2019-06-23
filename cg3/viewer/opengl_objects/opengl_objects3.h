/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_OPENGL_OBJECTS3_H
#define CG3_OPENGL_OBJECTS3_H

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

#include <cg3/geometry/point3.h>
#include <cg3/utilities/color.h>

namespace cg3 {

namespace opengl {

void drawPoint3(const Point3d& p, const Color& c, int size = 8);

void drawSphere(
        const Point3d& center,
        float radius,
        const Color& color,
        int precision = 4);

void drawCylinder(
        const Point3d& a,
        const Point3d& b,
        float top_radius,
        float bottom_radius,
        const Color& color,
        unsigned int slices = 50,
        unsigned int stacks = 10);

void drawArrow3(
        const Point3d& a,
        const Point3d& b,
        float bottom_radius,
        const Color& color,
        unsigned int slices = 50,
        unsigned int stacks = 10);

void drawLine3(
        const Point3d &a,
        const Point3d &b,
        const Color& c,
        int width = 3);

void drawSegment3(
        const Point3d &a,
        const Point3d &b,
        const Color& c,
        int width = 3);

void drawDashedLine3(
        const Point3d &a,
        const Point3d &b,
        const Color& c,
        int width = 3);

void drawTriangle(
        const Point3d &p1,
        const Point3d &p2,
        const Point3d &p3,
        const Color &c,
        int width = 3,
        bool fill = false);

void drawQuad3(
        const Point3d & a,
        const Point3d& b,
        const Point3d&c,
        const Point3d& d,
        int width = 3);

void drawBox3(const Point3d &min, const Point3d& max, const Color& c, int width = 3);

void drawBox3(const std::vector<Point3d> &p, const Color& c, int width = 3);

void drawBox3(
        const Point3d &p0,
        const Point3d &p1,
        const Point3d &p2,
        const Point3d &p3,
        const Point3d &p4,
        const Point3d &p5,
        const Point3d &p6,
        const Point3d &p7,
        const Color& c,
        int width = 3);

} //namespace cg3::opengl
} //namespace cg3

#include "opengl_objects3.cpp"

#endif // CG3_OPENGL_OBJECTS3_H
