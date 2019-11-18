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
#include <cg3/io/serialize.h>
#include <cg3/utilities/nested_initializer_lists.h>

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * @brief The Array class
 * is a dynamically allocated N-dimensional array, stored in RowWise mode.
 * All its elements are stored contiguously. For array 1D please use std::vector or std::array.
 *
 * For D-dimensional array you can declare your array in this way:
 * \code{.cpp}
 * cg3::Array<Type, D> array;
 * \endcode
 *
 * Where Type is a generic primitive or user-defined type and D is an unsigned integer that
 * represents the dimensions of the array.
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
 * You can also declare and initialize a generic N-Dimensional Array with nested initializer lists
 * (cg3::NestedInitializerLists).
 *
 * \code{.cpp}
 * cg3::Array<int, 3> array =
 * {
 *     {
 *         {1, 2, 3},
 *         {1, 2   }
 *     },
 *     {
 *         {1},
 *         {1, 4, 7},
 *         {2, 4},
 *         {5}
 *     }
 * }
 * \endcode
 *
 * In this example, array is a 3-dimensional array with sizes 2*4*3.
 * All the missing numbers are filled with zeros (in every dimension).
 */
template <class T, size_t N>
class Array : public SerializableObject {
    static_assert(N > 0, "Array dimension must be > 0.");
    friend class Array<T, N+1>;
public:
    Array();
    template<typename... Sizes>
    Array(Sizes... sizes);

    Array(cg3::NestedInitializerLists<T, N> values);

    constexpr unsigned long int dimensions() const;
    template<typename... I>
    T& operator () (I... indices);
    template<typename... I>
    const T& operator () (I... indices) const;
    template<typename... I>
    T* cArray(I... indices);
    template<typename... I>
    const T* cArray(I... indices) const;
	std::vector<T> stdVector();
	const std::vector<T>& stdVector() const;

    void fill (const T& t);
	template <typename C>
	void fillContainer (const C& container);
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

    Array<T, N-1> subArray(unsigned int r) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    unsigned long int getIndex(const unsigned long int indices[]) const;
    std::array<unsigned long int, N> reverseIndex(unsigned int index);
    static unsigned long int getIndex(const unsigned long int indices[], const unsigned long int sizes[]);

    void initializeNestedLists(cg3::NestedInitializerLists<T, N> values);

    std::array<unsigned long int, N> sizes;
    std::vector<T> v;
};

} //namespace cg3

#include "array_.cpp"

#endif // CG3_ARRAY_H
