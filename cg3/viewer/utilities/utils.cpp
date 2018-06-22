/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "utils.h"

#include <cg3/geometry/bounding_box.h>
#include <cg3/viewer/interfaces/drawable_object.h>

namespace cg3 {

BoundingBox getFullBoundingBoxDrawableObjects(
        const std::vector<const cg3::DrawableObject*>& drawlist,
        bool onlyVisible)
{
    cg3::BoundingBox bb(Pointd(-1,-1,-1), Pointd(1,1,1));
    if (drawlist.size() > 0) {
        unsigned int i = 0;
        if (onlyVisible) {
            //searching the first visible object and with radius > 0 in order to initialize bb
            while (i < drawlist.size() &&
                   drawlist[i] != nullptr &&
                   (!drawlist[i]->isVisible() ||
                   drawlist[i]->sceneRadius() <= 0))
                i++;
        }
        else {
            //searching the first visible object and with radius > 0 in order to initialize bb
            while (i < drawlist.size() && drawlist[i] != nullptr && drawlist[i]->sceneRadius() <= 0)
                i++;
        }

        if (i < drawlist.size()) { //i will point to the first visible object with radius  >0
            if (drawlist[i] != nullptr) {
                bb.min() = drawlist[i]->sceneCenter() - drawlist[i]->sceneRadius();
                bb.max() = drawlist[i]->sceneCenter() + drawlist[i]->sceneRadius();
            }
        }

        for (; i < drawlist.size(); i++) {
            if (drawlist[i] != nullptr) {
                if ((!onlyVisible || drawlist[i]->isVisible()) && drawlist[i]->sceneRadius() > 0) {
                    bb.min() =
                            bb.min().min(drawlist[i]->sceneCenter() - drawlist[i]->sceneRadius());
                    bb.max() =
                            bb.max().max(drawlist[i]->sceneCenter() + drawlist[i]->sceneRadius());
                }
            }
        }
    }
    return bb;
}

} //namespace cg3
