/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_PAIR_H
#define CG3_PAIR_H

#include <utility>

namespace cg3 {

template<typename A, typename B>
inline std::pair<B,A> flipPair(const std::pair<A,B> &p);

}

#include "pair.tpp"

#endif // CG3_PAIR_H
