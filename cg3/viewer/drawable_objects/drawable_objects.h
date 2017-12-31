/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_DRAWABLE_DEBUG_OBJECTS_H
#define CG3_DRAWABLE_DEBUG_OBJECTS_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/bounding_box.h>

namespace cg3 {

class DrawableObjects : public DrawableObject{
    public:
        DrawableObjects();

        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;
        bool isVisible() const;
        void setVisible(bool b);

        void updateBoundingBox();
        unsigned int numberObjects() const;

        void addSphere(const Pointd& center, double radius, const QColor &color, int precision = 4);
        void clearSpheres();
        void addCylinder(const Pointd& a, const Pointd& b, double radius, const QColor color);
        void clearCylinders();
        void addLine(const Pointd& a, const Pointd& b, int width, const QColor color);
        void clearLines();

    protected:
        typedef struct {
                Pointd center;
                double radius;
                QColor color;
                int precision;
        } Sphere;
        typedef struct {
                Pointd a;
                Pointd b;
                double radius;
                QColor color;
        } Cylinder;
        typedef struct {
                Pointd a;
                Pointd b;
                int width;
                QColor color;
        } Line;
        std::vector<Sphere> spheres;
        std::vector<Cylinder> cylinders;
        std::vector<Line> lines;

        bool visible;
        BoundingBox bb;
};

}

#endif // CG3_DRAWABLE_DEBUG_OBJECTS_H
