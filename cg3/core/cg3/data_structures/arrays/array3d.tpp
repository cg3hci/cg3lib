#include "array3d.h"

namespace cg3 {

template <class T>
inline Array3D<T>::Array3D() : sizeX(0), sizeY(0), sizeZ(0) {
    v.resize(0);
}

template <class T>
inline Array3D<T>::Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {
    v.resize(sizeX*sizeY*sizeZ);
}

template <class T>
inline Array3D<T>::Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, const T& value) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {
    v.resize(sizeX*sizeY*sizeZ, value);
}

template <class T>
inline T& Array3D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k) {
    return v[getIndex(i,j,k)];
}

template <class T>
inline T Array3D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k) const {
    return v[getIndex(i,j,k)];
}

template <class T>
inline const T* Array3D<T>::operator ()(unsigned long int i, unsigned long int j) const{
    assert (i < sizeX);
    assert (j < sizeY);
    return &(v[sizeZ*(j + sizeY*i)]);
}

template <class T>
inline unsigned long int Array3D<T>::getSizeX() const {
    return sizeX;
}

template <class T>
inline unsigned long int Array3D<T>::getSizeY() const{
    return sizeY;
}

template <class T>
inline unsigned long int Array3D<T>::getSizeZ() const {
    return sizeZ;
}

template <class T>
inline T&Array3D<T>::getMin() {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
const T&Array3D<T>::getMin() const {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
inline T&Array3D<T>::getMax() {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
const T&Array3D<T>::getMax() const {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
inline void Array3D<T>::setConstant(const T& c) {
    std::fill(v.begin(), v.end(), c);
}

template <class T>
inline void Array3D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z) {
    v.resize(x*y*z);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
}

template <class T>
inline void Array3D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z, const T& value) {
    v.resize(x*y*z, value);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
}

template <class T>
inline void Array3D<T>::serialize(std::ofstream& binaryFile) const {
    Serializer::serialize(sizeX, binaryFile);
    Serializer::serialize(sizeY, binaryFile);
    Serializer::serialize(sizeZ, binaryFile);
    for (unsigned int i = 0; i < v.size(); ++i)
        Serializer::serialize(v[i], binaryFile);
}

template <class T>
inline bool Array3D<T>::deserialize(std::ifstream& binaryFile) {
    Array3D<T> tmp;
    int begin = binaryFile.tellg();
    if (Serializer::deserialize(tmp.sizeX, binaryFile) &&
            Serializer::deserialize(tmp.sizeY, binaryFile) &&
            Serializer::deserialize(tmp.sizeZ, binaryFile)) {
        tmp.v.resize(tmp.sizeX*tmp.sizeY*tmp.sizeZ);
        for (unsigned int i = 0; i < tmp.v.size(); ++i){
            if (! Serializer::deserialize(tmp.v[i], binaryFile)){
                binaryFile.clear();
                binaryFile.seekg(begin);
                return false;
            }
        }
        *this = std::move(tmp);
        return true;
    }
    else{
        binaryFile.clear();
        binaryFile.seekg(begin);
        return false;
    }
}

template <class T>
inline unsigned long int Array3D<T>::getIndex(unsigned long int i, unsigned long int j, unsigned long int k) const {
    assert (i < sizeX);
    assert (j < sizeY);
    assert (k < sizeZ);
    return k+sizeZ*(j + sizeY*i);
}

}
