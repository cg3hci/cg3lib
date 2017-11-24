#ifndef CG3_DRAWABLE_DEBUG_OBJECTS_H
#define CG3_DRAWABLE_DEBUG_OBJECTS_H

#include "../interfaces/drawable_object.h"
#include <cg3/geometry/bounding_box.h>

namespace cg3 {

class DrawableDebugObjects : public DrawableObject{
    public:
        DrawableDebugObjects();

        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;
        bool isVisible() const;
        void setVisible(bool b);

        void addDebugSphere(const Pointd& center, double radius, const QColor &color, int precision = 4);
        void clearDebugSpheres();
        void addDebugCylinder(const Pointd& a, const Pointd& b, double radius, const QColor color);
        void clearDebugCylinders();

        void addDebugLine(const Pointd& a, const Pointd& b, int width, const QColor color);
        void clearDebugLines();

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
        std::vector<Sphere> debugSpheres;
        std::vector<Cylinder> debugCylinders;
        std::vector<Line> debugLines;

        bool visible;
};

}

#endif // CG3_DRAWABLE_DEBUG_OBJECTS_H
