/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#ifndef CG3_GL_CANVAS_H
#define CG3_GL_CANVAS_H

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
#include <cg3/geometry/2d/point2d.h>
#include "interfaces/drawable_object.h"
#include "interfaces/pickable_object.h"
#include <qmessagebox.h>

namespace cg3 {

namespace viewer {

class GLCanvas : public QGLViewer {

        Q_OBJECT

    public:

        GLCanvas(QWidget * parent = nullptr);

        //QGLViewer Override:
        void init();
        void draw();
        void drawWithNames();
        void postSelection(const QPoint& point);

        //GLCanvas methods:
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

    signals:
        void objectPicked(unsigned int);
        void point2DClicked(cg3::Point2Dd);
    private:

        QColor clearColor;
        std::vector<const cg3::DrawableObject *> drawlist;
        std::vector<bool> objVisibility;

        qglviewer::Vec orig, dir, selectedPoint;
};

}

}

#endif // CG3_GL_CANVAS_H
