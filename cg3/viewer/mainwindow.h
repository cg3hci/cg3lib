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
#include <QApplication>
#include <QSignalMapper>

#include <QProcess>
#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredeclared-class-member"
#endif
#include <boost/bimap.hpp>
#ifdef __APPLE__
#pragma clang diagnostic pop
#endif

#include "interfaces/abstract_mainwindow.h"
#include "glcanvas.h"
#include "utilities/loadersaver.h"
#include "utilities/console_stream.h"
#include "drawable_objects/drawable_mixed_objects.h"

#ifdef CG3_DCEL_DEFINED
#include "drawable_objects/drawable_dcel.h"
#include "drawable_objects/drawable_objects_container.h"
#endif

class QToolBox;
class QVBoxLayout;
class QSpacerItem;

namespace cg3 {

class DrawableObject;
class PickableObject;
class DrawableContainer;

namespace viewer {

class GLCanvas;
class DrawableObjectDrawListManager;

namespace Ui {

class MainWindow;

} //namespace cg3::viewer::Ui

namespace internal {

//class MeshManager;
class UiMainWindowRaiiWrapper;

} //namespace cg3::viewer::internal

/**
 * @brief Class that describes a Window containing an QGLViewer canvas and that manages
 * Managers and DrawableObjects.
 * @ingroup cg3viewer
 */
class MainWindow : public AbstractMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Canvas:
    cg3::Point2i canvasSize() const;
	// AbstractMainWindow interface
	void updateCanvas();
	void fitSceneCanvas();

    //DrawableObjects for the Canvas
    void pushDrawableObject(
            const cg3::DrawableObject * obj,
            std::string checkBoxName = "",
            bool checkBoxChecked = true,
            bool closeButtonVisible = false);
    void pushDrawableObject(const std::shared_ptr<const DrawableObject> &ptr,
            std::string checkBoxName = "",
            bool checkBoxChecked = true,
            bool closeButtonVisible = false);
    bool deleteDrawableObject(const cg3::DrawableObject * obj);
    bool deleteDrawableObject(const std::shared_ptr<const DrawableObject> &ptr);
    void setDrawableObjectVisibility(const cg3::DrawableObject * obj, bool visible);
    void setDrawableObjectVisibility(const std::shared_ptr<const DrawableObject> &ptr, bool visible);
    bool containsDrawableObject(const cg3::DrawableObject* obj);
    bool containsDrawableObject(const std::shared_ptr<const DrawableObject> &ptr);
    bool refreshDrawableObject(const cg3::DrawableObject* obj);
    bool refreshDrawableObject(const std::shared_ptr<const DrawableObject> &ptr);
    bool setDrawableObjectName(
            const cg3::DrawableObject* obj,
            const std::string& newName);
    bool setDrawableObjectName(
            const std::shared_ptr<const DrawableObject> &ptr,
            const std::string& newName);
    std::string nameOfDrawableObject(const cg3::DrawableObject* obj) const;
    std::string nameOfDrawableObject(const std::shared_ptr<const DrawableObject> &ptr) const;
    std::vector<const cg3::DrawableObject*> selectedDrawableObjects() const;
    const DrawableObject* selectedDrawableObject() const;

    //Debug Objects
    void enableDebugObjects();
    void disableDebugObjects();
    void toggleDebugObjects();
    void toggleUnitBox();

    //Window Options:
    void setFullScreen(bool);
    void toggleConsole(); //work in progress...
    void keyPressEvent(QKeyEvent * event); //event options for keys pressed
	void showDockWidget();
	void hideDockWidget();
	void showDrawList();
	void hideDrawList();

    //Managers:
    unsigned int addManager(QFrame *f, std::string name, QToolBox *parent = nullptr);
    QFrame *getManager(unsigned int i);
    void renameManager(unsigned int i, std::string s);
    void setCurrentManager(unsigned int i);

signals:

    /**
     * @brief undoEvent
     * Conntect your slot with this signal in ordert to execute an action when the
     * user uses CTRL+Z in the MainWindow
     */
    void undoEvent();

    /**
     * @brief redoEvent
     * Conntect your slot with this signal in ordert to execute an action when the
     * user uses MAIUSC+CTRL+Z in the MainWindow
     */
    void redoEvent();

private slots:

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
    void on_actionShow_Hide_Console_triggered();
    void on_actionShow_Hide_DrawList_triggered();
    void on_actionToggle_Debug_Objects_triggered();
    void on_action2D_Mode_triggered();
    void on_action3D_Mode_triggered();
    void on_actionReset_Point_of_View_triggered();
    void on_actionPerspective_Orthographic_Camera_Mode_triggered();
    void on_actionShow_Unit_Box_triggered();
    #ifdef CG3_DCEL_DEFINED
    void on_actionLoad_Mesh_triggered();
    #endif

private:

    struct ContainerProperties {
        QFrame* frame;
        std::vector<QCheckBox*> checkBoxes;
    };

    // GUI
    //
    //Ui::MainWindow* ui;
    internal::UiMainWindowRaiiWrapper* ui;
    std::vector<QFrame*> managers;
    bool consoleEnabled;
    QVBoxLayout* scrollAreaLayout;
    cg3::viewer::LoaderSaver povLS;
    QSpacerItem* m_spacer;

    // Mesh Stack
    //
    std::map<const DrawableObject*, DrawableObjectDrawListManager*> mapDrawListManagers;
    std::set<std::shared_ptr<const cg3::DrawableObject> > sharedDrawableObjects;
    bool first;
    bool debugObjectsEnabled;

    #ifdef CG3_DCEL_DEFINED
    cg3::DrawableObjectsContainer<cg3::DrawableDcel> openedDcels;
    cg3::viewer::LoaderSaver meshLS;
    #endif

public:

    GLCanvas& canvas; /** @brief Public member of type cg3::viewer::GLCanvas that allows
                          to manage the canvas contained in the MainWindow. */

    ConsoleStream console;

    cg3::DrawableMixedObjects debugObjects; /** @brief Public member of type
                                                cg3::DrawableMixedObjects that allows to
                                                manage the debug objects that can be shown
                                                in the canvas. In order to use this member,
                                                remember to call the function
                                                "MainWindow::enableDebugObjects()".*/
};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_MAINWINDOW_CPP "mainwindow.cpp"
#include CG3_MAINWINDOW_CPP
#undef CG3_MAINWINDOW_CPP
#endif //CG3_STATIC

#endif // CG3_MAINWINDOW_H
