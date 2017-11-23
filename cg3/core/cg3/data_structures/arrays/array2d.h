#ifndef CG3_ARRAY2D_H
#define CG3_ARRAY2D_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "../../io/serialize.h"

namespace cg3 {

template <class T> class Array2D : SerializableObject{

    public:
        Array2D();
        Array2D(unsigned long int sizeX, unsigned long int sizeY);
        Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value);
        T& operator () (unsigned long int i, unsigned long int j);
        T operator () (unsigned long int i, unsigned long int j) const;
        const T* operator () (unsigned long int i) const;

        unsigned long int getSizeX() const;
        unsigned long int getSizeY() const;
        unsigned long int rows() const;
        unsigned long int cols() const;

        T& getMin();
        const T& getMin() const;
        T& getMax();
        const T& getMax() const;

        void setConstant(const T& c);

        void resize (unsigned long int x, unsigned long int y);
        void resize (unsigned long int x, unsigned long int y, const T& value);
        void conservativeResize(unsigned long int x, unsigned long int y);

        void clear();

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(unsigned long int i, unsigned long int j) const;

        unsigned long int sizeX, sizeY;
        std::vector<T> v;        
    };

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a);

}

#include "array2d.tpp"

#endif // CG3_ARRAY2D_H
