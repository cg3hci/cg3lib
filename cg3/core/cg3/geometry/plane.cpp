/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#include "plane.h"
#include <cg3/utilities/utils.h>
#ifdef CG3_WITH_EIGEN
#include <Eigen/QR>
#endif

namespace cg3 {

Plane::Plane(const Vec3& normal, double d) : normal(normal), d(d) {
    normalize();
}

Plane::Plane(double a, double b, double c, double d) : normal(a, b, c), d(d){
    normalize();
}

Plane::Plane(const Pointd& p1, const Pointd& p2, const Pointd& p3){
    Vec3 v1 (p2 - p1);
    Vec3 v2 (p3 - p1);
    normal = v1.cross(v2);
    normal.normalize();
    d = -(normal.x() * p1.x() + normal.y() * p1.y() + normal.z() * p1.z());
}

double Plane::getA() const{
    return normal.x();
}

double Plane::getB() const{
    return normal.y();
}

double Plane::getC() const{
    return normal.z();
}

double Plane::getD() const{
    return d;
}

Vec3 Plane::getNormal() const {
    return normal;
}

void Plane::normalize() {
    double oldLength = normal.normalize();
    d /= oldLength;
}

/**
 * @brief Plane::pointLiesOnPlane checks if a point lies on the plane.
 * @param p
 * @return true if the point lies on the plane, false otherwise
 */
bool Plane::pointLiesOnPlane(const Pointd &p, double epsilon) const{
    double sum = normal.x()*p.x() + normal.y()*p.y() + normal.z()*p.z() + d;
    if(cg3::epsilonEqual(sum, 0.0, epsilon))
        return true;
    else
        return false;

}

#ifdef CG3_WITH_EIGEN
bool Plane::getIntersection(Pointd& intersection, const Line& l) const {
    Vec3 n(normal);
    n.normalize();
    Vec3 dir = l.getDir();
    dir.normalize();
    if (n.dot(dir) == 0) return false;

    Eigen::Matrix<double, 3, 3> A;
    A(0,0) = normal.x(); A(0,1) = normal.y(); A(0,2) = normal.z();
    A(1,0) = dir.z();    A(1,1) = 0;          A(1,2) = -(dir.x());
    A(2,0) = dir.y();    A(2,1) = -(dir.x()); A(2,2) = 0;

    Eigen::Matrix<double, 3, 1> B;
    B(0) = d;
    B(1) = (dir.z()*l.getStartingPoint().x())-(dir.x()*l.getStartingPoint().z());
    B(2) = (dir.y()*l.getStartingPoint().x())-(dir.x()*l.getStartingPoint().y());

    Eigen::Matrix<double, 3, 1> x = A.colPivHouseholderQr().solve(B);

    intersection.set(x[0], x[1], x[2]);

    return true;
}
#endif

double Plane::pointDistance(const Pointd& p) const {
    return (normal.dot(p - (normal*d)));
}

void Plane::serialize(std::ofstream& binaryFile) const {
    serializeObjectAttributes("cg3Plane", binaryFile, normal, d);
}

void Plane::deserialize(std::ifstream& binaryFile) {
    deserializeObjectAttributes("cg3Plane", binaryFile, normal, d);
}

}
