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

}

#include "map.tpp"

#endif // CG3_MAP_H
