/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

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

#ifndef CG3_UTILS_H
#define CG3_UTILS_H

#define EPSILON 1e-4

#include <vector>
#include <memory>
#include "../geometry/point.h"
#include "../geometry/2d/point2d.h"
#include "../data_structures/color.h"

namespace cg3 {

namespace Common {

    static const std::array<Vec3, 6> AXIS {
        Vec3( 1, 0, 0),
        Vec3( 0, 1, 0),
        Vec3( 0, 0 ,1),
        Vec3(-1, 0, 0),
        Vec3( 0,-1, 0),
        Vec3( 0, 0,-1),
    };

    template <typename T>
    int binarySearch(const T &n, const std::vector<T> &v);

    template <typename T>
    bool epsilonEqual(T x, T v, double epsilon = EPSILON);

    template <typename T>
    bool epsilonEqual(const Point<T> &x, const Point<T> &v, double epsilon = EPSILON);

    bool fileExists(const std::string& filename);

    template <typename T>
    std::string toStringWithPrecision(const T& value, unsigned int precision = 2);

    double truncate(double d, unsigned int numberOfDecimalDigitsToKeep);

    void separateExtensionFromFilename(const std::string& fullname, std::string& rawname, std::string& extension);

    void separateFilenameFromPath(const std::string& fullpath, std::string& path, std::string& filename);

    #ifdef CG3_WITH_EIGEN
    void getRotationMatrix(Vec3 axis, double angle, Eigen::Matrix3d &m);

    Eigen::Matrix3d getRotationMatrix(Vec3 axis, double angle);
    #endif

    void getRotationMatrix(Vec3 axis, double angle, double m[][3]);

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

    static const std::vector<Color> dummycolors = {
        Color(182, 215, 168), //
        Color(159, 197, 232), //
        Color(234, 153, 153), //
        Color(255, 229, 153), //
        Color(162, 196, 201), //
        Color(213, 166, 189), //
        Color(164, 194, 244), //
        Color(221, 126, 107), //
        Color(249, 203, 156), //
        Color(180, 167, 214) //
    };

    template <typename T, typename AdjComparator>
    std::map<T, Color> smartColoring(const std::vector<T> &elements, AdjComparator comp, const std::vector<Color> &colors = dummycolors);


    template <typename T>
    std::vector<size_t> sortIndexes(const std::vector<T> &v);

    #ifdef CG3_WITH_EIGEN
    template <typename T, int ...A>
    std::vector<T> eigenVectorToStdVector(const Eigen::Matrix<T, A...>& v);

    template <typename T, int ...A>
    void removeRowFromEigenMatrix(Eigen::Matrix<T, A...> &m, unsigned int row);

    template <typename T, int ...A>
    void removeColumnFromEigenMatrix(Eigen::Matrix<T, A...> &m, unsigned int column);
    #endif

    bool isCounterClockwise(const std::vector<Point2Dd>& polygon);
}

}

#include "utils.cpp"

#endif // CG3_UTILS_H

