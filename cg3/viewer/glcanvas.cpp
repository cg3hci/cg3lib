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
#include <cg3/utilities/cg3config.h>

namespace cg3 {
namespace viewer {

GLCanvas::GLCanvas(QWidget * parent) :
    backgroundColor(Qt::white),
    mode(_3D)
{
    setParent(parent);
    setSnapshotQuality(100);
    setSnapshotFormat("PNG");
    cg3::internal::initConfigFolder();
}

void GLCanvas::init()
{
    setFPSIsDisplayed(false);
    camera()->frame()->setSpinningSensitivity(100.0);
}

void GLCanvas::draw()
{
    QGLViewer::setBackgroundColor(backgroundColor);

    for(unsigned int i=0; i<drawlist.size(); ++i) {
        if (objVisibility[i] && drawlist[i] != nullptr)
            drawlist[i]->draw();
    }
}

void GLCanvas::drawWithNames()
{
    QGLViewer::setBackgroundColor(backgroundColor);

    for(int i=0; i<(int)drawlist.size(); ++i){
        if (objVisibility[i]){
            const PickableObject* obj =
                    dynamic_cast<const PickableObject*>(drawlist[i]);
            if (obj) // if it is a PickableObject
                obj->drawWithNames();
        }
    }
}

void GLCanvas::postSelection(const QPoint& point)
{
    unsigned int idName = selectedName();

    if ((int) idName == -1){
        if (mode == _2D){
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
                QMessageBox::information(
                            this, "No selection",
                            "No Intersection between Clicked Point and Z plane");
            }
        }
    }
    else {
        unsigned int idObject, idElement;
        PickableObject::getIdsFromIdName(idName, idObject, idElement);
        if (idObject < pickList.size() && pickList[idObject] != nullptr)
            emit objectPicked(pickList[idObject], idElement);
    }
}

void GLCanvas::fitScene()
{
    Pointd sceneCenter(0,0,0);
    double sceneRadius = 0.0;
    int   count  = 0;

    if (sizeVisibleDrawableObjects() == 0) sceneRadius = 1.0;
    else {
        const double dmax = std::numeric_limits<double>::max();
        const double dmin = std::numeric_limits<double>::min();
        BoundingBox bb(Pointd(dmax, dmax, dmax), Pointd(dmin, dmin, dmin));

        for(int i=0; i<(int)drawlist.size(); ++i) {
            const DrawableObject * obj = drawlist[i];
            if (objVisibility[i] &&
                    obj->sceneRadius() > std::numeric_limits<float>::epsilon()) {
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

void GLCanvas::fitScene(const Pointd& center, double radius)
{
    setSceneCenter(qglviewer::Vec(center.x(), center.y(), center.z()));
    setSceneRadius(radius);
    showEntireScene();
}

void GLCanvas::fitScene2d(const Point2Dd &center, double radius)
{
    setSceneCenter(qglviewer::Vec(center.x(), center.y(), 0));
    setSceneRadius(radius);
    showEntireScene();
}

void GLCanvas::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    update();
}

void GLCanvas::set2DMode()
{
    if (mode != _2D){
        mode = _2D;
        resetPointOfView();
        enableRotation(false);
        update();
    }
}

void GLCanvas::set3DMode()
{
    if (mode != _3D){
        mode = _3D;
        enableRotation();
        update();
    }
}

void GLCanvas::saveSnapshot()
{
    QGLViewer::saveSnapshot();
}

void GLCanvas::saveSnapshot(const QString &filename, bool overwrite)
{
    QGLViewer::saveSnapshot(filename, overwrite);
}

void GLCanvas::saveSnapshot(const std::string &filename, bool overwrite)
{
    QGLViewer::saveSnapshot(QString::fromStdString(filename), overwrite);
}

void GLCanvas::drawAxis(bool b)
{
    setAxisIsDrawn(b);
    update();
}

Pointd GLCanvas::cameraPosition() const
{
    qglviewer::Vec p = camera()->position();
    return cg3::Pointd(p.x, p.y, p.z);
}

Vec3 GLCanvas::cameraDirection() const
{
    qglviewer::Vec p = camera()->viewDirection();
    return cg3::Vec3(p.x, p.y, p.z);
}

void GLCanvas::resetPointOfView()
{
    qglviewer::Vec v(0,0,2.61313);
    qglviewer::Quaternion q(0,0,0,1);
    camera()->setPosition(v);
    camera()->setOrientation(q);
}

void GLCanvas::serializePointOfView(std::ofstream &file) const
{
    qglviewer::Vec v = this->camera()->position();
    qglviewer::Quaternion q = this->camera()->orientation();
    serializeObjectAttributes(
                "cg3PointOfView", file, v.x, v.y, v.z,
                q[0], q[1], q[2], q[3]);
}

bool GLCanvas::deserializePointOfView(std::ifstream &file)
{
    qglviewer::Vec v;
    qglviewer::Quaternion q;
    try {
        deserializeObjectAttributes(
                    "cg3PointOfView", file, v.x, v.y, v.z,
                    q[0], q[1], q[2], q[3]);
        this->camera()->setPosition(v);
        this->camera()->setOrientation(q);
        return true;
    }
    catch(...){
        return false;
    }
}

void GLCanvas::savePointOfView() const
{
    savePointOfView(cg3::internal::configFolderDirectory + "pov.cg3pov");
}

void GLCanvas::loadPointOfView()
{
    loadPointOfView(cg3::internal::configFolderDirectory + "pov.cg3pov");
}

void GLCanvas::savePointOfView(const std::string &filename) const
{
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    serializePointOfView(file);

    file.close();
}

bool GLCanvas::loadPointOfView(const std::string &filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);

    bool ok = deserializePointOfView(file);

    file.close();

    return ok;
}

void GLCanvas::setCameraDirection(const Vec3 &vec)
{
    qglviewer::Vec qglVec (vec.x(), vec.y(), vec.z());
    qglVec.normalize();
    camera()->setViewDirection(qglVec);
}

void GLCanvas::setCameraPosition(const Pointd &pos)
{
    qglviewer::Vec qglvec(pos.x(), pos.y(), pos.z());
    camera()->setPosition(qglvec);
}

void GLCanvas::clearDrawableObjectsList()
{
    drawlist.clear();
    objVisibility.clear();
}

unsigned int GLCanvas::pushDrawableObject(const DrawableObject* obj, bool visible)
{
    unsigned int id;
    if (unusedIds.size() == 0) {
        drawlist.push_back(obj);
        objVisibility.push_back(visible);
        update();
        id = drawlist.size();
    }
    else {
        id = *unusedIds.begin();
        drawlist[id] = obj;
        objVisibility[id] = visible;
        unusedIds.erase(id);
        update();
    }

    const PickableObject* pobj =
            dynamic_cast<const PickableObject*>(obj);

    if (pobj) {
        if (unusedPickableObjectsIds.size() == 0){
            pickList.push_back(pobj);
            pobj->id = pickList.size()-1;
        }
        else {
            pobj->id = *unusedPickableObjectsIds.begin();
            pickList[pobj->id] = pobj;
            unusedPickableObjectsIds.erase(unusedPickableObjectsIds.begin());
        }
    }
    return id;
}

bool GLCanvas::deleteDrawableObject(const DrawableObject* obj)
{
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = std::distance(drawlist.begin(), it);
        objVisibility[pos] = false;
        drawlist[pos] = nullptr;
        unusedIds.insert(pos);

        const PickableObject* pobj =
                dynamic_cast<const PickableObject*>(obj);

        if (pobj) {
            unusedPickableObjectsIds.insert(pobj->id);
            pickList[pobj->id] = nullptr;
        }

        return true;
    }
    return false;
}

bool GLCanvas::deleteDrawableObject(unsigned int idObject)
{
    if (idObject < drawlist.size() && drawlist[idObject] != nullptr){
        const cg3::DrawableObject* obj = drawlist[idObject];
        objVisibility[idObject] = false;
        drawlist[idObject] = nullptr;
        unusedIds.insert(idObject);

        const PickableObject* pobj =
                dynamic_cast<const PickableObject*>(obj);

        if (pobj) {
            unusedPickableObjectsIds.insert(pobj->id);
            pickList[pobj->id] = nullptr;
        }
        return true;
    }
    else
        return false;
}

bool GLCanvas::setDrawableObjectVisibility(const DrawableObject* obj, bool visible)
{
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        objVisibility[pos] = visible;
        return true;
    }
    return false;
}

bool GLCanvas::isDrawableObjectVisible(const DrawableObject* obj) const
{
    std::vector<const DrawableObject *>::const_iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        return objVisibility[pos];
    }
    return false;
}

bool GLCanvas::containsDrawableObject(const DrawableObject *obj) const
{
    std::vector<const DrawableObject *>::const_iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    return it != drawlist.end();
}

unsigned int GLCanvas::sizeVisibleDrawableObjects() const
{
    unsigned int count = 0;
    for(unsigned int i=0; i<drawlist.size(); ++i) {
        if (objVisibility[i]) count++;
    }
    return count;
}

unsigned int GLCanvas::sizeDrawableObjectsList() const
{
    return drawlist.size() - unusedIds.size();
}

BoundingBox GLCanvas::getFullBoundingBoxDrawableObjects(bool onlyVisible) const
{
    BoundingBox bb;
    for(int i=0; i<(int)drawlist.size(); ++i) {
        const DrawableObject * obj = drawlist[i];
        if (obj != nullptr) {
            if (onlyVisible) {
                if (objVisibility[i] && obj->sceneRadius() > 0) {
                    Pointd center = obj->sceneCenter();
                    bb.setMin(bb.getMin().min(Pointd(center.x() - obj->sceneRadius(), center.y() - obj->sceneRadius(), center.z() - obj->sceneRadius())));
                    bb.setMax(bb.getMax().max(Pointd(center.x() + obj->sceneRadius(), center.y() + obj->sceneRadius(), center.z() + obj->sceneRadius())));
                }
            }
            else {
                if (obj->sceneRadius() > 0) {
                    Pointd center = obj->sceneCenter();
                    bb.setMin(bb.getMin().min(Pointd(center.x() - obj->sceneRadius(), center.y() - obj->sceneRadius(), center.z() - obj->sceneRadius())));
                    bb.setMax(bb.getMax().max(Pointd(center.x() + obj->sceneRadius(), center.y() + obj->sceneRadius(), center.z() + obj->sceneRadius())));
                }
            }
        }
    }
    return bb;
}

void GLCanvas::enableRotation(bool b)
{
    if (b)
        setMouseBinding(Qt::NoModifier, Qt::LeftButton, CAMERA, ROTATE);
    else
        setMouseBinding(Qt::NoModifier, Qt::LeftButton, NO_CLICK_ACTION);
}

void GLCanvas::enableTranslation(bool b)
{
    if (b)
        setMouseBinding(Qt::NoModifier, Qt::RightButton, CAMERA, TRANSLATE);
    else
        setMouseBinding(Qt::NoModifier, Qt::RightButton, NO_CLICK_ACTION);
}

void GLCanvas::enableZoom(bool b)
{
    if (b)
        setWheelBinding(Qt::NoModifier, CAMERA, ZOOM);
    else
        setWheelBinding(Qt::NoModifier, CAMERA, NO_MOUSE_ACTION);
}

void GLCanvas::setSelectionLeftButton(bool b)
{
    if (b)
        setMouseBinding(Qt::NoModifier, Qt::LeftButton, SELECT);
    else
        enableRotation();
}

} //namespace cg3::viewer
} //namespace cg3
