/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "renderable_objects2d.h"

/**
 * @brief Viewer::drawPoint2D
 *
 * Draws a point on the plane (coord z = 0 if 3D).
 *
 * @param p: coordinates of the point
 * @param c: color of the point
 * @param size: size of the point (default: 8)
 */
static inline void cg3::viewer::drawPoint2D(const Point2Dd& p, const QColor& c, int size = 8) {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(size);
    glBegin(GL_POINTS);

    glColor3f(c.redF(), c.greenF(), c.blueF());

    glVertex2d(p.x(), p.y());

    glEnd();
}

/**
 * @brief Viewer::drawLine2D
 *
 * Draws a line with opengl on the plane (z=0 if 3D).
 * It links the two points passed as parameters.
 *
 * @param a: first point of the line
 * @param b: second point of the line
 * @param c: color of the line
 * @param width: width of the line (default: 3)
 */
template <typename T1, typename T2>
static inline void cg3::viewer::drawLine2D(const Point2D<T1>& a, const Point2D<T2>& b, const QColor& c, int width) {

    glLineWidth(width);

    glBegin(GL_LINES);

    glColor3f(c.redF(), c.greenF(), c.blueF());

    glVertex2d(a.x(), a.y());
    glVertex2d(b.x(), b.y());

    glEnd();
}

static inline void cg3::viewer::drawTriangle2D(const std::array<Point2Dd, 3>& arr, const QColor& c, int width, bool fill) {
    drawTriangle2D(arr[0], arr[1], arr[2], c, width, fill);
}


static inline void cg3::viewer::drawTriangle2D(const Point2Dd &p1, const Point2Dd &p2, const Point2Dd &p3, const QColor &c, int width, bool fill) {
    if (width != 0){
        cg3::viewer::drawLine2D(p1, p2, c, width);
        cg3::viewer::drawLine2D(p2, p3, c, width);
        cg3::viewer::drawLine2D(p3, p1, c, width);
    }
    if (fill) {
        glBegin(GL_TRIANGLES); //Begin triangle coordinates
        glVertex2f(p1.x(), p1.y());
        glVertex2f(p2.x(), p2.y());
        glVertex2f(p3.x(), p3.y());
        glEnd(); //End triangle coordinates
    }
}

static inline void cg3::viewer::drawQuad2D(const std::array<Point2Dd, 4>& points, const QColor &c, int width, bool fill) {
    for (unsigned int i = 0; i < 4; i++){
        cg3::viewer::drawLine2D(points[i], points[(i+1)%4], c, width);
    }
    if (fill) {
        //find angle >=90°
        int pivot = -1;
        for (unsigned int i = 0; i < 4; i++){
            double angle = (points[(i-1)%4] - points[i]).dot(points[(i+1)%4] - points[i]);
            if (angle <= 0)
                pivot = i;
        }
        assert(pivot >= 0);
        cg3::viewer::drawTriangle2D(points[pivot], points[(pivot+1)%4], points[(pivot+2)%4], c, 0, true);
        cg3::viewer::drawTriangle2D(points[(pivot+2)%4], points[(pivot+3)%4], points[pivot], c, 0, true);
    }
}

static inline void cg3::viewer::drawQuad2D(const Point2Dd &p1, const Point2Dd &p2, const Point2Dd &p3, const Point2Dd &p4, const QColor &c, int width, bool fill) {
    std::array<Point2Dd, 4> arr = {p1, p2, p3, p4};
    cg3::viewer::drawQuad2D(arr, c, width, fill);
}
