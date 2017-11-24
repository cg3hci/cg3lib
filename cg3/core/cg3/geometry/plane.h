#ifndef CG3_PLANE_H
#define CG3_PLANE_H

#include "point.h"
#include "line.h"

namespace cg3 {

class Plane : SerializableObject {
    public:
        Plane(const Vec3& normal, double d);
        Plane(double a, double b, double c, double d);
        Plane(const Pointd &p1, const Pointd &p2, const Pointd &p3);

        double getA() const;
        double getB() const;
        double getC() const;
        double getD() const;


        bool pointBelonging(const Pointd& p) const;
        #ifdef CG3_WITH_EIGEN
        bool getIntersection(Pointd&intersection, const Line &l) const;
        #endif

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:
        Vec3 normal;
        double d;
};

}

#endif // CG3_PLANE_H
