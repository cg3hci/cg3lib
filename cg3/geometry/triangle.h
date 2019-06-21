/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_TRIANGLE_H
#define CG3_TRIANGLE_H

#include "../io/serializable_object.h"
#include "segment.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief The Triangle class
 */
template <class T>
class Triangle : public SerializableObject
{
public:
    Triangle();
    Triangle(const T& v1, const T& v2, const T& v3);

    const T& v1() const;
    const T& v2() const;
    const T& v3() const;
	const T& operator[](unsigned int i) const;
    std::vector<T> vertices() const;

    T& v1();
    T& v2();
    T& v3();
	T& operator[](unsigned int i);
    void setV1(const T& v1);
    void setV2(const T& v2);
    void setV3(const T& v3);
    void set(const T& v1, const T& v2, const T& v3);

    cg3::Segment<T> side1() const;
    cg3::Segment<T> side2() const;
    cg3::Segment<T> side3() const;
    std::vector<cg3::Segment<T>> sides() const;

    T normal() const;
    double area() const;
    double perimeter() const;
    T barycenter() const;


    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
	T v[3];
};

} // namespace cg3

#include "triangle.cpp"

#endif // CG3_TRIANGLE_H
