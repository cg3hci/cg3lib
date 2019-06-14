/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "opengl_objects2.h"

namespace cg3 {
namespace opengl {

/**
 * @brief drawPoint2D
 *
 * Draws a point on the plane (coord z = 0 if 3D).
 *
 * @param p: coordinates of the point
 * @param c: color of the point
 * @param size: size of the point (default: 8)
 * @ingroup cg3viewer
 */
inline void drawPoint2(const Point2d& p, const Color& c, int size = 8)
{
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
 * @ingroup cg3viewer
 */
inline void drawLine2(
        const Point2d& a,
        const Point2d& b,
        const Color& c,
        int width)
{

    glLineWidth(width);

    glBegin(GL_LINES);

    glColor3f(c.redF(), c.greenF(), c.blueF());

    glVertex2d(a.x(), a.y());
    glVertex2d(b.x(), b.y());

    glEnd();
}

/**
 * @brief cg3::viewer::drawTriangle2D
 * @param arr
 * @param c
 * @param width
 * @param fill
 * @ingroup cg3viewer
 */
inline void drawTriangle2(
        const std::array<Point2d, 3>& arr,
        const Color& c,
        int width,
        bool fill)
{
    drawTriangle2(arr[0], arr[1], arr[2], c, width, fill);
}

/**
 * @brief cg3::viewer::drawTriangle2D
 * @param p1
 * @param p2
 * @param p3
 * @param c
 * @param width
 * @param fill
 * @ingroup cg3viewer
 */
inline void drawTriangle2(
        const Point2d &p1,
        const Point2d &p2,
        const Point2d &p3,
        const Color &c,
        int width,
        bool fill)
{
    if (width != 0){
        cg3::opengl::drawLine2(p1, p2, c, width);
        cg3::opengl::drawLine2(p2, p3, c, width);
        cg3::opengl::drawLine2(p3, p1, c, width);
    }
    if (fill) {
        glBegin(GL_TRIANGLES); //Begin triangle coordinates
        glVertex2f(p1.x(), p1.y());
        glVertex2f(p2.x(), p2.y());
        glVertex2f(p3.x(), p3.y());
        glEnd(); //End triangle coordinates
    }
}

/**
 * @brief cg3::viewer::drawQuad2D
 * @param points
 * @param c
 * @param width
 * @param fill
 * @ingroup cg3viewer
 */
inline void drawQuad2(
        const std::array<Point2d, 4>& points,
        const Color &c,
        int width,
        bool fill)
{
    for (unsigned int i = 0; i < 4; i++){
        cg3::opengl::drawLine2(points[i], points[(i+1)%4], c, width);
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
        cg3::opengl::drawTriangle2(points[pivot], points[(pivot+1)%4], points[(pivot+2)%4], c, 0, true);
        cg3::opengl::drawTriangle2(points[(pivot+2)%4], points[(pivot+3)%4], points[pivot], c, 0, true);
    }
}

/**
 * @brief cg3::viewer::drawQuad2D
 * @param p1
 * @param p2
 * @param p3
 * @param p4
 * @param c
 * @param width
 * @param fill
 * @ingroup cg3viewer
 */
inline void drawQuad2(
        const Point2d &p1,
        const Point2d &p2,
        const Point2d &p3,
        const Point2d &p4,
        const Color &c,
        int width,
        bool fill)
{
    std::array<Point2d, 4> arr = {p1, p2, p3, p4};
    cg3::opengl::drawQuad2(arr, c, width, fill);
}

} //namespace cg3::opengl
} //namespac3 cg3
