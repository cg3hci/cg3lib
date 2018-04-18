/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container.h"

#include <cg3/viewer/utilities/utils.h>

namespace cg3 {

#ifdef CG3_VIEWER_DEFINED
DrawableContainer::DrawableContainer(QObject *parent) : QObject(parent)
{
}
#else
DrawableContainer::DrawableContainer()
{
}
#endif

DrawableContainer::~DrawableContainer()
{
}

/**
 * @brief Pushes a DrawableObject to the container. If the container is already drawn by
 * the MainWindow::canvas, it emits a signal in order to communicate and apply the change
 * to the interface.
 * @param obj
 * @param objectName
 * @param visibility
 */
void DrawableContainer::pushBack(
        const DrawableObject *obj,
        const std::string& objectName,
        bool visibility)
{
    objects.push_back(obj);
    objectNames.push_back(objectName);
    obj->setVisibility(visibility);
    #ifdef CG3_VIEWER_DEFINED
    emit drawableContainerPushedObject(this, objectName, visibility);
    #endif
}

/**
 * @brief Access to the i-th element
 * @param i
 * @return
 */
const DrawableObject* DrawableContainer::operator [](unsigned int i) const
{
    return objects[i];
}

/**
 * @brief Returns the number of elements inside the container.
 */
unsigned int DrawableContainer::size() const
{
    return objects.size();
}

/**
 * @brief Removes the i-th element from the container, and shifts all the other
 * objects starting from the i+1 position.
 * @param i
 */
void DrawableContainer::erase(unsigned int i)
{
    #ifdef CG3_VIEWER_DEFINED
    emit drawableContainerErasedObject(this, i);
    #endif
    objects.erase(objects.begin() + i);
    objectNames.erase(objectNames.begin() + i);
}

const std::string&DrawableContainer::objectName(unsigned int i) const
{
    return objectNames[i];
}

void DrawableContainer::draw() const
{
    for (unsigned int i = 0; i < objects.size(); i++){
        if (objects[i]->isVisible())
            objects[i]->draw();
    }
}

Pointd DrawableContainer::sceneCenter() const
{
    return totalVisibleBoundingBox().center();
}

double DrawableContainer::sceneRadius() const
{
    BoundingBox bb = totalVisibleBoundingBox();
    if (bb.min() != bb.max())
        return bb.diag() /2;
    else
        return -1;
}

DrawableContainer::iterator DrawableContainer::begin()
{
    return objects.begin();
}

DrawableContainer::iterator DrawableContainer::end()
{
    return objects.end();
}

DrawableContainer::const_iterator DrawableContainer::begin() const
{
    return objects.begin();
}

DrawableContainer::const_iterator DrawableContainer::end() const
{
    return objects.end();
}

BoundingBox DrawableContainer::totalVisibleBoundingBox() const
{
    /*cg3::BoundingBox bb(Pointd(-1,-1,-1), Pointd(1,1,1));
    if (objects.size() > 0) {
        unsigned int i = 0;
        //searching the first visible object and with radius > 0 in order to initialize bb
        while (i < objects.size() &&
               (!(objects[i]->isVisible()) ||
               objects[i]->sceneRadius() <= 0))
            i++;

        if (i < objects.size()) { //i will point to the first visible object with radius >0
            bb.min() = objects[i]->sceneCenter() - objects[i]->sceneRadius();
            bb.max() = objects[i]->sceneCenter() + objects[i]->sceneRadius();
        }

        for (; i < objects.size(); i++) {
            if (objects[i]->isVisible() && objects[i]->sceneRadius() > 0) {
                bb.min() =
                        bb.min().min(objects[i]->sceneCenter() - objects[i]->sceneRadius());
                bb.max() =
                        bb.max().max(objects[i]->sceneCenter() + objects[i]->sceneRadius());
            }
        }
    }
    return bb;*/
    return cg3::getFullBoundingBoxDrawableObjects(objects, true);
}

} //namespace cg3
