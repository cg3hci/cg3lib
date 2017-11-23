#ifndef CG3_ARRAY3D_H
#define CG3_ARRAY3D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "../../io/serialize.h"

namespace cg3 {

template <class T> class Array3D : SerializableObject{

    public:
        Array3D();
        Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ);
        Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, const T& value);
        T& operator () (unsigned long int i, unsigned long int j, unsigned long int k);
        T operator () (unsigned long int i, unsigned long int j, unsigned long int k) const;
        const T* operator () (unsigned long int i, unsigned long int j) const;

        unsigned long int getSizeX() const;
        unsigned long int getSizeY() const;
        unsigned long int getSizeZ() const;

        T& getMin();
        const T& getMin() const;
        T& getMax();
        const T& getMax() const;

        void setConstant(const T& c);

        void resize (unsigned long int x, unsigned long int y, unsigned long int z);
        void resize (unsigned long int x, unsigned long int y, unsigned long int z, const T& value);

        void clear();

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(unsigned long int i, unsigned long int j, unsigned long int k) const;

        unsigned long int sizeX, sizeY, sizeZ;
        std::vector<T> v;
    };

}

#include "array3d.tpp"

#endif // CG3_ARRAY3D_H
