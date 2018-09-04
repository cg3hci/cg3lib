/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "utils.h"

#include <cg3/viewer/interfaces/drawable_object.h>

namespace cg3 {

bool elagibleObject(const cg3::DrawableObject* obj, bool onlyVisible)
{
    //object must:
    // - be different from nullptr
    // - have sceneRadius > 0
    // - be visible ONLY IF onlyVisible == true (if onlyVisible == false no check required)
    if (obj != nullptr){
        if (obj->sceneRadius() > 0){
            if (onlyVisible && obj->isVisible())
                return true;
            else if (!onlyVisible)
                return true;
        }
    }
    return false;
}

unsigned int searchFirstObject(
        const std::vector<const cg3::DrawableObject*>& drawlist,
        bool onlyVisible)
{
    unsigned int i = 0;
    bool found = false;
    while(i < drawlist.size() && !found){
        found = elagibleObject(drawlist[i], onlyVisible);
        if (!found)
            i++;
    }
    return i;
}

/**
 * @brief Returns the full bounding box of all the DrawableObjects contained in the DrawList.
 *
 * In order to be considered, an object of the drawlist must satisfy the follwing constraints:
 * - obj != nullptr
 * - obj->sceneRadius() > 0
 * - if (onlyVisible == true) -> obj->isVisible() == true
 *
 * @param drawlist
 * @param onlyVisible
 */
BoundingBox fullBoundingBoxDrawableObjects(
        const std::vector<const cg3::DrawableObject*>& drawlist,
        bool onlyVisible)
{
    BoundingBox bb(Pointd(-1,-1,-1), Pointd(1,1,1));
    if (drawlist.size() > 0) {
        unsigned int i = searchFirstObject(drawlist, onlyVisible);

        if (i < drawlist.size()) { //i will point to the first elagible object
            bb.min() = drawlist[i]->sceneCenter() - drawlist[i]->sceneRadius();
            bb.max() = drawlist[i]->sceneCenter() + drawlist[i]->sceneRadius();

            for (i = i+1; i < drawlist.size(); i++) { //rest of the list
                if (elagibleObject(drawlist[i], onlyVisible)) {
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
