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
#include "../geometry/point.h"
#include "../geometry/2d/point2d.h"
#include "../data_structures/color.h"
#include "const.h"

namespace cg3 {

namespace Common {

    template <typename T>
    int binarySearch(const T &n, const std::vector<T> &v);

    template <typename T>
    bool epsilonEqual(T x, T v, double epsilon = CG3_EPSILON);

    template <typename T>
    bool epsilonEqual(const Point<T> &x, const Point<T> &v, double epsilon = CG3_EPSILON);

    bool fileExists(const std::string& filename);

    template <typename T>
    std::string toStringWithPrecision(const T& value, unsigned int precision = 2);

    double truncate(double d, unsigned int numberOfDecimalDigitsToKeep);

    void separateExtensionFromFilename(const std::string& fullname, std::string& rawname, std::string& extension);

    void separateFilenameFromPath(const std::string& fullpath, std::string& path, std::string& filename);

    template<typename T>
    std::set<T> setIntersection(const std::set<T> &a, const std::set<T> &b);

    template<typename T>
    std::set<T> setUnion(const std::set<T> &a, const std::set<T> &b);

    template<typename T>
    std::set<T> setDifference(const std::set<T> &a, const std::set<T> &b);

    template<typename T>
    bool isSubset(const std::set<T> &a, const std::set<T> &b);

    std::string executeCommand(const std::string& cmd);

    std::string executeCommand(const char* cmd);

    template<typename A, typename B>
    inline std::pair<B,A> flipPair(const std::pair<A,B> &p);

    template<typename A, typename B, template<class,class,class...> class M, class... Args>
    inline std::multimap<B,A> flipMap(const M<A,B,Args...> &src);

    template <typename T>
    bool isInBounds(const T& value, const T& low, const T& high);

    template <typename T, typename R, typename Comparator>
    bool isInBounds(const T& value, const R& low, const R& high, Comparator comp);


    template <typename T, typename AdjComparator>
    std::map<T, Color> smartColoring(const std::vector<T> &elements, AdjComparator comp, const std::vector<Color> &colors = PASTEL_COLORS);


    template <typename T>
    std::vector<size_t> sortIndexes(const std::vector<T> &v);

    bool isCounterClockwise(const std::vector<Point2Dd>& polygon);
}

}

#include "utils.cpp"

#endif // CG3_UTILS_H

