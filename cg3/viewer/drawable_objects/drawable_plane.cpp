/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_plane.h"
#include <cg3/utilities/const.h>
#include <cg3/viewer/opengl_objects/opengl_objects3.h>
namespace cg3 {

CG3_INLINE DrawablePlane::DrawablePlane(const Vec3d &normal, double d) : Plane(normal, d)
{
    calculatePoints();
}

CG3_INLINE DrawablePlane::DrawablePlane(double a, double b, double c, double d) : Plane(a, b, c, d)
{
    calculatePoints();
}

CG3_INLINE DrawablePlane::DrawablePlane(const Point3d &p1, const Point3d &p2, const Point3d &p3) : Plane(p1, p2, p3)
{
    calculatePoints();
}

CG3_INLINE DrawablePlane::DrawablePlane(Plane p) : Plane(p)
{
    calculatePoints();
}

CG3_INLINE void DrawablePlane::draw() const
{
    opengl::drawQuad3(p1, p2, p3, p4);
}

CG3_INLINE Point3d DrawablePlane::sceneCenter() const
{
    return cg3::Point3d();
}

CG3_INLINE double DrawablePlane::sceneRadius() const
{
    return -1;
}

CG3_INLINE void DrawablePlane::deserialize(std::ifstream &binaryFile)
{
    Plane::deserialize(binaryFile);
    calculatePoints();
}

CG3_INLINE void DrawablePlane::calculatePoints()
{
    cg3::Vec3d u,v;
    if( _normal ==  AXIS[2] || _normal == AXIS[5]){ // similar -> you are lucky!!!
       u = AXIS[0]; // x
       v = AXIS[1]; // y
    }
    else{
       u = _normal.cross(AXIS[2]); // cross product -> note that u lies on the plane
       v = _normal.cross(u); // v is orthogonal to both N and u (again is in the plane)
    }

    // now simply draw a quad centered in a arbitrary point of the plane
    // and large enough to seems a plane
    cg3::Point3d p0 = - _normal * _d;        // "arbitrary" point
    float  f  = 10000;  // large enough
    cg3::Vec3d fu =  u * f;
    cg3::Vec3d fv =  v * f;
    p1 = p0 - fu - fv;
    p2 = p0 + fu - fv;
    p3 = p0 + fu + fv;
    p4 = p0 - fu + fv;
}

} // namespace cg3
