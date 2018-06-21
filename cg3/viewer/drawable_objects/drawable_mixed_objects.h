/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_DEBUG_OBJECTS_H
#define CG3_DRAWABLE_DEBUG_OBJECTS_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/bounding_box.h>
#include <cg3/geometry/2d/bounding_box2d.h>
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
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void updateBoundingBox();
    unsigned int numberObjects() const;

    unsigned int addSphere(
            const Pointd& center,
            double radius,
            const QColor &color,
            int precision = 4);
    void clearSpheres();
    unsigned int addPoint(
            const Pointd& p,
            const QColor &color,
            int size = 8);
    void clearPoints();
    unsigned int addCylinder(
            const Pointd& a,
            const Pointd& b,
            double radius,
            const QColor color);
    void clearCylinders();
    unsigned int addLine(
            const Pointd& a,
            const Pointd& b,
            const QColor color,
            int width= 3);
    unsigned int addLine(
            const Point2Dd& a,
            const Point2Dd& b,
            const QColor color,
            int width= 3);
    void clearLines();
    unsigned int addTriangle(
            const Pointd& a,
            const Pointd& b,
            const Pointd& c,
            const QColor color,
            int width = 3,
            bool fill = false);
    unsigned int addTriangle(
            const Point2Dd& a,
            const Point2Dd& b,
            const Point2Dd& c,
            const QColor color,
            int width = 3,
            bool fill = false);
    void clearTriangles();
    unsigned int addText(
            const Pointd& pos,
            const std::string& text);
    void clearTexts();

protected:
    struct Object
    {
    };

    struct Sphere
    {
            Pointd center;
            double radius;
            QColor color;
            int precision;
    };
    struct Cylinder
    {
            Pointd a;
            Pointd b;
            double radius;
            QColor color;
    };
    struct Point
    {
            Pointd p;
            QColor color;
            int size;
    };
    struct Line
    {
            Pointd a;
            Pointd b;
            int width;
            QColor color;
    };
    struct Triangle
    {
            Pointd a;
            Pointd b;
            Pointd c;
            int width;
            QColor color;
            bool fill;
    };
    struct Text
    {
            Pointd pos;
            std::string text;
    };
    std::vector<Sphere> spheres;
    std::vector<Cylinder> cylinders;
    std::vector<Line> lines;
    std::vector<Point> points;
    std::vector<Triangle> triangles;
    std::vector<Text> texts;

    BoundingBox bb;

    cg3::viewer::GLCanvas* canvas;
};

} //namespace cg3

#endif // CG3_DRAWABLE_DEBUG_OBJECTS_H
