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
Triangle<V>::Triangle() : v1(), v2(), v3() {
}

template<class V>
Triangle<V>::Triangle(const V& v1, const V& v2, const V& v3): v1(v1), v2(v2), v3(v3) {
}

template<class V>
V Triangle<V>::normal() const {
    V n = (v2 - v1).cross(v3 - v1);
    n.normalize();
    return n;
}

template<class V>
double Triangle<V>::area() const {
    return (((v3 - v1).cross(v2 - v1)).getLength() / 2);
}

template<class V>
inline void Triangle<V>::serialize(std::ofstream& binaryFile) const {
    cg3::serializeObjectAttributes("cg3Triangle", binaryFile, v1, v2, v3);
}

template<class V>
inline void Triangle<V>::deserialize(std::ifstream& binaryFile) {
    cg3::deserializeObjectAttributes("cg3Triangle", binaryFile, v1, v2, v3);
}

} // namespace cg3
