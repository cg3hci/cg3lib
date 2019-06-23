/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef DRAWABLEDCELVECTOR_H
#define DRAWABLEDCELVECTOR_H

#include <cg3/viewer/interfaces/drawable_container.h>

namespace cg3 {

/**
 * @brief The DrawableObjectsContainer class
 *
 * A templated container of DrawableObjects of the same type. It stores automatically
 * all the DrawableObjects.
 *
 * Due to the fact that it is templated, it cannot be a QObject and therefore it
 * cannot send signals to the MainWindow. Therefore, in order to create a
 * DrawableObjectsContainer, you'll need to pass a MainWindow object to the
 * constructor.
 */
template <typename T>
class DrawableObjectsContainer : public cg3::DrawableContainer, virtual public SerializableObject
{
public:

    using iterator = typename std::list<T>::iterator;
    using const_iterator = typename std::list<T>::const_iterator;

    DrawableObjectsContainer();
    ~DrawableObjectsContainer();
    DrawableObjectsContainer(const DrawableObjectsContainer<T>& other);
    unsigned int pushBack(const T& d, const std::string& name, bool vis = true);
    void pushList(const std::list<T>& list);
    const std::list<T>& getList() const;
    void clear();
    void erase(unsigned int i);

    const T& at(unsigned int i) const;
    T& at(unsigned int i);

    void setVisibleObject(int objectId);

    DrawableObjectsContainer & operator=(const DrawableObjectsContainer<T>& other);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    using DrawableContainer::pushBack;
    using DrawableContainer::erase;
    using DrawableContainer::clear;
    std::list<T> list;
    int visibleObject;
};

}

#include "drawable_objects_container.cpp"

#endif // DRAWABLEDCELVECTOR_H
