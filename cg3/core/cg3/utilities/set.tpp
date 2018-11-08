/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "set.h"
#include <algorithm>

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief intersection
 * @param a
 * @param b
 * @return
 */
template<typename T>
inline std::set<T> intersection(
        const std::set<T> &a,
        const std::set<T> &b)
{
    std::set<T> intersect;
    std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(intersect,intersect.begin()));
    return intersect;
}

/**
 * @ingroup cg3core
 * @brief union_
 * @param a
 * @param b
 * @return
 */
template<typename T>
inline std::set<T> union_(
        const std::set<T> &a,
        const std::set<T> &b)
{
    std::set<T> u;
    std::set_union(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(u,u.begin()));
    return u;
}

/**
 * @ingroup cg3core
 * @brief difference
 * @param a
 * @param b
 * @return
 */
template<typename T>
inline std::set<T> difference(
        const std::set<T> &a,
        const std::set<T> &b)
{
    std::set<T> diff;
    std::set_difference(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(diff,diff.begin()));
    return diff;
}

/**
 * @ingroup cg3core
 * @brief isSubset
 * @param a
 * @param b
 * @return
 */
template<typename T>
inline bool isSubset(
        const std::set<T> &a,
        const std::set<T> &b)
{
    return std::includes(b.begin(), b.end(), a.begin(), a.end());
}

/**
 * @ingroup cg3core
 * @brief contains
 * @param s
 * @param obj
 * @return
 */
template<typename T>
bool contains(const std::set<T>& s, const T& obj)
{
    return s.find(obj) != s.end();
}

} //namespace cg3
