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

#include <QColor>
#include <cg3/geometry/2d/point2d.h>

namespace cg3 {

namespace viewer {

static inline void drawPoint2D(const Point2Dd& p, const QColor& c, int size);

template<typename T1, typename T2>
static inline void drawLine2D(const Point2D<T1>&a, const Point2D<T2>& b, const QColor& c, int width = 3);

static inline void drawTriangle2D(const std::array<Point2Dd, 3>& arr, const QColor& c, int width = 3, bool fill = false);

static inline void drawTriangle2D(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3, const QColor& c, int width = 3, bool fill = false);

static inline void drawQuad2D(const std::array<Point2Dd, 4>& arr, const QColor& c, int width = 3, bool fill = false);

static inline void drawQuad2D(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3, const Point2Dd& p4, const QColor& c, int width = 3, bool fill = false);

}

}

#include "renderable_objects2d.tpp"

#endif // CG3_RENDERABLE_OBJECTS2D_H
