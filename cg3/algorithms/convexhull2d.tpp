#include "convexhull2d.h"

#include "cg3/geometry/geometryutils.h"

namespace cg3 {



/* ----- USEFUL FUNCTIONS ----- */


/**
 * @brief Step of the Graham scan
 * Erase a point (the one before the iterator) if it stays
 * at the right of the two neighbor points
 *
 * @param[out] list Current iterating list
 * @param[out] it Iterator to be checked
 * @return True if a point has been erased, false otherwise
 */
template <class T>
inline bool grahamScanStep(std::list<Point2D<T>>& list, typename std::list<Point2D<T>>::iterator& it1) {
    typename std::list<Point2D<T>>::iterator it2 = it1;
    it2--;
    if (it2 == list.begin())
        return false;

    typename std::list<Point2D<T>>::iterator it3 = it2;
    it3--;

    const Segment<Point2D<T>> seg(*it1, *it2);
    const Point2D<T>& point = *it3;

    if (cg3::isPointAtRight(seg, point)) {
        list.erase(it2);
        return true;
    }

    return false;
}

/**
 * @brief Graham scan on a list of points (upper or lower)
 *
 * @param[out] list List of points
 */
template <class T>
inline void grahamScanOnList(std::list<Point2D<T>>& list) {
    for (typename std::list<Point2D<T>>::iterator it = list.begin(); it != list.end(); it++) {
        bool done = false;
        while (it != list.begin() && !done) {
            done = !grahamScanStep(list, it);
        }
    }
}




/* ----- IMPLEMENTATION OF GRAHAM SCAN ----- */

/**
 * @brief Get the convex hull using Graham scan algorithm
 * @param[in] points Points of the shape
 * @param[out] convexHullPoints Points of the convex hull
 */
template <class Container, class T>
void convexHull2D(const Container& container, std::list<Point2D<T>>& convexHull) {

    //Sort points
    std::vector<Point2D<T>> sortedPoints(container.begin(), container.end());
    std::sort(sortedPoints.begin(), sortedPoints.end());

    //If there aren't more than 3 points, return the input points
    if (sortedPoints.size() <= 3) {
        convexHull.insert(convexHull.end(), sortedPoints.begin(), sortedPoints.end());
    }
    else {
        //Upper convex hull
        std::list<Point2D<T>> upperConvexHull(sortedPoints.begin(), sortedPoints.end());
        grahamScanOnList(upperConvexHull);

        //Reverse the sorted points
        std::reverse(sortedPoints.begin(), sortedPoints.end());

        //Lower convex hull
        std::list<Point2D<T>> lowerConvexHull(sortedPoints.begin(), sortedPoints.end());
        grahamScanOnList(lowerConvexHull);

        //Delete endpoints from lower convex hull
        lowerConvexHull.pop_back();
        lowerConvexHull.pop_front();

        //Concatenate upper and lower convex hull in the output list
        convexHull.splice(convexHull.end(), upperConvexHull);
        convexHull.splice(convexHull.end(), lowerConvexHull);
    }
}

}
