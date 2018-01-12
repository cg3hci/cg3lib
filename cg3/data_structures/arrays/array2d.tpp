/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "array2d.h"

namespace cg3 {

template <class T>
Array2D<T>::Array2D() : Array<T, 2>() {
}

template <class T>
inline Array2D<T>::Array2D(unsigned long int sizeX, unsigned long int sizeY) : Array<T, 2>(sizeX, sizeY){
}

/**
 * @brief Array2D<T>::Array2D
 * Initializes a 2D array with sizeX rows and sizeY columns.
 * All the values of the array will be initialized to the value passed as a parameter
 *
 * @param sizeX
 * @param sizeY
 * @param value
 */
template <class T>
inline Array2D<T>::Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value) {
    Array<T, 2>::v.resize(sizeX*sizeY, value);
    Array<T, 2>::sizes[0] = sizeX;
    Array<T, 2>::sizes[1] = sizeY;
}

/**
 * @brief Array2D<T>::getSizeX
 * Returns the number of rows of the array
 *
 * @return number of rows
 */
template <class T>
inline unsigned long int Array2D<T>::getSizeX() const {
    return Array<T, 2>::sizes[0];
}

/**
 * @brief Array2D<T>::getSizeY
 * Returns the number of columns of the array
 *
 * @return number of columns
 */
template <class T>
inline unsigned long int Array2D<T>::getSizeY() const{
    return Array<T, 2>::sizes[1];
}

/**
 * @brief Array2D<T>::rows
 * Returns the number of rows of the array
 *
 * @return number of rows
 */
template<class T>
inline unsigned long Array2D<T>::rows() const {
    return Array<T, 2>::sizes[0];
}

/**
 * @brief Array2D<T>::cols
 * Returns the number of columns of the array
 *
 * @return number of columns
 */
template<class T>
inline unsigned long Array2D<T>::cols() const {
    return Array<T, 2>::sizes[1];
}


template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a) {
    for (unsigned int i = 0; i < a.getSizeX(); i++){
        for (unsigned int j = 0; j < a.getSizeY(); j++){
            inputStream << std::setw(4) <<a(i,j) << " ";
        }
        inputStream << "\n";
    }
    return inputStream;
}

}
