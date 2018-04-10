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
#include <QCheckBox>
#include <QColorDialog>
#include <cg3/geometry/plane.h>
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
 * @brief Crea una nuova mainWindow composta da canvas, toolBox avente 0 frame e scrollArea.
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new internal::UiMainWindowRaiiWrapper(this)),
        consoleStream(nullptr),
        nMeshes(0),
        first(true),
        debugObjectsEnabled(false),
        canvas(*ui->glCanvas)
{
    ui->toolBox->removeItem(0);

    checkBoxMapper = new QSignalMapper(this);
    connect(checkBoxMapper, SIGNAL(mapped(int)), this, SLOT(checkBoxClicked(int)));

    //QVBoxLayout * layout = new QVBoxLayout(ui->scrollArea);
    QGridLayout * layout = new QGridLayout(ui->scrollArea);
    ui->scrollArea->setLayout(layout);
    ((QGridLayout*)ui->scrollArea->layout())->setHorizontalSpacing(0);
    ((QGridLayout*)ui->scrollArea->layout())->setVerticalSpacing(0);
    //((QVBoxLayout*)ui->scrollArea->layout())->setSpacing(0);

    ui->console->hide();

    povLS.addSupportedExtension("cg3pov");

    showMaximized();

    ui->glCanvas->setSnapshotQuality(100);
    ui->glCanvas->setSnapshotFormat("PNG");
}

MainWindow::~MainWindow()
{
    if (consoleStream != nullptr)
        delete consoleStream;
    delete ui;
}

Point2Di MainWindow::getCanvasSize() const
{
    return Point2Di(ui->glCanvas->width(), ui->glCanvas->height());
}

/**
 * @brief Aggiunge un DrawableObject alla scena e la relativa checkBox nella scrollBar.
 *
 * Aggiorna in automatico la scena visualizzata.
 *
 * @param obj: nuovo oggetto da visualizzare nella canvas
 * @param checkBoxName: nome assegnato alla checkbox relativa al nuovo oggetto
 */
void MainWindow::pushObj(const DrawableObject* obj, std::string checkBoxName, bool b)
{
    ui->glCanvas->pushDrawableObject(obj);
    if (b) ui->glCanvas->fitScene();
    ui->glCanvas->update();

    QCheckBox * cb = new QCheckBox();
    cb->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    cb->setText(checkBoxName.c_str());
    cb->setEnabled(true);
    cb->setChecked(true);

    checkBoxes[nMeshes] = cb;
    mapObjects.insert( boost::bimap<int, const DrawableObject*>::value_type(nMeshes, obj ) );
    connect(cb, SIGNAL(stateChanged(int)), checkBoxMapper, SLOT(map()));
    checkBoxMapper->setMapping(cb, nMeshes);
    nMeshes++;

    //((QVBoxLayout*)ui->scrollArea->layout())->addWidget(cb, 0, Qt::AlignTop);
    int nr = ((QGridLayout*)ui->scrollArea->layout())->rowCount();
    ((QGridLayout*)ui->scrollArea->layout())->addWidget(cb, nr, 0, 1, 0, Qt::AlignTop);
}

/**
 * @brief Elimina il DrawableObject dalla scena (non esegue nessuna free!) e la relativa checkBox nella scrollBar.
 *
 * Aggiorna in automatico la scena visualizzata.
 *
 * @param obj: oggetto che verrà rimosso dalla canvas
 */
bool MainWindow::deleteObj(const DrawableObject* obj, bool b)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator it = mapObjects.right.find(obj);
    if (it != mapObjects.right.end()){
        int i = it->second;

        QCheckBox * cb = checkBoxes[i];
        checkBoxMapper->removeMappings(cb);
        cb->setVisible(false);
        ui->scrollArea->layout()->removeWidget(cb);

        checkBoxes.erase(i);
        mapObjects.left.erase(i);

        delete cb;

        ui->glCanvas->deleteDrawableObject(obj);
        if (b) ui->glCanvas->fitScene();
        ui->glCanvas->update();
        return true;
    }
    else
        return false;
}

void MainWindow::setObjVisibility(const DrawableObject *obj, bool visible)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator it = mapObjects.right.find(obj);
    if (it != mapObjects.right.end()){
        int i = it->second;

        QCheckBox * cb = checkBoxes[i];
        cb->setChecked(visible);
    }

}

bool MainWindow::contains(const DrawableObject* obj)
{
    boost::bimap<int, const DrawableObject*>::right_const_iterator right_iter = mapObjects.right.find(obj);
    return (right_iter != mapObjects.right.end());
}

/**
 * @brief Restituisce il BoundingBox di tutti gli oggetti \i presenti presenti nella canvas
 * @return il bounding box contenente gli oggetti visibili
 */
BoundingBox MainWindow::getFullBoundingBox()
{
    return ui->glCanvas->getFullBoundingBoxDrawableObjects();
}

/**
 * @brief Restituisce il numero di oggetti visibili presenti nella canvas.
 * @return intero rappresentante il numero di oggetti visibili
 */
int MainWindow::getNumberVisibleObjects()
{
    return ui->glCanvas->sizeVisibleDrawableObjects();
}


void MainWindow::enableDebugObjects()
{
    if (debugObjectsEnabled == false){
        pushObj(&debugObjects, "Debug Objects");
        ui->actionEnable_Debug_Objects->setEnabled(false);
        ui->actionDisable_Debug_Objects->setEnabled(true);
        debugObjectsEnabled = true;
    }
}

void MainWindow::disableDebugObjects()
{
    if (debugObjectsEnabled == true){
        if (deleteObj(&debugObjects)) {
            ui->actionEnable_Debug_Objects->setEnabled(true);
            ui->actionDisable_Debug_Objects->setEnabled(false);
            debugObjectsEnabled = false;
        }
    }
    ui->glCanvas->update();
}

void MainWindow::setFullScreen(bool b)
{
    ui->glCanvas->setFullScreen(b);
    if (!b)
        showMaximized();
}

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

    if (event->matches(QKeySequence::Print)){ //ctrl+p
        canvas.savePointOfView();
    }
    if (QKeySequence(event->key() | event->modifiers()) == QKeySequence(Qt::CTRL + Qt::Key_L)){ //ctrl+l
        canvas.loadPointOfView();
    }
}

/**
 * @brief Aggiunge un manager (frame) alla toolbox della mainWindow.
 * @param[in] f: il QFrame del manager da aggiungere
 * @param[in] name: nome associato al manager inserito
 * @param[in] parent: di default è la toolbox alla quale aggiungiamo il manager
 * @return un intero rappresentante l'indice del manager inserito
 */
int MainWindow::addManager(QFrame * f, std::string name, QToolBox * parent)
{
    if (parent == nullptr) parent = ui->toolBox;
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
void MainWindow::setCurrentIndexToolBox(unsigned int i)
{
    if (i < managers.size())
        ui->toolBox->setCurrentIndex(i);
}

/**
 * @brief Evento i-esima checkBox cliccata, modifica la visibilità dell'oggetto ad essa collegato
 * @param[in] i: indice della checkBox cliccata
 */
void MainWindow::checkBoxClicked(int i)
{
    QCheckBox * cb = checkBoxes[i];
    const DrawableObject * obj = mapObjects.left.at(i);
    //if (cb->isChecked()) obj->setVisible(true);
    //else obj->setVisible(false);
    if (cb->isChecked()) ui->glCanvas->setDrawableObjectVisibility(obj, true);
    else ui->glCanvas->setDrawableObjectVisibility(obj, false);
    ui->glCanvas->update();
}

void MainWindow::on_actionSave_Snapshot_triggered()
{
    QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::CTRL | Qt::Key_S, Qt::NoModifier);
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
    QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::CTRL | Qt::Key_H, Qt::NoModifier);
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
    ui->glCanvas->resetPointOfView();
}

} //namespace cg3::viewer
} //namespace cg3
