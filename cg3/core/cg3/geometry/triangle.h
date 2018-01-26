/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_TRIANGLE_H
#define CG3_TRIANGLE_H

#include "../io/serializable_object.h"
#include "point.h"

namespace cg3 {

template <class V>
class Triangle : public SerializableObject {
    public:
        Triangle();
        Triangle(const V& v1, const V& v2, const V& v3);

        V normal() const;
        double area() const;
        V v1() const;
        V v2() const;
        V v3() const;
        V barycenter() const;

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:
        V _v1, _v2, _v3;
};

/* ----- Common typedefs (1D, 2D, 3D double) ----- */

template <class T>
using Triangle3D = Triangle<Point<T>>;

typedef Triangle3D<double> Triangle3Dd;
typedef Triangle3D<float> Triangle3Df;
typedef Triangle3D<int> Triangle3Di;

} // namespace cg3

#include "triangle.tpp"

#endif // CG3_TRIANGLE_H
