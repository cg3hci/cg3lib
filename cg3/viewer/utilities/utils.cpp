/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "utils.h"

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/viewer/interfaces/manipulable_object.h>

namespace cg3 {

CG3_INLINE bool elagibleObject(const cg3::DrawableObject* obj, bool onlyVisible)
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

CG3_INLINE unsigned int searchFirstObject(
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

CG3_INLINE cg3::Point3d sceneCenterOfDrawableObject(const cg3::DrawableObject* obj)
{
	const cg3::ManipulableObject* mobj = dynamic_cast<const cg3::ManipulableObject*>(obj);
	if (!mobj)
		return obj->sceneCenter();
	else
		return obj->sceneCenter() + mobj->position();
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
CG3_INLINE BoundingBox3 fullBoundingBoxDrawableObjects(
        const std::vector<const cg3::DrawableObject*>& drawlist,
        bool onlyVisible)
{
    BoundingBox3 bb(Point3d(-1,-1,-1), Point3d(1,1,1));
    if (drawlist.size() > 0) {
		unsigned int i = searchFirstObject(drawlist, onlyVisible);

		if (i < drawlist.size()) { //i will point to the first elagible object
			cg3::Point3d sc = sceneCenterOfDrawableObject(drawlist[i]);
			bb.min() = sc - drawlist[i]->sceneRadius();
			bb.max() = sc + drawlist[i]->sceneRadius();

			for (i = i+1; i < drawlist.size(); i++) { //rest of the list
				if (elagibleObject(drawlist[i], onlyVisible)) {
					cg3::Point3d sc = sceneCenterOfDrawableObject(drawlist[i]);

                    bb.min() =
							bb.min().min(sc - drawlist[i]->sceneRadius());
                    bb.max() =
							bb.max().max(sc + drawlist[i]->sceneRadius());
                }
            }
        }


    }
    return bb;
}

} //namespace cg3
