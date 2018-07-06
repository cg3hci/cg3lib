/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "segment.h"

#include <ostream>


namespace cg3 {

/* ----- Constructors/destructor ----- */

template <class T>
inline Segment<T>::Segment()
{
}

template <class T>
inline Segment<T>::Segment(const T& p1, const T& p2) :
    _p1(p1),
    _p2(p2)
{
}

/* ----- Getters ----- */

template <class T>
inline const T& Segment<T>::p1() const
{
    return _p1;
}

template <class T>
inline const T& Segment<T>::p2() const
{
    return _p2;
}

/* ----- Setters ----- */

template <class T>
inline void Segment<T>::setP1(const T& p1)
{
    this->_p1 = p1;
}

template <class T>
inline void Segment<T>::setP2(const T& p2)
{
    this->_p2 = p2;
}


template <class T>
inline void Segment<T>::set(const T& p1, const T& p2)
{
    setP1(p1);
    setP2(p2);
}

/* ----- Operators ----- */

template<class T>
inline double Segment<T>::length() const
{
    return _p1.dist(_p2);
}

/* ----- Operator override ----- */

template <class T>
inline bool Segment<T>::operator == (const Segment& otherSegment) const
{
    if (otherSegment._p1 != _p1)	return false;
    if (otherSegment._p2 != _p2)	return false;
    return true;
}

template <class T>
inline bool Segment<T>::operator != (const Segment& otherSegment) const
{
    if (otherSegment._p1 != _p1)	return true;
    if (otherSegment._p2 != _p2)	return true;
    return false;
}

template <class T>
inline bool Segment<T>::operator < (const Segment& otherSegment) const
{
    if (this->_p1 < otherSegment._p1) return true;
    if (this->_p1 > otherSegment._p1) return false;
    if (this->_p2 < otherSegment._p2) return true;
    return false;
}

template <class T>
inline bool Segment<T>::operator > (const Segment& otherSegment) const
{
    if (this->_p1 < otherSegment._p1) return false;
    if (this->_p1 > otherSegment._p1) return true;
    if (this->_p2 > otherSegment._p2) return true;
    return false;
}

template <class T>
inline bool Segment<T>::operator <= (const Segment& otherSegment) const
{
    return *this == otherSegment || *this < otherSegment;
}

template <class T>
inline bool Segment<T>::operator >= (const Segment& otherSegment) const
{
    return *this == otherSegment || *this > otherSegment;
}

/* ----- Serialization ----- */

template<class T>
inline void Segment<T>::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3Segment", binaryFile, _p1, _p2);
}

template<class T>
inline void Segment<T>::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3Segment", binaryFile, _p1, _p2);
}

/* ------ Utilities ------ */

template <class T>
std::ostream& operator<<(std::ostream& o, const Segment<T>& seg)
{
    o << "{" << seg.p1() << ", " << seg.p2() << "}";
    return o;
}

} //namespace cg3

//hash specialization
template<typename T>
inline std::size_t std::hash<cg3::Segment<T> >::operator()(const cg3::Segment<T> &k) const
{
    std::size_t h=0;
    cg3::hashCombine(h, k.p1(), k.p2());
    return h;
}
