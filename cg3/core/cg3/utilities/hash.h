/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_HASH_H
#define CG3_HASH_H

#include <vector>
#include <set>
#include <list>
#include <array>
#include "../cg3lib.h"

namespace cg3 {

inline void hashCombine(std::size_t& seed);

template <typename T, typename... Rest>
inline void hashCombine(std::size_t& seed, const T& v, Rest... rest);

}

namespace std {

template <typename T1, typename T2>
struct hash<std::pair<T1, T2>> {
    size_t operator()(const std::pair<T1, T2>& k) const;
};

template <typename T, typename ...A>
struct hash<std::vector<T, A...> > {
    size_t operator()(const std::vector<T, A...>& k) const;
};

template <typename T, typename ...A>
struct hash<std::set<T, A...> > {
    size_t operator()(const std::set<T, A...>& k) const;
};

template <typename T, typename ...A>
struct hash<std::list<T, A...> > {
    size_t operator()(const std::list<T, A...>& k) const;
};

template <typename T, unsigned long int ...A>
struct hash<std::array<T, A...> > {
    size_t operator()(const std::array<T, A...>& k) const;
};

}

#include "hash.tpp"

#endif // CG3_HASH_H
