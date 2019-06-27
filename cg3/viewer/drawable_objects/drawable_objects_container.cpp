/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_objects_container.h"

namespace cg3 {

template <typename T>
DrawableObjectsContainer<T>::DrawableObjectsContainer() :
    visibleObject(-1)
{
}

template <typename T>
DrawableObjectsContainer<T>::~DrawableObjectsContainer()
{

}

template<typename T>
DrawableObjectsContainer<T>::DrawableObjectsContainer(
        const DrawableObjectsContainer<T>& other) :
	cg3::DrawableContainer (),
    visibleObject(other.visibleObject)
{
    uint i = 0;
    for (const T& obj : other){
        bool visibility = visibleObject < 0 ? true : i == (uint)visibleObject;

        list.push_back(obj);
        cg3::DrawableContainer::pushBack(&(list.back()), other.objectName(i), visibility);
        ++i;
    }
}

template <typename T>
unsigned int DrawableObjectsContainer<T>::pushBack(const T& d, const std::string& name, bool vis)
{
    list.push_back(d);
    cg3::DrawableContainer::pushBack(&(list.back()), name, vis);
    return list.size()-1;
}

template <typename T>
void DrawableObjectsContainer<T>::pushList(const std::list<T>& list)
{
    unsigned int i = 0;
    for (const T& d: list){
       pushBack(d, "Object " + std::to_string(i++));
    }
}

template <typename T>
const std::list<T>& DrawableObjectsContainer<T>::getList() const
{
    return list;
}

template <typename T>
void DrawableObjectsContainer<T>::clear()
{
    cg3::DrawableContainer::clear();
    list.clear();
    visibleObject = -1;
}

template <typename T>
void DrawableObjectsContainer<T>::erase(unsigned int i)
{
    DrawableContainer::erase(i);
    typename std::list<T>::iterator it = list.begin();
    std::advance(it, i);
    list.erase(it);
    if ((int)i == visibleObject) {
        if (i >= list.size())
            i = (unsigned int)list.size()-1;
        setVisibleObject(i);
    }
}

template<typename T>
const T& DrawableObjectsContainer<T>::at(unsigned int i) const
{
    const T* obj = dynamic_cast<const T*> ((*this)[i]);
    return *obj;
}

template<typename T>
T& DrawableObjectsContainer<T>::at(unsigned int i)
{
    typename std::list<T>::iterator it = list.begin();
    std::advance(it, i);
    return *it;
}

template <typename T>
void DrawableObjectsContainer<T>::setVisibleObject(int objectId)
{
    if (visibleObject < 0) {
        if (objectId >= 0) {
            for (unsigned int i = 0; i < size(); i++){
                setObjectVisibility(i, false);
            }
            setObjectVisibility(objectId, true);
            visibleObject = objectId;
        }
    }
    else {
        if (objectId < 0) {
            for (unsigned int i = 0; i < size(); i++){
                setObjectVisibility(i, true);
            }
            visibleObject = objectId;
        }
        else {
            setObjectVisibility(visibleObject, false);
            setObjectVisibility(objectId, true);
            visibleObject = objectId;
        }
    }
}

template<typename T>
DrawableObjectsContainer<T>& DrawableObjectsContainer<T>::operator=(
        const DrawableObjectsContainer<T>& other)
{
    if (this != &other){
        clear();
        visibleObject = other.visibleObject;
        uint i = 0;
        for (const T& obj : other){
            bool visibility = visibleObject < 0 ? true : i == (uint)visibleObject;
            list.push_back(obj);
            cg3::DrawableContainer::pushBack(&(list.back()), other.objectName(i), visibility);
            ++i;
        }
    }
    return *this;
}

template<typename T>
void DrawableObjectsContainer<T>::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3DrawableObjectsContainer", binaryFile, list, visibleObject);
    for (unsigned int i = 0; i < size(); i++)
        cg3::serialize(this->objectName(i), binaryFile);
}

template<typename T>
void DrawableObjectsContainer<T>::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3DrawableObjectsContainer", binaryFile, list, visibleObject);
    uint i = 0;
    for (const T& obj : list){
        bool visibility = visibleObject < 0 ? true : i == (uint)visibleObject;
        std::string objectName;
        cg3::deserialize(objectName, binaryFile);
        cg3::DrawableContainer::pushBack(&obj, objectName, visibility);
        ++i;
    }

}

template <typename T>
typename DrawableObjectsContainer<T>::iterator DrawableObjectsContainer<T>::begin()
{
    return list.begin();
}

template <typename T>
typename DrawableObjectsContainer<T>::iterator DrawableObjectsContainer<T>::end()
{
    return list.end();
}

template <typename T>
typename DrawableObjectsContainer<T>::const_iterator DrawableObjectsContainer<T>::begin() const
{
    return list.begin();
}

template <typename T>
typename DrawableObjectsContainer<T>::const_iterator DrawableObjectsContainer<T>::end() const
{
    return list.end();
}

}
