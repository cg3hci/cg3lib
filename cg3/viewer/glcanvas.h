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

#include <cg3/geometry/point2.h>
#include "interfaces/drawable_object.h"
#include "interfaces/pickable_object.h"
#include "interfaces/manipulable_object.h"
#include "drawable_objects/drawable_bounding_box3.h"
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
    GLCanvas(QWidget* parent = nullptr);

    //QGLViewer Override:
    void init();
    void draw();
    void drawWithNames();
    void postSelection(const QPoint& point);

    //GLCanvas rendering member functions:
    void fitScene();
    void fitScene(const cg3::Point3d &center, double radius);
    void fitScene2d(const cg3::Point2d& center, double radius);
    void toggleUnitBox();
    void setBackgroundColor(const QColor & color);
    void set2DMode();
    void set3DMode();
    void saveSnapshot();
    void saveSnapshot(const QString& filename, bool overwrite = true);
    void saveSnapshot(const std::string& filename, bool overwrite = true);

    // Point of View member functions:
    cg3::Point3d cameraPosition() const;
    cg3::Vec3d cameraDirection() const;
    void resetPointOfView();
    void serializePointOfView(std::ofstream& file) const;
    bool deserializePointOfView(std::ifstream& file);
    void savePointOfView() const;
    void loadPointOfView();
    void savePointOfView(const std::string& filename) const;
    bool loadPointOfView(const std::string& filename);
    void setCameraDirection(const cg3::Vec3d& vec);
    void setCameraPosition(const cg3::Point3d& pos);
    void setPerspectiveCamera();
    void setOrthographicCamera();
    void toggleCameraType();
    bool isOrthographicCamera() const;

    //DrawableObjects List management:
    unsigned int sizeVisibleDrawableObjects() const;
    unsigned int sizeDrawableObjectsList() const;
    cg3::BoundingBox3 fullBoundingBoxDrawableObjects(bool onlyVisible = false) const;
    void setDrawableObjectVisibility(const cg3::DrawableObject* obj, bool vis);

    //DrawableObjects List management: these members should be used by cg3::MainWindow
    void clearDrawableObjectsList();
    void pushDrawableObject(const cg3::DrawableObject* obj, bool visible = true);
    void pushDrawableObject(const std::shared_ptr<const cg3::DrawableObject>& ptr, bool visible = true);
    bool deleteDrawableObject(const cg3::DrawableObject* obj);
    bool deleteDrawableObject(const std::shared_ptr<const cg3::DrawableObject>& ptr);
    bool containsDrawableObject(const cg3::DrawableObject* obj) const;
    bool containsDrawableObject(const std::shared_ptr<const cg3::DrawableObject>& ptr) const;

    unsigned int zoomSceneFactor;

signals:

    void objectPicked(const cg3::PickableObject*, unsigned int);
    void point2DClicked(cg3::Point2d);

private:

    void enableRotation(bool b = true);
    void enableTranslation(bool b = true);
    void enableZoom(bool b = true);
    void setSelectionLeftButton(bool b = true);

    QColor backgroundColor;
    std::vector<const cg3::DrawableObject*> drawlist;
    std::vector<const cg3::PickableObject*> pickList;
    std::set<std::shared_ptr<const cg3::DrawableObject> > sharedDrawableObjects;
    std::set<unsigned int> unusedPickableObjectsIds;
    Mode mode;

	const DrawableBoundingBox3 unitBox;
    bool unitBoxEnabled;
};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_GL_CANVAS_CPP "glcanvas.cpp"
#include CG3_GL_CANVAS_CPP
#undef CG3_GL_CANVAS_CPP
#endif //CG3_STATIC

#endif // CG3_GL_CANVAS_H
