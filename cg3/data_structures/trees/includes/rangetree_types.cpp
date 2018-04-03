#include "rangetree_types.h"

namespace cg3 {

namespace internal {


/* ----- COMPARATORS FOR 2D POINTS ----- */

/**
 * @brief Comparator for X components of 3D points
 * @param o1 Point 1
 * @param o2 Point 2
 * @return True if the first point is less than the other
 * (X component)
 */
bool point2DDimensionComparatorX(const Point2Dd& o1, const Point2Dd& o2)
{
    if (o1.x() < o2.x())
        return true;
    if (o2.x() < o1.x())
        return false;

    return o1 < o2;
}

/**
 * @brief Comparator for Y components of 2D points
 * @param o1 Point 1
 * @param o2 Point 2
 * @return True if the first point is less than the other
 * (Y component)
 */
bool point2DDimensionComparatorY(const Point2Dd& o1, const Point2Dd& o2)
{
    if (o1.y() < o2.y())
        return true;
    if (o2.y() < o1.y())
        return false;

    return o1 < o2;
}



/* ----- COMPARATORS FOR 3D POINTS ----- */

/**
 * @brief Comparator for X components of 3D points
 * @param o1 Point 1
 * @param o2 Point 2
 * @return True if the first point is less than the other
 * (X component)
 */
bool point3DDimensionComparatorX(const Pointd& o1, const Pointd& o2)
{
    if (o1.x() < o2.x())
        return true;
    if (o2.x() < o1.x())
        return false;

    return o1 < o2;
}

/**
 * @brief Comparator for Y components of 3D points
 * @param o1 Point 1
 * @param o2 Point 2
 * @return True if the first point is less than the other
 * (Y component)
 */
bool point3DDimensionComparatorY(const Pointd& o1, const Pointd& o2)
{
    if (o1.y() < o2.y())
        return true;
    if (o2.y() < o1.y())
        return false;

    return o1 < o2;
}

/**
 * @brief Comparator for Z components of 3D points
 * @param o1 Point 1
 * @param o2 Point 2
 * @return True if the first point is less than the other
 * (Z component)
 */
bool point3DDimensionComparatorZ(const Pointd& o1, const Pointd& o2)
{
    if (o1.z() < o2.z())
        return true;
    if (o2.z() < o1.z())
        return false;

    return o1 < o2;
}




/* ----- GET VECTORS OF COMPARATORS FOR 2D AND 3D POINTS ----- */


/**
 * @brief Get the comparators for each dimension of a 2D point
 * @return Vector of comparators
 */
std::vector<DefaultComparatorType<Point2Dd>> getComparatorsForPoint2D()
{
    //Creating vector of comparators for each dimension
    std::vector<DefaultComparatorType<Point2Dd>> customComparators;

    customComparators.push_back(&point2DDimensionComparatorX);
    customComparators.push_back(&point2DDimensionComparatorY);

    return customComparators;
}


/**
 * @brief Get the comparators for each dimension of a 3D point
 * @return Vector of comparators
 */
std::vector<DefaultComparatorType<Pointd>> getComparatorsForPoint3D()
{
    //Creating vector of comparators for each dimension
    std::vector<DefaultComparatorType<Pointd>> customComparators;

    customComparators.push_back(&point3DDimensionComparatorX);
    customComparators.push_back(&point3DDimensionComparatorY);
    customComparators.push_back(&point3DDimensionComparatorZ);

    return customComparators;
}

}

}
