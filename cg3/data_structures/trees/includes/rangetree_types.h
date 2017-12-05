#ifndef CG3_RANGETREE_TYPES_H
#define CG3_RANGETREE_TYPES_H

#include <vector>

#include "cg3/geometry/point.h"
#include "cg3/geometry/2d/point2d.h"

#include "cg3/data_structures/trees/rangetree.h"

namespace cg3 {

namespace internal {

/* Comparators for 2D points */
bool point2DDimensionComparatorX(const Point2Dd& o1, const Point2Dd& o2);
bool point2DDimensionComparatorY(const Point2Dd& o1, const Point2Dd& o2);

/* Comparators for 3D points */
bool point2DDimensionComparatorX(const Pointd& o1, const Pointd& o2);
bool point2DDimensionComparatorY(const Pointd& o1, const Pointd& o2);
bool point2DDimensionComparatorZ(const Pointd& o1, const Pointd& o2);

/* Get vector of comparators for 2D and 3D points */
std::vector<LessComparatorType<Point2Dd>> getComparatorsForPoint2D();
std::vector<LessComparatorType<Pointd>> getComparatorsForPoint3D();

}

/**
 * Range tree of 2D points (double components)
 *
 * Type T is the type of the value associated to the range tree
 */
class RangeTree2D : public RangeTree<Point2Dd> {
public:
    RangeTree2D()
        : RangeTree<Point2Dd>(2, internal::getComparatorsForPoint2D()) {}
    RangeTree2D(const std::vector<Point2Dd>& vec)
        : RangeTree<Point2Dd>(2, vec, internal::getComparatorsForPoint2D()) {}
};

/**
 * Range tree of 3D points (double components)
 */
class RangeTree3D : public RangeTree<Pointd> {
public:
    RangeTree3D()
        : RangeTree<Pointd>(3, internal::getComparatorsForPoint3D()) {}
    RangeTree3D(const std::vector<Pointd>& vec)
        : RangeTree<Pointd>(3, vec, internal::getComparatorsForPoint3D()) {}
};

}

#endif // CG3_RANGETREE_TYPES_H
