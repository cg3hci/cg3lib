/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VIEWER_UTILS_H
#define CG3_VIEWER_UTILS_H

#include <vector>
#include <cg3/geometry/bounding_box.h>

namespace cg3 {

class DrawableObject;

BoundingBox fullBoundingBoxDrawableObjects(
        const std::vector<const DrawableObject*>& drawlist,
        bool onlyVisible = true);

#ifdef CG3_OLD_NAMES_COMPATIBILITY
inline BoundingBox getFullBoundingBoxDrawableObjects(
        const std::vector<const DrawableObject*>& drawlist,
        bool onlyVisible = true)
{
    return fullBoundingBoxDrawableObjects(drawlist, onlyVisible);
}
#endif

} //namespace cg3

#endif // CG3_VIEWER_UTILS_H
