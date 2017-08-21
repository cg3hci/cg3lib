/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
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

//using namespace std;

class GLcanvas : public QGLViewer {

        Q_OBJECT

    public:

        GLcanvas(QWidget * parent = nullptr);
        ~GLcanvas();

        void init();
        void draw();
        void drawWithNames();
        void clear();
        void fitScene();
        void fitScene(const cg3::Pointd &center, double radius);
        void setClearColor(const QColor & color);
        cg3::BoundingBox getFullBoundingBox();
        int getNumberVisibleObjects();
        void postSelection(const QPoint& point);

        int  pushObj(const cg3::DrawableObject * obj, bool visible = true);
        void deleteObj(const cg3::DrawableObject* obj);
        void setVisibility(const cg3::DrawableObject * obj, bool visible = true);
        bool isVisible(const cg3::DrawableObject* obj);

    signals:
        void objectPicked(unsigned int);
        void point2DClicked(cg3::Point2Dd);
    private:

        QColor clearColor;
        std::vector<const cg3::DrawableObject *> drawlist;
        std::vector<bool> objVisibility;

        qglviewer::Vec orig, dir, selectedPoint;
};

#endif // CG3_GL_CANVAS_H
