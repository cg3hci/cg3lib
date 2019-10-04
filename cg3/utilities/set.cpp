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
template<typename T, typename ...A>
inline std::set<T, A...> intersection(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b)
{
	std::set<T, A...> intersect;
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
template<typename T, typename ...A>
inline std::set<T, A...> union_(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b)
{
	std::set<T, A...> u;
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
template<typename T, typename ...A>
inline std::set<T, A...> difference(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b)
{
	std::set<T, A...> diff;
    std::set_difference(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(diff,diff.begin()));
    return diff;
}

/**
 * @ingroup cg3core
 * @param a
 * @param b
 * @return returns true if set a is subset of set b, false otherwise
 */
template<typename T, typename ...A>
inline bool isSubset(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b)
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
template<typename T, typename ...A>
inline bool contains(const std::set<T, A...>& s, const T& obj)
{
    return s.find(obj) != s.end();
}

} //namespace cg3
