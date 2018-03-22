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
struct NestedInitializerListsTraits {
    using type = std::initializer_list<typename NestedInitializerListsTraits<T, L - 1>::type>;
};

template<typename T> //base case: no list, only the type T
struct NestedInitializerListsTraits<T, 0> {
    using type = T;
};

}

//Alias
/**
 * @class NestedInitializerLists
 * @brief It manages nested std::initializer_list<T> types
 */
template<typename T, std::size_t L>
using NestedInitializerLists = typename internal::NestedInitializerListsTraits<T, L>::type;

//Processors that allow to automatically iterate through nested initializer lists

// Recursive part.
template<typename T, std::size_t L>
struct NestedInitializerListsProcessor {
    using NestedInitializerLists = cg3::NestedInitializerLists<T, L>;

    static std::list<size_t> maxDimensionsLevels (NestedInitializerLists values){
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

    template<typename T_Function>
    static void processElements(NestedInitializerLists values, T_Function function, std::list<size_t> sizes) {
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
};

// Last level.
template<typename T>
struct NestedInitializerListsProcessor<T, 1> {
    using InitializerList = cg3::NestedInitializerLists<T, 1>;

    static std::list<size_t> maxDimensionsLevels (InitializerList values){
        std::list<size_t> dim;
        dim.push_back(values.size());
        return dim;
    }

    template<typename T_Function>
    static void processElements(InitializerList values, T_Function function, std::list<size_t> sizes) {
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
};


}

#endif // CG3_NESTED_INITIALIZER_LISTS_H
