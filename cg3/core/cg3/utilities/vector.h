#ifndef CG3_VECTOR_H
#define CG3_VECTOR_H

#include <vector>

namespace cg3 {

template <typename T>
int binarySearch(const T &n, const std::vector<T> &v);

template <typename T>
std::vector<size_t> sortIndexes(const std::vector<T> &v);

}

#include "vector.ipp"

#endif // CG3_VECTOR_H
