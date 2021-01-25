/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "array4d.h"

namespace cg3 {

template<typename T>
Array4D<T>::Array4D() : Array<T, 4>()
{
}

template<typename T>
Array4D<T>::Array4D(const Array<T, 4>& a) : Array<T, 4>(a)
{
}

template <class T>
inline Array4D<T>::Array4D(
        unsigned long int sizeX,
        unsigned long int sizeY,
        unsigned long int sizeZ,
        unsigned long int sizeW) :
    Array<T,4>(sizeX, sizeY, sizeZ, sizeW)
{
}

template <class T>
inline Array4D<T>::Array4D(
        unsigned long int sizeX,
        unsigned long int sizeY,
        unsigned long int sizeZ,
        unsigned long int sizeW,
        const T& value)
{
    Array<T, 4>::v.resize(sizeX*sizeY*sizeZ*sizeW, value);
    Array<T, 4>::sizes[0] = sizeX;
    Array<T, 4>::sizes[1] = sizeY;
    Array<T, 4>::sizes[2] = sizeZ;
    Array<T, 4>::sizes[3] = sizeW;
}

template <class T>
inline Array4D<T>::Array4D(cg3::NestedInitializerLists<T, 4> values)
{
    Array<T, 4>::initializeNestedLists(values);
}

template <class T>
inline unsigned long int Array4D<T>::sizeX() const
{
    return Array<T, 4>::sizes[0];
}

template <class T>
inline unsigned long int Array4D<T>::sizeY() const
{
    return Array<T, 4>::sizes[1];
}

template <class T>
inline unsigned long int Array4D<T>::sizeZ() const
{
    return Array<T, 4>::sizes[2];
}

template <class T>
inline unsigned long int Array4D<T>::sizeW() const
{
    return Array<T, 4>::sizes[3];
}

} //namespace cg3
