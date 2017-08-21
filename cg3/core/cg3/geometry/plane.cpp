#include "plane.h"

#ifdef CG3_WITH_EIGEN
#include <Eigen/QR>
#endif

namespace cg3 {

Plane::Plane(const Vec3& normal, double d) : normal(normal), d(d) {
}

Plane::Plane(double a, double b, double c, double d) : normal(a, b, c), d(d){
}

Plane::Plane(const Pointd& p1, const Pointd& p2, const Pointd& p3){
    Vec3 v1 (p2 - p1);
    Vec3 v2 (p3 - p1);
    normal = v1.cross(v2);
    normal.normalize();
    d = normal.x() * p1.x() + normal.y() * p1.y() + normal.z() * p1.z();
}

Plane::~Plane(){
}

/**
 * @brief Line::pointBelonging Metodo che si occupa di controllare se un punto appartiene alla retta
 * @param p il punto del quale contollare l'appartenenza
 * @return true se il punto appartiene alla retta, false viceversa
 */
bool Plane::pointBelonging(const Pointd &p) const{

    int sum = normal.x()*p.x() + normal.y()*p.y() + normal.z()*p.z() + d;
    //Se il punto appartiene al piano, allora l'equazione del piano deve essere
    //verificata sostituendo alle variabili i valori del punto
    if(sum == 0)
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

}
