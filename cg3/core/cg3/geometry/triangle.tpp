/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "triangle.h"
#include "../io/serialize.h"

namespace cg3 {

template <class V>
inline Triangle<V>::Triangle() : _v1(), _v2(), _v3() {
}

template<class V>
inline Triangle<V>::Triangle(const V& v1, const V& v2, const V& v3): _v1(v1), _v2(v2), _v3(v3) {
}

template<class V>
inline V Triangle<V>::normal() const {
    V n = (_v2 - _v1).cross(_v3 - _v1);
    n.normalize();
    return n;
}

template<class V>
inline double Triangle<V>::area() const {
    return (((_v3 - _v1).cross(_v2 - _v1)).getLength() / 2);
}

template<class V>
inline V Triangle<V>::v1() const {
    return _v1;
}

template<class V>
inline V Triangle<V>::v2() const {
    return _v2;
}

template<class V>
inline V Triangle<V>::v3() const {
    return _v3;
}

template<class V>
inline V Triangle<V>::barycenter() const {
    return (_v1 + _v2 +_v3) / 3;
}

template<class V>
inline void Triangle<V>::serialize(std::ofstream& binaryFile) const {
    cg3::serializeObjectAttributes("cg3Triangle", binaryFile, _v1, _v2, _v3);
}

template<class V>
inline void Triangle<V>::deserialize(std::ifstream& binaryFile) {
    cg3::deserializeObjectAttributes("cg3Triangle", binaryFile, _v1, _v2, _v3);
}

} // namespace cg3
