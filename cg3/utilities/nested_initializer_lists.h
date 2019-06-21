/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_NESTED_INITIALIZER_LISTS_H
#define CG3_NESTED_INITIALIZER_LISTS_H

/// \file

/**
  * @link https://zcrou.com/blog/dev/nested-initializers
  */

#include <cstddef>
#include <assert.h>
#include <initializer_list>
#include <list>

namespace cg3 {

//Traits
namespace internal {

template<typename T, std::size_t L> //recursive case: a nested list is a list of L-1 levels
struct NestedInitializerListsTraits
{
    using type = std::initializer_list<typename NestedInitializerListsTraits<T, L - 1>::type>;
};

template<typename T> //base case: no list, only the type T
struct NestedInitializerListsTraits<T, 0>
{
    using type = T;
};

} //namespace cg3::internal

//Alias
/**
 * @ingroup cg3core
 * @class NestedInitializerLists
 * @brief It manages nested std::initializer_list<T> types of #L levels
 * L must be known at compile time, and compilation will fail if the NestedInitializerLists used
 * does not correspond to the number of used levels.
 */
template<typename T, std::size_t L>
using NestedInitializerLists = typename internal::NestedInitializerListsTraits<T, L>::type;

//Processors that allow to automatically iterate through nested initializer lists

// Recursive part.
/**
 * @ingroup cg3core
 * @brief The NestedInitializerListsProcessor class
 *
 * Proposes some helper static functions that allows to process cg3::NestedInitializerLists of L levels.
 */
template<typename T, std::size_t L>
class NestedInitializerListsProcessor
{
public:
    static std::list<size_t> maxDimensionsLevels (
            NestedInitializerLists<T, L> values);

    template<typename T_Function>
    static void processElements(
            NestedInitializerLists<T, L> values,
            T_Function function);

    template<typename T_Function>
    static void processElements(
            NestedInitializerLists<T, L> values,
            T_Function function,
            std::list<size_t> sizes);

};

// Last level.
template<typename T>
class NestedInitializerListsProcessor<T, 1>
{
public:
    using InitializerList = cg3::NestedInitializerLists<T, 1>;

    static std::list<size_t> maxDimensionsLevels (
            InitializerList values);

    template<typename T_Function>
    static void processElements(
            InitializerList values,
            T_Function function,
            std::list<size_t> sizes);

    template<typename T_Function>
    static void processElements(
            InitializerList values,
            T_Function function);
};

} //namespace cg3

#include "nested_initializer_lists.cpp"

#endif // CG3_NESTED_INITIALIZER_LISTS_H
