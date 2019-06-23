/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_MIXED_OBJECTS_H
#define CG3_DRAWABLE_MIXED_OBJECTS_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/bounding_box3.h>
#include <cg3/geometry/bounding_box2.h>
#include <cg3/viewer/glcanvas.h>

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawableObjects class
 */
class DrawableMixedObjects : public DrawableObject
{
public:
    typedef enum {SPHERE, CYLINDER, POINT, LINE, TRIANGLE} Elements;

    DrawableMixedObjects(cg3::viewer::GLCanvas* canvas = nullptr);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

    void updateBoundingBox();
    unsigned int numberObjects() const;

    unsigned int addSphere(
            const Point3d& center,
            double radius,
            const QColor &color,
            int precision = 4);
    void clearSpheres();
    unsigned int addPoint(
            const Point3d& p,
            const QColor &color,
            int size = 8);
    void clearPoints();
    unsigned int addCylinder(
            const Point3d& a,
            const Point3d& b,
            double radius,
            const QColor color);
    void clearCylinders();
    unsigned int addLine(
            const Point3d& a,
            const Point3d& b,
            const QColor color,
            int width= 3);
    unsigned int addLine(
            const Point2d& a,
            const Point2d& b,
            const QColor color,
            int width= 3);
    void clearLines();
    unsigned int addTriangle(
            const Point3d& a,
            const Point3d& b,
            const Point3d& c,
            const QColor color,
            int width = 3,
            bool fill = false);
    unsigned int addTriangle(
            const Point2d& a,
            const Point2d& b,
            const Point2d& c,
            const QColor color,
            int width = 3,
            bool fill = false);
    void clearTriangles();
    unsigned int addText(
            const Point3d& pos,
            const std::string& text);
    void clearTexts();

protected:
    struct Object
    {
    };

    struct Sphere
    {
            Point3d center;
            double radius;
            QColor color;
            int precision;
    };
    struct Cylinder
    {
            Point3d a;
            Point3d b;
            double radius;
            QColor color;
    };
    struct Point
    {
            Point3d p;
            QColor color;
            int size;
    };
    struct Line
    {
            Point3d a;
            Point3d b;
            int width;
            QColor color;
    };
    struct Triangle
    {
            Point3d a;
            Point3d b;
            Point3d c;
            int width;
            QColor color;
            bool fill;
    };
    struct Text
    {
            Point3d pos;
            std::string text;
    };
    std::vector<Sphere> spheres;
    std::vector<Cylinder> cylinders;
    std::vector<Line> lines;
    std::vector<Point> points;
    std::vector<Triangle> triangles;
    std::vector<Text> texts;

    BoundingBox3 bb;

    cg3::viewer::GLCanvas* canvas;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_MIXED_OBJECTS_CPP "drawable_mixed_objects.cpp"
#include CG3_DRAWABLE_MIXED_OBJECTS_CPP
#undef CG3_DRAWABLE_MIXED_OBJECTS_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_MIXED_OBJECTS_H
