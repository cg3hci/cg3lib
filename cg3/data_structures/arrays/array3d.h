/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_ARRAY3D_H
#define CG3_ARRAY3D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "array.h"
#include "array_bool.h"

namespace cg3 {

/**
 * @brief The Array3D class
 * Specialization of cg3::Array class with 3 dimensions.
 */
template <typename T>
class Array3D : public Array<T, 3>
{
public:
    Array3D();
    Array3D(
            unsigned long int sizeX,
            unsigned long int sizeY,
            unsigned long int sizeZ);
    Array3D(
            unsigned long int sizeX,
            unsigned long int sizeY,
            unsigned long int sizeZ,
            const T& value);
    Array3D(cg3::NestedInitializerLists<T, 3> values);
    unsigned long int sizeX() const;
    unsigned long int sizeY() const;
    unsigned long int sizeZ() const;

    #ifdef CG3_OLD_NAMES_COMPATIBILITY
    inline unsigned long int getSizeX() const {return sizeX();}
    inline unsigned long int getSizeY() const {return sizeY();}
    inline unsigned long int getSizeZ() const {return sizeZ();}
    #endif
};

} //namespace cg3

#include "array3d.tpp"

#endif // CG3_ARRAY3D_H
