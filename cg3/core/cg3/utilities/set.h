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

template<typename T>
std::set<T> intersection(
        const std::set<T> &a,
        const std::set<T> &b);

template<typename T>
std::set<T> union_(
        const std::set<T> &a,
        const std::set<T> &b);

template<typename T>
std::set<T> difference(
        const std::set<T> &a,
        const std::set<T> &b);

template<typename T>
bool isSubset(
        const std::set<T> &a,
        const std::set<T> &b);

} //namespace cg3

#include "set.tpp"

#endif // CG3_SET_H
