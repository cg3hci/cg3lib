/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_POINT2D_H
#define CG3_POINT2D_H

#include <sstream>
#include <assert.h>
#include <string>
#include <ostream>

#include "../../io/serialize.h"
#include "../../utilities/hash.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * @class Point2D
 * @brief The Point2D class models a point or a vector in a 2D plane.
 *
 * It representes a 2D point or vector, with the precision given by the template type T.
 * Specified types with T = int, float or double are already defined as Point2Di,
 * Point2Df and Point2Dd (Vec2).
 *
 * @author Alessandro Muntoni
 */
template <class T>
class Point2D : SerializableObject {
public:
    Point2D(T x = 0.0, T y = 0.0);
#ifdef CG3_WITH_EIGEN
    Point2D(const Eigen::VectorXd &v);
#endif

    const T& x() const;
    const T& y() const;
    double dist(const Point2D<T> &otherPoint) const;
    double dot(const Point2D<T> &otherVector) const;
    double perpendicularDot(const Point2D<T> &otherVector) const;
    double getLength() const;
    double getLengthSquared() const;
    Point2D<T> min(const Point2D<T> &otherPoint) const;
    Point2D<T> max(const Point2D<T> &otherPoint) const;

    const T& operator[](unsigned int i)                 const;
    const T& operator()(unsigned int i)                 const;
    bool operator == (const Point2D<T> &otherPoint)   const;
    bool operator != (const Point2D<T> &otherPoint)   const;
    bool operator < (const Point2D<T>& otherPoint)    const;
    bool operator > (const Point2D<T>& otherPoint)    const;
    bool operator <= (const Point2D<T>& otherPoint)   const;
    bool operator >= (const Point2D<T>& otherPoint)   const;
    Point2D<T> operator - ()                          const;
    Point2D<T> operator + (const T& scalar) const;
    Point2D<T> operator + (const Point2D<T>& otherPoint) const;
    Point2D<T> operator - (const Point2D<T>& otherPoint) const;
    Point2D<T> operator * (const T& scalar)      const;
    Point2D<T> operator * (const Point2D<T>& otherPoint) const;
    Point2D<T> operator / (const T& scalar )     const;
    Point2D<T> operator / (const Point2D<T>& otherPoint) const;

    T& x();
    T& y();
    void setXCoord(const T& x);
    void setYCoord(const T& y);
    void set(const T& x, const T& y);
    double normalize();
    void rotate(T matrix[][2], const Point2D<T>& centroid = Point2D<T>());
    T& operator[](unsigned int i);
    T& operator()(unsigned int i);
    Point2D<T> operator += (const Point2D<T>& otherPoint);
    Point2D<T> operator -= (const Point2D<T>& otherPoint);
    Point2D<T> operator *= (const T& scalar);
    Point2D<T> operator *= (const Point2D<T>& otherPoint);
    Point2D<T> operator /= (const T& scalar );
    Point2D<T> operator /= (const Point2D<T>& otherPoint);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

private:
    T xCoord, yCoord;
    void rot(T matrix[][2]);


};

template <class T>
std::ostream& operator<<(std::ostream& o, const Point2D<T>& p);

/****************
* Other Methods *
*****************/

template <class T>
Point2D<T> operator * (const T& scalar, const Point2D<T>& point);

template <class T>
Point2D<T> normalOfSegment(const Point2D<T>& p1, const Point2D<T>& p2);

//Type definition
typedef Point2D<double> Point2Dd;
typedef Point2D<float> Point2Df;
typedef Point2D<int> Point2Di;
typedef Point2D<double> Vec2;

}

//hash specialization
namespace std {

template <typename T>
struct hash<cg3::Point2D<T>> {
    size_t operator()(const cg3::Point2D<T>& k) const;
};

}

#include "point2d.tpp"

#endif // CG3_POINT2D_H
