/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container.h"

#include <cg3/viewer/utilities/utils.h>

namespace cg3 {

CG3_INLINE DrawableContainer::DrawableContainer(QObject *parent) : QObject(parent)
{
}

CG3_INLINE DrawableContainer::~DrawableContainer()
{
    clear();
}

/**
 * @brief Pushes a DrawableObject to the container. If the container is already drawn by
 * the MainWindow::canvas, it emits a signal in order to communicate and apply the change
 * to the interface.
 * @param obj
 * @param objectName
 * @param visibility
 */
CG3_INLINE void DrawableContainer::pushBack(
        const DrawableObject *obj,
        const std::string& objectName,
        bool objVisibility)
{
    objects.push_back(obj);
    objectNames.push_back(objectName);
    emit drawableContainerPushedObject(objectName, objVisibility);
}

/**
 * @brief Access to the i-th element
 * @param i
 * @return
 */
CG3_INLINE const DrawableObject* DrawableContainer::operator [](unsigned int i) const
{
    return objects[i];
}

/**
 * @brief Returns the number of elements inside the container.
 */
CG3_INLINE unsigned int DrawableContainer::size() const
{
    return (unsigned int)objects.size();
}

/**
 * @brief Removes the i-th element from the container, and shifts all the other
 * objects starting from the i+1 position.
 * @param i
 */
CG3_INLINE void DrawableContainer::erase(unsigned int i)
{
    emit drawableContainerErasedObject(objects[i]);
    objects.erase(objects.begin() + i);
    objectNames.erase(objectNames.begin() + i);
}

/**
 * @brief Clears the container.
 */
CG3_INLINE void DrawableContainer::clear()
{
    for (int i = (int)objects.size()-1; i >= 0; i--){
        emit drawableContainerErasedObject(objects[i]);
    }
    objects.clear();
    objectNames.clear();
}

CG3_INLINE const std::string& DrawableContainer::objectName(unsigned int i) const
{
    return objectNames[i];
}

CG3_INLINE void DrawableContainer::setObjectVisibility(unsigned int i, bool vis) const
{
    emit drawableContainerVisibilityObjectChanged(objects[i], vis);
}

CG3_INLINE void DrawableContainer::draw() const
{
    if (isVisible()){
        for (const DrawableObject* o : objects){
            if (o->isVisible())
                o->draw();
        }
    }
}

CG3_INLINE Point3d DrawableContainer::sceneCenter() const
{
    return totalBoundingBox().center();
}

CG3_INLINE double DrawableContainer::sceneRadius() const
{
    return totalBoundingBox().diag() / 2;
}

CG3_INLINE BoundingBox3 DrawableContainer::totalBoundingBox() const
{
    return cg3::fullBoundingBoxDrawableObjects(objects, true);
}

} //namespace cg3
