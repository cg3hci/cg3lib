#ifndef CG3_MAP_H
#define CG3_MAP_H

#include "pair.h"
#include <map>

namespace cg3 {

template<typename A, typename B, template<class,class,class...> class M, class... Args>
inline std::multimap<B,A> flipMap(const M<A,B,Args...> &src);

}

#include "map.cpp"

#endif // CG3_MAP_H
