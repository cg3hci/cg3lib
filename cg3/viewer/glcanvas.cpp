/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#include <iostream>

#include "glcanvas.h"
#include <cg3/geometry/plane.h>
#include <cg3/geometry/2d/point2d.h>

namespace cg3 {

namespace viewer {

GLCanvas::GLCanvas(QWidget * parent) : clearColor(Qt::white) {
    setParent(parent);
}

void GLCanvas::init() {
    setFPSIsDisplayed(true);
    camera()->frame()->setSpinningSensitivity(100.0);
}

void GLCanvas::draw() {
    setBackgroundColor(clearColor);

    for(unsigned int i=0; i<drawlist.size(); ++i) {
        if (objVisibility[i])
            drawlist[i]->draw();
    }
}

void GLCanvas::drawWithNames() {
    setBackgroundColor(clearColor);

    for(int i=0; i<(int)drawlist.size(); ++i){
        if (objVisibility[i]){
            const PickableObject* obj = dynamic_cast<const PickableObject*>(drawlist[i]);
            if (obj) // se il drawable object è anche un pickable object, allora chiamo la draw with names
                obj->drawWithNames();
        }
    }
}

void GLCanvas::postSelection(const QPoint& point) {
    // Find the selectedPoint coordinates, using camera()->pointUnderPixel().
    bool found;
    selectedPoint = camera()->pointUnderPixel(point, found);
    selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.
    unsigned int idObject = selectedName();
    // Note that "found" is different from (selectedObjectId()>=0) because of the size of the selected region.

    if ((int) idObject == -1){
        qglviewer::Vec orig, dir;
        camera()->convertClickToLine(point, orig, dir);
        Line line(Pointd(orig.x, orig.y, orig.z), Vec3(dir.x, dir.y, dir.z));
        Plane plane(Vec3(0,0,1),0);
        Pointd inters;
        bool b = plane.getIntersection(inters, line);
        if (b) {
            emit point2DClicked(Point2Dd(inters.x(), inters.y()));
        }
        else {
            QMessageBox::information(this, "No selection", "No Intersection between Clicked Point and Z plane");
        }
    }
    else
        for(int i=0; i<(int)drawlist.size(); ++i){
            const PickableObject* po = dynamic_cast<const PickableObject*>(drawlist[i]);
            if (po) { // se è un PickableObject, allora faccio la emit sull'object!
                emit objectPicked(idObject);
                update();
            }
        }
}

void GLCanvas::clear() {
    drawlist.clear();
    objVisibility.clear();
}

unsigned int GLCanvas::pushObj(const DrawableObject* obj, bool visible) {
    drawlist.push_back(obj);
    objVisibility.push_back(visible);
    update();

    return (unsigned int)drawlist.size();
}

void GLCanvas::deleteObj(const DrawableObject* obj) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = std::distance(drawlist.begin(), it);
        objVisibility.erase(objVisibility.begin()+pos);
        drawlist.erase(it);
    }
}

void GLCanvas::setVisibility(const DrawableObject* obj, bool visible) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        objVisibility[pos] = visible;
    }
}

bool GLCanvas::isVisible(const DrawableObject* obj) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        return objVisibility[pos];
    }
    return false;
}

void GLCanvas::resetPointOfView() {
    qglviewer::Vec v(0,0,2.61313);
    qglviewer::Quaternion q(0,0,0,1);
    camera()->setPosition(v);
    camera()->setOrientation(q);
}

void GLCanvas::serializePointOfView(std::ofstream &file) {
    qglviewer::Vec v = this->camera()->position();
    qglviewer::Quaternion q = this->camera()->orientation();
    serializeObjectAttributes("cg3PointOfView", file, v.x, v.y, v.z, q[0], q[1], q[2], q[3]);
}

bool GLCanvas::deserializePointOfView(std::ifstream &file) {
    qglviewer::Vec v;
    qglviewer::Quaternion q;
    try {
        deserializeObjectAttributes("cg3PointOfView", file, v.x, v.y, v.z, q[0], q[1], q[2], q[3]);
        this->camera()->setPosition(v);
        this->camera()->setOrientation(q);
        return true;
    }
    catch(...){
        return false;
    }
}

void GLCanvas::savePointOfView(const std::string &filename) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    serializePointOfView(file);

    file.close();
}

bool GLCanvas::loadPointOfView(const std::string &filename) {

    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);

    bool ok = deserializePointOfView(file);

    file.close();

    return ok;
}

void GLCanvas::fitScene() {
    Pointd sceneCenter(0,0,0);
    double sceneRadius = 0.0;
    int   count  = 0;

    if (getNumberVisibleObjects() == 0) sceneRadius = 1.0;
    else {
        const double dmax = std::numeric_limits<double>::max();
        const double dmin = std::numeric_limits<double>::min();
        BoundingBox bb(Pointd(dmax, dmax, dmax), Pointd(dmin, dmin, dmin));

        for(int i=0; i<(int)drawlist.size(); ++i) {
            const DrawableObject * obj = drawlist[i];
            if (objVisibility[i] && obj->sceneRadius() > std::numeric_limits<float>::epsilon()) {
                Pointd objCenter = obj->sceneCenter();
                double objRadius = obj->sceneRadius();

                bb.minX() = std::min((objCenter + Pointd(-objRadius,0,0)).x(), bb.minX());
                bb.maxX() = std::max((objCenter + Pointd( objRadius,0,0)).x(), bb.maxX());

                bb.minY() = std::min((objCenter + Pointd(0,-objRadius,0)).y(), bb.minY());
                bb.maxY() = std::max((objCenter + Pointd(0, objRadius,0)).y(), bb.maxY());

                bb.minZ() = std::min((objCenter + Pointd(0,0,-objRadius)).z(), bb.minZ());
                bb.maxZ() = std::max((objCenter + Pointd(0,0, objRadius)).z(), bb.maxZ());

                ++count;
            }
        }
        if (count == 0) {
            bb.min() = Pointd(-1,-1,-1);
            bb.max() = Pointd( 1, 1, 1);
        }

        sceneRadius = bb.diag() / 2;
        sceneCenter = bb.center();
    }

    setSceneCenter(qglviewer::Vec(sceneCenter.x(), sceneCenter.y(), sceneCenter.z()));
    setSceneRadius(sceneRadius);
    showEntireScene();
}

void GLCanvas::fitScene(const Pointd& center, double radius) {
    setSceneCenter(qglviewer::Vec(center.x(), center.y(), center.z()));
    setSceneRadius(radius);
    showEntireScene();
}

void GLCanvas::setClearColor(const QColor &color) {
    clearColor = color;
    update();
}

BoundingBox GLCanvas::getFullBoundingBox() const {
    BoundingBox bb;
    for(int i=0; i<(int)drawlist.size(); ++i) {
        const DrawableObject * obj = drawlist[i];
        if (objVisibility[i] && obj->sceneRadius() > 0) {
            Pointd center = obj->sceneCenter();
            bb.setMin(bb.getMin().min(Pointd(center.x() - obj->sceneRadius(), center.y() - obj->sceneRadius(), center.z() - obj->sceneRadius())));
            bb.setMax(bb.getMax().max(Pointd(center.x() + obj->sceneRadius(), center.y() + obj->sceneRadius(), center.z() + obj->sceneRadius())));
        }
    }
    return bb;
}

int GLCanvas::getNumberVisibleObjects() const {
    int count = 0;
    for(int i=0; i<(int)drawlist.size(); ++i) {
        if (objVisibility[i]) count++;
    }
    return count;
}

}

}
