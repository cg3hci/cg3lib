/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_UTILS_H
#define CG3_UTILS_H

#include <vector>
#include <memory>
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <string>
#include <cstdlib>
#include <map>
#include "../geometry/point.h"
#include "../geometry/2d/point2d.h"
#include "../utilities/color.h"
#include "const.h"

namespace cg3 {

namespace internal {
    static BoundingBox dummyBB(cg3::Pointd(), cg3::Pointd(1,1,1));
}

template <typename T>
bool epsilonEqual(T x, T v, double epsilon = CG3_EPSILON);

template <typename T>
bool epsilonEqual(const Point<T> &x, const Point<T> &v, double epsilon = CG3_EPSILON);

template <typename T>
bool epsilonEqual(const Point2D<T> &x, const Point2D<T> &v, double epsilon = CG3_EPSILON);

Pointd randomPoint(const BoundingBox& bb = internal::dummyBB);

double truncate(double d, unsigned int numberOfDecimalDigitsToKeep);

template <typename T>
bool isInBounds(const T& value, const T& low, const T& high);

template <typename T, typename R, typename Comparator>
bool isInBounds(const T& value, const R& low, const R& high, Comparator comp);

template <typename T, typename AdjComparator>
std::map<T, Color> smartColoring(
        const std::vector<T> &elements,
        AdjComparator comp,
        const std::vector<Color> &colors = PASTEL_COLORS);

template <typename T>
std::string typeName(
        bool specifyIfConst = true,
        bool specifyIfVolatile = true,
        bool specifyIfReference = true);

} //namespace cg3

#include "utils.tpp"

#endif // CG3_UTILS_H

