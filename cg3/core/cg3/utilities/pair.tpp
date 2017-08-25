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
