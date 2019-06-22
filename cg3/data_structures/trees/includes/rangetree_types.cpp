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
CG3_INLINE bool point2DDimensionComparatorX(const Point2d& o1, const Point2d& o2)
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
CG3_INLINE bool point2DDimensionComparatorY(const Point2d& o1, const Point2d& o2)
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
CG3_INLINE bool point3DDimensionComparatorX(const Point3d& o1, const Point3d& o2)
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
CG3_INLINE bool point3DDimensionComparatorY(const Point3d& o1, const Point3d& o2)
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
CG3_INLINE bool point3DDimensionComparatorZ(const Point3d& o1, const Point3d& o2)
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
CG3_INLINE std::vector<DefaultComparatorType<Point2d>> getComparatorsForPoint2D()
{
    //Creating vector of comparators for each dimension
    std::vector<DefaultComparatorType<Point2d>> customComparators;

    customComparators.push_back(&point2DDimensionComparatorX);
    customComparators.push_back(&point2DDimensionComparatorY);

    return customComparators;
}


/**
 * @brief Get the comparators for each dimension of a 3D point
 * @return Vector of comparators
 */
CG3_INLINE std::vector<DefaultComparatorType<Point3d>> getComparatorsForPoint3D()
{
    //Creating vector of comparators for each dimension
    std::vector<DefaultComparatorType<Point3d>> customComparators;

    customComparators.push_back(&point3DDimensionComparatorX);
    customComparators.push_back(&point3DDimensionComparatorY);
    customComparators.push_back(&point3DDimensionComparatorZ);

    return customComparators;
}

} //namespace cg3::internal

} //namespace cg3
