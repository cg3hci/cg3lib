#ifndef CG3_ARRAY4D_H
#define CG3_ARRAY4D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "array.h"

namespace cg3 {

template <typename T>
class Array4D : public Array<T, 4> {
public:
    Array4D();
    Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW, const T& value);

    unsigned long int getSizeX() const;
    unsigned long int getSizeY() const;
    unsigned long int getSizeZ() const;
    unsigned long int getSizeW() const;
};

}

#include "array4d.tpp"

#endif // CG3_ARRAY4D_H
