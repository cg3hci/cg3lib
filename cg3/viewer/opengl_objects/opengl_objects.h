/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_RENDERABLE_OBJECTS_H
#define CG3_RENDERABLE_OBJECTS_H

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

#include <QColor>
#include <cg3/geometry/point.h>

namespace cg3 {

namespace opengl {

void drawPoint(const Pointd& p, const QColor& c, int size = 8);

void drawSphere(
        const Pointd& center,
        float radius,
        const QColor& color,
        int precision = 4);

void drawCylinder(
        const Pointd& a,
        const Pointd& b,
        float top_radius,
        float bottom_radius,
        const QColor& color);

void drawLine(
        const Pointd &a,
        const Pointd &b,
        const QColor& c,
        int width = 3);

void drawDashedLine(
        const Pointd &a,
        const Pointd &b,
        const QColor& c,
        int width = 3);

void drawTriangle(
        const Pointd &p1,
        const Pointd &p2,
        const Pointd &p3,
        const QColor &c,
        int width = 3,
        bool fill = false);

void drawQuad(
        const Pointd & a,
        const Pointd& b,
        const Pointd&c,
        const Pointd& d,
        int width = 3);

void drawBox(const Pointd &min, const Pointd& max, const QColor& c, int width = 3);

void drawBox(const std::vector<Pointd> &p, const QColor& c, int width = 3);

void drawBox(
        const Pointd &p0,
        const Pointd &p1,
        const Pointd &p2,
        const Pointd &p3,
        const Pointd &p4,
        const Pointd &p5,
        const Pointd &p6,
        const Pointd &p7,
        const QColor& c,
        int width = 3);

} //namespace cg3::opengl
} //namespace cg3

#include "opengl_objects.tpp"

#endif // CG3_RENDERABLE_OBJECTS_H
