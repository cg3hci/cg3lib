#include "segment.h"

namespace cg3 {

/* ----- Constructors/destructor ----- */

template <class T>
inline Segment<T>::Segment()
{

}

template <class T>
inline Segment<T>::Segment(const T& p1, const T& p2) {
    set(p1, p2);
}

template <class T>
inline Segment<T>::Segment(const Segment& otherSegment) {
    set(otherSegment.getP1(), otherSegment.getP2());
}

template <class T>
inline Segment<T>::~Segment()
{

}


/* ----- Getters/setters ----- */

template <class T>
inline const T& Segment<T>::getP1() const {
    return p1;
}

template <class T>
inline const T& Segment<T>::getP2() const {
    return p2;
}

template <class T>
inline void Segment<T>::setP1(const T& p1) {
    this->p1 = p1;
}

template <class T>
inline void Segment<T>::setP2(const T& p2) {
    this->p2 = p2;
}



template <class T>
inline void Segment<T>::set(const T& p1, const T& p2) {
    setP1(p1);
    setP2(p2);
}


/* ----- Operator override ----- */

template <class T>
inline bool Segment<T>::operator == (const Segment& otherSegment) const {
    if (otherSegment.p1 != p1)	return false;
    if (otherSegment.p2 != p2)	return false;
    return true;
}

template <class T>
inline bool Segment<T>::operator != (const Segment& otherSegment) const {
    if (otherSegment.p1 != p1)	return true;
    if (otherSegment.p2 != p2)	return true;
    return false;
}

template <class T>
inline bool Segment<T>::operator < (const Segment& otherSegment) const {
    if (this->p1 < otherSegment.p1) return true;
    if (this->p1 > otherSegment.p1) return false;
    if (this->p2 < otherSegment.p2) return true;
    return false;
}

template <class T>
inline bool Segment<T>::operator > (const Segment& otherSegment) const {
    if (this->p1 < otherSegment.p1) return false;
    if (this->p1 > otherSegment.p1) return true;
    if (this->p2 > otherSegment.p2) return true;
    return false;
}

template <class T>
inline bool Segment<T>::operator <= (const Segment& otherSegment) const {
    return *this == otherSegment || *this < otherSegment;
}

template <class T>
inline bool Segment<T>::operator >= (const Segment& otherSegment) const {
    return *this == otherSegment || *this > otherSegment;
}

template <class T>
inline std::ostream& operator<<(std::ostream& inputStream, const Segment<T>& seg) {
    inputStream << seg.toString();
    return inputStream;
}


/* SerializableObject interface */

template <class T>
inline void Segment<T>::serialize(std::ofstream &myfile) const{
    Serializer::serialize(p1, myfile);
    Serializer::serialize(p2, myfile);
}

template <class T>
inline bool Segment<T>::deserialize(std::ifstream& myfile) {
    return (Serializer::deserialize(p1, myfile) && Serializer::deserialize(p2, myfile));
}


/* Utilities interface */

template <class T>
std::string Segment<T>::toString() const {
    std::stringstream ss;
    ss << "{ " << p1 << ";" << p2 << " }";
    std::string s1 = ss.str();
    return s1;
}

}
