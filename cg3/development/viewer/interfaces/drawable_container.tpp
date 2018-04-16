/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container.h"
namespace cg3 {

template <typename T>
DrawableContainer<T>::DrawableContainer()
{
}

template<typename T>
DrawableContainer<T>::~DrawableContainer()
{
}

template<typename T>
void DrawableContainer<T>::pushBack(const T &obj, bool visibility)
{
    objects.push_back(obj);
    objectsVisibility.push_back(visibility);

    emit drawableContainerPushedObject(this, objects.size()-1, visibility);
}

template<typename T>
const T& DrawableContainer<T>::operator [](unsigned int i) const
{
    return objects[i];
}

template<typename T>
T& DrawableContainer<T>::operator [](unsigned int i)
{
    return objects[i];
}

template<typename T>
unsigned int DrawableContainer<T>::size() const
{
    return objects.size();
}

template<typename T>
void DrawableContainer<T>::erase(unsigned int i)
{
    objects.erase(objects.begin() + i);
    objectsVisibility.erase(objectsVisibility.begin()+i);

    emit drawableContainerErasedObject(this, i);
}

template<typename T>
void DrawableContainer<T>::draw() const
{
    for (unsigned int i = 0; i < objects.size(); i++){
        if (objectsVisibility[i])
            objects[i].draw();
    }
}

template<typename T>
Pointd DrawableContainer<T>::sceneCenter() const
{
    return totalVisibleBoundingBox().center();
}

template<typename T>
double DrawableContainer<T>::sceneRadius() const
{
    BoundingBox bb = totalVisibleBoundingBox();
    if (bb.min() != bb.max())
        return bb.diag() /2;
    else
        return -1;
}

template<typename T>
BoundingBox DrawableContainer<T>::totalVisibleBoundingBox() const
{
    cg3::BoundingBox bb;
    if (objects.size() > 0) {
        unsigned int i = 0;
        //searching the first visible object and with radius > 0 in order to initialize bb
        while (i < objects.size() && objectsVisibility[i] && objects[i].sceneRadius() <= 0)
            i++;

        if (i < objects.size()) { //i will point to the first visible object with radius >0
            bb.min() = objects[i].sceneCenter() - objects[i].sceneRadius();
            bb.max() = objects[i].sceneCenter() + objects[i].sceneRadius();
        }

        for (; i < objects.size(); i++) {
            if (objectsVisibility[i] && objects[i].sceneRadius() <= 0) {
                bb.min() = bb.min().min(objects[i].sceneCenter() - objects[i].sceneRadius());
                bb.max() = bb.max().max(objects[i].sceneCenter() + objects[i].sceneRadius());
            }
        }
    }
    return bb;
}

}
