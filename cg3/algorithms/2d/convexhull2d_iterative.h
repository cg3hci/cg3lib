/**
    @author Stefano Nuvoli
*/
#ifndef CG3_CONVEXHULL2D_ITERATIVE_H
#define CG3_CONVEXHULL2D_ITERATIVE_H

#include <set>

#include "cg3/geometry/2d/point2d.h"
#include "cg3/geometry/2d/utils2d.h"

namespace cg3 {

/**
 * @brief Iterative convex hull data structure
 */
template <class T>
class IterativeConvexHull2D {

public:

    /* Constructors / destructors */

    IterativeConvexHull2D();

    template <class InputContainer>
    IterativeConvexHull2D(const InputContainer& container);

    template <class InputIterator>
    IterativeConvexHull2D(const InputIterator first, const InputIterator end);


    /* Methods */

    void addPoint(const Point2D<T>& point);


    template <class InputContainer>
    void addPoints(const InputContainer& container);

    template <class InputIterator>
    void addPoints(const InputIterator first, const InputIterator end);


    template <class OutputIterator>
    void getConvexHull(OutputIterator out);

    void clear();

private:

    /* Private fields */

    std::set<Point2D<T>> upper;
    std::set<Point2D<T>> lower;

};

/* Algorithm interface */

template <class T = double>
void addPointToConvexHull(
        const Point2D<T>& point,
        IterativeConvexHull2D<Point2D<T>>& iterativeConvexHull2D);

}

#include "convexhull2d_iterative.tpp"


#endif // CG3_CONVEXHULL2DITERATIVE_H
