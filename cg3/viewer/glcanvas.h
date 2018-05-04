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

class MainWindow;

/**
 * @brief The GLCanvas class
 *
 * A QGLViewer Canvas that can be used in 2D or 3D mode
 * and that manages a list of DrawableObjects/PickableObjects that can be
 * automatically drawn.
 *
 * It provides utilities like saving high quality snapshots, save/restore of
 * a point of view and a lot of other utilities.
 *
 * @ingroup cg3viewer
 */
class GLCanvas : public QGLViewer
{
    Q_OBJECT

public:

    typedef enum {_2D, _3D} Mode;

    friend class cg3::viewer::MainWindow;
    GLCanvas(QWidget * parent = nullptr);

    //QGLViewer Override:
    void init();
    void draw();
    void drawWithNames();
    void postSelection(const QPoint& point);

    //GLCanvas rendering member functions:
    void fitScene();
    void fitScene(const cg3::Pointd &center, double radius);
    void fitScene2d(const cg3::Point2Dd& center, double radius);
    void setBackgroundColor(const QColor & color);
    void set2DMode();
    void set3DMode();
    void saveSnapshot();
    void saveSnapshot(const QString& filename, bool overwrite = true);
    void saveSnapshot(const std::string& filename, bool overwrite = true);
    void drawAxis(bool b);

    // Point of View member functions:
    cg3::Pointd cameraPosition() const;
    cg3::Vec3 cameraDirection() const;
    void resetPointOfView();
    void serializePointOfView(std::ofstream& file) const;
    bool deserializePointOfView(std::ifstream& file);
    void savePointOfView() const;
    void loadPointOfView();
    void savePointOfView(const std::string& filename) const;
    bool loadPointOfView(const std::string& filename);
    void setCameraDirection(const cg3::Vec3& vec);
    void setCameraPosition(const cg3::Pointd& pos);

    //DrawableObjects List management:
    unsigned int sizeVisibleDrawableObjects() const;
    unsigned int sizeDrawableObjectsList() const;
    bool isDrawableObjectVisible(const cg3::DrawableObject* obj) const;
    cg3::BoundingBox getFullBoundingBoxDrawableObjects(bool onlyVisible = false) const;

    //DrawableObjects List management: these members should be used by cg3::MainWindow
    void clearDrawableObjectsList();
    void pushDrawableObject(const cg3::DrawableObject* obj, bool visible = true);
    bool deleteDrawableObject(const cg3::DrawableObject* obj);
    void setDrawableObjectVisibility(const cg3::DrawableObject* obj, bool visible = true);
    bool containsDrawableObject(const cg3::DrawableObject* obj) const;

    unsigned int zoomSceneFactor;

signals:

    void objectPicked(const cg3::PickableObject*, unsigned int);
    void point2DClicked(cg3::Point2Dd);

private:

    void enableRotation(bool b = true);
    void enableTranslation(bool b = true);
    void enableZoom(bool b = true);
    void setSelectionLeftButton(bool b = true);

    QColor backgroundColor;
    std::vector<const cg3::DrawableObject*> drawlist;
    std::vector<bool> visibility;
    std::vector<const cg3::PickableObject*> pickList;
    std::set<unsigned int> unusedPickableObjectsIds;
    std::set<unsigned int> unusedIds;
    Mode mode;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_GL_CANVAS_H
