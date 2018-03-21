/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_NESTED_INITIALIZER_LISTS_H
#define CG3_NESTED_INITIALIZER_LISTS_H

/**
  * @link https://zcrou.com/blog/dev/nested-initializers
  */

#include <cstddef>
#include <initializer_list>


namespace cg3 {

//Traits

template<typename T, std::size_t L> //recursive case: a nested list is composed of L-1 levels
struct NestedInitializerListsT {
    using type = std::initializer_list<typename NestedInitializerListsT<T, L - 1>::type>;
};

template<typename T> //base case: a nested is a simple list of elements of type T with 0 levels
struct NestedInitializerListsT<T, 0> {
    using type = T;
};


//Aliases

template<typename T, std::size_t L>
using NestedInitializerLists = typename NestedInitializerListsT<T, L>::type;

}

#endif // CG3_NESTED_INITIALIZER_LISTS_H
