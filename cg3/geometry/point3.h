/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_POINT3_H
#define CG3_POINT3_H

#include <string>

#include "../io/serialize.h"
#include "../utilities/hash.h"

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif //CG3_WITH_EIGEN

#ifdef CG3_CINOLIB_DEFINED
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <cinolib/geometry/vec3.h>
#pragma GCC diagnostic pop
#else //__GNUC__
#include <cinolib/geometry/vec3.h>
#endif //__GNUC__
#endif //CG3_CINOLIB_DEFINED

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * @ingroup cg3core
 * @class Point
 * @brief The Point class models a point or a vector on a 3D space.
 *
 * Represents a 3D point or vector, with the precision given by the template type T.
 * In particular, it is possible to have vectros/points with integer, float or double precision,
 * using the specified types Pointi, Pointf and Pointd.
 * There is also the type Vec3, that is a Pointd, which is a simple sinctactic sugar in order to
 * distinguish between points on a 3D space and vectors.
 */
template <class T>
class Point3 : public SerializableObject
{
public:

	Point3(T xCoord = 0.0, T yCoord = 0.0, T zCoord = 0.0);
    #ifdef CG3_WITH_EIGEN
	Point3(const Eigen::VectorXd &v);
    #endif
    #ifdef CG3_CINOLIB_DEFINED
	Point3(const cinolib::vec3<T> &v);
    #endif

    const T& x()                                        const;
    const T& y()                                        const;
    const T& z()                                        const;
	double dist(const Point3<T>& otherPoint)             const;
	double dot(const Point3<T>& otherVector)             const;
	double angleRAD(const Point3<T>& otherVector)        const;
	double angleDEG(const Point3<T>& otherVector)        const;
	Point3<T> cross(const Point3<T>& otherVector)         const;
    double length()                                     const;
    double lengthSquared()                              const;
	Point3<T> orthogonalVector()                         const;
	Point3<T> min(const Point3<T>& otherPoint)            const;
	Point3<T> max(const Point3<T>& otherPoint)            const;

    // Operators
    const T& operator[](unsigned int i)                 const;
    const T& operator()(unsigned int i)                 const;
	bool operator == (const Point3<T>& otherPoint)       const;
	bool operator != (const Point3<T>& otherPoint)       const;
	bool operator < (const Point3<T>& otherPoint)        const;
	Point3<T> operator - ()                              const;
	Point3<T> operator + (const T& scalar)               const;
	Point3<T> operator + (const Point3<T>& otherPoint)    const;
	Point3<T> operator - (const T& scalar)               const;
	Point3<T> operator - (const Point3<T>& otherPoint)    const;
	Point3<T> operator * (const T& scalar)               const;
	Point3<T> operator * (const Point3<T>& otherPoint)    const;
	Point3<T> operator / (const T& scalar )              const;
	Point3<T> operator / (const Point3<T>& otherPoint)    const;

    T& x();
    T& y();
    T& z();
    void setX(const T& x);
    void setY(const T& y);
    void setZ(const T& z);
    void set(const T& x, const T& y, const T& z);
    double normalize();
	Point3<T> normalized() const;
    #ifdef CG3_WITH_EIGEN
    Eigen::Vector3d toEigenVector() const;
	void rotate(const Eigen::Matrix3d &matrix, const Point3<T>& centroid = Point3<T>());
    #endif //CG3_WITH_EIGEN
	void rotate(double matrix[3][3], const Point3<T>& centroid = Point3<T>());

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    // Operators
    T& operator[](unsigned int i);
    T& operator()(unsigned int i);
	Point3<T> operator += (const Point3<T>& otherPoint);
	Point3<T> operator -= (const Point3<T>& otherPoint);
	Point3<T> operator *= (const T& scalar);
	Point3<T> operator *= (const Point3<T>& otherPoint);
	Point3<T> operator /= (const T& scalar );
	Point3<T> operator /= (const Point3<T>& otherPoint);

protected:
    T xCoord;
    T yCoord;
    T zCoord;
};

/****************
* Other Methods *
*****************/

template <class T>
Point3<T> operator * (const T& scalar, const Point3<T>& point);

template <class T>
Point3<T> mul(const T m[][3], const Point3<T>& point);

#ifdef CG3_WITH_EIGEN
template <class T>
Point3<T> mul(const Eigen::Matrix3d &m, const Point3<T>& point);
#endif //CG3_WITH_EIGEN

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Point3<T>& p);

template <class T>
std::string to_string(const Point3<T>& p);

/**************
* Other Types *
***************/

typedef Point3<float>  Point3f; /**< \~English @brief Point composed of float components */
typedef Point3<double> Point3d; /**< \~English @brief Point composed of double components */
typedef Point3<int>    Point3i; /**< \~English @brief Point composed of integer components */
typedef Point3<float>   Vec3f; /**< \~English @brief Point composed of float components, sinctactic sugar to discriminate points from vectors */
typedef Point3<double>   Vec3d; /**< \~English @brief Point composed of double components, sinctactic sugar to discriminate points from vectors */
typedef Point3<int>   Vec3i; /**< \~English @brief Point composed of integer components, sinctactic sugar to discriminate points from vectors */


/**< \~English @brief alias of Point */

} //namespace cg3

//hash specialization
namespace std {

template <typename T>
struct hash<cg3::Point3<T>> {
	size_t operator()(const cg3::Point3<T>& k) const;
};

} //namespace std

#include "point3.cpp"

#endif // CG3_POINT3_H
