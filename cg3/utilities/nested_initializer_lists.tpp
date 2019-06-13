/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "nested_initializer_lists.h"

namespace cg3 {

/**
 * @brief Returns a list containing the maximum size of elements for every dimension.
 *
 * \code{.cpp}
 * std::list<size_t> list = cg3::NestedInitializerListsProcessor<int, 2>::maxDimensionsLevels({{2, 3, 5, 4}, {2}, {2, 4, 6}});
 * //the list will contain the values 3 and 4.
 * std::list<size_t> list = cg3::NestedInitializerListsProcessor<int, 3>::maxDimensionsLevels( {{{2, 3}, {5, 4}, {6}, {2, 5}}, {{2}, {3, 4, 6}}} );
 * //the list will contain the values 2, 4 and 3.
 * \endcode
 *
 * @param[in] values: the nested initializer lists
 * @return a list of #L numbers, where every number is the maximum size of elements for every dimension.
 */
template<typename T, std::size_t L>
std::list<size_t> NestedInitializerListsProcessor<T, L>::maxDimensionsLevels(
        NestedInitializerLists<T, L> values)
{
    std::list<size_t> final;
    bool first = true;
    for (auto nested : values) {
        std::list<size_t> l = NestedInitializerListsProcessor<T, L-1>::maxDimensionsLevels(nested);

        if (first){
            first = false;
            for (size_t s : l)
                final.push_back(s);
        }
        else {
            assert(l.size() == final.size());
            std::list<size_t>::iterator it = l.begin();
            for (size_t& s : final){
                if (s < *it)
                    s = *it;
                ++it;
            }
        }
    }
    final.push_front(values.size());
    return final;
}

/**
 * @brief Applies the lambda function passed as parameter to all the elements of the NestedInitializerLists
 *
 * Example: save all the elements in a vector:
 *
 * \code{.cpp}
 * std::vector<T> v;
 * //resize vector proprerly, see NestedInitializerListsProcessor<T, N>::maxDimensionsLevel
 * typename std::vector<T>::iterator iterator = v.begin();
 * NestedInitializerListsProcessor<T, N>::processElements(values, [&iterator](T value) { *(iterator++) = value; });
 * \endcode
 *
 * @note This function does not take into account the sizes of every list. If some values are missing from the lists
 * they will be skipped and function is not applied.
 * @param values
 * @param function: a lambda function that takes an argument of type T as input.
 */
template<typename T, std::size_t L>
template<typename T_Function>
void NestedInitializerListsProcessor<T, L>::processElements(
        NestedInitializerLists<T, L> values,
        T_Function function)
{
    for (auto nested : values) {
        NestedInitializerListsProcessor<T, L-1>::processElements(nested, function);
    }
}

/**
 * @brief Applies the lambda function passed as parameter to all the elements of the NestedInitializerLists
 *
 * Example: save all the elements in a vector:
 *
 * \code{.cpp}
 * std::vector<T> v;
 * //resize vector proprerly, see NestedInitializerListsProcessor<T, N>::maxDimensionsLevel
 * std::list<std::size_t> sizes;
 * //push values properly in sizes (example: sizes = NestedInitializerListsProcessor<T, N>::maxDimensionsLevel)
 * typename std::vector<T>::iterator iterator = v.begin();
 * NestedInitializerListsProcessor<T, N>::processElements(values, [&iterator](T value) { *(iterator++) = value; });
 * \endcode
 *
 * @note This function takes into account the sizes of every list fits every list in the given sizes.
 * If some values are missing in a list, a zero vale casted to the type T is assed to the function.
 * @param values
 * @param function: a lambda function that takes an argument of type T as input.
 * @param sizes
 */
template<typename T, std::size_t L>
template<typename T_Function>
void NestedInitializerListsProcessor<T, L>::processElements(
        NestedInitializerLists<T, L> values,
        T_Function function,
        std::list<size_t> sizes)
{
    size_t curr_size = sizes.front();
    sizes.pop_front();
    for (auto nested : values) {
        NestedInitializerListsProcessor<T, L-1>::processElements(nested, function, sizes);
    }

    //0 in left values
    if (values.size() < curr_size) {
        std::size_t count = 1;
        for (size_t s : sizes)
            count *= s;

        while (count-- > 0)
            function(static_cast<T>(0));
    }
}

template<typename T>
std::list<size_t> NestedInitializerListsProcessor<T, 1>::maxDimensionsLevels(
        NestedInitializerListsProcessor<T, 1>::InitializerList values)
{
    std::list<size_t> dim;
    dim.push_back(values.size());
    return dim;
}

template<typename T>
template<typename T_Function>
void NestedInitializerListsProcessor<T, 1>::processElements(
        NestedInitializerListsProcessor<T, 1>::InitializerList values,
        T_Function function)
{
    std::for_each(values.begin(), values.end(), function);
}

template<typename T>
template<typename T_Function>
void NestedInitializerListsProcessor<T, 1>::processElements(
        NestedInitializerListsProcessor<T, 1>::InitializerList values,
        T_Function function,
        std::list<size_t> sizes)
{
    size_t row_size = 1;
    for (size_t s : sizes)
        row_size *= s;
    std::for_each(values.begin(), values.end(), function);

    //0 in left values
    if (values.size() < row_size) {
        std::size_t count = row_size - values.size();
        while (count-- > 0) {
            function(static_cast<T>(0));
        }
    }
}

} //namespace cg3
