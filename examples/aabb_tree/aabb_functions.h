/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_AABB_FUNCTIONS_H
#define CG3_AABB_FUNCTIONS_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment.h>
#include <cg3/data_structures/trees/aabbtree.h>

typedef cg3::AABBValueType AABBValueType;
typedef cg3::Point2<int> Point2D;
typedef cg3::Segment<Point2D> Segment2D;

double aabbValueExtractor(
		const Segment2D& segment,
		const AABBValueType& valueType,
		const int& dim);

bool segment2DIntersectionChecker(const Segment2D& segment1, const Segment2D& segment2);

bool segment2DCustomComparator(const Segment2D& o1, const Segment2D& o2);

#endif //CG3_AABB_FUNCTIONS_H
