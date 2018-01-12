/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "vector.h"

namespace cg3 {

/**
 * \~English
 * @brief This function computes a binary search of an element on a sorted std::vector
 * @param[in] n: the object that we are searching on the vector
 * @param[in] v: a sorted std::vector
 * @return the position index of the object if it is found, -1 otherwise
 *
 * \~Italian
 * @brief Questa funzione esegue una ricerca binaria di un elemento su un std::vector ordinato
 * @param[in] n: l'oggetto che si deve cercare all'interno del vector
 * @param[in] v: un std::vector ordinato
 * @return l'indice di posizione dell'oggetto se è stato trovato, -1 altrimenti
 */
template <typename T>
inline int binarySearch(const T &n, const std::vector<T> &v) {
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
 * @brief sortIndexes
 *
 * returns the indices corrispondence of the v vector sorted.
 *
 * @link https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
 *
 * @param v
 * @return
 */
template <typename T>
inline std::vector<size_t> sortIndexes(const std::vector<T> &v) {

    // initialize original index locations
    std::vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    std::sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

}
