/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QCheckBox>
#include <cg3/geometry/plane.h>
#include "utilities/consolestream.h"

using namespace cg3;

/**
 * @brief Crea una nuova mainWindow composta da canvas, toolBox avente 0 frame e scrollArea.
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow),
                                          nMeshes(0),
                                          first(true),
                                          debugObjects(nullptr){
    ui->setupUi(this);
    ui->toolBox->removeItem(0);

    checkBoxMapper = new QSignalMapper(this);
    connect(checkBoxMapper, SIGNAL(mapped(int)), this, SLOT(checkBoxClicked(int)));
    connect(ui->glCanvas, SIGNAL(objectPicked(unsigned int)),
            this, SLOT(slotObjectPicked(unsigned int)));
    connect(ui->glCanvas, SIGNAL(point2DClicked(cg3::Point2Dd)),
            this, SLOT(slotPoint2DClicked(cg3::Point2Dd)));

    QVBoxLayout * layout = new QVBoxLayout(ui->scrollArea);
    ui->scrollArea->setLayout(layout);

    ui->console->hide();

    //doesn't work
    ConsoleStream(std::cerr, this->ui->console);
    ConsoleStream::registerConsoleMessageHandler();
    showMaximized();

    ui->glCanvas->setSnapshotQuality(100);
    ui->glCanvas->setSnapshotFormat("PNG");
}

MainWindow::~MainWindow() {
    if (debugObjects!=nullptr){
        deleteObj(debugObjects);
        delete debugObjects;
    }
    delete ui;
}

void MainWindow::fitScene() {
    ui->glCanvas->fitScene();
}

void MainWindow::fitScene(const Pointd& center, double radius) {
    ui->glCanvas->fitScene(center, radius);
}

Point2Di MainWindow::getCanvasSize() const {
    return Point2Di(ui->glCanvas->width(), ui->glCanvas->height());
}

/**
 * @brief Centra la scena tenendo conto di tutti gli oggetti visibili all'interno di essa
 */
void MainWindow::updateGlCanvas() {
    //ui->glCanvas->fitScene();
    ui->glCanvas->update();
}

/**
 * @brief Aggiunge un DrawableObject alla scena e la relativa checkBox nella scrollBar.
 *
 * Aggiorna in automatico la scena visualizzata.
 *
 * @param obj: nuovo oggetto da visualizzare nella canvas
 * @param checkBoxName: nome assegnato alla checkbox relativa al nuovo oggetto
 */
void MainWindow::pushObj(const DrawableObject* obj, std::string checkBoxName, bool b) {
    ui->glCanvas->pushObj(obj);
    if (b) ui->glCanvas->fitScene();
    ui->glCanvas->update();

    QCheckBox * cb = new QCheckBox();
    cb->setText(checkBoxName.c_str());
    cb->setEnabled(true);
    cb->setChecked(true);

    checkBoxes[nMeshes] = cb;
    mapObjects.insert( boost::bimap<int, const DrawableObject*>::value_type(nMeshes, obj ) );
    connect(cb, SIGNAL(stateChanged(int)), checkBoxMapper, SLOT(map()));
    checkBoxMapper->setMapping(cb, nMeshes);
    nMeshes++;

    ((QVBoxLayout*)ui->scrollArea->layout())->addWidget(cb, 1, Qt::AlignTop);
}

/**
 * @brief Elimina il DrawableObject dalla scena (non esegue nessuna free!) e la relativa checkBox nella scrollBar.
 *
 * Aggiorna in automatico la scena visualizzata.
 *
 * @param obj: oggetto che verrà rimosso dalla canvas
 */
void MainWindow::deleteObj(const DrawableObject* obj, bool b) {
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

        ui->glCanvas->deleteObj(obj);
        if (b) ui->glCanvas->fitScene();
        ui->glCanvas->update();
    }
}

void MainWindow::setObjVisibility(const DrawableObject *obj, bool visible) {
    boost::bimap<int, const DrawableObject*>::right_const_iterator it = mapObjects.right.find(obj);
    if (it != mapObjects.right.end()){
        int i = it->second;

        QCheckBox * cb = checkBoxes[i];
        cb->setChecked(visible);
    }

}

bool MainWindow::contains(const DrawableObject* obj) {
    boost::bimap<int, const DrawableObject*>::right_const_iterator right_iter = mapObjects.right.find(obj);
    return (right_iter != mapObjects.right.end());
}

/**
 * @brief Restituisce il BoundingBox di tutti gli oggetti \i presenti presenti nella canvas
 * @return il bounding box contenente gli oggetti visibili
 */
BoundingBox MainWindow::getFullBoundingBox() {
    return ui->glCanvas->getFullBoundingBox();
}

/**
 * @brief Restituisce il numero di oggetti visibili presenti nella canvas.
 * @return intero rappresentante il numero di oggetti visibili
 */
int MainWindow::getNumberVisibleObjects() {
    return ui->glCanvas->getNumberVisibleObjects();
}

/**
 * @brief salva uno snapshot della scena presente nella canvas.
 *
 * Aggiorna in automatico la scena visualizzata.
 */
void MainWindow::saveSnapshot() {
    ui->glCanvas->update();
    ui->glCanvas->saveSnapshot();
}

/**
 * @brief Visualizza gli assi xyz in base al booleano passato in input.
 *
 * Aggiorna in autmoatico la scena visualizzata.
 * @param[in] b: se true visualizza gli assi, se false non li visualizza.
 */
void MainWindow::drawAxis(bool b) {
    ui->glCanvas->setAxisIsDrawn(b);
    ui->glCanvas->update();
}

void MainWindow::savePointOfView(std::string filename) {
    ui->glCanvas->savePointOfView(filename);
}

void MainWindow::loadPointOfView(std::string filename) {
    ui->glCanvas->loadPointOfView(filename);
    ui->glCanvas->update();
}

/**
 * @brief Aggiunge un manager (frame) alla toolbox della mainWindow.
 * @param[in] f: il QFrame del manager da aggiungere
 * @param[in] name: nome associato al manager inserito
 * @param[in] parent: di default è la toolbox alla quale aggiungiamo il manager
 * @return un intero rappresentante l'indice del manager inserito
 */
int MainWindow::addManager(QFrame * f, std::string name, QToolBox * parent) {
    if (parent == nullptr) parent = ui->toolBox;
    ui->toolBox->insertItem(managers.size(), f, QString(name.c_str()));
    ui->toolBox->adjustSize();

    f->show();
    managers.push_back(f);
    //adjustSize();
    return managers.size()-1;
}

/**
 * @brief Restituisce il puntatore al manager identificato dall'indice passato come parametro.
 * @param[in] i: indice del manager da restituire
 * @return il puntatore al manager se esiste, nullptr altrimenti
 */
QFrame *MainWindow::getManager(unsigned int i) {
    if (i < managers.size()) return managers[i];
    else return nullptr;
}

/**
 * @brief Rinomina il manager identificato dall'indice passato come parametro
 * @param[in] i: indice del manager da rinominare
 * @param[in] s: il nuovo nome del manager
 */
void MainWindow::renameManager(unsigned int i, std::string s) {
    if (i < managers.size())
        ui->toolBox->setItemText(i, QString(s.c_str()));
}

/**
 * @brief Modifica il manager visualizzato all'i-esimo.
 * @param[in] i: indice del manager da visualizzare
 */
void MainWindow::setCurrentIndexToolBox(unsigned int i){
    if (i < managers.size())
        ui->toolBox->setCurrentIndex(i);
}

void MainWindow::disableRotation() {
    ui->glCanvas->setMouseBinding(Qt::NoModifier, Qt::LeftButton, ui->glCanvas->NO_CLICK_ACTION);
}

void MainWindow::enableRotation() {
    ui->glCanvas->setMouseBinding(Qt::NoModifier, Qt::LeftButton, ui->glCanvas->CAMERA, ui->glCanvas->ROTATE);
}

void MainWindow::disableTranslation() {
    ui->glCanvas->setMouseBinding(Qt::NoModifier, Qt::RightButton, ui->glCanvas->NO_CLICK_ACTION);
}

void MainWindow::enableTranslation() {
    ui->glCanvas->setMouseBinding(Qt::NoModifier, Qt::RightButton, ui->glCanvas->CAMERA, ui->glCanvas->TRANSLATE);
}

void MainWindow::disableZoom() {
    ui->glCanvas->setWheelBinding(Qt::NoModifier, ui->glCanvas->CAMERA, ui->glCanvas->NO_MOUSE_ACTION);
}

void MainWindow::enableZoom() {
    ui->glCanvas->setWheelBinding(Qt::NoModifier, ui->glCanvas->CAMERA, ui->glCanvas->ZOOM);
}

void MainWindow::setSelectLeftButton() {
    ui->glCanvas->setMouseBinding(Qt::NoModifier, Qt::LeftButton, ui->glCanvas->SELECT);
}

void MainWindow::enableDebugObjects() {
    if (debugObjects == nullptr){
        debugObjects = new DrawableDebugObjects();
        pushObj(debugObjects, "Debug Objects");
    }
}

void MainWindow::disableDebugObjects() {
    if (debugObjects != nullptr){
        deleteObj(debugObjects);
        delete debugObjects;
        debugObjects = nullptr;
    }
    ui->glCanvas->update();
}

void MainWindow::addDebugSphere(const Pointd& center, double radius, const QColor& color, int precision) {
    if (debugObjects!= nullptr){
        debugObjects->addDebugSphere(center, radius, color, precision);
        ui->glCanvas->update();
    }
}

void MainWindow::clearDebugSpheres() {
    if (debugObjects!= nullptr){
        debugObjects->clearDebugSpheres();
        ui->glCanvas->update();
    }
}

void MainWindow::addDebugCylinder(const Pointd& a, const Pointd& b, double radius, const QColor color) {
    if (debugObjects!=nullptr){
        debugObjects->addDebugCylinder(a,b,radius, color);
        ui->glCanvas->update();
    }
}

void MainWindow::clearDebugCylinders() {
    if (debugObjects!=nullptr){
        debugObjects->clearDebugCylinders();
        ui->glCanvas->update();
    }
}

void MainWindow::addDebugLine(const Pointd &a, const Pointd &b, int width, const QColor color) {
    if (debugObjects != nullptr){
        debugObjects->addDebugLine(a,b,width, color);
        ui->glCanvas->update();
    }
}

void MainWindow::clearDebugLines() {
    if (debugObjects!=nullptr){
        debugObjects->clearDebugLines();
        ui->glCanvas->update();
    }
}

/**
 * @brief Evento i-esima checkBox cliccata, modifica la visibilità dell'oggetto ad essa collegato
 * @param[in] i: indice della checkBox cliccata
 */
void MainWindow::checkBoxClicked(int i) {
    QCheckBox * cb = checkBoxes[i];
    const DrawableObject * obj = mapObjects.left.at(i);
    //if (cb->isChecked()) obj->setVisible(true);
    //else obj->setVisible(false);
    if (cb->isChecked()) ui->glCanvas->setVisibility(obj, true);
    else ui->glCanvas->setVisibility(obj, false);
    ui->glCanvas->update();
}

void MainWindow::slotObjectPicked(unsigned int i) {
    emit objectPicked(i);
}

void MainWindow::slotPoint2DClicked(Point2Dd p) {
    emit point2DClicked(p);
}

/**
 * WIDGETS SLOTS
 */

void MainWindow::setFullScreen(bool b) {
    ui->glCanvas->setFullScreen(b);
}

void MainWindow::setBackgroundColor(const QColor & color) {
    ui->glCanvas->setClearColor(color);
}

void MainWindow::keyPressEvent(QKeyEvent * event){
    if(event->matches(QKeySequence::Undo))
        emit(undoEvent());
    if (event->matches(QKeySequence::Redo))
        emit(redoEvent());
    if (event->matches(QKeySequence::Replace)){ //ctrl+h
        std::cerr << "\n";
        if (ui->dockWidget->isHidden())
            ui->dockWidget->show();
        else
            ui->dockWidget->hide();
    }
    /** @todo doesn't work */
    if (event->matches(QKeySequence::SelectAll)){ //ctrl+a
        std::cerr << "\n";
        if (ui->console->isHidden())
            ui->console->show();
        else
            ui->console->hide();
    }

    if (event->matches(QKeySequence::Print)){ //ctrl+p
        savePointOfView();
    }
    if (QKeySequence(event->key() | event->modifiers()) == QKeySequence(Qt::CTRL + Qt::Key_L)){ //ctrl+l
        loadPointOfView();
    }
}
