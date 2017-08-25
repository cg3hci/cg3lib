#ifndef CG3_ARRAY4D_H
#define CG3_ARRAY4D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "../../io/serialize.h"

namespace cg3 {

template <class T> class Array4D : public SerializableObject{

    public:
        Array4D();
        Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW);
        Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW, const T& value);
        T& operator () (unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l);
        T operator () (unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) const;
        const T* operator () (unsigned long int i, unsigned long int j, unsigned long int k) const;

        unsigned long int getSizeX() const;
        unsigned long int getSizeY() const;
        unsigned long int getSizeZ() const;
        unsigned long int getSizeW() const;

        T& getMin();
        const T& getMin() const;
        T& getMax();
        const T& getMax() const;

        void setConstant(const T& c);

        void resize (unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w);
        void resize (unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w, const T& value);

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        bool deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l);

        unsigned long int sizeX, sizeY, sizeZ, sizeW;
        std::vector<T> v;
};

}

#include "array4d.tpp"

#endif // CG3_ARRAY4D_H
