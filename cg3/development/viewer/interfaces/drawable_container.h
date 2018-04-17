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
#include <QtCore>

namespace cg3 {

namespace viewer {
class GLCanvas;
class MainWindow;
} //namespace cg3::viewer

class DrawableContainer : public QObject, public DrawableObject
{
    Q_OBJECT
public:
    friend class viewer::GLCanvas;
    friend class viewer::MainWindow;

    typedef std::vector<const DrawableObject*>::iterator iterator;

    explicit DrawableContainer(QObject *parent = 0);
    virtual ~DrawableContainer();
    virtual void pushBack(const DrawableObject* obj, bool visibility = true);
    virtual const DrawableObject* operator [] (unsigned int i) const;
    virtual unsigned int size() const;
    virtual void erase(unsigned int i);

    // DrawableObject interface
    virtual void draw() const;
    virtual Pointd sceneCenter() const;
    virtual double sceneRadius() const;

    virtual iterator begin();
    virtual iterator end();

signals:
    void drawableContainerPushedObject(const DrawableObject*, unsigned int i, bool vis);
    void drawableContainerErasedObject(const DrawableObject*, unsigned int i);
    void drawableCntainerVisibilityObject(const DrawableObject*, unsigned int i, bool vis);

private:
    cg3::BoundingBox totalVisibleBoundingBox() const;

    std::vector<const cg3::DrawableObject*> objects;
    std::vector<bool> objectsVisibility;

};

} //namespace cg3

#endif // CG3_DRAWABLE_CONTAINER_H
