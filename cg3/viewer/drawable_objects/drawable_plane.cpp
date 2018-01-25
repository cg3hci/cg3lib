/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_plane.h"
#include <cg3/utilities/const.h>
#include <cg3/viewer/renderable_objects/renderable_objects.h>
namespace cg3 {

DrawablePlane::DrawablePlane(const Vec3 &normal, double d) : Plane(normal, d) {
    calculatePoints();
}

DrawablePlane::DrawablePlane(double a, double b, double c, double d) : Plane(a, b, c, d) {
    calculatePoints();
}

DrawablePlane::DrawablePlane(const Pointd &p1, const Pointd &p2, const Pointd &p3) : Plane(p1, p2, p3) {
    calculatePoints();
}

DrawablePlane::DrawablePlane(Plane p) : Plane(p) {
    calculatePoints();
}

void DrawablePlane::draw() const {
    viewer::drawQuad(p1, p2, p3, p4);
}

Pointd DrawablePlane::sceneCenter() const {
    return cg3::Pointd();
}

double DrawablePlane::sceneRadius() const {
    return -1;
}

void DrawablePlane::deserialize(std::ifstream &binaryFile) {
    Plane::deserialize(binaryFile);
    calculatePoints();
}

void DrawablePlane::calculatePoints() {
    cg3::Vec3 u,v;
    if( normal ==  AXIS[2] || normal == AXIS[5]){ // similar -> you are lucky!!!
       u = AXIS[0]; // x
       v = AXIS[1]; // y
    }
    else{
       u = normal.cross(AXIS[2]); // cross product -> note that u lies on the plane
       v = normal.cross(u); // v is orthogonal to both N and u (again is in the plane)
    }

    // now simply draw a quad centered in a arbitrary point of the plane
    // and large enough to seems a plane
    cg3::Pointd p0 = - normal * d;        // "arbitrary" point
    float  f  = 10000;  // large enough
    cg3::Vec3 fu =  u * f;
    cg3::Vec3 fv =  v * f;
    p1 = p0 - fu - fv;
    p2 = p0 + fu - fv;
    p3 = p0 + fu + fv;
    p4 = p0 - fu + fv;
}

} // namespace cg3
