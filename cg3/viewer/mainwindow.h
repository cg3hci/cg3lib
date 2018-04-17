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
#include <QSpacerItem>
#include <QProcess>
#include <QGridLayout>
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
#include <cg3/viewer/interfaces/drawable_container.h>
#include "utilities/loadersaver.h"
#include <cg3/geometry/bounding_box.h>
#include "drawable_objects/drawable_mixed_objects.h"
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

    //DrawableObjects for the Canvas
    void pushDrawableObject(const cg3::DrawableObject * obj, std::string checkBoxName, bool checkBoxChecked = true);
    bool deleteDrawableObject(const cg3::DrawableObject * obj);
    void setDrawableObjectVisibility(const cg3::DrawableObject * obj, bool visible);
    bool containsDrawableObject(const cg3::DrawableObject* obj);
    cg3::BoundingBox getFullBoundingBox();
    int getNumberVisibleDrawableObjects();

    //Debug Objects
    void enableDebugObjects();
    void disableDebugObjects();

    //Window Options:
    void setFullScreen(bool);
    void toggleConsoleStream(); //work in progress...
    void keyPressEvent(QKeyEvent * event); //event options for keys pressed

    //Managers:
    unsigned int addManager(QFrame *f, std::string name, QToolBox *parent = nullptr);
    QFrame *getManager(unsigned int i);
    void renameManager(unsigned int i, std::string s);
    void setCurrentManager(unsigned int i);

signals:

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

    void addCheckBoxDrawableContainer(const DrawableContainer* cont, const std::string& objectName, bool vis);
    void removeCheckBoxDrawableContainer(const DrawableContainer* cont, unsigned int i);

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

    QCheckBox* createCheckBoxAndLinkSignal(const DrawableObject* obj, const std::string& checkBoxName, bool isChecked = true);
    void addContainerCheckBoxes(const DrawableContainer* container);

    // GUI
    //
    internal::UiMainWindowRaiiWrapper* ui;
    std::vector<QFrame*> managers;
    ConsoleStream* consoleStream;
    QVBoxLayout* scrollAreaLayout;
    cg3::viewer::LoaderSaver povLS;

    // Mesh Stack
    //
    QSignalMapper* checkBoxMapper;
    std::map<int, QCheckBox*> checkBoxes;
    boost::bimap<int, const cg3::DrawableObject*> mapObjects;
    int nCheckBoxes;
    std::map<const cg3::DrawableContainer*, std::vector<QCheckBox*> > containerCheckBoxes;
    bool first;
    bool debugObjectsEnabled;
    QSpacerItem* m_spacer;

public:

    GLCanvas& canvas;
    cg3::DrawableMixedObjects debugObjects;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_MAINWINDOW_H
