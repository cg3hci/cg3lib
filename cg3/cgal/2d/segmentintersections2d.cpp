/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "segmentintersections2d.h"

#include <cg3/utilities/utils.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>

namespace cg3 {
namespace cgal {

typedef CGAL::Simple_cartesian<double>                          CK;
typedef CK::Point_2                                             CK_Point_2;
typedef CK::Segment_2                                           CK_Segment_2;
typedef CK::Intersect_2                                         CK_Intersect_2;
typedef CK::Line_2                                              CK_Line_2;
typedef CGAL::Polygon_2<CK>                                     CK_Polygon_2;

/**
 * @ingroup cg3cgal
 * @brief checkSegmentIntersection2D
 * @param seg1
 * @param seg2
 * @param ignoreEndPoints
 * @return
 */
bool checkSegmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints)
{
    Point2Dd p1From = seg1.p1();
    Point2Dd p1To = seg1.p2();
    Point2Dd p2From = seg2.p1();
    Point2Dd p2To = seg2.p2();
    double eps = 0.001;

    //Exclude endpoints
    if (ignoreEndPoints && (
            (cg3::epsilonEqual(p1From.x(), p2From.x(), eps) && cg3::epsilonEqual(p1From.y(), p2From.y(), eps)) ||
            (cg3::epsilonEqual(p1To.x(), p2To.x(), eps) && cg3::epsilonEqual(p1To.y(), p2To.y(), eps)) ||
            (cg3::epsilonEqual(p1From.x(), p2To.x(), eps) && cg3::epsilonEqual(p1From.y(), p2To.y(), eps)) ||
            (cg3::epsilonEqual(p2From.x(), p1To.x(), eps) && cg3::epsilonEqual(p2From.y(), p1To.y(), eps))
    )) {
        return false;
    }

    CK_Segment_2 cgalSeg1(CK_Point_2(p1From.x(), p1From.y()), CK_Point_2(p1To.x(), p1To.y()));
    CK_Segment_2 cgalSeg2(CK_Point_2(p2From.x(), p2From.y()), CK_Point_2(p2To.x(), p2To.y()));

    if (intersection(cgalSeg1, cgalSeg2)) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @ingroup cg3cgal
 * @brief getSegmentIntersection2D
 * @param seg1
 * @param seg2
 * @param ignoreEndPoints
 * @return
 */
std::vector<Segment2Dd> segmentIntersection2D(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool& ignoreEndPoints)
{
    std::vector<Segment2Dd> resultVec;
    Point2Dd p1From = seg1.p1();
    Point2Dd p1To = seg1.p2();
    Point2Dd p2From = seg2.p1();
    Point2Dd p2To = seg2.p2();
    double eps = 0.001;

    //Exclude endpoints
    if (ignoreEndPoints && (
            (cg3::epsilonEqual(p1From.x(), p2From.x(), eps) && cg3::epsilonEqual(p1From.y(), p2From.y(), eps)) ||
            (cg3::epsilonEqual(p1To.x(), p2To.x(), eps) && cg3::epsilonEqual(p1To.y(), p2To.y(), eps)) ||
            (cg3::epsilonEqual(p1From.x(), p2To.x(), eps) && cg3::epsilonEqual(p1From.y(), p2To.y(), eps)) ||
            (cg3::epsilonEqual(p2From.x(), p1To.x(), eps) && cg3::epsilonEqual(p2From.y(), p1To.y(), eps))
    )) {
        return resultVec;
    }

    CK_Segment_2 cgalSeg1(CK_Point_2(p1From.x(), p1From.y()), CK_Point_2(p1To.x(), p1To.y()));
    CK_Segment_2 cgalSeg2(CK_Point_2(p2From.x(), p2From.y()),CK_Point_2(p2To.x(), p2To.y()));

    CGAL::cpp11::result_of<CK_Intersect_2(CK_Segment_2, CK_Segment_2)>::type
        result = intersection(cgalSeg1, cgalSeg2);

    if (result) {
        if (const CK_Segment_2* seg = boost::get<CK_Segment_2>(&*result)) {
            CK_Point_2 start = seg->start();
            CK_Point_2 end = seg->end();
            Point2Dd p1 = Point2Dd(start.x(), end.y());
            Point2Dd p2 = Point2Dd(end.x(), end.y());

            resultVec.push_back(Segment2Dd(p1, p2));
        }
        else {
            const CK_Point_2* point = boost::get<CK_Point_2>(&*result);
            Point2Dd p = Point2Dd(point->x(), point->y());

            resultVec.push_back(Segment2Dd(p,p));
        }
    }

    return resultVec;
}

} //namespace cg3::cgal
} //namespace cg3
