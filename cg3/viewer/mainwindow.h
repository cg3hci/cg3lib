/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#ifndef CG3_MAINWINDOW_H
#define CG3_MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBox>
#include <QFrame>
#include <QSignalMapper>
#include <QCheckBox>
#include <QProcess>
#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredeclared-class-member"
#endif
#include <boost/bimap.hpp>
#ifdef __APPLE__
#pragma clang diagnostic pop
#endif
#include <QApplication>

#include "interfaces/drawable_object.h"
#include "interfaces/pickable_object.h"
#include "utilities/loadersaver.h"
#include <cg3/geometry/bounding_box.h>
#include "drawable_objects/drawable_objects.h"
#include "utilities/consolestream.h"
#include <cg3/geometry/2d/point2d.h>

#include "glcanvas.h"

namespace cg3 {
namespace viewer {
namespace Ui {
    class MainWindow;
} //namespace cg3::viewer::Ui

namespace internal {
    class UiMainWindowRaiiWrapper;
} //namespace cg3::viewer::internal

/**
 * @brief MainWindow is a class that manages a QGLViewer canvas and all the managers
 * which are added to it.
 * @ingroup cg3viewer
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Canvas:
    cg3::Point2Di getCanvasSize() const;

    void savePointOfView();
    void loadPointOfView();
    void savePointOfView(std::string filename);
    void loadPointOfView(std::string filename);
    void setBackgroundColor(const QColor &);
    void set2DMode(bool b = true);
    void setCameraDirection(const cg3::Vec3& vec);

    //DrawableObjects for the Canvas
    void pushObj(const cg3::DrawableObject * obj, std::string checkBoxName, bool b = true);
    bool deleteObj(const cg3::DrawableObject * obj, bool b = true);
    void setObjVisibility(const cg3::DrawableObject * obj, bool visible);
    bool contains(const cg3::DrawableObject* obj);
    cg3::BoundingBox getFullBoundingBox();
    int getNumberVisibleObjects();

    //Debug Objects
    void enableDebugObjects();
    void disableDebugObjects();

    //Window Options:
    void setFullScreen(bool);
    void toggleConsoleStream(); //work in progress...
    void keyPressEvent(QKeyEvent * event); //event options for keys pressed

    //Managers:
    int addManager(QFrame *f, std::string name, QToolBox *parent = nullptr);
    QFrame *getManager(unsigned int i);
    void renameManager(unsigned int i, std::string s);
    void setCurrentIndexToolBox(unsigned int i);

    cg3::DrawableObjects debugObjects;

signals:
    /**
     * @brief objectClicked
     * Segnale da "catchare", ha come parametro l'oggetto cliccato nella GLCanvas
     */
    void objectPicked(unsigned int);
    void point2DClicked(cg3::Point2Dd);

    /**
     * @brief undoEvent
     * Segnale da "catchare", viene lanciato quando viene premuto CTRL+Z
     */
    void undoEvent();

    /**
     * @brief undoEvent
     * Segnale da "catchare", viene lanciato quando viene premuto MAIUSC+CTRL+Z
     */
    void redoEvent();

private slots:
    void checkBoxClicked(int i);
    void slotObjectPicked(unsigned int i);
    void slotPoint2DClicked(cg3::Point2Dd p);

    //Menu Actions
    void on_actionSave_Snapshot_triggered();
    void on_actionShow_Axis_triggered();
    void on_actionFull_Screen_toggled(bool arg1);
    void on_actionUpdate_Canvas_triggered();
    void on_actionFit_Scene_triggered();
    void on_actionChange_Background_Color_triggered();
    void on_actionSave_Point_Of_View_triggered();
    void on_actionLoad_Point_of_View_triggered();
    void on_actionShow_Hide_Dock_Widget_triggered();
    void on_actionLoad_Point_Of_View_from_triggered();
    void on_actionSave_Point_Of_View_as_triggered();
    void on_actionShow_Hide_Console_Stream_triggered();
    void on_actionEnable_Debug_Objects_triggered();
    void on_actionDisable_Debug_Objects_triggered();
    void on_action2D_Mode_triggered();
    void on_action3D_Mode_triggered();
    void on_actionReset_Point_of_View_triggered();

private:

    // GUI
    //
    internal::UiMainWindowRaiiWrapper* ui;
    std::vector<QFrame*> managers;
    cg3::viewer::LoaderSaver povLS;
    ConsoleStream* consoleStream;


    bool mode2D;

    // Mesh Stack
    //
    QSignalMapper* checkBoxMapper;
    std::map<int, QCheckBox*> checkBoxes;
    boost::bimap<int, const cg3::DrawableObject*> mapObjects;
    int nMeshes;
    bool first;
    bool debugObjectsEnabled;

public:

    GLCanvas& canvas;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_MAINWINDOW_H
