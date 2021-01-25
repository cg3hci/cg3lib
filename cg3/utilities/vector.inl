/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "vector.h"
#include <algorithm>
#include <numeric>

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief This function computes a binary search of an element on a sorted std::vector
 * @param[in] n: the object that we are searching on the vector
 * @param[in] v: a sorted std::vector
 * @return the position index of the object if it is found, -1 otherwise
 */
template <typename T, typename ...A>
inline int binarySearch(const T &n, const std::vector<T, A...> &v) {
    int first = 0, last =v.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) first = mid + 1;
        else if (v[mid] == n) return mid;
        else last = mid - 1;
    }
    return -1;
}

/**
 * @ingroup cg3core
 * @brief Returns the indices corrispondence of the v vector sorted.
 *
 * @link https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
 *
 * @param v
 * @return
 */
template <typename T, typename ...A>
inline std::vector<size_t> sortIndexes(const std::vector<T, A...> &v)
{
    // initialize original index locations
    std::vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    std::sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

/**
 * @ingroup cg3core
 * @brief Returns true if the element exists in the vector.
 *
 * @param v
 * @param value
 * @return
 */
template<typename T, typename ...A>
inline bool contains(const std::vector<T, A...>& v, const T& value)
{
    return std::find(v.begin(), v.end(), value) != v.end();
}

/**
 * @ingroup cg3core
 * @brief Returns the position index of the element if it exists in the vector,
 * -1 otherwise.
 *
 * @param v
 * @param value
 * @return
 */
template<typename T, typename ...A>
int positionOfElement(const std::vector<T, A...>& v, const T& value)
{
    typename std::vector<T>::const_iterator it = std::find(v.begin(), v.end(), value);
    if (it == v.end())
        return -1;
    return std::distance(v.begin(), it);
}

} //namespace cg3
