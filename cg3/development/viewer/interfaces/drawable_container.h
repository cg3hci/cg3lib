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

namespace internal {

class DrawableContainerSignals : public QObject {
    Q_OBJECT

public:
    explicit DrawableContainerSignals(QObject *parent = 0) :
        QObject(parent) {}
signals:
    void drawableContainerPushedObject(const DrawableObject*, unsigned int i, bool vis);
    void drawableContainerErasedObject(const DrawableObject*, unsigned int i);
    void drawableCntainerVisibilityObject(const DrawableObject*, unsigned int i, bool vis);
};

}

namespace viewer {
class GLCanvas;
class MainWindow;
}

template <typename T>
class DrawableContainer : public DrawableObject, public internal::DrawableContainerSignals
{
public:
    friend class viewer::GLCanvas;
    friend class viewer::MainWindow;

    DrawableContainer();
    virtual ~DrawableContainer();
    virtual void pushBack(const T &obj, bool visibility = true);
    virtual const T& operator [] (unsigned int i) const;
    virtual T &operator [] (unsigned int i);
    virtual unsigned int size() const;
    virtual void erase(unsigned int i);

    // DrawableObject interface
    virtual void draw() const;
    virtual Pointd sceneCenter() const;
    virtual double sceneRadius() const;

    typedef typename std::vector<T>::iterator iterator;

private:
    cg3::BoundingBox totalVisibleBoundingBox() const;

    std::vector<T> objects;
    std::vector<bool> objectsVisibility;

};

}

#include "drawable_container.tpp"

#endif // CG3_DRAWABLE_CONTAINER_H
