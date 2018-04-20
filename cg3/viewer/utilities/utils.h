/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VIEWER_UTILS_H
#define CG3_VIEWER_UTILS_H

#include <vector>

namespace cg3 {

class BoundingBox;
class DrawableObject;

BoundingBox getFullBoundingBoxDrawableObjects(const std::vector<const DrawableObject*>& drawlist,
        const std::vector<bool>& visibility,
        bool onlyVisible = true);

}

#endif // CG3_VIEWER_UTILS_H
