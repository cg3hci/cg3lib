/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_COMPARATORS_H
#define CG3_COMPARATORS_H

#include "../geometry/point3.h"

namespace cg3 {

template <class T>
struct cmpStdPair
{
    bool operator()(const std::pair<T,T>& a, const std::pair<T,T>& b) const
    {
        if (a.first < b.first) {
            return true;
        }
        else {
            if (a.first == b.first){
                if (a.second < b.second)
                    return true;
            }
        }
        return false;
    }
};

/**
 * @ingroup cg3core
 * @struct cmpUnorderedStdPair
 * @brief la struttura cmpUnorderedStdPair implementa un comparatore per la classe std::pair<T,T>
 *
 * It compares a couple of elements and decides if one is less than the other without taking account on the elements order.
 * It can be used if you need a set of unordered couples, where you can't have couples with inverted elements.
 *
 * Example: the couple (0,2) is not less than (2,0), and viceversa.
 *
 * Example: the couple (2,0) is less than the couple (0,3).
 *
 * Example of usage:
 * \code{.cpp}
 * std::set<std::pair<int, int>, cmpUnorderedStdPair<int> > set;
 * \endcode
 * Note that the type of the elements of the pair must be the same, and must match to the comparator type.
 */
template <class T>
struct cmpUnorderedStdPair
{
    bool operator()(const std::pair<T,T>& a, const std::pair<T,T>& b) const
    {
        T amin, bmin, amax, bmax;
        if (a.first < a.second) {
            amin = a.first;
            amax = a.second;
        }
        else {
            amin = a.second;
            amax = a.first;
        }
        if (b.first < b.second){
            bmin = b.first;
            bmax = b.second;
        }
        else {
            bmin = b.second;
            bmax = b.first;
        }
        if (amin < bmin) return true;
        else if (amin == bmin) return (amax < bmax);
        return false;
    }
};

/**
 * @ingroup cg3core
 * @struct cmpPointY
 * @brief The cmpPointY structure implements a comparator for the Point class using Y coordinate first.
 *
 * It defines another minus operator on Point class, ordering on the components y, x and z. It can be used, for example,
 * when you need to store Point on ordered containers like std::set or std::map, and you want to order them using the y coordinate.
 *
 * Example:
 * \code{.cpp}
 * std::map<Pointd, int, cmpPointY<double>> map;
 * \endcode
 */
template <class T>
struct cmpPointY
{
    bool operator()(const Point3<T>& a, const Point3<T>& b) const
    {
        if (a == b) return false;
        if (a.y() == b.y() && a.x() == b.x()) return (a.z() < b.z());
        if (a.y() == b.y()) return (a.x() < b.x());
        return (a.y() < b.y());
    }
};

/**
 * @ingroup cg3core
 * @struct cmpPointZ
 * @brief The cmpPointZ structure implements a comparator for the Point class using Z coordinate first.
 *
 * It defines another minus operator on Point class, ordering on the components z, x and y. It can be used, for example,
 * when you need to store Point on ordered containers like std::set or std::map, and you want to order them using the z coordinate.
 *
 * Example:
 * \code{.cpp}
 * std::map<Pointd, int, cmpPointZ<double>> map;
 * \endcode
 */
template <class T>
struct cmpPointZ
{
    bool operator()(const Point3<T>& a, const Point3<T>& b) const
    {
        if (a == b) return false;
        if (a.z() == b.z() && a.x() == b.x()) return (a.y() < b.y());
        if (a.z() == b.z()) return (a.x() < b.x());
        return (a.z() < b.z());
    }
};

typedef cmpPointY<int> cmpPointiY;
typedef cmpPointY<float> cmpPointfY;
typedef cmpPointY<double> cmpPointdY;
typedef cmpPointY<double> cmpVec3Y;

typedef cmpPointZ<int> cmpPointiZ;
typedef cmpPointZ<float> cmpPointfZ;
typedef cmpPointZ<double> cmpPointdZ;
typedef cmpPointZ<double> cmpVec3Z;

} //namespace cg3

#endif // CG3_COMPARATORS_H

