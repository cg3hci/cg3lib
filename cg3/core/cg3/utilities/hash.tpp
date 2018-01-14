/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "hash.h"

namespace cg3 {

inline void hashCombine(std::size_t& seed) {
    CG3_SUPPRESS_WARNING(seed);
}

/**
 * @brief hashCombine
 * @link https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
 * Example:\n
 * \code{.cpp}
 * std::size_t h=0;
 * hashCombine(h, obj1, obj2, obj3);
 * \endcode
 * @param seed
 */
template <typename T, typename... Rest>
inline void hashCombine(std::size_t& seed, const T& v, Rest... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    hashCombine(seed, rest...);
}

}

namespace std {

/**
 * @brief hash<std::pair<T1, T2> >::operator ()
 * combines tha hashes of the T1 and T2 elements.
 * It works only if the hash is specialized for T1 ans T2 types.
 * @param k
 * @return the hash of a std::pair
 */
template<typename T1, typename T2>
size_t hash<std::pair<T1, T2> >::operator()(const std::pair<T1, T2> &k) const {
    std::size_t seed = 0;
    cg3::hashCombine(seed, k.first, k.second);
    return seed;
}

/**
 * @brief hash<std::vector<T, A> >::operator ()
 * combines tha hashes of the elements of a vector.
 * It works only if the hash is specialized for the T type.
 * @param k
 * @return the hash of a vector
 */
template<typename T, typename ...A>
size_t hash<std::vector<T, A...> >::operator()(const std::vector<T, A...> &k) const {
    std::size_t seed = 0;
    for (const T& e : k){
        cg3::hashCombine(seed, e);
    }
    return seed;
}

/**
 * @brief hash<std::set<T, A> >::operator ()
 * combines tha hashes of the elements of a set.
 * It works only if the hash is specialized for the T type.
 * @param k
 * @return the hash of a set
 */
template<typename T, typename ...A>
size_t hash<std::set<T, A...> >::operator()(const std::set<T, A...> &k) const {
    std::size_t seed = 0;
    for (const T& e : k){
        cg3::hashCombine(seed, e);
    }
    return seed;
}

/**
 * @brief hash<std::list<T, A> >::operator ()
 * combines tha hashes of the elements of a list.
 * It works only if the hash is specialized for the T type.
 * @param k
 * @return the hash of a list
 */
template<typename T, typename ...A>
size_t hash<std::list<T, A...> >::operator()(const std::list<T, A...> &k) const {
    std::size_t seed = 0;
    for (const T& e : k){
        cg3::hashCombine(seed, e);
    }
    return seed;
}

/**
 * @brief hash<std::array<T, A> >::operator ()
 * combines tha hashes of the elements of an array.
 * It works only if the hash is specialized for the T type.
 * @param k
 * @return the hash of an array
 */
template<typename T, unsigned long int ...A>
size_t hash<std::array<T, A...> >::operator()(const std::array<T, A...> &k) const {
    std::size_t seed = 0;
    for (const T& e : k){
        cg3::hashCombine(seed, e);
    }
    return seed;
}

}
