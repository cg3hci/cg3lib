#ifndef CG3_HASH_H
#define CG3_HASH_H

#include "../cg3lib.h"

namespace cg3 {

inline void hashCombine(std::size_t& seed);

template <typename T, typename... Rest>
inline void hashCombine(std::size_t& seed, const T& v, Rest... rest);

}

#include "hash.tpp"

#endif // CG3_HASH_H
