/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef CG3_UTILS_H
#define CG3_UTILS_H

/**
 * \~English
 * @brief This header contains some generic functions that may be useful.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 *
 * \~Italian
 * @brief Questo header contiene alcune funzioni generiche che possono essere utili.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <vector>
#include <memory>
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <string>
#include <cstdlib>
#include "../geometry/point.h"
#include "../geometry/2d/point2d.h"
#include "../utilities/color.h"
#include "const.h"

namespace cg3 {

    template <typename T>
    bool epsilonEqual(T x, T v, double epsilon = CG3_EPSILON);

    template <typename T>
    bool epsilonEqual(const Point<T> &x, const Point<T> &v, double epsilon = CG3_EPSILON);

    double truncate(double d, unsigned int numberOfDecimalDigitsToKeep);

    template <typename T>
    bool isInBounds(const T& value, const T& low, const T& high);

    template <typename T, typename R, typename Comparator>
    bool isInBounds(const T& value, const R& low, const R& high, Comparator comp);

    template <typename T, typename AdjComparator>
    std::map<T, Color> smartColoring(const std::vector<T> &elements, AdjComparator comp, const std::vector<Color> &colors = PASTEL_COLORS);

    template <typename T>
    std::string typeName(bool specifyIfConst = true, bool specifyIfVolatile = true, bool specifyIfReference = true);

}

#include "utils.tpp"

#endif // CG3_UTILS_H

