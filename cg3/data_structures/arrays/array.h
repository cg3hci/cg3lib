/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_ARRAY_H
#define CG3_ARRAY_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include <cg3/io/serialize.h>

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * @brief The Array class
 * This is a dynamically allocated N-dimensional array, stored in RowWise mode.
 * All its elements are stored contiguously. For array 1D please use std::vector or std::array.
 *
 * For D-dimensional array you can declare your array in this way:
 * \code{.cpp}
 * cg3::Array<Type, D> array;
 * \endcode
 *
 * Where Type is a generic primitive or user-defined type and D is an unsigned integer that
 * represents the dimensions of the aray.
 *
 * You can also specify the sizes of the array on initialization:
 * \code{.cpp}
 * cg3::Array<int, 3> array(n,m,l);
 * \endcode
 *
 * In this example, array is a 3-dimensional array with sizes n*m*l.
 * The sizes of the array can be accessed using "size" member function.
 * You can access to its elements by using () operator:
 * \code{.cpp}
 * for (unsigned int i = 0; i < array.size(0); i++)
 *      for (unsigned int j = 0; j < array.size(1); j++)
 *          for (unsigned int k = 0; k < array.size(2); k++)
 *              array(i,j,k) = someFunction();
 * \endcode
 *
 */
template <class T, size_t N>
class Array : SerializableObject {
        static_assert(N > 0, "Array dimension must be > 0.");

    public:
        Array();
        template<typename... Sizes>
        Array(Sizes... sizes);
        constexpr unsigned long int dimensions() const;
        template<typename... I>
        T& operator () (I... indices);
        template<typename... I>
        T operator () (I... indices) const;
        template<typename... I>
        const T* cArray(I... indices) const;

        void fill (const T& t);
        unsigned long int size(unsigned long int dim) const;

        T& min();
        const T& min() const;
        T& max();
        const T& max() const;

        template<typename... Sizes>
        void resize (Sizes... s);

        template<typename... Sizes>
        void conservativeResize (Sizes... s);

        void clear();

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:
        unsigned long int getIndex(const unsigned long int indices[]) const;
        std::array<unsigned long int, N> reverseIndex(unsigned int index);
        static unsigned long int getIndex(const unsigned long int indices[], const unsigned long int sizes[]);

        std::array<unsigned long int, N> sizes;
        std::vector<T> v;
};

}

#include "array.tpp"

#endif // CG3_ARRAY_H
