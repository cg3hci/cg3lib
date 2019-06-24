/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "utils.h"
#include <random>


namespace cg3 {

/**
 * @ingroup cg3core
 * @brief This function computes an equality between two parameters considering an epsilon offset
 * @param[in] x: first parameter
 * @param[in] v: second parameter
 * @param[in] epsilon: offset for equality, default value 0.0000001
 * @return true if the two parameters are equals on the epsilon interval, false otherwise
 */
template <typename T>
inline bool epsilonEqual(T x, T v, double epsilon)
{
    if (std::abs(x-v) < epsilon) return true;
    return false;
}

/**
 * @ingroup cg3core
 * @brief This function computes an equality between two Points considering an epsilon offset
 * @param[in] x: first Point parameter
 * @param[in] v: second Point parameter
 * @param[in] epsilon: offset for equality, default value 0.0000001
 * @return true if the two Points are equals on the epsilon interval, false otherwise
 */
template <typename T>
inline bool epsilonEqual(const Point3<T> &x, const Point3<T> &v, double epsilon)
{
    if ((epsilonEqual(x.x(), v.x(), epsilon)) &&
            (epsilonEqual(x.y(), v.y(), epsilon)) &&
            (epsilonEqual(x.z(), v.z(), epsilon)))
        return true;
    else return false;
}

/**
 * @ingroup cg3core
 * @brief This function computes an equality between two Point2D considering an epsilon offset
 * @param[in] x: first Point parameter
 * @param[in] v: second Point parameter
 * @param[in] epsilon: offset for equality, default value 0.0000001
 * @return true if the two Points are equals on the epsilon interval, false otherwise
 */
template <typename T>
inline bool epsilonEqual(const Point2<T> &x, const Point2<T> &v, double epsilon)
{
    if ((epsilonEqual(x.x(), v.x(), epsilon)) &&
            (epsilonEqual(x.y(), v.y(), epsilon)))
        return true;
    else return false;
}

/**
 * @ingroup cg3core
 * @brief randomPoint
 * @param bb
 * @return
 */
inline Point3d randomPoint(const BoundingBox3& bb)
{
    static std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> distx(bb.minX(), bb.maxX());
    std::uniform_real_distribution<> disty(bb.minY(), bb.maxY());
    std::uniform_real_distribution<> distz(bb.minZ(), bb.maxZ());
    return Point3d(distx(e2), disty(e2), distz(e2));
}

/**
 * @ingroup cg3core
 * @brief randomDirection
 * @link https://stackoverflow.com/questions/5408276/sampling-uniformly-distributed-random-points-inside-a-spherical-volume
 * @return
 */
inline Vec3d randomDirection()
{
    static std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> distphi(0,2*M_PI);
    std::uniform_real_distribution<> disttheta(-1,1);

    double phi = distphi(e2);
    double costheta = disttheta(e2);

    double theta = std::acos(costheta);

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);
    return Vec3d(x,y,z);
}


/**
 * @ingroup cg3core
 * @brief truncate
 * @param d
 * @param numberOfDecimalDigitsToKeep
 * @return
 */
inline double truncate(double d, unsigned int numberOfDecimalDigitsToKeep)
{
    int tmp = (int)((10*numberOfDecimalDigitsToKeep)*d);
    if (numberOfDecimalDigitsToKeep > 0)
        return (double) tmp / (10*numberOfDecimalDigitsToKeep);
    else return d;
}

/**
 * @ingroup cg3core
 * @brief isInBounds
 * @param value
 * @param low
 * @param high
 * @return
 */
template <typename T>
inline bool isInBounds(const T& value, const T& low, const T& high)
{
    return !(value < low) && !(high < value);
}

/**
 * @ingroup cg3core
 * @brief isInBounds
 * @param value
 * @param low
 * @param high
 * @param comp
 * @return
 */
template <typename T, typename R, typename Comparator>
inline bool isInBounds(const T& value, const R& low, const R& high, Comparator comp)
{
    return !comp(value, low) && !comp(high, value);
}

/**
 * @ingroup cg3core
 * Returns true if the two intervals A and B overlap each other (extremes included)
 */
template<typename T>
bool intervalOverlap(const T &minA, const T &maxA, const T &minB, const T &maxB)
{
	return minA <= maxB && minB <= maxA;
}

/**
 * @ingroup cg3core
 * @brief smartColoring
 * @param elements
 * @param comp
 * @param colors
 * @return
 */
template <typename T, typename AdjComparator>
inline std::map<T, Color> smartColoring(
        const std::vector<T> &elements,
        AdjComparator comp,
        const std::vector<Color> &colors)
{
    std::set<T> colored;
    std::map<T, Color> colorMap;
    for (const T i : elements){
        if (colored.find(i) == colored.end()){
            std::set<Color> adjColors;
            std::set<T> adjacences = comp.getAdjacences(i);
            for (T adj : adjacences){
                if (colored.find(adj) != colored.end())
                    adjColors.insert(colorMap[adj]);
            }

            Color color;
            bool finded = false;
            for (unsigned int k = 0; k < colors.size() && !finded; k++){
                if (adjColors.find(colors[k]) == adjColors.end()){
                    finded = true;
                    color = colors[k];
                }
            }
            if (finded){
                colorMap[i] = color;
                colored.insert(i);
            }
            else
                colorMap[i] = Color(0,0,0);
        }
    }
    return colorMap;
}

/**
 * @ingroup cg3core
 * @brief typeName
 * Returns the type of T as a std::string
 *
 * Example.\n
 * \code{.cpp}
 * int i;
 * std::cout << "Type of i is " << typeName<decltype(i)>() << "\n";
 * \endcode
 *
 * @link https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
 * @return the type of T as a std::string
 */
template<typename T>
inline std::string typeName(
        bool specifyIfConst,
        bool specifyIfVolatile,
        bool specifyIfReference)
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own(
    #ifndef _MSC_VER
                    abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
    #else
                    nullptr,
    #endif
                    std::free);
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value && specifyIfConst)
        r += " const";
    if (std::is_volatile<TR>::value && specifyIfVolatile)
        r += " volatile";
    if (specifyIfReference){
        if (std::is_lvalue_reference<T>::value)
            r += "&";
        else if (std::is_rvalue_reference<T>::value)
            r += "&&";
    }
    return r;
}

} //namespace cg3
