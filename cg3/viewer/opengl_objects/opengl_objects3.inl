/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "opengl_objects3.h"

namespace cg3 {
namespace opengl {

/**
 * @brief Draws a point on the plane (coord z = 0 if 3D).
 *
 * @param p: coordinates of the point
 * @param c: color of the point
 * @param size: size of the point (default: 8)
 * @ingroup cg3viewer
 */
inline void drawPoint3(
        const Point3d& p,
        const Color &c,
        int size)
{
    glEnable(GL_POINT_SMOOTH);
    glPointSize(size);
    glBegin(GL_POINTS);

    glColor3f(c.redF(), c.greenF(), c.blueF());

    glVertex3d(p.x(), p.y(), p.z());

    glEnd();
}

/**
 * @brief Draws a sphere with opengl
 *
 * @param center: coordinates of the center of the sphere
 * @param radius: radius of the sphere
 * @param color: color of the sphere
 * @param precision: precision of the rendered sphere (default: 4)
 * @ingroup cg3viewer
 */
inline void drawSphere(
        const Point3d  & center,
        float         radius,
        const Color &color,
        int precision)
{
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glColor3f(color.redF(), color.greenF(), color.blueF());
    glPushMatrix();
    glTranslated(center.x(), center.y(), center.z());
    GLUquadric *sphere = gluNewQuadric();
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricOrientation(sphere, GLU_OUTSIDE);
    gluSphere(sphere, radius, precision, precision);
    glPopMatrix();

}

/**
 * @brief Viewer::drawCylinder
 *
 * Draws a cylinder with opengl.
 * The cylinder links the two points passed as parameters
 *
 * @param a: first point of the cylinder
 * @param b: second point of the cylinder
 * @param top_radius: radius at the "a" point
 * @param bottom_radius: radius at the "b" point
 * @param color: color of the cylinder
 * @ingroup cg3viewer
 */
inline void drawCylinder(
        const Point3d  & a,
        const Point3d  & b,
        float         top_radius,
        float         bottom_radius,
        const Color &color,
        unsigned int slices,
        unsigned int stacks)
{
    Vec3d dir     = b - a; dir.normalize();
    Point3d z       = Point3d(0,0,1);
    Vec3d normal  = dir.cross(z);
    double angle = acos(dir.dot(z)) * 180 / M_PI;

	bool cull = glIsEnabled(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//cylinder
	glColor3f(color.redF(), color.greenF(), color.blueF());
	glPushMatrix();
	glTranslated(a.x(), a.y(), a.z());
	glRotatef(-angle, normal.x(), normal.y(), normal.z());

	GLUquadric *cylinder = gluNewQuadric();
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricOrientation(cylinder, GLU_OUTSIDE);
    gluCylinder(cylinder, top_radius, bottom_radius, (a-b).length(), slices, stacks);

	GLUquadric *disk1 = gluNewQuadric();
	gluQuadricNormals(disk1, GLU_SMOOTH);
	gluQuadricOrientation(disk1, GLU_INSIDE);
	gluDisk(disk1, 0, top_radius, slices, stacks);

	/*glTranslated((b-a).x(), (b-a).y(), (b-a).z());
	GLUquadric *disk2 = gluNewQuadric();
	gluQuadricNormals(disk2, GLU_SMOOTH);
	gluQuadricOrientation(disk2, GLU_OUTSIDE);
	gluDisk(disk2, 0, bottom_radius, slices, stacks);*/

	glColor3f(0, 0, 0);
	glPopMatrix();
	if (cull)
		glEnable(GL_CULL_FACE);
}

/**
 * @brief drawArrow
 * @param a
 * @param b
 * @param bottom_radius
 * @param color
 * @param slices
 * @param stacks
 */
inline void drawArrow3(
        const Point3d& a,
        const Point3d& b,
        float bottom_radius,
        const Color& color,
        unsigned int slices,
        unsigned int stacks)
{
    Point3d midPoint = (a * 1 + b * 9) / 10;
    drawCylinder(a, midPoint, bottom_radius, bottom_radius, color, slices, stacks);
    drawCylinder(midPoint, b, bottom_radius*2, 0, color, slices, stacks);
}

/**
 * @brief Viewer::drawLine
 *
 * Draws a line with opengl that links the two points passed as parameters.
 *
 * @param a: first point of the line
 * @param b: second point of the line
 * @param c: color of the line
 * @param width: width of the line (default: 3)
 * @ingroup cg3viewer
 */
inline void drawLine3(
        const Point3d &a,
        const Point3d &b,
        const Color &c,
        int width)
{
    glLineWidth(width);
    glColor3f(c.redF(), c.greenF(), c.blueF());
    glBegin(GL_LINES);
    glVertex3f(a.x(), a.y(), a.z());
    glVertex3f(b.x(), b.y(), b.z());
    glEnd();
	glColor3f(0, 0, 0);
}

/**
 * @brief
 * @see cg3::opengl::drawLine
 */
inline void drawSegment3(
        const Point3d &a,
        const Point3d &b,
        const Color &c,
        int width)
{
	drawLine3(a, b, c, width);
}

/**
 * @brief Viewer::drawDashedLine
 *
 * Draws a dashed line with opengl that links the two points passed as parameters.
 *
 * @param a: first point of the dashed line
 * @param b: second point of the dashed line
 * @param c: color of the dashed line
 * @param width: width of the dashed line (default: 3)
 * @ingroup cg3viewer
 */
inline void drawDashedLine3(
        const Point3d &a,
        const Point3d &b,
        const Color& c,
        int width)
{
    glPushAttrib(GL_ENABLE_BIT);

    glColor3f(c.redF(), c.greenF(), c.blueF());
    glLineWidth(width);
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(a.x(), a.y(), a.z());
    glVertex3f(b.x(), b.y(), b.z());
    glEnd();

    glPopAttrib();
}

/**
 * @brief viewer::drawTriangle
 * @param p1
 * @param p2
 * @param p3
 * @param c
 * @param width
 * @param fill
 * @ingroup cg3viewer
 */
inline void drawTriangle(
        const Point3d &p1,
        const Point3d &p2,
        const Point3d &p3,
        const Color &c,
        int width,
        bool fill)
{
    if (width != 0){
		cg3::opengl::drawLine3(p1, p2, c, width);
		cg3::opengl::drawLine3(p2, p3, c, width);
		cg3::opengl::drawLine3(p3, p1, c, width);
    }
    if (fill) {
        glBegin(GL_TRIANGLES); //Begin triangle coordinates
        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p2.x(), p2.y(), p2.z());
        glVertex3f(p3.x(), p3.y(), p3.z());
        glEnd(); //End triangle coordinates
    }
}

/**
 * @brief viewer::drawQuad
 * @param a
 * @param b
 * @param c
 * @param d
 * @param width
 * @ingroup cg3viewer
 */
inline void drawQuad3(
        const Point3d &a,
        const Point3d &b,
        const Point3d &c,
        const Point3d &d,
        int width)
{
    glBegin(GL_QUADS);
    glLineWidth(width);
    glVertex3f(a.x(), a.y(), a.z());
    glVertex3f(b.x(), b.y(), b.z());
    glVertex3f(c.x(), c.y(), c.z());
    glVertex3f(d.x(), d.y(), d.z());
    glEnd();
}

/**
 * @brief Viewer::drawBox
 *
 * Draws an axis aligned 3D box using opengl lines.
 *
 * @param min
 * @param max
 * @param c
 * @param width
 * @ingroup cg3viewer
 */
inline void drawBox3(
        const Point3d& min,
        const Point3d& max,
        const Color& c,
        int width)
{
	drawLine3(min, Point3d(max.x(), min.y(), min.z()), c, width);
	drawLine3(Point3d(max.x(), min.y(), min.z()), Point3d(max.x(), min.y(), max.z()), c, width);
	drawLine3(Point3d(max.x(), min.y(), max.z()), Point3d(min.x(), min.y(), max.z()), c, width);
	drawLine3(min, Point3d(min.x(), min.y(), max.z()), c, width);

	drawLine3(Point3d(min.x(), max.y(), min.z()), Point3d(max.x(), max.y(), min.z()), c, width);
	drawLine3(Point3d(max.x(), max.y(), min.z()), max, c, width);
	drawLine3(max, Point3d(min.x(), max.y(), max.z()), c, width);
	drawLine3(Point3d(min.x(), max.y(), min.z()), Point3d(min.x(), max.y(), max.z()), c, width);

	drawLine3(min, Point3d(min.x(), max.y(), min.z()), c, width);
	drawLine3(Point3d(max.x(), min.y(), min.z()), Point3d(max.x(), max.y(), min.z()), c, width);
	drawLine3(Point3d(max.x(), min.y(), max.z()), max, c, width);
	drawLine3(Point3d(min.x(), min.y(), max.z()), Point3d(min.x(), max.y(), max.z()), c, width);
}

/**
 * @brief Viewer::drawBox
 *
 * draws the box composed by the first 8 point contained on the vector passed as parameter.
 *
 * @param p
 * @param c
 * @param width
 * @ingroup cg3viewer
 */
inline void drawBox3(const std::vector<Point3d> &p, const Color& c, int width)
{
	drawLine3(p[0], p[1], c, width);
	drawLine3(p[1], p[2], c, width);
	drawLine3(p[2], p[3], c, width);
	drawLine3(p[0], p[3], c, width);

	drawLine3(p[4], p[5], c, width);
	drawLine3(p[5], p[6], c, width);
	drawLine3(p[6], p[7], c, width);
	drawLine3(p[4], p[7], c, width);

	drawLine3(p[0], p[4], c, width);
	drawLine3(p[1], p[5], c, width);
	drawLine3(p[2], p[6], c, width);
	drawLine3(p[3], p[7], c, width);
}

/**
 * @brief viewer::drawBox
 * @param p0
 * @param p1
 * @param p2
 * @param p3
 * @param p4
 * @param p5
 * @param p6
 * @param p7
 * @param c
 * @param width
 * @ingroup cg3viewer
 */
inline void drawBox3(
        const Point3d &p0,
        const Point3d &p1,
        const Point3d &p2,
        const Point3d &p3,
        const Point3d &p4,
        const Point3d &p5,
        const Point3d &p6,
        const Point3d &p7,
        const Color& c,
        int width)
{
	drawLine3(p0, p1, c, width);
	drawLine3(p1, p2, c, width);
	drawLine3(p2, p3, c, width);
	drawLine3(p0, p3, c, width);

	drawLine3(p4, p5, c, width);
	drawLine3(p5, p6, c, width);
	drawLine3(p6, p7, c, width);
	drawLine3(p4, p7, c, width);

	drawLine3(p0, p4, c, width);
	drawLine3(p1, p5, c, width);
	drawLine3(p2, p6, c, width);
	drawLine3(p3, p7, c, width);
}

} //namespace cg3::opengl
} //namespace cg3
