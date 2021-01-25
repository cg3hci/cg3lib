/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "convex_hull2_incremental.h"

namespace cg3 {


/* ----- INTERNAL FUNCTION DECLARATION ----- */

namespace internal {

template <class T>
void processConvexHull(
        const Point2<T>& point,
        std::set<Point2<T>>& upper,
        std::set<Point2<T>>& lower);

}


/* ----- INCREMENTAL CONVEX HULL 2D IMPLEMENTATION ----- */


/* CONSTRUCTORS/DESTRUCTORS */

/**
 * @brief Constructor for empty datastructure
 */
template <class T>
IncrementalConvexHull<T>::IncrementalConvexHull()
{

}

/**
 * @brief Constructors to initialize the convex hull with given points
 * given the on iterators of containers
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 */
template <class T> template <class InputIterator>
IncrementalConvexHull<T>::IncrementalConvexHull(
        const InputIterator first,
        const InputIterator end)
{
    this->addPoints(first, end);
}

/**
 * @brief Constructors to initialize the convex hull with given points
 * in a container
 * @param[in] points Container of the points of the shape
 */
template <class T> template <class InputContainer>
IncrementalConvexHull<T>::IncrementalConvexHull(const InputContainer& container)
{
    this->addPoints(container.begin(), container.end());
}



/**
 * @brief Constructors to initialize the convex hull with given points
 * given the on iterators of containers
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 */
template <class T> template <class InputIterator>
void IncrementalConvexHull<T>::addPoints(const InputIterator first, const InputIterator end)
{
    for (InputIterator it = first; it != end; it++) {
        this->addPoint(*it);
    }
}

/**
 * @brief Constructors to initialize the convex hull with given points
 * in a container
 * @param[in] points Container of the points of the shape
 */
template <class T> template <class InputContainer>
void IncrementalConvexHull<T>::addPoints(const InputContainer& container)
{
    this->addPoints(container.begin(), container.end());
}




/**
 * @brief Add a new point to the convex hull
 * @param[in] point Input point
 */
template <class T>
void IncrementalConvexHull<T>::addPoint(const Point2<T>& point)
{
    internal::processConvexHull<T>(point, this->upper, this->lower);
}

/**
 * @brief Get convex hull of the current data structure
 * @param[out] out Output iterator
 */
template <class T> template <class OutputIterator>
void IncrementalConvexHull<T>::convexHull(OutputIterator out)
{

    if (this->upper.size() > 1) {

        //Upper convex hull
        auto firstUpper = this->upper.begin();
        auto lastUpper = std::prev(this->upper.end());

        typename std::set<Point2<T>>::iterator itUpper = firstUpper;

        do {
            *out = *itUpper;
            out++;

            itUpper++;
        } while (itUpper != lastUpper);


        //Lower convex hull
        if (!this->lower.empty()) {
            auto firstLower = this->lower.rbegin();
            auto lastLower = std::prev(this->lower.rend());

            typename std::set<Point2<T>>::reverse_iterator itLower = firstLower;

            do {
                *out = *itLower;
                out++;

                itLower++;
            } while (itLower != lastLower);
        }

    }
    else {
        for (const Point2<T>& p : this->upper) {
            *out = p;
            out++;
        }
    }

}


/**
 * @brief Clear convex hull
 */
template <class T>
void IncrementalConvexHull<T>::clear()
{
    upper.clear();
    lower.clear();
}


/* ----- ALGORITHM INTERFACE IMPLEMENTATION ----- */

/**
 * @brief Add point to the convex hull
 */
template <class T>
void addPointToConvexHull(
        const Point2<T>& point,
        IncrementalConvexHull<T>& incrementalConvexHull2D)
{
    incrementalConvexHull2D.addPoint(point);
}



/* ----- INTERNAL FUNCTION IMPLEMENTATION ----- */

namespace internal {

/**
 * @brief Algorithm step for processing incremental convex hull
 *
 * @param[in] point Added point
 * @param[out] upper Current upper convex hull
 * @param[out] lower Current upper convex hull
 */
template <class T>
void processConvexHull(
        const Point2<T>& point,
        std::set<Point2<T>>& upper,
        std::set<Point2<T>>& lower)
{
    typedef typename std::set<Point2<T>>::iterator SetIt;


    // Upper convex hull

    if (upper.size() < 2) {
        upper.insert(point);
    }
    else {
        //Get first and last
        SetIt firstUpper = upper.begin();
        SetIt lastUpper = std::prev(upper.end());


        //If the point is an endpoints
        //Or the it is at the left of the first-last segment
        if (
                point < *firstUpper ||
                point > *lastUpper ||
                cg3::isPointAtRight(*firstUpper, *lastUpper, point))
        {
            std::pair<SetIt, bool> pairUpperIt = upper.insert(point);
            SetIt upperIt = pairUpperIt.first;

            //Set endpoints if they exist

            SetIt upperPrev = upper.end();
            if (*upperIt != *firstUpper) {
                upperPrev = upperIt;
                upperPrev--;
            }
            SetIt upperNext = upper.end();
            if (*upperIt != *lastUpper) {
                upperNext = upperIt;
                upperNext++;
            }

            //If the new iterator has prev and next
            //Erase point if the point is at left of the neighbor segment
            if (
                    upperPrev != upper.end() &&
                    upperNext != upper.end() &&
                    !cg3::isPointAtRight(*upperPrev, *upperNext, *upperIt))
            {
                upper.erase(upperIt);
            }
            else {
                //If the point has a prev
                if (upperPrev != upper.end()) {
                    SetIt upperPrevPrev = upperPrev;
                    upperPrevPrev--;

                    while (*upperPrev != *firstUpper &&
                           !cg3::isPointAtRight(*upperPrevPrev, *upperIt, *upperPrev)) {
                        upperPrevPrev--;
                        upper.erase(upperPrev--);
                    }
                }

                //If the point has a next
                if (upperNext != upper.end()) {
                    SetIt upperNextNext = upperNext;
                    upperNextNext++;

                    while (*upperNext != *lastUpper &&
                           !cg3::isPointAtRight(*upperIt, *upperNextNext, *upperNext)) {
                        upperNextNext++;
                        upper.erase(upperNext++);
                    }
                }
            }
        }
    }



    // Lower convex hull


    if (lower.size() < 2) {
        lower.insert(point);
    }
    else {
        //Get first and last
        SetIt firstLower = std::prev(lower.end());
        SetIt lastLower = lower.begin();

        //If the point is an endpoints
        //Or the it is at the left of the first-last segment
        if (
                point > *firstLower ||
                point < *lastLower ||
                cg3::isPointAtRight(*firstLower, *lastLower, point))
        {
            std::pair<SetIt, bool> pairLowerIt = lower.insert(point);
            SetIt lowerIt = pairLowerIt.first;

            //Set endpoints if they exist

            SetIt lowerPrev = lower.end();
            if (*lowerIt != *firstLower) {
                lowerPrev = lowerIt;
                lowerPrev++;
            }
            SetIt lowerNext = lower.end();
            if (*lowerIt != *lastLower) {
                lowerNext = lowerIt;
                lowerNext--;
            }

            //If the new iterator has prev and next
            //Erase point if the point is at left of the neighbor segment
            if (
                    lowerPrev != lower.end() &&
                    lowerNext != lower.end() &&
                    !cg3::isPointAtRight(*lowerPrev, *lowerNext, *lowerIt))
            {
                lower.erase(lowerIt);
            }
            else {
                //If the point has a prev
                if (lowerPrev != lower.end()) {
                    SetIt lowerPrevPrev = lowerPrev;
                    lowerPrevPrev++;

                    while (*lowerPrev != *firstLower &&
                           !cg3::isPointAtRight(*lowerPrevPrev, *lowerIt, *lowerPrev)) {
                        lowerPrevPrev++;
                        lower.erase(lowerPrev++);
                    }
                }

                //If the point has a next
                if (lowerNext != lower.end()) {
                    SetIt lowerNextNext = lowerNext;
                    lowerNextNext--;

                    while (*lowerNext != *lastLower &&
                           !cg3::isPointAtRight(*lowerIt, *lowerNextNext, *lowerNext)) {
                        lowerNextNext--;
                        lower.erase(lowerNext--);
                    }
                }
            }
        }
    }

}

} //namespace cg3::internal
} //namespace cg3
