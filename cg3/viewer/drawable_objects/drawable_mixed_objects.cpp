/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "drawable_mixed_objects.h"
#include "../opengl_objects/opengl_objects3.h"
#include "../opengl_objects/opengl_objects2.h"


namespace cg3 {

CG3_INLINE DrawableMixedObjects::DrawableMixedObjects(viewer::GLCanvas* canvas) :
    canvas(canvas)
{
}

CG3_INLINE void DrawableMixedObjects::draw() const
{
    for (const Sphere& s : spheres){
        opengl::drawSphere(s.center, s.radius, s.color, s.precision);
    }
    for (const Point& p : points){
		opengl::drawPoint3(p.p, p.color, p.size);
    }
    for (const Cylinder& c : cylinders){
        opengl::drawCylinder(c.a, c.b, c.radius, c.radius, c.color);
    }
    for (const Line& l : lines){
		opengl::drawLine3(l.a, l.b, l.color, l.width);
    }
    for (const Triangle& t : triangles){
        opengl::drawTriangle(t.a, t.b, t.c, t.color, t.width, t.fill);
    }
    if (canvas != nullptr){
        for (const Text& t : texts) {
            qglviewer::Vec pos2d =
                    canvas->camera()->projectedCoordinatesOf(qglviewer::Vec(t.pos.x(), t.pos.y(), t.pos.z()));
            canvas->drawText(pos2d.x, pos2d.y, QString::fromStdString(t.text));
        }
    }
}

CG3_INLINE Point3d DrawableMixedObjects::sceneCenter() const
{
    if (bb.diag() > 0)
        return bb.center();
    return Point3d();
}

CG3_INLINE double DrawableMixedObjects::sceneRadius() const
{
    //if (bb.diag() > 0)
    //    return bb.diag()/2;
    return -1;
}

CG3_INLINE void DrawableMixedObjects::updateBoundingBox()
{
    if (numberObjects() == 0) {
        bb = BoundingBox3();
    }
    else {
        const double dmax = std::numeric_limits<double>::max();
        const double dmin = std::numeric_limits<double>::min();
        bb = BoundingBox3(Point3d(dmax, dmax, dmax), Point3d(dmin, dmin, dmin));
    }
    for (const Sphere& s : spheres){
        bb.min() = bb.min().min(s.center);
        bb.max() = bb.max().max(s.center);
    }
    for (const Point& p : points){
        bb.min() = bb.min().min(p.p);
        bb.max() = bb.max().max(p.p);
    }
    for (const Cylinder& c : cylinders){
        bb.min() = bb.min().min(c.a);
        bb.min() = bb.min().min(c.b);
        bb.max() = bb.max().max(c.a);
        bb.max() = bb.max().max(c.b);
    }
    for (const Line& l : lines){
        bb.min() = bb.min().min(l.a);
        bb.min() = bb.min().min(l.b);
        bb.max() = bb.max().max(l.a);
        bb.max() = bb.max().max(l.b);
    }
}

CG3_INLINE unsigned int DrawableMixedObjects::numberObjects() const
{
    return (unsigned int) (spheres.size() + cylinders.size() + lines.size());
}

CG3_INLINE unsigned int DrawableMixedObjects::addSphere(const Point3d& center, double radius, const QColor& color, int precision)
{
    Sphere s = {center, radius, color, precision};
    spheres.push_back(s);
    bb.min() = bb.min().min(center);
    bb.max() = bb.max().max(center);
    return (unsigned int)spheres.size()-1;
}

CG3_INLINE void DrawableMixedObjects::clearSpheres()
{
    spheres.clear();
    updateBoundingBox();
}

CG3_INLINE unsigned int DrawableMixedObjects::addPoint(const Point3d& p, const QColor& color, int size)
{
    Point pp = {p, color, size};
    points.push_back(pp);
    bb.min() = bb.min().min(p);
    bb.max() = bb.max().max(p);
    return (unsigned int)points.size()-1;
}

CG3_INLINE void DrawableMixedObjects::clearPoints() {
    points.clear();
    updateBoundingBox();
}

CG3_INLINE unsigned int DrawableMixedObjects::addCylinder(const Point3d& a, const Point3d& b, double radius, const QColor color)
{
    Cylinder c = {a, b, radius, color};
    cylinders.push_back(c);

    bb.min() = bb.min().min(a);
    bb.min() = bb.min().min(b);
    bb.max() = bb.max().max(a);
    bb.max() = bb.max().max(b);

    return (unsigned int)cylinders.size()-1;
}

CG3_INLINE void DrawableMixedObjects::clearCylinders()
{
    cylinders.clear();
    updateBoundingBox();
}

CG3_INLINE unsigned int DrawableMixedObjects::addLine(const Point3d &a, const Point3d &b, const QColor color, int width)
{
    Line l = {a, b, width, color};
    lines.push_back(l);
    bb.min() = bb.min().min(a);
    bb.min() = bb.min().min(b);
    bb.max() = bb.max().max(a);
    bb.max() = bb.max().max(b);
    return (unsigned int)lines.size()-1;
}

CG3_INLINE unsigned int DrawableMixedObjects::addLine(const Point2d& a, const Point2d& b, const QColor color, int width)
{
    Point3d a_(a.x(), a.y(), 0);
    Point3d b_(b.x(), b.y(), 0);
    Line l = {a_, b_, width, color};
    lines.push_back(l);
    bb.min() = bb.min().min(a_);
    bb.min() = bb.min().min(b_);
    bb.max() = bb.max().max(a_);
    bb.max() = bb.max().max(b_);
    return (unsigned int)lines.size()-1;
}

CG3_INLINE void DrawableMixedObjects::clearLines()
{
    lines.clear();
    updateBoundingBox();
}

CG3_INLINE unsigned int DrawableMixedObjects::addTriangle(const Point3d& a, const Point3d& b, const Point3d& c, const QColor color, int width, bool fill)
{
    Triangle t {a, b, c, width, color, fill};
    triangles.push_back(t);
    bb.min() = bb.min().min(a);
    bb.min() = bb.min().min(b);
    bb.min() = bb.min().min(c);
    bb.max() = bb.max().max(a);
    bb.max() = bb.max().max(b);
    bb.max() = bb.max().max(c);

    return (unsigned int)triangles.size()-1;
}

CG3_INLINE unsigned int DrawableMixedObjects::addTriangle(const Point2d& a, const Point2d& b, const Point2d& c, const QColor color, int width, bool fill)
{
    Point3d a_(a.x(), a.y(), 0);
    Point3d b_(b.x(), b.y(), 0);
    Point3d c_(c.x(), c.y(), 0);
    Triangle t {a_, b_, c_, width, color, fill};
    triangles.push_back(t);
    bb.min() = bb.min().min(a_);
    bb.min() = bb.min().min(b_);
    bb.min() = bb.min().min(c_);
    bb.max() = bb.max().max(a_);
    bb.max() = bb.max().max(b_);
    bb.max() = bb.max().max(c_);

    return (unsigned int)triangles.size()-1;
}

CG3_INLINE void DrawableMixedObjects::clearTriangles()
{
    triangles.clear();
    updateBoundingBox();
}

CG3_INLINE unsigned int DrawableMixedObjects::addText(const Point3d& pos, const std::string& text)
{
    texts.push_back({pos, text});
    return (unsigned int) texts.size()-1;
}

CG3_INLINE void DrawableMixedObjects::clearTexts()
{
    texts.clear();
}

} //namespace cg3
