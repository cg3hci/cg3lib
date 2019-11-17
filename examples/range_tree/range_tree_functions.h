/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef RANGE_TREE_FUNCTIONS_H
#define RANGE_TREE_FUNCTIONS_H

#include <cg3/geometry/point2.h>

typedef cg3::Point2d Point2d;

/* ---- COMPARATORS FOR POINTERS ----- */

bool point2DPointerDimensionComparatorX(Point2d* const& o1, Point2d* const& o2);
bool point2DPointerDimensionComparatorY(Point2d* const& o1, Point2d* const& o2);

#endif // RANGETEST_H
