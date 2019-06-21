/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_VECTOR_H
#define CG3_VECTOR_H

#include <vector>

namespace cg3 {

template <typename T, typename ...A>
int binarySearch(const T &n, const std::vector<T, A...> &v);

template <typename T, typename ...A>
std::vector<size_t> sortIndexes(const std::vector<T, A...> &v);

template <typename T, typename ...A>
bool contains(const std::vector<T, A...>& v, const T& value);

template <typename T, typename ...A>
int positionOfElement(const std::vector<T, A...>& v, const T& value);


} //namespace cg3

#include "vector.cpp"

#endif // CG3_VECTOR_H
