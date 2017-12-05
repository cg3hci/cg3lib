#include "array3d.h"

namespace cg3 {

template <class T>
Array3D<T>::Array3D() : Array<T,3>() {
}

template <class T>
inline Array3D<T>::Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ) : Array<T,3>(sizeX, sizeY, sizeZ){
}

template <class T>
inline Array3D<T>::Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, const T& value) {
    Array<T, 3>::v.resize(sizeX*sizeY*sizeZ, value);
    Array<T, 3>::sizes[0] = sizeX;
    Array<T, 3>::sizes[1] = sizeY;
    Array<T, 3>::sizes[2] = sizeZ;
}

template <class T>
inline unsigned long int Array3D<T>::getSizeX() const {
    return Array<T, 3>::sizes[0];
}

template <class T>
inline unsigned long int Array3D<T>::getSizeY() const{
    return Array<T, 3>::sizes[1];
}

template <class T>
inline unsigned long int Array3D<T>::getSizeZ() const {
    return Array<T, 3>::sizes[2];
}

}
