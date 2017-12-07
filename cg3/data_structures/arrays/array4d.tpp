#include "array4d.h"

namespace cg3 {

template<typename T>
Array4D<T>::Array4D() : Array<T, 4>() {
}

template <class T>
inline Array4D<T>::Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW, const T& value) {
    Array<T, 4>::v.resize(sizeX*sizeY*sizeZ*sizeW, value);
    Array<T, 4>::sizes[0] = sizeX;
    Array<T, 4>::sizes[1] = sizeY;
    Array<T, 4>::sizes[2] = sizeZ;
    Array<T, 4>::sizes[3] = sizeW;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeX() const {
    return Array<T, 4>::sizes[0];
}

template <class T>
inline unsigned long int Array4D<T>::getSizeY() const{
    return Array<T, 4>::sizes[1];
}

template <class T>
inline unsigned long int Array4D<T>::getSizeZ() const {
    return Array<T, 4>::sizes[2];
}

template <class T>
inline unsigned long int Array4D<T>::getSizeW() const {
    return Array<T, 4>::sizes[3];
}

}