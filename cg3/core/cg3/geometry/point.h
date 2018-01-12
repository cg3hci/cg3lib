/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_POINT_H
#define CG3_POINT_H

#include <assert.h>
#include <string>
#include <iostream>

#include "../io/serialize.h"
#include "../utilities/hash.h"

#ifdef CG3_CINOLIB_DEFINED
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <cinolib/geometry/vec3.h>
#pragma GCC diagnostic pop
#endif //__GNUC__
#endif //CG3_CINOLIB_DEFINED

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * \~English
 * @class Point
 * @brief The Point class models a point or a vector on a 3D space.
 *
 * Represents a 3D point or vector, with the precision given by the template type T.
 * In particular, it is possible to have vectros/points with integer, float or double precision,
 * using the specified types Pointi, Pointf and Pointd.
 * There is also the type Vec3, that is a Pointd, which is a simple sinctactic sugar in order to
 * distinguish between points on a 3D space and vectors.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class T> class Point : SerializableObject {

    public:

        /****************
         * Constructors *
         ****************/

        Point(T xCoord = 0.0, T yCoord = 0.0, T zCoord = 0.0);
        #ifdef CG3_WITH_EIGEN
        Point(const Eigen::VectorXd &v);
        #endif
        #ifdef CG3_CINOLIB_DEFINED
        Point(const cinolib::vec3<T> &v);
        #endif

        /*************************
        * Public Inline Methods *
        *************************/

        const T& x()                                        const;
        const T& y()                                        const;
        const T& z()                                        const;
        double dist(const Point<T>& otherPoint)             const;
        double dot(const Point<T>& otherVector)             const;
        Point<T> cross(const Point<T>& otherVector)         const;
        double getLength()                                  const;
        double getLengthSquared()                           const;
        Point<T> min(const Point<T>& otherPoint)            const;
        Point<T> max(const Point<T>& otherPoint)            const;        

        // Operators
        const T& operator[](unsigned int i)                 const;
        const T& operator()(unsigned int i)                 const;
        bool operator == (const Point<T>& otherPoint)       const;
        bool operator != (const Point<T>& otherPoint)       const;
        bool operator < (const Point<T>& otherPoint)        const;
        Point<T> operator - ()                              const;
        Point<T> operator + (const T& scalar)               const;
        Point<T> operator + (const Point<T>& otherPoint)    const;
        Point<T> operator - (const T& scalar)               const;
        Point<T> operator - (const Point<T>& otherPoint)    const;
        Point<T> operator * (const T& scalar)               const;
        Point<T> operator * (const Point<T>& otherPoint)    const;
        Point<T> operator / (const T& scalar )              const;
        Point<T> operator / (const Point<T>& otherPoint)    const;


        T& x();
        T& y();
        T& z();
        void setX(const T& x);
        void setY(const T& y);
        void setZ(const T& z);
        void set(const T& x, const T& y, const T& z);
        double normalize();
        #ifdef CG3_WITH_EIGEN
        void rotate(const Eigen::Matrix3d &matrix, const Point<T>& centroid = Point<T>());
        #endif //CG3_WITH_EIGEN
        void rotate(double matrix[3][3], const Point<T>& centroid = Point<T>());

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

        // Operators
        T& operator[](unsigned int i);
        T& operator()(unsigned int i);
        Point<T> operator += (const Point<T>& otherPoint);
        Point<T> operator -= (const Point<T>& otherPoint);
        Point<T> operator *= (const T& scalar);
        Point<T> operator *= (const Point<T>& otherPoint);
        Point<T> operator /= (const T& scalar );
        Point<T> operator /= (const Point<T>& otherPoint);

    protected:

        /**************
        * Attributes *
        **************/

        T xCoord; /**< \~English @brief The \c x component of the point/vector */
        T yCoord; /**< \~English @brief The \c y component of the point/vector */
        T zCoord; /**< \~English @brief The \c z component of the point/vector */
    };

/****************
* Other Methods *
*****************/

template <class T>
Point<T> operator * (const T& scalar, const Point<T>& point);

template <class T>
Point<T> mul(const T m[][3], const Point<T>& point);

#ifdef CG3_WITH_EIGEN
template <class T>
Point<T> mul(const Eigen::Matrix3d &m, const Point<T>& point);
#endif //CG3_WITH_EIGEN

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Point<T>& p);

template <class T>
std::string to_string(const Point<T>& p);

/**************
* Other Types *
***************/

typedef Point<float>  Pointf; /**< \~English @brief Point composed of float components */
typedef Point<double> Pointd; /**< \~English @brief Point composed of double components */
typedef Point<int>    Pointi; /**< \~English @brief Point composed of integer components */
typedef Point<double>   Vec3; /**< \~English @brief Point composed of double components, sinctactic sugar for discriminate points from vectors */
template<typename T>
using Point3D = Point<T>; /**< \~English @brief alias of Point */

}

//hash specialization
namespace std {

template <typename T>
struct hash<cg3::Point<T>> {
    size_t operator()(const cg3::Point<T>& k) const;
};

}

#include "point.tpp"

#endif // CG3_POINT_H
