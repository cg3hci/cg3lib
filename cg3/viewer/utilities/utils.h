/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VIEWER_UTILS_H
#define CG3_VIEWER_UTILS_H

#include <vector>
#include <cg3/geometry/bounding_box3.h>

namespace cg3 {

class DrawableObject;

BoundingBox3 fullBoundingBoxDrawableObjects(
        const std::vector<const DrawableObject*>& drawlist,
        bool onlyVisible = true);

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_VIEWER_UTILS_CPP "utils.cpp"
#include CG3_VIEWER_UTILS_CPP
#undef CG3_VIEWER_UTILS_CPP
#endif //CG3_STATIC

#endif // CG3_VIEWER_UTILS_H
