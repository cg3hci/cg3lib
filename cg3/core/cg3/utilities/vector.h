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

template <typename T>
int binarySearch(const T &n, const std::vector<T> &v);

template <typename T>
std::vector<size_t> sortIndexes(const std::vector<T> &v);

}

#include "vector.tpp"

#endif // CG3_VECTOR_H
