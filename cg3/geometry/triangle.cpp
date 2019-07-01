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
    v{}
{
}

template<class T>
inline Triangle<T>::Triangle(const T& v1, const T& v2, const T& v3):
    v{v1, v2, v3}
{
}

template<class T>
inline const T& Triangle<T>::v1() const
{
	return v[0];
}

template<class T>
inline const T& Triangle<T>::v2() const
{
	return v[1];
}

template<class T>
inline const T& Triangle<T>::v3() const
{
	return v[2];
}

template<class T>
inline const T& Triangle<T>::operator[](unsigned int i) const
{
	assert(i < 3);
	return v[i];
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
	return v[0];
}

template<class T>
inline T& Triangle<T>::v2()
{
	return v[1];
}

template<class T>
inline T& Triangle<T>::v3()
{
	return v[2];
}

template<class T>
inline T& Triangle<T>::operator[](unsigned int i)
{
	assert(i < 3);
	return v[i];
}

template<class T>
inline void Triangle<T>::setV1(const T& v1)
{
	v[0] = v1;
}

template<class T>
inline void Triangle<T>::setV2(const T& v2)
{
	v[1] = v2;
}

template<class T>
inline void Triangle<T>::setV3(const T& v3)
{
	v[2] = v3;
}

template<class T>
inline void Triangle<T>::set(const T& v1, const T& v2, const T& v3)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}

template<class T>
inline cg3::Segment<T> Triangle<T>::side1() const
{
	return cg3::Segment<T>(v[0], v[1]);
}
template<class T>
inline cg3::Segment<T> Triangle<T>::side2() const
{
	return cg3::Segment<T>(v[1], v[2]);
}
template<class T>
inline cg3::Segment<T> Triangle<T>::side3() const
{
	return cg3::Segment<T>(v[2], v[0]);
}

template<class T>
inline std::vector<cg3::Segment<T>> Triangle<T>::sides() const
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
	T n = (v[1] - v[0]).cross(v[2] - v[0]);
    n.normalize();
    return n;
}

template<class T>
inline double Triangle<T>::area() const
{
	return (((v[2] - v[0]).cross(v[1] - v[0])).length() / 2);
}

template<class T>
inline double Triangle<T>::perimeter() const
{
	return v[0].dist(v[1]) + v[1].dist(v[2]) + v[2].dist(v[0]);
}

template<class T>
inline T Triangle<T>::barycenter() const
{
	return (v[0] + v[1] + v[2]) / 3;
}

template<class T>
inline void Triangle<T>::serialize(std::ofstream& binaryFile) const
{
	cg3::serializeObjectAttributes("cg3Triangle", binaryFile, v[0], v[1], v[2]);
}

template<class T>
inline void Triangle<T>::deserialize(std::ifstream& binaryFile)
{
	cg3::deserializeObjectAttributes("cg3Triangle", binaryFile, v[0], v[1], v[2]);
}

} //namespace cg3
