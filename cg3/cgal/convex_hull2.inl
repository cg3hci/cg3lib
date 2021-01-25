/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "convex_hull2.h"

#include <CGAL/ch_graham_andrew.h>
#include <CGAL/Simple_cartesian.h>

namespace cg3 {
namespace cgal {

/**
 * @ingroup cg3cgal
 * @brief Get the 2D convex hull using Graham scan algorithm
 * @param[in] container Container of the points of the shape
 * @param[out] convexHull Output container for the convex hull
 */
template <class T, class InputContainer, class OutputContainer>
void convexHull2D(
        const InputContainer& points,
        OutputContainer& convexHull)
{
    cg3::cgal::convexHull2D<T>(points.begin(), points.end(), std::back_inserter(convexHull));
}

/**
 * @ingroup cg3cgal
 * @brief Get the 2D convex hull using Graham scan algorithm on iterators of containers
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 * @param[out] outIt Output iterator for the container containing the convex hull
 */
template <class T, class InputIterator, class OutputIterator>
void convexHull2D(
        InputIterator first,
        InputIterator end,
        OutputIterator outIt)
{

    typedef CGAL::Simple_cartesian<T>                               CK;
    typedef typename CK::Point_2                                    CK_Point_2;

    std::vector<CK_Point_2> cgalPoints;

    for (InputIterator it = first; it != end; it++) {
        CK_Point_2 point(it->x(), it->y());
        cgalPoints.push_back(point);
    }

    //Compute convex hull
    std::vector<CK_Point_2> cgalCHPoints;
    CGAL::ch_graham_andrew(cgalPoints.begin(), cgalPoints.end(), std::back_inserter(cgalCHPoints));

    for (const CK_Point_2 p : cgalCHPoints) {
        *outIt = Point2<T>(p.x(), p.y());
        outIt++;
    }
}

} //namespace cg3::cgal
} //namespace cg3
