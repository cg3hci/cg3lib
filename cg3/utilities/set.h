/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SET_H
#define CG3_SET_H

#include <set>

namespace cg3 {

template<typename T, typename ...A>
std::set<T, A...> intersection(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b);

template<typename T, typename ...A>
std::set<T, A...> union_(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b);

template<typename T, typename ...A>
std::set<T, A...> difference(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b);

template<typename T, typename ...A>
bool isSubset(
		const std::set<T, A...> &a,
		const std::set<T, A...> &b);

template<typename T, typename ...A>
bool contains(
		const std::set<T, A...> &s,
        const T& obj);

} //namespace cg3

#include "set.cpp"

#endif // CG3_SET_H
