/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "array_.h"

/**
 * @brief Creates an N-Dimensional Array with size 0 for every dimension.
 */
template<class T, size_t N>
inline cg3::Array<T, N>::Array() :
    v(0)
{
    sizes.fill(0);
}

/**
 * @brief Creates an N-Dimensional Array with the given sizes. All its elements are initialized to 0.
 *
 * @param[in] s: #N sizes, one for every dimension of the array.
 */
template<class T, size_t N>
template<typename... Sizes>
cg3::Array<T, N>::Array(Sizes... s)
{
    static_assert(sizeof...(s) == N, "Wrong number of constructor arguments for Array.");
    unsigned long int args[N] = { static_cast<unsigned long int>(s)... };
    unsigned long int totalSize = 1;
    for (unsigned int i = 0; i < N; i++){
        sizes[i] = args[i];
        totalSize*=args[i];
    }
    v.resize(totalSize);
}

/**
 * @brief Creates and initializes an N-Dimensional Array. Sizes are given by the maximum size of the
 * initializer lists for every dimension, and missing values are automatically setted to zero.
 *
 * Example code:
 * \code{.cpp}
 * cg3::Array<int, 2> array = { {1,2,3,4}, {5}, {9, 10} };
 * \endcode
 *
 * This code initializes a 3x4 2D array with the following values:
 * \code{.cpp}
 *  1  2  3  4
 *  5  0  0  0
 *  9 10  0  0
 * \endcode
 *
 * @warning The number of levels of the nested initializer lists must correspond to the number of
 * dimensions of the array. The following example generates a compilation error:
 * \code{.cpp}
 * cg3::Array<int, 2> array = {1, 2, 3}; //Error: it is a 2 dimensional array but the initializer list has one level.
 * \endcode
 * @param[in] values: the nested initializer lists of values.
 */
template<class T, size_t N>
inline cg3::Array<T, N>::Array(cg3::NestedInitializerLists<T, N> values)
{
    initializeNestedLists(values);
}

/**
 * @brief Returns the number of dimensions of the array.
 */
template<class T, size_t N>
constexpr unsigned long int cg3::Array<T, N>::dimensions() const
{
    return N;
}

/**
 * @brief Operator () that allows to access one element of the array. It can be used as left or right value.
 * @param[in] indices: #N indices that allows to access to an element of the array.
 * A number of indices not equal to N will generate a compilation error.
 * @return a reference to the element of the array.
 */
template<class T, size_t N>
template<typename... I>
T& cg3::Array<T, N>::operator ()(I... indices)
{
    static_assert(sizeof...(indices) == N, "Wrong number of arguments for operator().");
    unsigned long int args[N] = { static_cast<unsigned long int>(indices)... };
    return v[getIndex(args)];
}

/**
 * @brief Operator () that allows to access one element of the array. It can be used only as right value.
 * @param[in] indices: #N indices that allows to access to an element of the array.
 * A number of indices not equal to N will generate a compilation error.
 * @return a reference to the element of the array.
 */
template<class T, size_t N>
template<typename... I>
const T& cg3::Array<T, N>::operator ()(I... indices) const
{
    static_assert(sizeof...(indices) == N, "Wrong number of arguments for operator().");
    unsigned long int args[N] = { static_cast<unsigned long int>(indices)... };
    return v[getIndex(args)];
}

/**
 * @brief Allows to get a C array of the cg3::Array, that can be also modified.
 * Example:
 * \code{.cpp}
 * cg3::Array<int, 3> array(10, 13, 4);
 * //...
 * int* carray = array.cArray(3); //carray will point to the element in position (3,0,0).
 * for (unsigned int i = 0; i < 13*4; i++)
 *    std::cout << carry[i]; // will print all the elements of the sub 2D array starting from (3,0,0).
 *
 * carray = array.cArray(4, 2); // carray will point to the element in position (4, 2, 0).
 * for (unsigned int i = 0; i < 4; i++)
 *    std::cout << carry[i]; // will print all the elements of the sub 1D array starting from (4,2,0).
 *
 * carray = array.cArray(); // carray will point to the element in position (0, 0, 0).
 *
 * \endcode
 *
 * @param[in] indices: a number of indices that is less than the number of dimensions of the array.
 * @return a C array starting from the indicized element.
 */
template<class T, size_t N>
template<typename... I>
T* cg3::Array<T, N>::cArray(I... indices)
{
    static_assert(sizeof...(indices) < N, "Wrong number of arguments for operator cArray().");
    const unsigned long int n = sizeof...(indices);
    if (n == 0){
        return v.data();
    }
    unsigned long int args[] = { static_cast<unsigned long int>(indices)... };
    unsigned long int ind = args[0];
    assert(args[0] < sizes[0]);
    unsigned int i;
    for (i = 1; i < n; i++){
        assert(args[i] < sizes[i]);
        ind*=sizes[i];
        ind+=args[i];
    }
    for (; i < N; i++){
        ind*=sizes[i];
    }
    return &v[ind];
}

/**
 * @brief Allows to get a C array of the cg3::Array, that cannot be modified.
 * Example:
 * \code{.cpp}
 * cg3::Array<int, 3> array(10, 13, 4);
 * //...
 * const int* carray = array.cArray(3); //carray will point to the element in position (3,0,0).
 * for (unsigned int i = 0; i < 13*4; i++)
 *    std::cout << carry[i]; // will print all the elements of the sub 2D array starting from (3,0,0).
 *
 * carray = array.cArray(4, 2); // carray will point to the element in position (4, 2, 0).
 * for (unsigned int i = 0; i < 4; i++)
 *    std::cout << carry[i]; // will print all the elements of the sub 1D array starting from (4,2,0).
 *
 * carray = array.cArray(); // carray will point to the element in position (0, 0, 0).
 *
 * \endcode
 *
 * @param[in] indices: a number of indices that is less than the number of dimensions of the array.
 * @return a C array starting from the indicized element.
 */
template<class T, size_t N>
template<typename... I>
const T* cg3::Array<T, N>::cArray(I... indices) const
{
    static_assert(sizeof...(indices) < N, "Wrong number of arguments for operator cArray().");
    const unsigned long int n = sizeof...(indices);
    if (n == 0){
        return v.data();
    }
    unsigned long int args[] = { static_cast<unsigned long int>(indices)... };
    unsigned long int ind = args[0];
    assert(args[0] < sizes[0]);
    unsigned int i;
    for (i = 1; i < n; i++){
        assert(args[i] < sizes[i]);
        ind*=sizes[i];
        ind+=args[i];
    }
    for (; i < N; i++){
        ind*=sizes[i];
    }
    return &v[ind];
}

/**
 * @brief Returns a std::vector containing the elements of the array in row-major order
 */
template<class T, size_t N>
std::vector<T> cg3::Array<T, N>::stdVector()
{
	return v;
}

/**
 * @brief Returns a std::vector containing the elements of the array in row-major order
 */
template<class T, size_t N>
const std::vector<T>& cg3::Array<T, N>::stdVector() const
{
	return v;
}

/**
 * @brief Fills the entire Array with the value t.
 * @param[in] t
 */
template<class T, size_t N>
void cg3::Array<T, N>::fill(const T& t)
{
    std::fill(v.begin(), v.end(), t);
}

/**
 * @brief Fills the entire Array with the values contained in the container c, in row-major
 * order.
 *
 * If the size of the container is greater than the total size of the array, the remaining
 * of the container will be ignored. If otherwise the size of the container is less, the
 * remaining values in the array will be left as they were.
 *
 * @param[in] c: a container of the same type of the array (begin() and end() members must
 * be provided in the container).
 */
template<class T, size_t N>
template<typename C>
void cg3::Array<T, N>::fillContainer(const C& container)
{
	uint i = 0;
	for (auto it = container.begin(); it != container.end() && i < v.size(); ++i, ++it)
		v[i] = *it;
}

/**
 * @brief Returns the size of the given dimension.
 * @param[in] dim
 */
template<class T, size_t N>
unsigned long int cg3::Array<T, N>::size(unsigned long dim) const
{
    assert(dim < N);
    return sizes[dim];
}

/**
 * @brief Returns a reference to the element which is the minimum contained in the array.
 */
template<class T, size_t N>
T& cg3::Array<T, N>::min()
{
    return *(std::min_element(v.begin(), v.end()));
}

/**
 * @brief Returns a const reference to the element which is the minimum contained in the array.
 */
template<class T, size_t N>
const T& cg3::Array<T, N>::min() const
{
    return *(std::min_element(v.begin(), v.end()));
}

/**
 * @brief Returns a reference to the element which is the maximum contained in the array.
 */
template<class T, size_t N>
T& cg3::Array<T, N>::max()
{
    return *(std::max_element(v.begin(), v.end()));
}

/**
 * @brief Returns a const reference to the element which is the maximum contained in the array.
 */
template<class T, size_t N>
const T& cg3::Array<T, N>::max() const
{
    return *(std::max_element(v.begin(), v.end()));
}

/**
 * @brief Allows to resize the Array, not conserving the values of the previous array.
 * @param[in] s: #N elements representing the new sizes of the Array.
 */
template<class T, size_t N>
template<typename... Sizes>
void cg3::Array<T, N>::resize(Sizes... s)
{
    static_assert(sizeof...(s) == N, "Wrong number of resize arguments for Array.");
    unsigned long int args[N] = { static_cast<unsigned long int>(s)... };
    unsigned long int totalSize = 1;
    for (unsigned int i = 0; i < N; i++){
        sizes[i] = args[i];
        totalSize*=args[i];
    }
    v.resize(totalSize);
}

/**
 * @brief Allows to resize the Array, conserving the values of the previous array.
 * @param[in] s: #N elements representing the new sizes of the Array.
 */
template<class T, size_t N>
template<typename... Sizes>
void cg3::Array<T, N>::conservativeResize(Sizes... s)
{
    static_assert(sizeof...(s) == N, "Wrong number of resize arguments for Array.");
    unsigned long int newSizes[N] = { static_cast<unsigned long int>(s)... };
    unsigned long int newTotalSize = 1;
    for (unsigned int i = 0; i < N; i++)
        newTotalSize*=newSizes[i];
    std::vector<T> newVector(newTotalSize);

    for (unsigned long int i = 0; i < v.size(); i++){
        std::array<unsigned long int, N> indices = reverseIndex(i);
        bool outOfBound = false;
        for (unsigned long int j = 0; j < N; j++)
            if (indices[j] >= newSizes[j] || indices[j] >= sizes[j])
                outOfBound = true;
        if (!outOfBound){
            newVector[getIndex(indices.data(), newSizes)] = v[i];
        }
    }

    for (unsigned long int i = 0; i < sizes.size(); i++){
        sizes[i] = newSizes[i];
    }

    v = std::move(newVector);
}

/**
 * @brief Clear the entire array, setting every dimension to size 0.
 */
template<class T, size_t N>
void cg3::Array<T, N>::clear()
{
    v.clear();
    for (unsigned int i = 0; i < N; i++)
        sizes[i] = 0;
}

/**
 * @brief Creates a new subArray of dimension N-1, starting from the given index at its first dimension.
 *
 * Example:
 * \code{.cpp}
 * cg3::Array<int, 3> a(4,2,6);
 * cg3::Array<int, 2> sa = a.subArray(1);
 * //sa is a 2x6 2D Array, containing the elements at the second "row" of Array a.
 * \endcode
 *
 * @param r
 */
template<class T, size_t N>
cg3::Array<T, N-1> cg3::Array<T, N>::subArray(unsigned int r) const
{
    static_assert(N > 1, "Impossible to create subArray with an Array having dimension < 2.");
    assert(r < sizes[0]);
    cg3::Array<T, N-1> sub;
    size_t size = 1;
    for (unsigned int i = 0; i < sizes.size()-1; i++){
        sub.sizes[i] = sizes[i+1];
        size *= sub.sizes[i];
    }
    sub.v = std::vector<T>(v.begin() + r*size, v.begin() + (r+1)*size);
    return sub;
}

/**
 * @brief Serializes in a binary file the Array
 *
 * @param binaryFile
 */
template<class T, size_t N>
void cg3::Array<T, N>::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Array" + std::to_string(N) + "D", binaryFile, sizes, v);
}

/**
 * @brief Deserializes from a binary file an Array
 * @param binaryFile
 */
template<class T, size_t N>
void cg3::Array<T, N>::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Array"  + std::to_string(N)+ "D", binaryFile, sizes, v);
}

template<class T, size_t N>
unsigned long int cg3::Array<T, N>::getIndex(const unsigned long indices[]) const
{
    unsigned long int ind = indices[0];
    assert(indices[0] < sizes[0]);
    for (unsigned int i = 1; i < N; i++){
        assert(indices[i] < sizes[i]);
        ind*=sizes[i];
        ind+=indices[i];
    }
    return ind;
}

template<class T, size_t N>
std::array<unsigned long int, N> cg3::Array<T, N>::reverseIndex(unsigned int index)
{
    std::array<unsigned long int, N> indices;
    for (long int i = N-1; i >= 0; i--){
        indices[i] = index%sizes[i];
        index/= sizes[i];
    }
    return indices;
}

template<class T, size_t N>
unsigned long cg3::Array<T, N>::getIndex(const unsigned long indices[], const unsigned long sizes[])
{
    unsigned long int ind = indices[0];
    assert(indices[0] < sizes[0]);
    for (unsigned int i = 1; i < N; i++){
        assert(indices[i] < sizes[i]);
        ind*=sizes[i];
        ind+=indices[i];
    }
    return ind;
}

template<typename T, size_t N>
void cg3::Array<T, N>::initializeNestedLists(cg3::NestedInitializerLists<T, N> values)
{
    std::list<std::size_t> szs = NestedInitializerListsProcessor<T, N>::maxDimensionsLevels(values);
    unsigned int i = 0;
    size_t totalSize = 1;
    for (std::size_t s : szs){
        totalSize *= s;
        sizes[i++] = s;
    }
    v.resize(totalSize);

    typename std::vector<T>::iterator iterator = v.begin();
    NestedInitializerListsProcessor<T, N>::processElements(values, [&iterator](T value) { *(iterator++) = value; }, szs);
}
