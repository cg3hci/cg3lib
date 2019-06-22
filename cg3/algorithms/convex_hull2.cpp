/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "convex_hull2.h"

#include <vector>

#include "cg3/geometry/point2.h"
#include "cg3/geometry/utils2.h"

namespace cg3 {

/* ----- INTERNAL FUNCTION DECLARATION ----- */

namespace internal {

template <class T = double, class InputIterator, class OutputIterator>
inline void grahamScanOnContainer(const InputIterator first, const InputIterator end, OutputIterator& outIt);

} //namespace cg3::internal


/* ----- IMPLEMENTATION OF GRAHAM SCAN ----- */

/**
 * @brief Get the 2D convex hull using Graham scan algorithm
 * @param[in] container Container of the points of the shape
 * @param[out] convexHull Output container for the convex hull
 */
template <class T, class InputContainer, class OutputContainer>
void convexHull2D(const InputContainer& container, OutputContainer& convexHull)
{
    convexHull2D<T>(container.begin(), container.end(), std::back_inserter(convexHull));
}

/**
 * @brief Get the 2D convex hull using Graham scan algorithm on iterators of containers
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 * @param[out] outIt Output iterator for the container containing the convex hull
 * @return New output iterator
 */
template <class T, class InputIterator, class OutputIterator>
OutputIterator convexHull2D(InputIterator first, InputIterator end, OutputIterator outIt)
{
    //If the container is empty
    if (first == end)
        return outIt;

    //Sort the points
    std::vector<Point2<T>> sortedPoints(first, end);
    std::sort(sortedPoints.begin(), sortedPoints.end());

    //If the is composed by 1 points (or more than 1 of the same point)
    if (*(sortedPoints.begin()) == *(sortedPoints.rbegin())) {
        *outIt = *(sortedPoints.begin());
        outIt++;

        return outIt;
    }

    //Graham scan on upper and lower convex hull
    internal::grahamScanOnContainer<T>(sortedPoints.begin(), sortedPoints.end(), outIt);
    internal::grahamScanOnContainer<T>(sortedPoints.rbegin(), sortedPoints.rend(), outIt);

    return outIt;
}




/* ----- INTERNAL FUNCTIONS IMPLEMENTATION ----- */

namespace internal {

/**
 * @brief Graham scan on a collection of points (upper or lower)
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 * @param[out] container Container that contains the points
 */

template <class T, class InputIterator, class OutputIterator>
void grahamScanOnContainer(const InputIterator first, const InputIterator end, OutputIterator& outIt)
{
    //Iterators
    InputIterator it1;
    InputIterator it2;
    InputIterator it3;

    InputIterator last;

    //Stack of iterator to the vector (it is going to be the output)
    std::vector<InputIterator> stack;

    //Last points to the last element of the collection
    last = end;
    last--;

    assert(first != end);
    assert(std::next(first) != end);
    assert(*first != *last);

    //Add first and last to the results
    stack.push_back(last);
    stack.push_back(first);

    //Initializing t1
    it1 = first;

    //Skip points not at the left of first-last segment
    do
    {
        it1++;
    } while (it1 != last && !cg3::isPointAtRight(*first, *last, *it1));

    if (it1 != last) {
        //Initialize stack with the first element which could be in the convex hull
        stack.push_back(it1);

        it2 = it1;

        //Iterator to stack, pointing to the previous element of the back element
        typename std::vector<InputIterator>::reverse_iterator stackItR = stack.rbegin();
        stackItR++;

        it3 = *stackItR;

        for (it1++; it1 != last; it1++) {
            //Skip point for which last element is on the right of
            //it1 - it2 segment
            if (cg3::isPointAtRight(*it1, *it2, *last)) {
                while (!cg3::isPointAtRight(*it2, *it3, *it1)) {
                    //Pop from stack
                    stack.pop_back();

                    //Setting other iterators
                    it2 = it3;

                    stackItR = stack.rbegin();
                    stackItR++;

                    it3 = *stackItR;

                    assert(stack.size() >= 2);
                }

                //Add to stack it1 and setting other iterators
                stack.push_back(it1);
                it3 = it2;
                it2 = it1;
            }
        }
    }

    //Writing on the output iterator the results
    typename std::vector<InputIterator>::iterator sIter = stack.begin();
    for (++sIter;  sIter != stack.end(); ++sIter) {
        *outIt =  **sIter;
        ++outIt;
    }
}

} //namespace cg3::internal;
} //namespace cg3
