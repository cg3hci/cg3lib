/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "intersections2d.h"

namespace cg3 {


/* ----- INTERNAL FUNCTION DECLARATION ----- */

namespace internal {

bool areCollinearPoints(
        const Point2Dd& a,
        const Point2Dd& b,
        const Point2Dd& c,
        const double eps);

bool isBetween(
        const Point2Dd& a,
        const Point2Dd& b,
        const Point2Dd& c,
        const double eps);
}


/* ----- IMPLEMENTATION OF INTERSECTION CHECK ----- */

/**
 * @brief Check if two segments have an intersection
 * @param[in] seg1 Segment 1
 * @param[in] seg2 Segment 2
 * @param[in] ignoreEndPoints Ignore if endpoints are the same
 * @return True if segments have an intersection
 */
bool checkSegmentIntersection(
        const Segment2Dd& seg1,
        const Segment2Dd& seg2,
        const bool ignoreEndPoints)
{
    char code;

    cg3::checkSegmentIntersection(seg1, seg2, code);

    //Intersection found
    if (code == '1')
        return true;

    //Common endpoint (v) or common endpoint and equals(s)
    if (!ignoreEndPoints && (code == 'v' || code == 's' || code == 'e'))
        return true;

    return false;
}


/**
 * @brief Check if two segments have an intersection
 * @param[in] seg1 Segment 1
 * @param[in] seg2 Segment 2
 * @param[out] code Character identifying the result
 * @param[in] eps Epsilon for operations
 * @param[out] intersectionPoint Point in which the segment intersect
 */
void checkSegmentIntersection(
        const Segment2Dd& seg1,
        const Segment2Dd& seg2,
        char& code,
        const double eps,
        Point2Dd& intersectionPoint)
{
    /* Return char characterizing intersection.
     *
     * 'e': The segments collinearly overlap, sharing a point.
     * 'v': An endpoint (vertex) of one segment is on the other segment,
     *      but 'e' doesn't hold.
     * '1': The segments intersect properly (i.e., they share a point and
     *      neither 'v' nor 'e' holds).
     * 's': The segments are the same.
     * '0': The segments do not intersect (i.e., they share no points).
     *
     */
    code = '?';

    double  s, t;       /* The two parameters of the parametric eqns. */
    double num, denom;  /* Numerator and denoninator of equations. */

    Point2Dd a = seg1.getP1();
    Point2Dd b = seg1.getP2();
    Point2Dd c = seg2.getP1();
    Point2Dd d = seg2.getP2();

    //Same segment
    if ((cg3::epsilonEqual(a, c, eps) && cg3::epsilonEqual(b, d, eps)) ||
        (cg3::epsilonEqual(a, d, eps) && cg3::epsilonEqual(b, c, eps)))
    {
        intersectionPoint = a;
        code = 's';
        return;
    }

    //Endpoints
    if (cg3::epsilonEqual(a, c, eps) || cg3::epsilonEqual(a, d, eps)) {
        intersectionPoint = a;
        code = 'v';
        return;
    }
    else if (cg3::epsilonEqual(b, d, eps) || cg3::epsilonEqual(c, b, eps))
    {
        intersectionPoint = b;
        code = 'v';
        return;
    }

    denom =
            a.x() * ( d.y() - c.y() ) +
            b.x() * ( c.y() - d.y() ) +
            d.x() * ( b.y() - a.y() ) +
            c.x() * ( a.y() - b.y() );

    // If denom is zero, then segments are parallel: handle separately.
    if (cg3::epsilonEqual(denom, 0.0, eps)) {
        if (internal::areCollinearPoints(a, b, c, eps)) { //Collinear points
            if (internal::isBetween(a, b, c, eps)) {
                intersectionPoint = c; //Set intersection point
                code = 'e';
            }
            else if (internal::isBetween(a, b, d,eps)) {
                intersectionPoint = d; //Set intersection point
                code = 'e';
            }
            else if (internal::isBetween(c, d, a, eps)) {
                intersectionPoint = a; //Set intersection point
                code = 'e';
            }
            else if (internal::isBetween(c, d, b, eps)) {
                intersectionPoint = b; //Set intersection point
                code = 'e';
            }
            else {
                code = '0';
            }
        }
        else {
            code = '0';
        }
    }
    else {
        num =
                a.x() * ( d.y() - c.y() ) +
                c.x() * ( a.y() - d.y() ) +
                d.x() * ( c.y() - a.y() );


        s = num / denom;


        num =
                -(a.x() * ( c.y() - b.y() ) +
                  b.x() * ( a.y() - c.y() ) +
                  c.x() * ( b.y() - a.y() ) );


        t = num / denom;


        //Intersection found
        if ((0.0 <= s) && (s <= 1.0) && (0.0 <= t) && (t <= 1.0)) {
            code = '1';

            //Set intersection point
            intersectionPoint.set(
                        a.x() + s * (b.x() - a.x()),
                        a.y() + s * (b.y() - a.y())
                        );
        }

        //Intersection not found
        else if ((0.0 > s) || (s > 1.0) || (0.0 > t) || (t > 1.0))
            code = '0';

    }
}


/* ----- INTERNAL FUNCTION IMPLEMENTATION ----- */

namespace internal {
/**
 * Returns true iff the 3 points are collinear. 3 points are collinear
 * iff triangle area is zero
 */
bool areCollinearPoints(
        const Point2Dd& a,
        const Point2Dd& b,
        const Point2Dd& c,
        const double eps)
{
    return cg3::epsilonEqual(
                (b.x() - a.x()) * (c.y() - a.y()),
                (c.x() - a.x()) * (b.y() - a.y()),
                eps);
}

/**
 * Returns true iff point c lies on the closed segment ab.
 * Assumes it is already known that abc are collinear.
 */
bool isBetween(
        const Point2Dd& a,
        const Point2Dd& b,
        const Point2Dd& c,
        const double eps)
{
   /* If ab not vertical, check betweenness on x; else on y. */
   if (!cg3::epsilonEqual(a.x(), b.x(), eps))
      return ((a.x() <= c.x()) && (c.x() <= b.x())) ||
             ((a.x() >= c.x()) && (c.x() >= b.x()));
   else
      return ((a.y() <= c.y()) && (c.y() <= b.y())) ||
             ((a.y() >= c.y()) && (c.y() >= b.y()));
}

}


}




