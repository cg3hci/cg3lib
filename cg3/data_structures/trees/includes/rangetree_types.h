#ifndef CG3_RANGETREE_TYPES_H
#define CG3_RANGETREE_TYPES_H

#include <vector>

#include "cg3/geometry/point3.h"
#include "cg3/geometry/point2.h"

#include "cg3/data_structures/trees/rangetree.h"

namespace cg3 {

namespace internal {

/* Comparators for 2D points */
inline bool point2DDimensionComparatorX(const Point2d& o1, const Point2d& o2);
inline bool point2DDimensionComparatorY(const Point2d& o1, const Point2d& o2);

/* Comparators for 3D points */
inline bool point2DDimensionComparatorX(const Point3d& o1, const Point3d& o2);
inline bool point2DDimensionComparatorY(const Point3d& o1, const Point3d& o2);
inline bool point2DDimensionComparatorZ(const Point3d& o1, const Point3d& o2);

/* Get vector of comparators for 2D and 3D points */
std::vector<DefaultComparatorType<Point2d>> getComparatorsForPoint2D();
std::vector<DefaultComparatorType<Point3d>> getComparatorsForPoint3D();

} //namespace cg3::internal

/**
 * Range tree of 2D points (double components)
 *
 * Type T is the type of the value associated to the range tree
 */
class RangeTree2D : public RangeTree<Point2d> {
public:
    RangeTree2D()
        : RangeTree<Point2d>(2, internal::getComparatorsForPoint2D()) {}
    RangeTree2D(const std::vector<Point2d>& vec)
        : RangeTree<Point2d>(2, vec, internal::getComparatorsForPoint2D()) {}
};

/**
 * Range tree of 3D points (double components)
 */
class RangeTree3D : public RangeTree<Point3d> {
public:
    RangeTree3D()
        : RangeTree<Point3d>(3, internal::getComparatorsForPoint3D()) {}
    RangeTree3D(const std::vector<Point3d>& vec)
        : RangeTree<Point3d>(3, vec, internal::getComparatorsForPoint3D()) {}
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_RANGETREE_TYPES_CPP "rangetree_types.cpp"
#include CG3_RANGETREE_TYPES_CPP
#undef CG3_RANGETREE_TYPES_CPP
#endif //CG3_STATIC

#endif // CG3_RANGETREE_TYPES_H
