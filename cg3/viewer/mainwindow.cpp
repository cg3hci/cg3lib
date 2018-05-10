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
#include "utilities/consolestream.h"

#include <cg3/utilities/cg3config.h>

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
MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
        ui(new internal::UiMainWindowRaiiWrapper(this)),
        consoleStream(nullptr),
        nCheckBoxes(0),
        first(true),
        debugObjectsEnabled(false),
        canvas(*ui->glCanvas)
{
    ui->toolBox->removeItem(0);

    checkBoxMapper = new QSignalMapper(this);
    connect(checkBoxMapper, SIGNAL(mapped(int)), this, SLOT(checkBoxClicked(int)));

    scrollAreaLayout = new QVBoxLayout(ui->scrollArea);
    ui->scrollArea->setLayout(scrollAreaLayout);

    m_spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollAreaLayout->addItem(m_spacer);

    ui->console->hide();

    povLS.addSupportedExtension("cg3pov");

    showMaximized();

    canvas.setSnapshotQuality(100);
    canvas.setSnapshotFormat("PNG");
}

MainWindow::~MainWindow()
{
    if (consoleStream != nullptr)
        delete consoleStream;
    delete ui;
}

/**
 * @brief Returns the sizes of the Canvas as number of pixels.
 */
Point2Di MainWindow::getCanvasSize() const
{
    return Point2Di(canvas.width(), canvas.height());
}

/**
 * @brief Adds a new DrawableObject to the canvas and links it to a new checkbox in the
 * ScrollArea, and updates automatically the scene.
 *
 * @param obj: the DrawableObject
 * @param checkBoxName: a name associated to the DrawableObject
 * @param checkBoxChecked: true if the object will be visible, false otherwise
 */
void MainWindow::pushDrawableObject(
        const DrawableObject* obj,
        std::string checkBoxName,
        bool checkBoxChecked)
{
    if (obj != nullptr){
        pushDrawableObject(obj, ui->scrollArea, checkBoxName, checkBoxChecked);

        scrollAreaLayout->removeItem(m_spacer);
        scrollAreaLayout->addItem(m_spacer);
    }
}

/**
 * @brief Removes the DrawableObject from the canvas and the relative checkbox from the
 * MainWindow.
 *
 * @param obj: the object that will be removed from the canvas
 */
bool MainWindow::deleteDrawableObject(const DrawableObject* obj)
{
    return deleteDrawableObject(obj, ui->scrollArea);
}

/**
 * @brief Sets the visibility/non visibility of a DrawableObject, checking/unchecking its
 * checkbox accordingly.
 */
void MainWindow::setDrawableObjectVisibility(const DrawableObject* obj, bool visible)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator it =
            mapObjects.right.find(obj);
    if (it != mapObjects.right.end()){
        int i = it->second;

        QCheckBox * cb = checkBoxes[i];
        cb->setChecked(visible);
    }

}

/**
 * @brief Returns true if the input DrawableObject is already drawn in the canvas.
 */
bool MainWindow::containsDrawableObject(const DrawableObject* obj)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator right_iter =
            mapObjects.right.find(obj);
    return (right_iter != mapObjects.right.end());
}

/**
 * @brief Refreshes the visibility of a DrawableObject if it was assigned.
 * @todo Manage PickableObject and DrawableContainer..
 */
bool MainWindow::refreshDrawableObject(const DrawableObject* obj)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator right_iter =
            mapObjects.right.find(obj);
    if (right_iter != mapObjects.right.end()) {

        const PickableObject* pobj = dynamic_cast<const PickableObject*>(obj);
        if (pobj) {
            bool b = canvas.isDrawableObjectVisible(obj);
            canvas.deleteDrawableObject(obj);
            canvas.pushDrawableObject(obj, b);
            canvas.update();
        }

        return true;
    }
    else {
        return false;
    }
}

bool MainWindow::setDrawableObjectName(const DrawableObject* obj, const std::string& newName)
{
    int id;
    QCheckBox* cb = getCheckBoxDrawableObject(obj, id);
    if (cb != nullptr){
        cb->setText(QString::fromStdString(newName));
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Enables the Debug Objects, they will be drawn in the canvas and their
 * checkbox in the scroll area will be shown.
 */
void MainWindow::enableDebugObjects()
{
    if (debugObjectsEnabled == false){
        pushDrawableObject(&debugObjects, "Debug Objects");
        ui->actionEnable_Debug_Objects->setEnabled(false);
        ui->actionDisable_Debug_Objects->setEnabled(true);
        debugObjectsEnabled = true;
    }
}

/**
 * @brief Disables the Debug Objects, they will be removed from the canvas and their
 * checkbox in the scroll area will be removed.
 */
void MainWindow::disableDebugObjects()
{
    if (debugObjectsEnabled == true){
        if (deleteDrawableObject(&debugObjects)) {
            ui->actionEnable_Debug_Objects->setEnabled(true);
            ui->actionDisable_Debug_Objects->setEnabled(false);
            debugObjectsEnabled = false;
        }
    }
    canvas.update();
}

/**
 * @brief Sets the full screen mode to the MainWindow according to the boolean parameter.
 */
void MainWindow::setFullScreen(bool b)
{
    canvas.setFullScreen(b);
    if (!b)
        showMaximized();
}

/**
 * @brief Enables/Disables the console stream that allows to show std::out and std::err
 * streams of the application in the MainWindow.
 */
void MainWindow::toggleConsoleStream()
{
    if (consoleStream == nullptr){
        ui->console->show();
        consoleStream =  new ConsoleStream(std::cout, std::cerr, this->ui->console);
        ConsoleStream::registerConsoleMessageHandler();
    }
    else {
        ui->console->hide();
        delete consoleStream;
        consoleStream = nullptr;
    }
}

/**
 * @brief Manages a Key Event and executes relative operations or emits signals.
 */
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_F)
        canvas.fitScene();
    if (event->key() == Qt::Key_U)
        canvas.update();
    if(event->matches(QKeySequence::Undo))
        emit(undoEvent());
    if (event->matches(QKeySequence::Redo))
        emit(redoEvent());
    if (event->matches(QKeySequence::Replace)){ //ctrl+h
        if (ui->dockWidget->isHidden())
            ui->dockWidget->show();
        else
            ui->dockWidget->hide();
    }
    if (event->key() == Qt::Key_C){ //c
        toggleConsoleStream();
    }
    if (event->key() == Qt::Key_T){ //t
        canvas.toggleCameraType();
        canvas.update();
    }

    if (event->matches(QKeySequence::Print)){ //ctrl+p
        canvas.savePointOfView();
    }
    if (QKeySequence(event->key() | event->modifiers()) ==
            QKeySequence(Qt::CTRL + Qt::Key_L)){ //ctrl+l
        canvas.loadPointOfView();
    }
}

/**
 * @brief Adds a manager (QFrame) to the toolbox of the mainWindow.
 * @param[in] f: a QFrame
 * @param[in] name: name associated to the manager
 * @param[in] parent: the default parent of the QFrame will be the toolbox of the mainwindow.
 * @return an id representing the manager inside the mainWindow.
 */
unsigned int MainWindow::addManager(QFrame* f, std::string name, QToolBox* parent)
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
QFrame *MainWindow::getManager(unsigned int i)
{
    if (i < managers.size()) return managers[i];
    else return nullptr;
}

/**
 * @brief Rinomina il manager identificato dall'indice passato come parametro
 * @param[in] i: indice del manager da rinominare
 * @param[in] s: il nuovo nome del manager
 */
void MainWindow::renameManager(unsigned int i, std::string s)
{
    if (i < managers.size())
        ui->toolBox->setItemText(i, QString(s.c_str()));
}

/**
 * @brief Modifica il manager visualizzato all'i-esimo.
 * @param[in] i: indice del manager da visualizzare
 */
void MainWindow::setCurrentManager(unsigned int i)
{
    if (i < managers.size())
        ui->toolBox->setCurrentIndex(i);
}

void MainWindow::on_actionSave_Snapshot_triggered()
{
    QKeyEvent *event =
            new QKeyEvent ( QEvent::KeyPress, Qt::CTRL | Qt::Key_S, Qt::NoModifier);
    QCoreApplication::postEvent (ui->glCanvas, event);
}

void MainWindow::on_actionShow_Axis_triggered()
{
    QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
    QCoreApplication::postEvent (ui->glCanvas, event);
}

void MainWindow::on_actionFull_Screen_toggled(bool arg1)
{
    setFullScreen(arg1);
}

void MainWindow::on_actionUpdate_Canvas_triggered()
{
    canvas.update();
}

void MainWindow::on_actionFit_Scene_triggered()
{
    canvas.fitScene();
}

void MainWindow::on_actionChange_Background_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    canvas.setBackgroundColor(color);
    canvas.update();
}

void MainWindow::on_actionSave_Point_Of_View_triggered()
{
    canvas.savePointOfView();
}

void MainWindow::on_actionLoad_Point_of_View_triggered()
{
    canvas.loadPointOfView();
}

void MainWindow::on_actionShow_Hide_Dock_Widget_triggered()
{
    QKeyEvent *event =
            new QKeyEvent ( QEvent::KeyPress, Qt::CTRL | Qt::Key_H, Qt::NoModifier);
    QCoreApplication::postEvent (ui->glCanvas, event);
}

void MainWindow::on_actionLoad_Point_Of_View_from_triggered()
{
    std::string s = povLS.loadDialog("Open Point Of View");
    if (s != ""){
        canvas.loadPointOfView(s);
    }
}

void MainWindow::on_actionSave_Point_Of_View_as_triggered()
{
    std::string s = povLS.saveDialog("Save Point Of View");
    if (s != ""){
        canvas.savePointOfView(s);
    }
}

void MainWindow::on_actionShow_Hide_Console_Stream_triggered()
{
    toggleConsoleStream();
}

void MainWindow::on_actionEnable_Debug_Objects_triggered()
{
    enableDebugObjects();
}

void MainWindow::on_actionDisable_Debug_Objects_triggered()
{
    disableDebugObjects();
}

void MainWindow::on_action2D_Mode_triggered()
{
    canvas.set2DMode();
}

void MainWindow::on_action3D_Mode_triggered()
{
    canvas.set3DMode();
}

void MainWindow::on_actionReset_Point_of_View_triggered()
{
    canvas.resetPointOfView();
}

void MainWindow::on_actionPerspective_Orthographic_Camera_Mode_triggered()
{
    canvas.toggleCameraType();
    canvas.update();
}

/**
 * @brief Evento i-esima checkBox cliccata, modifica la visibilità dell'oggetto ad essa collegato
 * @param[in] i: indice della checkBox cliccata
 */
void MainWindow::checkBoxClicked(int i)
{
    QCheckBox * cb = checkBoxes[i];
    const DrawableObject * obj = mapObjects.left.at(i);
    if (cb->isTristate()){
        const DrawableContainer* cont = dynamic_cast<const DrawableContainer*>(obj);
        Qt::CheckState state = cb->checkState();
        if (state == Qt::Unchecked){
            for (unsigned int i = 0; i < cont->size(); i++)
                canvas.setDrawableObjectVisibility((*cont)[i], false);
            //set visibility checkboxes -> false
            containerFrames[cont].frame->setVisible(false);
        }
        else if (state == Qt::PartiallyChecked) {
            for (unsigned int i = 0; i < cont->size(); i++){
                canvas.setDrawableObjectVisibility(
                            (*cont)[i],
                            containerFrames[cont].checkBoxes[i]->isChecked());
            }
            //set visibility checkboxes -> false
            containerFrames[cont].frame->setVisible(false);
        }
        else {
            for (unsigned int i = 0; i < cont->size(); i++){
                canvas.setDrawableObjectVisibility(
                            (*cont)[i],
                            containerFrames[cont].checkBoxes[i]->isChecked());
            }
            //set visibility checkboxes -> true
            containerFrames[cont].frame->setVisible(true);
        }
    }
    else {
        if (cb->isChecked())
            canvas.setDrawableObjectVisibility(obj, true);
        else
            canvas.setDrawableObjectVisibility(obj, false);
    }
    canvas.update();
}

void MainWindow::addCheckBoxOfDrawableContainer(
        const DrawableContainer* cont,
        const std::string& objectName,
        bool vis)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator it =
            mapObjects.right.find((const DrawableObject*)cont);
    if (it != mapObjects.right.end()){
        assert(containerFrames.find(cont) != containerFrames.end());

        QCheckBox* cb = pushDrawableObject(
                (*cont)[cont->size()-1],
                containerFrames[cont].frame,
                objectName,
                vis);
        containerFrames[cont].checkBoxes.push_back(cb);
        if (!canvas.isDrawableObjectVisible(cont))
            canvas.setDrawableObjectVisibility((*cont)[cont->size()-1], false);
    }
}

void MainWindow::removeCheckBoxOfDrawableContainer(
        const DrawableContainer* cont,
        unsigned int i)
{
    if(containerFrames.find(cont) != containerFrames.end()){
        deleteDrawableObject((*cont)[i], containerFrames[cont].frame);
        containerFrames[cont].checkBoxes.erase(containerFrames[cont].checkBoxes.begin()+ i);
    }
}

QCheckBox* MainWindow::pushDrawableObject(
        const DrawableObject* obj,
        QWidget* parent,
        std::string checkBoxName,
        bool checkBoxChecked)
{

    QCheckBox* cb = createCheckBoxAndLinkSignal(obj, checkBoxName, checkBoxChecked);
    ((QVBoxLayout*)parent->layout())->addWidget(cb, 0, Qt::AlignTop);

    const DrawableContainer* cont = dynamic_cast<const DrawableContainer*>(obj);
    if (!cont){ //if is not a DrawableContainer, it will be a DrawableObject in the canvas
        canvas.pushDrawableObject(obj, checkBoxChecked);
        canvas.update();
    }
    else { //otherwise, I need to push in the canvas all the contained objects
        connect(cont,
                SIGNAL(drawableContainerPushedObject(
                           const DrawableContainer*,
                           const std::string&,
                           bool)),
                this,
                SLOT(addCheckBoxOfDrawableContainer(
                         const DrawableContainer*,
                         const std::string&,
                         bool)));

        connect(cont,
                SIGNAL(drawableContainerErasedObject
                       (const DrawableContainer*,
                        unsigned int)),
                this,
                SLOT(removeCheckBoxOfDrawableContainer(
                         const DrawableContainer*,
                         unsigned int)));

        std::vector<QCheckBox*> vec;
        vec.reserve(cont->size());
        QFrame* frame = new QFrame(parent);
        frame->setLayout(new QVBoxLayout());
        //frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
        ((QVBoxLayout*)parent->layout())->addWidget(frame, 0, Qt::AlignTop);
        for (unsigned int i = 0; i < cont->size(); i++){
            const DrawableObject* obj = (*cont)[i];
            QCheckBox* ccb = pushDrawableObject(obj, frame, cont->objectName(i), true);
            vec.push_back(ccb);
        }
        containerFrames[cont].checkBoxes = vec;
        containerFrames[cont].frame = frame;

        cb->setCheckState(Qt::PartiallyChecked);
        cb->setTristate(true);
    }
    return cb;
}

bool MainWindow::deleteDrawableObject(const DrawableObject* obj, QWidget* parent)
{
    int idCheckBox;
    QCheckBox* cb = getCheckBoxDrawableObject(obj, idCheckBox);
    if (cb != nullptr){
        removeCheckBox(cb, idCheckBox);

        const DrawableContainer* cont = dynamic_cast<const DrawableContainer*>(obj);
        if (cont){ // if it is a container, remove recursively all its objects

            disconnect(cont,
                    SIGNAL(drawableContainerPushedObject(
                               const DrawableContainer*,
                               const std::string&,
                               bool)),
                    this,
                    SLOT(addCheckBoxOfDrawableContainer(
                             const DrawableContainer*,
                             const std::string&,
                             bool)));

            disconnect(cont,
                    SIGNAL(drawableContainerErasedObject
                           (const DrawableContainer*,
                            unsigned int)),
                    this,
                    SLOT(removeCheckBoxOfDrawableContainer(
                             const DrawableContainer*,
                             unsigned int)));


            for (unsigned int i = 0; i < cont->size(); i++){
                deleteDrawableObject((*cont)[i], containerFrames[cont].frame);
            }
            //remove its frame from the parent
            ((QVBoxLayout*)parent->layout())->removeWidget(containerFrames[cont].frame);
            containerFrames.erase(cont);
        }
        else {
            canvas.deleteDrawableObject(obj);
        }
        canvas.update();
        return true;
    }
    else
        return false;
}

QCheckBox *MainWindow::createCheckBoxAndLinkSignal(
        const DrawableObject *obj,
        const std::string &checkBoxName,
        bool isChecked)
{
    QCheckBox * cb = new QCheckBox(this);
    cb->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    cb->setText(checkBoxName.c_str());
    cb->setEnabled(true);
    cb->setChecked(isChecked);

    checkBoxes[nCheckBoxes] = cb;
    mapObjects.insert(
                boost::bimap<int, const DrawableObject*>::value_type(nCheckBoxes, obj));
    connect(cb, SIGNAL(stateChanged(int)), checkBoxMapper, SLOT(map()));
    checkBoxMapper->setMapping(cb, nCheckBoxes);
    nCheckBoxes++;

    return cb;
}

QCheckBox*MainWindow::getCheckBoxDrawableObject(const DrawableObject* obj, int& idCheckBox)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator it =
            mapObjects.right.find(obj);
    if (it != mapObjects.right.end()){ //if the object exists
        idCheckBox = it->second;
        return checkBoxes.at(it->second);
    }
    else {
        idCheckBox = -1;
        return nullptr;
    }
}

void MainWindow::removeCheckBox(QCheckBox* cb, int idCheckBox)
{
    checkBoxMapper->removeMappings(cb);
    cb->setVisible(false);
    ((QVBoxLayout*)((QWidget*)cb->parent())->layout())->removeWidget(cb);

    checkBoxes.erase(idCheckBox);
    mapObjects.left.erase(idCheckBox);

    delete cb;
}



} //namespace cg3::viewer
} //namespace cg3
