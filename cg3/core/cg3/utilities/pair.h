#ifndef CG3_PAIR_H
#define CG3_PAIR_H

#include <utility>

namespace cg3 {

template<typename A, typename B>
inline std::pair<B,A> flipPair(const std::pair<A,B> &p);

}

#include "pair.tpp"

#endif // CG3_PAIR_H
