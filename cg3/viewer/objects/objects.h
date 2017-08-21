#ifndef VIEWER_OBJECTS_H
#define VIEWER_OBJECTS_H

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

#include <cmath>
#include <QColor>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

namespace cg3 {

namespace Viewer{

static inline void drawSphere(const Pointd& center, float radius, const QColor& color, int precision = 4);

static inline void drawPoint2D(const Point2Dd& p, const QColor& c, int size);

static inline void drawCylinder(const Pointd& a, const Pointd& b, float top_radius, float bottom_radius, const QColor& color);

static inline void drawLine(const Pointd &a, const Pointd &b, const QColor& c, int width = 3);

static inline void drawLine2D(const Point2Dd&a, const Point2Dd& b, const QColor& c, int width = 3);

static inline void drawBox(const Pointd &min, const Pointd& max, const QColor& c, int width = 3);

static inline void drawBox(const std::vector<Pointd> &p, const QColor& c, int width = 3);

static inline void drawBox(const Pointd &p0, const Pointd &p1, const Pointd &p2, const Pointd &p3, const Pointd &p4, const Pointd &p5, const Pointd &p6, const Pointd &p7, const QColor& c, int width = 3);

}

}

#include "objects.cpp"

#endif // VIEWER_OBJECTS_H
