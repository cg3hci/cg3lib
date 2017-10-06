#include "intersections.h"

namespace cg3 {

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
    return cg3::epsilonEqual((b.x() - a.x()) * (c.y() - a.y()), (c.x() - a.x()) * ((b.y()- a.y())), eps);
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


bool checkSegmentIntersection(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
        const bool ignoreEndPoints)
{
    char code;

    cg3::checkSegmentIntersection(seg1, seg2, code);

    //Intersection found
    if (code == '1' || code == 'e')
        return true;

    //Common endpoint (v) or common endpoint and equals(s)
    if (!ignoreEndPoints && (code == 'v' || code == 's'))
        return true;

    return false;
}

void checkSegmentIntersection(
        const Segment2Dd& seg1, const Segment2Dd& seg2,
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
        if (areCollinearPoints(a, b, c, eps)) { //Collinear points
            if (isBetween(a, b, c, eps)) {
                intersectionPoint = c; //Set intersection point
                code = 'e';
            }
            else if (isBetween(a, b, d,eps)) {
                intersectionPoint = d; //Set intersection point
                code = 'e';
            }
            else if (isBetween(c, d, a, eps)) {
                intersectionPoint = a; //Set intersection point
                code = 'e';
            }
            else if (isBetween(c, d, b, eps)) {
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



}



