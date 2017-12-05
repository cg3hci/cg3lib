#ifndef CG3_ARRAY3D_H
#define CG3_ARRAY3D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "array.h"

namespace cg3 {

template <typename T>
class Array3D : public Array<T, 3> {
public:
    Array3D();
    Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ);
    Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, const T& value);
    unsigned long int getSizeX() const;
    unsigned long int getSizeY() const;
    unsigned long int getSizeZ() const;
};

}

#include "array3d.tpp"

#endif // CG3_ARRAY3D_H
