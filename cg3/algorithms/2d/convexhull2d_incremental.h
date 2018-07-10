/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_CONVEXHULL2D_INCREMENTAL_H
#define CG3_CONVEXHULL2D_INCREMENTAL_H

#include <set>

#include "cg3/geometry/2d/point2d.h"
#include "cg3/geometry/2d/utils2d.h"

namespace cg3 {

/**
 * @brief Incremental convex hull data structure
 */
template <class T>
class IncrementalConvexHull {

public:

    /* Constructors / destructors */

    IncrementalConvexHull();

    template <class InputContainer>
    IncrementalConvexHull(const InputContainer& container);

    template <class InputIterator>
    IncrementalConvexHull(const InputIterator first, const InputIterator end);


    /* Methods */

    void addPoint(const Point2D<T>& point);


    template <class InputContainer>
    void addPoints(const InputContainer& container);

    template <class InputIterator>
    void addPoints(const InputIterator first, const InputIterator end);


    template <class OutputIterator>
    void convexHull(OutputIterator out);

    void clear();

    #ifdef CG3_OLD_NAMES_COMPATIBILITY
    template <class OutputIterator>
    inline void getConvexHull(OutputIterator out) {return convexHull(out);}
    #endif

private:

    /* Private fields */

    std::set<Point2D<T>> upper;
    std::set<Point2D<T>> lower;

};

/* Algorithm interface */

template <class T = double>
inline void addPointToConvexHull(
        const Point2D<T>& point,
        IncrementalConvexHull<Point2D<T>>& incrementalConvexHull2D);

} //namespace cg3

#include "convexhull2d_incremental.tpp"


#endif // CG3_CONVEXHULL2DINCREMENTAL_H
