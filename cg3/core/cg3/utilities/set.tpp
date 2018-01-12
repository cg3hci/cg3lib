/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "set.h"

namespace cg3 {

template<typename T>
inline std::set<T> setIntersection(const std::set<T> &a, const std::set<T> &b){
    std::set<T> intersect;
    std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(intersect,intersect.begin()));
    return intersect;
}

template<typename T>
inline std::set<T> setUnion(const std::set<T> &a, const std::set<T> &b){
    std::set<T> u;
    std::set_union(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(u,u.begin()));
    return u;
}

template<typename T>
inline std::set<T> setDifference(const std::set<T> &a, const std::set<T> &b){
    std::set<T> diff;
    std::set_difference(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(diff,diff.begin()));
    return diff;
}

template<typename T>
inline bool isSubset(const std::set<T> &a, const std::set<T> &b){
    return std::includes(b.begin(), b.end(), a.begin(), a.end());
}

}
