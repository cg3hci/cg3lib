/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_MAP_H
#define CG3_MAP_H

#include "pair.h"
#include <map>

namespace cg3 {

template<typename A, typename B, template<class,class,class...> class M, class... Args>
inline std::multimap<B,A> flipMap(const M<A,B,Args...> &src);

template<typename K, typename V, typename ...A>
bool contains(
		const std::map<K, V, A...> &m,
		const K& obj);

} //namespace cg3

#include "map.cpp"

#endif // CG3_MAP_H
