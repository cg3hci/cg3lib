/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_manager.h"
#include "ui_dcel_manager.h"

#include <QFileDialog>
#include <QColorDialog>
#include <iostream>

namespace cg3 {

namespace viewer {

/**
 * @brief Crea un DcelManager
 * @param parent
 */
DcelManager::DcelManager(QWidget *parent) : QFrame(parent), ui(new Ui::DcelManager), mainWindow((cg3::viewer::MainWindow&)*parent), drawableDcel(nullptr) {
    ui->setupUi(this);
    dcells.addSupportedExtension("obj","ply","dcel");
}

/**
 * @brief Elimina un DcelManager e la DrawableDcel contenuta in esso
 */
DcelManager::~DcelManager() {
    delete ui;
    if (drawableDcel!=nullptr)
        delete drawableDcel;
}

/**
 * @brief Restituisce il puntatore alla drawableDcel contenuta nel manager
 * @return La drawableDcel presente nel manager
 */
DrawableDcel *DcelManager::getDcel() {
    return drawableDcel;
}

/**
 * @brief Setta la Dcel contenuta nel manager, creando una \i copia della Dcel passata come parametro.
 *
 * Aggiorna in automatico la canvas, e setta i pulsanti del manager in modalità "dcelLoaded".
 * Elimina eventuali altre Dcel presenti precedentemente nel manager.
 *
 * @param[in] dcel: la dcel che verrà copiata all'interno del manager
 * @param[in] b: se true, viene visualizzata una dcel in base alla segmentazione
 */
void DcelManager::setDcel(const Dcel &dcel, const std::string &name, bool b) {
    cleanDcel();
    drawableDcel = new DrawableDcel(dcel);
    mainWindow.pushObj(drawableDcel, name);
    if (b){
        drawableDcel->setFlatShading();
        ui->flatDcelRadioButton->setChecked(true);
    }
    mainWindow.updateGlCanvas();

    setButtonsDcelLoaded();
}

/**
 * @brief Elimina la Dcel contenuta nel manager.
 *
 * Aggiorna in automatico la canvasm e setta i pulsanti del manager in modalità "dcelNotLoaded".
 */
void DcelManager::cleanDcel() {
    setButtonsDcelNotLoaded();

    if (drawableDcel != nullptr){
        resetDefaults();
        drawableDcel->setVisible(false);
        mainWindow.updateGlCanvas();
        mainWindow.deleteObj(drawableDcel);
        delete drawableDcel;
        drawableDcel = nullptr;

    }
}

/**
 * @brief Applica le modifiche effettuate nella Dcel alla DrawableDcel.
 * Vedi DrawableDcel::update().
 */
void DcelManager::updateDcel() {
    if (drawableDcel != nullptr){
        drawableDcel->update();
    }
}

/**
 * @brief setta ai valori predefiniti tutti gli oggetti presenti nel QFrame del DcelManager
 */
void DcelManager::resetDefaults() {
    ui->wireframeDcelCheckBox->setChecked(false);
    ui->boundingBoxCheckBox->setChecked(false);
    ui->drawDcelCheckBox->setChecked(true);
    ui->smoothDcelRadioButton->setChecked(true);
    ui->triangleColorDcelRadioButton->setChecked(true);
    ui->wireframeWidthDcelSlider->setValue(1);
}

/**
 * @brief Setta tutti i pulsandi del QFrame del DcelManager in modalità "dcelLoaded".
 *
 * Tutti i pulsanti che permettono di effettuare operazioni di modifica visualizzazione sulla Dcel
 * vengono attivati.
 * @warning tutti questi pulsanti assumono che all'interno della DcelManager sia presente una Dcel, per cui
 * non chiamare mai questo metodo se non è presente una dcel all'interno del manager.
 */
void DcelManager::setButtonsDcelLoaded() {
    ui->wireframeColorDcelButton->setEnabled(true);
    ui->boundingBoxCheckBox->setEnabled(true);
    ui->drawDcelCheckBox->setEnabled(true);
    ui->wireframeDcelCheckBox->setEnabled(true);
    ui->wireframeWidthDcelSlider->setEnabled(true);
    ui->flatDcelRadioButton->setEnabled(true);
    ui->pointsDcelRadioButton->setEnabled(true);
    ui->smoothDcelRadioButton->setEnabled(true);
    ui->triangleColorDcelRadioButton->setEnabled(true);
    ui->vertexColorDcelRadioButton->setEnabled(true);
    ui->cleanDcelButton->setEnabled(true);
    ui->loadDcelButton->setEnabled(false);
    ui->saveDcelButton->setEnabled(true);
}

/**
 * @brief Setta tutti i pulsandi del QFrame del DcelManager in modalità "dcelNotLoaded".
 *
 * Tutti i pulsanti che permettono di effettuare operazioni di modifica visualizzazione sulla Dcel
 * vengono disattivati.
 */
void DcelManager::setButtonsDcelNotLoaded() {
    ui->boundingBoxCheckBox->setEnabled(false);
    ui->wireframeColorDcelButton->setEnabled(false);
    ui->drawDcelCheckBox->setEnabled(false);
    ui->wireframeDcelCheckBox->setEnabled(false);
    ui->wireframeWidthDcelSlider->setEnabled(false);
    ui->facesWireframeDcelCheckBox->setEnabled(false);
    ui->flatDcelRadioButton->setEnabled(false);
    ui->pointsDcelRadioButton->setEnabled(false);
    ui->smoothDcelRadioButton->setEnabled(false);
    ui->triangleColorDcelRadioButton->setEnabled(false);
    ui->vertexColorDcelRadioButton->setEnabled(false);
    ui->cleanDcelButton->setEnabled(false);
    ui->loadDcelButton->setEnabled(true);
    ui->saveDcelButton->setEnabled(false);
}
/**
 * @brief Metodo chiamato quando viene premuto il pulsante LoadDcel
 */
void DcelManager::on_loadDcelButton_clicked() {
    std::string filename = dcells.loadDialog("Open Dcel");

    if (filename != "") {
        if (drawableDcel != nullptr) {
            mainWindow.deleteObj(drawableDcel);
            delete drawableDcel;
        }
        bool success = true;
        drawableDcel = new DrawableDcel();
        success = drawableDcel->loadFromFile(filename);

        if (success) {
            std::cout << "load: " << filename << std::endl;
            if (! drawableDcel->isTriangleMesh()){
                std::cerr << "No Triangle Mesh\n";
                ui->facesWireframeDcelCheckBox->setEnabled(true);
            }
            else {
                std::cerr << "Triangle Mesh\n";
            }
            //drawableDcel->setFacesWireframe(true);
            drawableDcel->setSmoothShading();
            drawableDcel->update();
            mainWindow.pushObj(drawableDcel, filename.substr(filename.find_last_of("/") + 1));
            mainWindow.updateGlCanvas();

            setButtonsDcelLoaded();
        }
        else {
            std::cerr << "Error Loading File\n";
            delete drawableDcel;
            drawableDcel = nullptr;
        }

    }
}

/**
 * @brief Metodo chiamato quando viene premuto il pulsante cleanDcel
 */
void DcelManager::on_cleanDcelButton_clicked() {
    cleanDcel();
}

/**
 * @brief Metodo chiamato quando viene premuto il pulsante saveDcel
 */
void DcelManager::on_saveDcelButton_clicked() {
    std::string selectedFilter;
    std::string filename = dcells.saveDialog("Save Dcel", selectedFilter);
    if (filename != ""){

        std::cout << "save: " << filename << std::endl;

        if (selectedFilter == "ply") {
            drawableDcel->saveOnPlyFile(filename);
        }
        else  if (selectedFilter == "obj") {
            drawableDcel->saveOnObjFile(filename);
        }
        else {
            drawableDcel->saveOnDcelFile(filename);
        }
    }
}

void DcelManager::on_wireframeDcelCheckBox_stateChanged(int state) {
    drawableDcel->setWireframe(state == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void DcelManager::on_wireframeWidthDcelSlider_valueChanged(int value) {
    drawableDcel->setWireframeWidth(value);
    mainWindow.updateGlCanvas();
}

void DcelManager::on_wireframeColorDcelButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);

    drawableDcel->setWireframeColor(color.redF(), color.greenF(), color.blueF());
    mainWindow.updateGlCanvas();
}

void DcelManager::on_drawDcelCheckBox_stateChanged(int state) {
    drawableDcel->setVisible(state == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void DcelManager::on_pointsDcelRadioButton_toggled(bool checked) {
    if (checked)
        drawableDcel->setPointsShading();
    mainWindow.updateGlCanvas();
}

void DcelManager::on_flatDcelRadioButton_toggled(bool checked) {
    if (checked)
        drawableDcel->setFlatShading();
    mainWindow.updateGlCanvas();
}

void DcelManager::on_smoothDcelRadioButton_toggled(bool checked) {
    if (checked)
        drawableDcel->setSmoothShading();
    mainWindow.updateGlCanvas();
}

void DcelManager::on_vertexColorDcelRadioButton_toggled(bool checked) {
    if (checked)
        drawableDcel->setEnableVertexColor();
    mainWindow.updateGlCanvas();
}

void DcelManager::on_triangleColorDcelRadioButton_toggled(bool checked) {
    if (checked)
        drawableDcel->setEnableTriangleColor();
    mainWindow.updateGlCanvas();
}

void DcelManager::on_boundingBoxCheckBox_stateChanged(int state) {
    drawableDcel->setVisibleBoundingBox(state == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void DcelManager::on_facesWireframeDcelCheckBox_stateChanged(int state) {
    drawableDcel->setFacesWireframe(state == Qt::Checked);
    mainWindow.updateGlCanvas();
}

}

}
