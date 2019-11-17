/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "range_tree_functions.h"


/* ---- COMPARATORS FOR POINTERS IMPLEMENTATION ----- */

bool point2DPointerDimensionComparatorX(
		Point2d* const& o1,
		Point2d* const& o2)
{
    if (o1->x() < o2->x()) {
        return true;
    }
    if (o2->x() < o1->x()) {
        return false;
    }
    return o1->y() < o2->y();
}

bool point2DPointerDimensionComparatorY(
		Point2d* const& o1,
		Point2d* const& o2)
{
    if (o1->y() < o2->y()) {
        return true;
    }
    if (o2->y() < o1->y()) {
        return false;
    }
    return o1->x() < o2->x();
}

