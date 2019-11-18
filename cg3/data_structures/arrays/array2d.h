/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_ARRAY2D_H
#define CG3_ARRAY2D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "array_.h"
#include "array_bool.h"

namespace cg3 {

/**
 * @brief The Array2D class
 * Specialization of cg3::Array class with 2 dimensions.
 */
template <typename T>
class Array2D : public Array<T, 2>
{
public:
    Array2D();
	Array2D(const Array<T, 2>& a);
    Array2D(unsigned long int sizeX, unsigned long int sizeY);
    Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value);
    Array2D(cg3::NestedInitializerLists<T, 2> values);

    unsigned long int sizeX() const;
    unsigned long int sizeY() const;
    unsigned long int rows() const;
    unsigned long int cols() const;
};

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a);

} //namespace cg3

#include "array2d.cpp"

#endif // CG3_ARRAY2D_H
