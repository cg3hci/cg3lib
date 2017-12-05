#ifndef CG3_ARRAY2D_H
#define CG3_ARRAY2D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "array.h"

namespace cg3 {

template <typename T>
class Array2D : public Array<T, 2> {
public:
    Array2D();
    Array2D(unsigned long int sizeX, unsigned long int sizeY);
    Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value);

    unsigned long int getSizeX() const;
    unsigned long int getSizeY() const;
    unsigned long int rows() const;
    unsigned long int cols() const;
};

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a);

}

#include "array2d.tpp"

#endif // CG3_ARRAY2D_H
