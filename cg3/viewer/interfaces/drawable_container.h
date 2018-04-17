/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_CONTAINER_H
#define CG3_DRAWABLE_CONTAINER_H

#include <cg3/viewer/interfaces/drawable_object.h>

#include <cg3/geometry/bounding_box.h>
#ifdef CG3_VIEWER_DEFINED
#include <QtCore>
#endif

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
        #ifdef CG3_VIEWER_DEFINED
        public QObject,
        #endif
        public DrawableObject
{
    #ifdef CG3_VIEWER_DEFINED
    Q_OBJECT
    #endif
public:

    typedef std::vector<const DrawableObject*>::iterator iterator;
    typedef std::vector<const DrawableObject*>::const_iterator const_iterator;

    #ifdef CG3_VIEWER_DEFINED
    explicit DrawableContainer(QObject *parent = 0);
    #else
    DrawableContainer();
    #endif
    virtual ~DrawableContainer();
    virtual void pushBack(
            const DrawableObject* obj,
            const std::string& objectName = "",
            bool visibility = true);
    virtual const DrawableObject* operator [] (unsigned int i) const;
    virtual unsigned int size() const;
    virtual void erase(unsigned int i);
    virtual const std::string& objectName(unsigned int i) const;

    // DrawableObject interface
    virtual void draw() const;
    virtual Pointd sceneCenter() const;
    virtual double sceneRadius() const;

    virtual iterator begin();
    virtual iterator end();
    virtual const_iterator begin() const;
    virtual const_iterator end() const;

    #ifdef CG3_VIEWER_DEFINED
signals:
    void drawableContainerPushedObject(
            const DrawableContainer*,
            const std::string& objectName,
            bool vis);
    void drawableContainerErasedObject(const DrawableContainer*, unsigned int i);
    #endif

private:
    cg3::BoundingBox totalVisibleBoundingBox() const;

    std::vector<const cg3::DrawableObject*> objects;
    std::vector<std::string> objectNames;
};

} //namespace cg3

#endif // CG3_DRAWABLE_CONTAINER_H
