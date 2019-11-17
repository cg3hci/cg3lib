/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "aabb_functions.h"

/*
 * Function to extract the values of the AABB from a segment
 */
double aabbValueExtractor(
        const Segment2D& segment,
        const AABBValueType& valueType,
        const int& dim)
{
    if (valueType == AABBValueType::MIN) {
        switch (dim) {
        case 1:
			return (double) std::min(segment.p1().x(), segment.p2().x());
        case 2:
			return (double) std::min(segment.p1().y(), segment.p2().y());
        }
    }
    if (valueType == AABBValueType::MAX) {
        switch (dim) {
        case 1:
			return (double) std::max(segment.p1().x(), segment.p2().x());
        case 2:
			return (double) std::max(segment.p1().y(), segment.p2().y());
        }
    }
    assert(false);
    return false;
}


/*
 * Returns true if the two segment have an intersection
 * or they collide
 */
bool segment2DIntersectionChecker(const Segment2D& segment1, const Segment2D& segment2) {
	double s1MinX = std::min(segment1.p1().x(), segment1.p2().x());
	double s2MinX = std::min(segment2.p1().x(), segment2.p2().x());
	double s1MaxX = std::max(segment1.p1().x(), segment1.p2().x());
	double s2MaxX = std::max(segment2.p1().x(), segment2.p2().x());

	double s1MinY = std::min(segment1.p1().y(), segment1.p2().y());
	double s2MinY = std::min(segment2.p1().y(), segment2.p2().y());
	double s1MaxY = std::max(segment1.p1().y(), segment1.p2().y());
	double s2MaxY = std::max(segment2.p1().y(), segment2.p2().y());

    Point2D a(s1MinX, s1MinY);
    Point2D b(s1MaxX, s1MaxY);
    Point2D c(s2MinX, s2MinY);
    Point2D d(s2MaxX, s2MaxY);


    float den = ((d.y()-c.y())*(b.x()-a.x())-(d.x()-c.x())*(b.y()-a.y()));
    float num1 = ((d.x() - c.x())*(a.y()-c.y()) - (d.y()- c.y())*(a.x()-c.x()));
    float num2 = ((b.x()-a.x())*(a.y()-c.y())-(b.y()-a.y())*(a.x()-c.x()));
    float u1 = num1/den;
    float u2 = num2/den;

    /* The two lines are coincidents */
    if (den == 0 && num1 == 0 && num2 == 0)
        return true;
    /* The two lines are parallel */
    if (den == 0)
        return false;
    /* Lines do not collide */
    if (u1 < 0 || u1 > 1 || u2 < 0 || u2 > 1)
        return false;
    /* Lines DO collide */
    return true;
}


/*
 * Default comparator for a 2D segment. It is needed whether
 * no operator < has been defined on segment2D class. It is
 * used to determine whether an object is a duplicated,
 * if the equality test with the dimension comparator has
 * returned true
 */
bool segment2DCustomComparator(const Segment2D& o1, const Segment2D& o2) {
	if (o1.p1() < o2.p1())
        return true;
	if (o2.p2() < o1.p1())
        return false;
	return o1.p2() < o2.p2();
}
