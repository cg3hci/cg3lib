/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_POINT2_H
#define CG3_POINT2_H

#include <string>
#include <ostream>
#include <cmath>

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif //CG3_WITH_EIGEN

#include "../io/serialize.h"
#include "../utilities/hash.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * @ingroup cg3core
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
class Point2 : public SerializableObject
{
public:
	Point2(T x = 0.0, T y = 0.0);
    #ifdef CG3_WITH_EIGEN
	Point2(const Eigen::VectorXd &v);
    #endif

    const T& x() const;
    const T& y() const;
	double dist(const Point2<T> &otherPoint) const;
	double dot(const Point2<T> &otherVector) const;
	double perpendicularDot(const Point2<T> &otherVector) const;
    double length() const;
    double lengthSquared() const;
	Point2<T> min(const Point2<T> &otherPoint) const;
	Point2<T> max(const Point2<T> &otherPoint) const;

    const T& operator[](unsigned int i)                 const;
    const T& operator()(unsigned int i)                 const;
	bool operator == (const Point2<T> &otherPoint)   const;
	bool operator != (const Point2<T> &otherPoint)   const;
	bool operator < (const Point2<T>& otherPoint)    const;
	bool operator > (const Point2<T>& otherPoint)    const;
	bool operator <= (const Point2<T>& otherPoint)   const;
	bool operator >= (const Point2<T>& otherPoint)   const;
	Point2<T> operator - ()                          const;
	Point2<T> operator + (const T& scalar) const;
	Point2<T> operator + (const Point2<T>& otherPoint) const;
	Point2<T> operator - (const Point2<T>& otherPoint) const;
	Point2<T> operator * (const T& scalar)      const;
	Point2<T> operator * (const Point2<T>& otherPoint) const;
	Point2<T> operator / (const T& scalar )     const;
	Point2<T> operator / (const Point2<T>& otherPoint) const;

    T& x();
    T& y();
    void setXCoord(const T& x);
    void setYCoord(const T& y);
    void set(const T& x, const T& y);
    double normalize();
	void rotate(T matrix[][2], const Point2<T>& centroid = Point2<T>());
    T& operator[](unsigned int i);
    T& operator()(unsigned int i);
	Point2<T> operator += (const Point2<T>& otherPoint);
	Point2<T> operator -= (const Point2<T>& otherPoint);
	Point2<T> operator *= (const T& scalar);
	Point2<T> operator *= (const Point2<T>& otherPoint);
	Point2<T> operator /= (const T& scalar );
	Point2<T> operator /= (const Point2<T>& otherPoint);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

private:
    T xCoord, yCoord;
    void rot(T matrix[][2]);
};

template <class T>
std::ostream& operator<<(std::ostream& o, const Point2<T>& p);

/****************
* Other Methods *
*****************/

template <class T>
Point2<T> operator * (const T& scalar, const Point2<T>& point);

template <class T>
Point2<T> normalOfSegment(const Point2<T>& p1, const Point2<T>& p2);

//Type definition
typedef Point2<double> Point2d;
typedef Point2<float> Point2f;
typedef Point2<int> Point2i;
typedef Point2<double> Vec2d;
typedef Point2<float> Vec2f;
typedef Point2<int> Vec2i;

} //namespace cg3

//hash specialization
namespace std {

template <typename T>
struct hash<cg3::Point2<T>> {
	size_t operator()(const cg3::Point2<T>& k) const;
};

} //namespace std

#include "point2.cpp"

#endif // CG3_POINT2_H
