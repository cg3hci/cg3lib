#include "hash.h"

namespace cg3 {

/**
 * @brief hash_combine
 * @link https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
 * @example
 * \code{.cpp}
 * std::size_t h=0;
 * hashCombine(h, obj1, obj2, obj3);
 * \endcode
 * @param seed
 */

inline void hashCombine(std::size_t& seed) {
    CG3_SUPPRESS_WARNING(seed);
}

template <typename T, typename... Rest>
inline void hashCombine(std::size_t& seed, const T& v, Rest... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    hashCombine(seed, rest...);
}

}
