/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollArea>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QColorDialog>
#include <QDockWidget>
#include <QToolBox>
#include <QFrame>

#include "interfaces/drawable_container.h"
#include "interfaces/drawable_mesh.h"
#include "internal/drawable_mesh_drawlist_manager.h"
#include "internal/drawable_container_drawlist_manager.h"
#include "internal/drawable_object_drawlist_manager.h"

#include <cg3/utilities/cg3_config_folder.h>
#include <cg3/utilities/string.h>
#include <cg3/utilities/timer.h>

namespace cg3 {
namespace viewer {
namespace internal {
class UiMainWindowRaiiWrapper : public Ui::MainWindow
{
public:
    UiMainWindowRaiiWrapper(QMainWindow *MainWindow)
    {
        setupUi(MainWindow);
    }
};
} //namespace cg3::viewer::internal

/**
 * @brief Constructor that creates and initializes all the members of the MainWindow,
 * setting up the canvas and linking it to the scroll area that will contain the
 * checkboxes associtated to the DrawableObjects contained in the canvas.
 */
CG3_INLINE MainWindow::MainWindow(QWidget* parent) :
		AbstractMainWindow(parent),
        ui(new internal::UiMainWindowRaiiWrapper(this)),
        consoleEnabled(false),
        first(true),
        debugObjectsEnabled(false),
        canvas(*ui->glCanvas),
        console(ui->console),
        debugObjects(&canvas)
{
    ui->toolBox->removeItem(0);

    scrollAreaLayout = new QVBoxLayout(ui->scrollArea);
    ui->scrollArea->setLayout(scrollAreaLayout);

    m_spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollAreaLayout->addItem(m_spacer);

    ui->console->hide();

    povLS.addSupportedExtension("cg3pov");
    #ifdef CG3_DCEL_DEFINED
    meshLS.addSupportedExtension("obj", "ply", "dcel");
    #else
    ui->actionLoad_Mesh->setVisible(false);
    #endif

	QMainWindow::showMaximized();

    canvas.setSnapshotQuality(100);
    canvas.setSnapshotFormat("PNG");
}

CG3_INLINE MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Returns the sizes of the Canvas as number of pixels.
 */
CG3_INLINE Point2i MainWindow::canvasSize() const
{
	return Point2i(canvas.width(), canvas.height());
}

CG3_INLINE void MainWindow::updateCanvas()
{
	canvas.update();
}

CG3_INLINE void MainWindow::fitSceneCanvas()
{
	canvas.fitScene();
}

/**
 * @brief Adds a new DrawableObject to the canvas and links it to a new checkbox in the
 * ScrollArea, and updates automatically the scene.
 *
 * @param obj: the DrawableObject
 * @param checkBoxName: a name associated to the DrawableObject
 * @param checkBoxChecked: true if the object will be visible, false otherwise
 */
CG3_INLINE void MainWindow::pushDrawableObject(
        const DrawableObject* obj,
        std::string checkBoxName,
        bool checkBoxChecked,
        bool closeButtonVisible)
{
    if (obj != nullptr && !canvas.containsDrawableObject(obj)) {
        canvas.pushDrawableObject(obj, checkBoxChecked);
        DrawableObjectDrawListManager* manager =
                new DrawableObjectDrawListManager(this, obj, checkBoxName, checkBoxChecked, closeButtonVisible);
        mapDrawListManagers[obj] = manager;

        scrollAreaLayout->addWidget(manager);

        scrollAreaLayout->removeItem(m_spacer);
        scrollAreaLayout->addItem(m_spacer);
        canvas.update();
    }
}

CG3_INLINE void MainWindow::pushDrawableObject(
        const std::shared_ptr<const DrawableObject> &ptr,
        std::string checkBoxName,
        bool checkBoxChecked,
        bool closeButtonVisible)
{
    if (!containsDrawableObject(ptr)){
        sharedDrawableObjects.insert(ptr);
        pushDrawableObject(ptr.get(), checkBoxName, checkBoxChecked, closeButtonVisible);
    }
}

/**
 * @brief Removes the DrawableObject from the canvas and the relative checkbox from the
 * MainWindow.
 *
 * @param obj: the object that will be removed from the canvas
 */
CG3_INLINE bool MainWindow::deleteDrawableObject(const DrawableObject* obj)
{
    if (obj != nullptr && mapDrawListManagers.find(obj) != mapDrawListManagers.end()){
        canvas.deleteDrawableObject(obj);
        //mapDrawListManagers[obj]->deleteSubManager();
        scrollAreaLayout->removeWidget(mapDrawListManagers[obj]);
        delete mapDrawListManagers[obj];
        mapDrawListManagers.erase(obj);
        canvas.update();
        return true;
    }
	else {
		if (canvas.containsDrawableObject(obj)){
			canvas.deleteDrawableObject(obj);
			canvas.update();
		}
	}
    return false;
}

CG3_INLINE bool MainWindow::deleteDrawableObject(const std::shared_ptr<const DrawableObject> &ptr)
{
    bool b = deleteDrawableObject(ptr.get());
    sharedDrawableObjects.erase(ptr);
    return b;
}

/**
 * @brief Sets the visibility/non visibility of a DrawableObject, checking/unchecking its
 * checkbox accordingly if it is in the list of DrawableObjects of the MainWindow.
 */
CG3_INLINE void MainWindow::setDrawableObjectVisibility(const DrawableObject* obj, bool visible)
{
	if (mapDrawListManagers.find(obj) != mapDrawListManagers.end()){
		if (obj->isVisible() != visible)
			mapDrawListManagers[obj]->setDrawableObjectVisibility(visible);

	}
	canvas.setDrawableObjectVisibility(obj, visible);
	canvas.update();
}

CG3_INLINE void MainWindow::setDrawableObjectVisibility(const std::shared_ptr<const DrawableObject> &ptr, bool visible)
{
    setDrawableObjectVisibility(ptr.get(), visible);
}

/**
 * @brief Returns true if the input DrawableObject is already drawn in the canvas.
 */
CG3_INLINE bool MainWindow::containsDrawableObject(const DrawableObject* obj)
{
    return (mapDrawListManagers.find(obj) != mapDrawListManagers.end());
}

CG3_INLINE bool MainWindow::containsDrawableObject(const std::shared_ptr<const DrawableObject> &ptr)
{
    return sharedDrawableObjects.find(ptr) != sharedDrawableObjects.end();
}

/**
 * @brief Refreshes the visibility of a DrawableObject if it was assigned.
 * Sets the properties of the user interface in the DrawableObject.
 * @todo Manage PickableObject and DrawableContainer..
 */
CG3_INLINE bool MainWindow::refreshDrawableObject(const DrawableObject* obj)
{
    if (mapDrawListManagers.find(obj) != mapDrawListManagers.end()) {

        const PickableObject* pobj = dynamic_cast<const PickableObject*>(obj);
        if (pobj) {
            canvas.deleteDrawableObject(obj);
            canvas.pushDrawableObject(obj, obj->isVisible());
            canvas.update();
        }
        mapDrawListManagers[obj]->updateObjectProperties();

        return true;
    }
    else {
        return false;
    }
}

CG3_INLINE bool MainWindow::refreshDrawableObject(const std::shared_ptr<const DrawableObject> &ptr)
{
    return refreshDrawableObject(ptr.get());
}

CG3_INLINE bool MainWindow::setDrawableObjectName(const DrawableObject* obj, const std::string& newName)
{
    if (mapDrawListManagers.find(obj) != mapDrawListManagers.end()){
        mapDrawListManagers[obj]->setDrawableObjectName(newName);
        return true;
    }
    return false;
}

CG3_INLINE bool MainWindow::setDrawableObjectName(const std::shared_ptr<const DrawableObject> &ptr, const std::string &newName)
{
    return setDrawableObjectName(ptr.get(), newName);
}

CG3_INLINE std::string MainWindow::nameOfDrawableObject(const DrawableObject* obj) const
{
    auto it = mapDrawListManagers.find(obj);
    if (it != mapDrawListManagers.end()){
        return it->second->drawableObjectName();
    }
    else
        return "";
}

CG3_INLINE std::string MainWindow::nameOfDrawableObject(const std::shared_ptr<const DrawableObject> &ptr) const
{
    return nameOfDrawableObject(ptr.get());
}

/**
 * @brief Returns a vector of all the selected DrawableObjects of the DrawList.
 * @return the vector of selected objects.
 */
CG3_INLINE std::vector<const DrawableObject*> MainWindow::selectedDrawableObjects() const
{
    std::vector<const DrawableObject*> vec;
    for (const std::pair<const DrawableObject*, DrawableObjectDrawListManager*>& p :
         mapDrawListManagers){
        if (p.second->isSelected()){
            vec.push_back(p.first);
        }
        if (p.second->isContainer()){
            std::vector<const DrawableObject*> tmp = p.second->containedSelectedObjects();
            vec.insert(vec.end(), tmp.begin(), tmp.end());
        }
    }
    return vec;
}

/**
 * @brief Returns the only DrawableObject which is selected, nullptr if none or more than
 * one object is selected.
 * @return the selected DrawableObject (if and ONLY if there is one selected DrawableObject)
 */
CG3_INLINE const DrawableObject* MainWindow::selectedDrawableObject() const
{
    const DrawableObject* obj = nullptr;
    for (const std::pair<const DrawableObject*, DrawableObjectDrawListManager*>& p :
         mapDrawListManagers){
        if (p.second->isSelected()){
            if (obj == nullptr){
                obj = p.first;
            }
            else {
                return nullptr;
            }
        }
        if (p.second->isContainer()){
            std::vector<const DrawableObject*> tmp = p.second->containedSelectedObjects();
            if (tmp.size() > 0){
                if (obj == nullptr && tmp.size() == 1){
                    obj = tmp[0];
                }
                else {
                    return nullptr;
                }
            }
        }
    }
    return obj;
}

/**
 * @brief Enables the Debug Objects, they will be drawn in the canvas and their
 * checkbox in the scroll area will be shown.
 */
CG3_INLINE void MainWindow::enableDebugObjects()
{
    if (debugObjectsEnabled == false){
        pushDrawableObject(&debugObjects, "Debug Objects");
        ui->actionToggle_Debug_Objects->setChecked(true);
        debugObjectsEnabled = true;
    }
}

/**
 * @brief Disables the Debug Objects, they will be removed from the canvas and their
 * checkbox in the scroll area will be removed.
 */
CG3_INLINE void MainWindow::disableDebugObjects()
{
    if (debugObjectsEnabled == true){
        if (deleteDrawableObject(&debugObjects)) {
            ui->actionToggle_Debug_Objects->setChecked(false);
            debugObjectsEnabled = false;
        }
    }
    canvas.update();
}

CG3_INLINE void MainWindow::toggleDebugObjects()
{
    if (debugObjectsEnabled)
        disableDebugObjects();
    else
        enableDebugObjects();
}

/**
 * @brief Sets the full screen mode to the MainWindow according to the boolean parameter.
 */
CG3_INLINE void MainWindow::setFullScreen(bool b)
{
    canvas.setFullScreen(b);
    if (!b)
        showMaximized();
}

/**
 * @brief Enables/Disables the console stream
 * streams of the application in the MainWindow.
 */
CG3_INLINE void MainWindow::toggleConsole()
{
    if (consoleEnabled){
        consoleEnabled = false;
        ui->console->hide();
    }
    else {
        consoleEnabled = true;
        ui->console->show();
    }
}

/**
 * @brief Manages a Key Event and executes relative operations or emits signals.
 */
CG3_INLINE void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->matches(QKeySequence::Undo))
        emit(undoEvent());
    if (event->matches(QKeySequence::Redo))
		emit(redoEvent());
}

CG3_INLINE void MainWindow::showDockWidget()
{
	ui->dockToolBox->show();
}

CG3_INLINE void MainWindow::hideDockWidget()
{
	ui->dockToolBox->hide();
}

CG3_INLINE void MainWindow::showDrawList()
{
	ui->dockDrawList->show();
}

CG3_INLINE void MainWindow::hideDrawList()
{
	ui->dockDrawList->hide();
}

/**
 * @brief Adds a manager (QFrame) to the toolbox of the mainWindow.
 * @param[in] f: a QFrame
 * @param[in] name: name associated to the manager
 * @param[in] parent: the default parent of the QFrame will be the toolbox of the mainwindow.
 * @return an id representing the manager inside the mainWindow.
 */
CG3_INLINE unsigned int MainWindow::addManager(QFrame* f, std::string name, QToolBox* parent)
{
    if (parent == nullptr)
        parent = ui->toolBox;
    ui->toolBox->insertItem((int)managers.size(), f, QString(name.c_str()));
    ui->toolBox->adjustSize();

    f->show();
    managers.push_back(f);
    //adjustSize();
    return (int)managers.size()-1;
}

/**
 * @brief Restituisce il puntatore al manager identificato dall'indice passato come parametro.
 * @param[in] i: indice del manager da restituire
 * @return il puntatore al manager se esiste, nullptr altrimenti
 */
CG3_INLINE QFrame *MainWindow::getManager(unsigned int i)
{
    if (i < managers.size()) return managers[i];
    else return nullptr;
}

/**
 * @brief Rinomina il manager identificato dall'indice passato come parametro
 * @param[in] i: indice del manager da rinominare
 * @param[in] s: il nuovo nome del manager
 */
CG3_INLINE void MainWindow::renameManager(unsigned int i, std::string s)
{
    if (i < managers.size())
        ui->toolBox->setItemText(i, QString(s.c_str()));
}

/**
 * @brief Modifica il manager visualizzato all'i-esimo.
 * @param[in] i: indice del manager da visualizzare
 */
CG3_INLINE void MainWindow::setCurrentManager(unsigned int i)
{
    if (i < managers.size())
        ui->toolBox->setCurrentIndex(i);
}

CG3_INLINE void MainWindow::on_actionSave_Snapshot_triggered()
{
    ui->glCanvas->saveSnapshot(QString(), false);
}

CG3_INLINE void MainWindow::on_actionShow_Axis_triggered()
{
    ui->glCanvas->toggleAxisIsDrawn();
}

CG3_INLINE void MainWindow::on_actionFull_Screen_toggled(bool arg1)
{
    setFullScreen(arg1);
}

CG3_INLINE void MainWindow::on_actionUpdate_Canvas_triggered()
{
    canvas.update();
}

CG3_INLINE void MainWindow::on_actionFit_Scene_triggered()
{
    canvas.fitScene();
}

CG3_INLINE void MainWindow::on_actionChange_Background_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    canvas.setBackgroundColor(color);
    canvas.update();
}

CG3_INLINE void MainWindow::on_actionSave_Point_Of_View_triggered()
{
    canvas.savePointOfView();
}

CG3_INLINE void MainWindow::on_actionLoad_Point_of_View_triggered()
{
    canvas.loadPointOfView();
}

CG3_INLINE void MainWindow::on_actionShow_Hide_Dock_Widget_triggered()
{
    if (ui->dockToolBox->isHidden())
        ui->dockToolBox->show();
    else
        ui->dockToolBox->hide();
}

CG3_INLINE void MainWindow::on_actionLoad_Point_Of_View_from_triggered()
{
    std::string s = povLS.loadDialog("Open Point Of View");
    if (s != ""){
        canvas.loadPointOfView(s);
    }
}

CG3_INLINE void MainWindow::on_actionSave_Point_Of_View_as_triggered()
{
    std::string s = povLS.saveDialog("Save Point Of View");
    if (s != ""){
        canvas.savePointOfView(s);
    }
}

CG3_INLINE void MainWindow::on_actionShow_Hide_Console_triggered()
{
    toggleConsole();
}

CG3_INLINE void MainWindow::on_actionShow_Hide_DrawList_triggered()
{
    if (ui->dockDrawList->isHidden())
        ui->dockDrawList->show();
    else
        ui->dockDrawList->hide();
}

CG3_INLINE void MainWindow::on_actionToggle_Debug_Objects_triggered()
{
    toggleDebugObjects();
}

CG3_INLINE void MainWindow::on_action2D_Mode_triggered()
{
    canvas.set2DMode();
}

CG3_INLINE void MainWindow::on_action3D_Mode_triggered()
{
    canvas.set3DMode();
}

CG3_INLINE void MainWindow::on_actionReset_Point_of_View_triggered()
{
    canvas.resetPointOfView();
}

CG3_INLINE void MainWindow::on_actionPerspective_Orthographic_Camera_Mode_triggered()
{
    canvas.toggleCameraType();
    canvas.update();
}

CG3_INLINE void MainWindow::on_actionShow_Unit_Box_triggered()
{
    canvas.toggleUnitBox();
    canvas.update();
}

#ifdef CG3_DCEL_DEFINED
CG3_INLINE void MainWindow::on_actionLoad_Mesh_triggered()
{
    std::string filename = meshLS.loadDialog("Open Mesh");
    if (filename != ""){
        std::string name = cg3::filenameWithoutExtension(filename);
        cg3::Timer t("Load " + name);
        unsigned int i = openedDcels.pushBack(cg3::DrawableDcel(filename), name);
        t.stop();
        pushDrawableObject((openedDcels[i]), name, true, true);
        canvas.fitScene();
        console.setCoutOutput(false);
        console << filename << "\n";
        console << "N. Vertices: " << openedDcels.at(i).numberVertices()
                << "; N. Faces: " << openedDcels.at(i).numberFaces() << "\n";
        console << "Loaded in " << t.delay() << " seconds.\n";
        console.setCoutOutput(true);
    }
}
#endif

} //namespace cg3::viewer
} //namespace cg3
