/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container.h"

#include <cg3/viewer/utilities/utils.h>

namespace cg3 {

DrawableContainer::DrawableContainer(QObject *parent) : QObject(parent)
{
}

DrawableContainer::~DrawableContainer()
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
void DrawableContainer::pushBack(
        const DrawableObject *obj,
        const std::string& objectName,
        bool objVisibility)
{
    objects.push_back(obj);
    objectNames.push_back(objectName);
    emit drawableContainerPushedObject(this, objectName, objVisibility);
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
    return (unsigned int)objects.size();
}

/**
 * @brief Removes the i-th element from the container, and shifts all the other
 * objects starting from the i+1 position.
 * @param i
 */
void DrawableContainer::erase(unsigned int i)
{
    emit drawableContainerErasedObject(this, i);
    objects.erase(objects.begin() + i);
    objectNames.erase(objectNames.begin() + i);
}

/**
 * @brief Clears the container.
 */
void DrawableContainer::clear()
{
    for (int i = (int)objects.size()-1; i >= 0; i--){
        emit drawableContainerErasedObject(this, i);
    }
    objects.clear();
    objectNames.clear();
}

const std::string& DrawableContainer::objectName(unsigned int i) const
{
    return objectNames[i];
}

void DrawableContainer::draw() const
{

}

Pointd DrawableContainer::sceneCenter() const
{
    return Pointd();
}

double DrawableContainer::sceneRadius() const
{
    return -1;
}

BoundingBox DrawableContainer::totalBoundingBox() const
{
    return cg3::getFullBoundingBoxDrawableObjects(objects, true);
}

} //namespace cg3
