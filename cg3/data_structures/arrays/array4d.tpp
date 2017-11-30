#include "array4d.h"

namespace cg3 {

///
/// Array4D
///

template <class T>
inline Array4D<T>::Array4D() : sizeX(0), sizeY(0), sizeZ(0), sizeW(0) {
    v.resize(0);
}

template <class T>
inline Array4D<T>::Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW) {
    v.resize(sizeX*sizeY*sizeZ*sizeW);
}

template <class T>
inline Array4D<T>::Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW, const T& value) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW) {
    v.resize(sizeX*sizeY*sizeZ*sizeW, value);
}

template <class T>
inline T& Array4D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) {
    return v[getIndex(i,j,k,l)];
}

template <class T>
inline T Array4D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) const {
    return v[getIndex(i,j,k,l)];
}

template <class T>
inline const T* Array4D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k) const {
    assert (i < sizeX);
    assert (j < sizeY);
    assert (k < sizeZ);
    return &(v[sizeW*(k + sizeZ*(j + sizeY*i))]);
}

template <class T>
inline unsigned long int Array4D<T>::getSizeX() const {
    return sizeX;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeY() const{
    return sizeY;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeZ() const {
    return sizeZ;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeW() const {
    return sizeW;
}

template <class T>
inline T&Array4D<T>::getMin() {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
const T&Array4D<T>::getMin() const {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
inline T&Array4D<T>::getMax() {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
const T&Array4D<T>::getMax() const {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
inline void Array4D<T>::setConstant(const T& c) {
    std::fill(v.begin(), v.end(), c);
}

template <class T>
inline void Array4D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w) {
    v.resize(x*y*z*w);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    sizeW = w;
}

template <class T>
inline void Array4D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w, const T& value) {
    v.resize(x*y*z*w, value);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    sizeW = w;
}

template<class T>
inline void Array4D<T>::clear() {
    v.clear();
    sizeX = sizeY = sizeZ = sizeW = 0;
}

template<class T>
inline void Array4D<T>::serialize(std::ofstream& binaryFile) const {
    Serializer::serializeObjectAttributes("cg3Array4D", binaryFile, sizeX, sizeY, sizeZ, sizeW, v);
}

template<class T>
inline void Array4D<T>::deserialize(std::ifstream& binaryFile) {
    Serializer::deserializeObjectAttributes("cg3Array4D", binaryFile, sizeX, sizeY, sizeZ, sizeW, v);
}

template <class T>
inline unsigned long int Array4D<T>::getIndex(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) {
    assert (i < sizeX);
    assert (j < sizeY);
    assert (k < sizeZ);
    assert (l < sizeW);
    return l + sizeW*(k + sizeZ*(j + sizeY*i));
}

}
