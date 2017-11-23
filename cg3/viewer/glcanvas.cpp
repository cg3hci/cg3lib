/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#include <iostream>

#include "glcanvas.h"
#include <cg3/geometry/plane.h>
#include <cg3/geometry/2d/point2d.h>

using namespace cg3;

GLcanvas::GLcanvas(QWidget * parent) : clearColor(Qt::white) {
    setParent(parent);
}

GLcanvas::~GLcanvas() {
}

void GLcanvas::init() {
    setFPSIsDisplayed(true);
    camera()->frame()->setSpinningSensitivity(100.0);
}

void GLcanvas::clear() {
    drawlist.clear();
    objVisibility.clear();
}

void GLcanvas::postSelection(const QPoint& point) {
  // Find the selectedPoint coordinates, using camera()->pointUnderPixel().
  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.
  unsigned int idObject = selectedName();
  // Note that "found" is different from (selectedObjectId()>=0) because of the size of the select region.

  if ((int) idObject == -1){
      qglviewer::Vec orig, dir;
      //qglviewer::Vec vdir;
      qglviewer::Vec scenter = camera()->sceneCenter();
      Pointd pointCenter(scenter.x, scenter.y, scenter.z);
      camera()->convertClickToLine(point, orig, dir);
      Line line(Pointd(orig.x, orig.y, orig.z), Vec3(dir.x, dir.y, dir.z));
      Plane plane(Vec3(0,0,1),0);
      Pointd inters;
      bool b = plane.getIntersection(inters, line);
      inters += pointCenter;
      if (b){
          //QMessageBox::information(this, "Point", "Coord Point: " + QString::number(point.x()) + "," + QString::number(point.y()) + "\n"
          //                         + "Point Clicked: " + QString::number(inters.x()) + "," + QString::number(inters.y()));
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
              updateGL();
          }
      }
}

void GLcanvas::drawWithNames() {
    setBackgroundColor(clearColor);

    for(int i=0; i<(int)drawlist.size(); ++i){
        if (/*(drawlist[i])->isVisible() &&*/ objVisibility[i]){
            const PickableObject* obj = dynamic_cast<const PickableObject*>(drawlist[i]);
            if (obj) // se il drawable object è anche un pickable object, allora chiamo la draw with names
                obj->drawWithNames();
        }
    }
}

void GLcanvas::draw() {
    setBackgroundColor(clearColor);

    for(int i=0; i<(int)drawlist.size(); ++i) {
        if (objVisibility[i])
            drawlist[i]->draw();
    }
}

int GLcanvas::pushObj(const DrawableObject* obj, bool visible) {
    drawlist.push_back(obj);
    objVisibility.push_back(visible);
    updateGL();

    return drawlist.size();
}

void GLcanvas::deleteObj(const DrawableObject* obj) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        drawlist.erase(it);
        int pos = it - drawlist.begin();
        objVisibility.erase(objVisibility.begin()+pos);
    }
}

void GLcanvas::setVisibility(const DrawableObject* obj, bool visible) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        objVisibility[pos] = visible;
    }
}

bool GLcanvas::isVisible(const DrawableObject* obj) {
    std::vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) {
        int pos = it - drawlist.begin();
        return objVisibility[pos];
    }
    return false;
}

void GLcanvas::serializePointOfView(std::ofstream &file) {
    qglviewer::Vec v = this->camera()->position();
    qglviewer::Quaternion q = this->camera()->orientation();
    Serializer::serializeObjectAttributes("cg3PointOfView", file, v.x, v.y, v.z, q[0], q[1], q[2], q[3]);
}

bool GLcanvas::deserializePointOfView(std::ifstream &file) {
    qglviewer::Vec v;
    qglviewer::Quaternion q;
    try {
        Serializer::deserializeObjectAttributes("cg3PointOfView", file, v.x, v.y, v.z, q[0], q[1], q[2], q[3]);
        return true;
    }
    catch(...){
        return false;
    }
}

void GLcanvas::savePointOfView(const std::string &filename) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    serializePointOfView(file);

    file.close();
}

bool GLcanvas::loadPointOfView(const std::string &filename) {

    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);

    bool ok = deserializePointOfView(file);

    file.close();

    return ok;
}

void GLcanvas::fitScene() {
    Pointd sceneCenter(0,0,0);
    double sceneRadius = 0.0;
    int   count  = 0;

    if (getNumberVisibleObjects() == 0) sceneRadius = 1.0;
    else {
        double minx = DBL_MAX;
        double maxx = -DBL_MAX;
        double miny = DBL_MAX;
        double maxy = -DBL_MAX;
        double minz = DBL_MAX;
        double maxz = -DBL_MAX;

        for(int i=0; i<(int)drawlist.size(); ++i) {
            const DrawableObject * obj = drawlist[i];
            if (objVisibility[i] /*&& obj->isVisible()*/ && obj->sceneRadius() > std::numeric_limits<float>::epsilon()) {
                Pointd objCenter = obj->sceneCenter();
                double objRadius = obj->sceneRadius();

                minx = std::min((objCenter + Pointd(-objRadius,0,0)).x(), minx);
                maxx = std::max((objCenter + Pointd(objRadius,0,0)).x(), maxx);

                miny = std::min((objCenter + Pointd(0,-objRadius,0)).y(), miny);
                maxy = std::max((objCenter + Pointd(0,objRadius,0)).y(), maxy);

                minz = std::min((objCenter + Pointd(0,0,-objRadius)).z(), minz);
                maxz = std::max((objCenter + Pointd(0,0,objRadius)).z(), maxz);

                ++count;
            }
        }
        if (count == 0){
            minx = miny = minz = -1;
            maxx = maxy = maxz = 1;
        }

        BoundingBox bb(Pointd(minx, miny, minz), Pointd(maxx, maxy, maxz));

        sceneRadius = bb.diag() / 2;
        sceneCenter = bb.center();
    }

    setSceneCenter(qglviewer::Vec(sceneCenter.x(), sceneCenter.y(), sceneCenter.z()));
    setSceneRadius(sceneRadius);

    showEntireScene();
}

void GLcanvas::fitScene(const Pointd& center, double radius) {
    setSceneCenter(qglviewer::Vec(center.x(), center.y(), center.z()));
    setSceneRadius(radius);
    showEntireScene();
}

void GLcanvas::setClearColor(const QColor &color) {
    clearColor = color;
    updateGL();
}

BoundingBox GLcanvas::getFullBoundingBox() {
    BoundingBox bb;
    for(int i=0; i<(int)drawlist.size(); ++i) {
        const DrawableObject * obj = drawlist[i];
        if (objVisibility[i] /*&& obj->isVisible()*/ && obj->sceneRadius() > 0) {
            Pointd center = obj->sceneCenter();
            bb.setMin(bb.getMin().min(Pointd(center.x() - obj->sceneRadius(), center.y() - obj->sceneRadius(), center.z() - obj->sceneRadius())));
            bb.setMax(bb.getMax().max(Pointd(center.x() + obj->sceneRadius(), center.y() + obj->sceneRadius(), center.z() + obj->sceneRadius())));
        }
    }
    return bb;
}

int GLcanvas::getNumberVisibleObjects() {
    int count = 0;
    for(int i=0; i<(int)drawlist.size(); ++i) {
        if (objVisibility[i]) count++;
    }
    return count;
}
