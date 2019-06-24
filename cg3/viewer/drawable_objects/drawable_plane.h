/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_PLANE_H
#define CG3_DRAWABLE_PLANE_H

#include <cg3/geometry/plane.h>
#include <cg3/viewer/interfaces/drawable_object.h>

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The DrawablePlane class
 */
class DrawablePlane : public cg3::Plane, public DrawableObject
{
public:
    DrawablePlane(const Vec3d& _normal, double _d);
    DrawablePlane(double a, double b, double c, double _d);
    DrawablePlane(const Point3d &p1, const Point3d &p2, const Point3d &p3);
    DrawablePlane(Plane p);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

    // SerializableObject interface
    void deserialize(std::ifstream& binaryFile);

protected:
    void calculatePoints();
    cg3::Point3d p1, p2, p3, p4;
};

} // namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_PLANE_CPP "drawable_plane.cpp"
#include CG3_DRAWABLE_PLANE_CPP
#undef CG3_DRAWABLE_PLANE_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_PLANE_H
