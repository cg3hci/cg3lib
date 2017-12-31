/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */
#include "offlineviewer.h"

namespace cg3 {

namespace viewer {

OfflineViewer::OfflineViewer() {
    resize(QSize(1920, 1080));
    drawlist.push_back(&obj);
}

void OfflineViewer::draw() {
    setBackgroundColor(clearColor);

    for(unsigned int i=0; i<drawlist.size(); ++i) {
        if (objVisibility[i])
            drawlist[i]->draw();
    }
}

void OfflineViewer::changeResolution(unsigned int w, unsigned int h) {
    resize(QSize(w, h));
}

void OfflineViewer::clear() {
    drawlist.clear();
    objVisibility.clear();
}

void OfflineViewer::fitScene() {
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
        if (count == 0){
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

void OfflineViewer::fitScene(const Pointd& center, double radius) {
    setSceneCenter(qglviewer::Vec(center.x(), center.y(), center.z()));
    setSceneRadius(radius);
    showEntireScene();
}

void OfflineViewer::setClearColor(const QColor& color) {
    clearColor = color;
    update();
}

BoundingBox OfflineViewer::getFullBoundingBox() const {
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

int OfflineViewer::getNumberVisibleObjects() const {
    int count = 0;
    for(int i=0; i<(int)drawlist.size(); ++i) {
        if (objVisibility[i]) count++;
    }
    return count;
}

unsigned int OfflineViewer::pushObj(const DrawableObject* obj, bool visible) {
    drawlist.push_back(obj);
    objVisibility.push_back(visible);
    update();

    return (unsigned int)drawlist.size();
}

void OfflineViewer::deleteObj(const DrawableObject* obj) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        drawlist.erase(it);
        int pos = it - drawlist.begin();
        objVisibility.erase(objVisibility.begin()+pos);
    }
}

void OfflineViewer::setVisibility(const DrawableObject* obj, bool visible) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        objVisibility[pos] = visible;
    }
}

bool OfflineViewer::isVisible(const DrawableObject* obj) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        return objVisibility[pos];
    }
    return false;
}

void OfflineViewer::resetPointOfView() {
    qglviewer::Vec v(0,0,2.61313);
    qglviewer::Quaternion q(0,0,0,1);
    camera()->setPosition(v);
    camera()->setOrientation(q);
}

void OfflineViewer::serializePointOfView(std::ofstream& file) {
    qglviewer::Vec v = this->camera()->position();
    qglviewer::Quaternion q = this->camera()->orientation();
    serializeObjectAttributes("cg3PointOfView", file, v.x, v.y, v.z, q[0], q[1], q[2], q[3]);
}

bool OfflineViewer::deserializePointOfView(std::ifstream& file) {
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

void OfflineViewer::savePointOfView(const std::string& filename) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    serializePointOfView(file);

    file.close();
}

bool OfflineViewer::loadPointOfView(const std::string& filename) {
    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);

    bool ok = deserializePointOfView(file);

    file.close();

    return ok;
}

void OfflineViewer::saveSnapshot() {
    update();
    QGLViewer::saveSnapshot();
}

void OfflineViewer::saveSnapshot(const std::string& filename) {
    update();
    QGLViewer::saveSnapshot(QString::fromStdString(filename), true);
}

void OfflineViewer::drawAxis(bool b) {
    setAxisIsDrawn(b);
    update();
}

}

}
