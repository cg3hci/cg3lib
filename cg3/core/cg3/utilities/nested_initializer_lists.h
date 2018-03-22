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
#include <list>


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

//Processors that allow to automatically iterate through nested initializer lists

template<typename T, std::size_t L>
struct NestedInitializerListsProcessor;

// Recursive part.
template<typename T, std::size_t L>
struct NestedInitializerListsProcessor {
    using NestedInitializerLists = cg3::NestedInitializerLists<T, L>;

    template<typename T_Function>
    static void process(NestedInitializerLists values, T_Function function, std::list<size_t> sizes) {
        size_t curr_size = sizes.front();
        sizes.pop_front();
        for (auto nested : values) {
            NestedInitializerListsProcessor<T, L-1>::process(nested, function, sizes);
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
};

// Last level.
template<typename T>
struct NestedInitializerListsProcessor<T, 0> {
    using InitializerList = cg3::NestedInitializerLists<T, 1>;

    template<typename T_Function>
    static void process(InitializerList values, T_Function function, std::list<size_t> sizes) {
        size_t row_size;
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
};


}

#endif // CG3_NESTED_INITIALIZER_LISTS_H
