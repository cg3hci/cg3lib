/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */
#ifndef CG3_OFFLINEVIEWER_H
#define CG3_OFFLINEVIEWER_H

#ifdef WIN32
#include "windows.h"
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedCameraFrame.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <vector>

#include <cg3/geometry/bounding_box.h>
#include "interfaces/drawable_object.h"
#include "drawable_objects/drawable_objects.h"


class OfflineViewer : public QGLViewer {
    public:
        OfflineViewer();

        //QGLViewer Override:
        void draw();

        //OfflineViewer methods:
        void changeResolution(unsigned int w, unsigned int h);
        void clear();
        void fitScene();
        void fitScene(const cg3::Pointd &center, double radius);
        void setClearColor(const QColor & color);
        cg3::BoundingBox getFullBoundingBox() const;
        int getNumberVisibleObjects() const;

        unsigned int pushObj(const cg3::DrawableObject * obj, bool visible = true);
        void deleteObj(const cg3::DrawableObject* obj);
        void setVisibility(const cg3::DrawableObject * obj, bool visible = true);
        bool isVisible(const cg3::DrawableObject* obj);

        void resetPointOfView();
        void serializePointOfView(std::ofstream& file);
        bool deserializePointOfView(std::ifstream& file);
        void savePointOfView(const std::string& filename);
        bool loadPointOfView(const std::string& filename);

        void saveSnapshot();
        void saveSnapshot(const std::string& filename);
        void drawAxis(bool b);

    private:
        QColor clearColor;
        std::vector<const cg3::DrawableObject *> drawlist;
        std::vector<bool> objVisibility;
        cg3::DrawableObjects obj;

};

#endif // CG3_OFFLINEVIEWER_H
