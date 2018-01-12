/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "pair.h"

namespace cg3 {

/**
 * \~English
 * @brief this function flips a pair
 * @param[in] p: input pair
 * @return the flipped pair
 */
template<typename A, typename B>
inline std::pair<B,A> flipPair(const std::pair<A,B> &p) {
    return std::pair<B,A>(p.second, p.first);
}

}
