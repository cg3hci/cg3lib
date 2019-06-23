/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_CONTAINER_H
#define CG3_DRAWABLE_CONTAINER_H

#include <cg3/viewer/interfaces/drawable_object.h>

#include <cg3/geometry/bounding_box3.h>
#include <QtCore>

namespace cg3 {

/**
 * @brief The DrawableContainer class defines a container of pointers to DrawableObjects.
 *
 * Allows an automatic management of a container of DrawableObjects which are correlated, and
 * allows to automatically draw/not draw the entire list or draw/not draw every
 * DrawableObject contained in the container. To every Object is associated also a
 * std::string which will be visualized in the MainWindow.
 * The container is implemented as a vector, therefore an unsigned integer is associated
 * to every Object, and an erase operation will shift all the elements after the removed
 * element.
 */
class DrawableContainer :
        public QObject,
        public DrawableObject
{
    Q_OBJECT
public:
    explicit DrawableContainer(QObject *parent = 0);
    DrawableContainer(const DrawableContainer&) = delete;
    DrawableContainer & operator=(const DrawableContainer&) = delete;

    virtual ~DrawableContainer();
    virtual void pushBack(const DrawableObject* obj,
            const std::string& objectName = "",
            bool objVisibility = true);
    virtual const DrawableObject* operator [] (unsigned int i) const;
    virtual unsigned int size() const;
    virtual void erase(unsigned int i);
    virtual void clear();
    virtual const std::string& objectName(unsigned int i) const;
    virtual void setObjectVisibility(unsigned int i, bool vis) const;

    // DrawableObject interface
    virtual void draw() const;
    virtual Point3d sceneCenter() const;
    virtual double sceneRadius() const;

signals:
    void drawableContainerPushedObject(
            const std::string&,
            bool);
    void drawableContainerErasedObject(const DrawableObject*);
    void drawableContainerVisibilityObjectChanged(const DrawableObject*, bool) const;

private:
    cg3::BoundingBox3 totalBoundingBox() const;

    std::vector<const cg3::DrawableObject*> objects;
    std::vector<std::string> objectNames;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_CONTAINER_CPP "drawable_container.cpp"
#include CG3_DRAWABLE_CONTAINER_CPP
#undef CG3_DRAWABLE_CONTAINER_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_CONTAINER_H
