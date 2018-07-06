/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "triangle.h"
#include "../io/serialize.h"

namespace cg3 {

template <class T>
inline Triangle<T>::Triangle() :
    _v1(),
    _v2(),
    _v3()
{
}

template<class T>
inline Triangle<T>::Triangle(const T& v1, const T& v2, const T& v3):
    _v1(v1),
    _v2(v2),
    _v3(v3)
{
}

template<class T>
inline const T& Triangle<T>::v1() const
{
    return _v1;
}

template<class T>
inline const T& Triangle<T>::v2() const
{
    return _v2;
}

template<class T>
inline const T& Triangle<T>::v3() const
{
    return _v3;
}

template<class T>
inline std::vector<T> Triangle<T>::vertices() const
{
    std::vector<T> vertices(3);
    vertices[0] = v1();
    vertices[1] = v2();
    vertices[2] = v3();
    return vertices;
}


template<class T>
inline T& Triangle<T>::v1()
{
    return _v1;
}

template<class T>
inline T& Triangle<T>::v2()
{
    return _v2;
}

template<class T>
inline T& Triangle<T>::v3()
{
    return _v3;
}


template<class T>
inline void Triangle<T>::setV1(const T& v1)
{
    this->_v1 = v1;
}

template<class T>
inline void Triangle<T>::setV2(const T& v2)
{
    this->_v2 = v2;
}

template<class T>
inline void Triangle<T>::setV3(const T& v3)
{
    this->_v3 = v3;
}

template<class T>
inline void Triangle<T>::set(const T& v1, const T& v2, const T& v3)
{
    this->_v1 = v1;
    this->_v2 = v2;
    this->_v3 = v3;
}

template<class T>
inline cg3::Segment<T> Triangle<T>::side1() const
{
    return cg3::Segment<T>(_v1, _v2);
}
template<class T>
inline cg3::Segment<T> Triangle<T>::side2() const
{
    return cg3::Segment<T>(_v2, _v3);
}
template<class T>
inline cg3::Segment<T> Triangle<T>::side3() const
{
    return cg3::Segment<T>(_v3, _v1);
}

template<class T>
inline std::vector<cg3::Segment<T>> Triangle<T>::getSides() const
{
    std::vector<cg3::Segment<T>> sides(3);    
    sides[0] = side1();
    sides[1] = side2();
    sides[2] = side3();
    return sides;
}


template<class T>
inline T Triangle<T>::normal() const
{
    T n = (_v2 - _v1).cross(_v3 - _v1);
    n.normalize();
    return n;
}

template<class T>
inline double Triangle<T>::area() const
{
    return (((_v3 - _v1).cross(_v2 - _v1)).getLength() / 2);
}

template<class T>
inline double Triangle<T>::perimeter() const
{
    return _v1.dist(_v2) + _v2.dist(_v3) + _v3.dist(_v1);
}

template<class T>
inline T Triangle<T>::barycenter() const
{
    return (_v1 + _v2 +_v3) / 3;
}

template<class T>
inline void Triangle<T>::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Triangle", binaryFile, _v1, _v2, _v3);
}

template<class T>
inline void Triangle<T>::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Triangle", binaryFile, _v1, _v2, _v3);
}

} //namespace cg3
