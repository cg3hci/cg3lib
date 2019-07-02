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
 * @brief Creates a Dcel Manager
 * @param parent: this parameter must be the pointer to the MainWindow.
 */
CG3_INLINE DcelManager::DcelManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DcelManager),
	mainWindow((cg3::viewer::AbstractMainWindow&)*parent),
    loaded(false)
{
    ui->setupUi(this);
    dcells.addSupportedExtension("obj","ply","dcel");
}

/**
 * @brief Deletes the Dcel Manager and removes the Dcel from the MainWindow eventually.
 */
CG3_INLINE DcelManager::~DcelManager()
{
    if (loaded)
        mainWindow.deleteDrawableObject(&drawableDcel);
    delete ui;
}

/**
 * @brief Returns a reference to the Dcel of contained in the Manager
 * @return
 */
CG3_INLINE DrawableDcel &DcelManager::dcel()
{
    return drawableDcel;
}

/**
 * @brief Allows to set from the outside the Dcel contained in the manager.
 * The manager passes in "Dcel Loaded" mode, enabling/disabling all the gui's elements
 * accordingly.
 *
 * @param[in] dcel
 */
CG3_INLINE void DcelManager::setDcel(const Dcel &dcel, const std::string &name)
{
    cleanDcel();
    drawableDcel = dcel;
    mainWindow.pushDrawableObject(&drawableDcel, name);
	mainWindow.updateCanvas();
    loaded = true;

    setButtonsDcelLoaded();
}

/**
 * @brief Deletes the contained Dcel in the manager.
 * The manager passes in "Dcel not Loaded" mode, enabling/disabling all the gui's elements
 * accordingly.
 */
CG3_INLINE void DcelManager::cleanDcel()
{
    if (loaded){
        setButtonsDcelNotLoaded();

        resetDefaults();
        mainWindow.deleteDrawableObject(&drawableDcel);
		mainWindow.updateCanvas();
		mainWindow.fitSceneCanvas();
        loaded = false;
    }
}

/**
 * @brief Calls the update() member of the contained dcel.
 * @see DrawableDcel::update().
 */
CG3_INLINE void DcelManager::updateDcel()
{
    if (loaded){
        drawableDcel.update();
		mainWindow.updateCanvas();
		mainWindow.fitSceneCanvas();
    }
}

/**
 * @brief DcelManager::isDcelLoaded
 */
CG3_INLINE bool DcelManager::isDcelLoaded() const
{
    return loaded;
}

/**
 * @brief Metodo chiamato quando viene premuto il pulsante LoadDcel
 */
CG3_INLINE void DcelManager::on_loadDcelButton_clicked()
{
    std::string filename = dcells.loadDialog("Open Dcel");

    if (filename != "") {
        if (loaded) {
            cleanDcel();
        }
        bool success = true;
        success = drawableDcel.loadFromFile(filename);

        if (success) {
            std::cout << "load: " << filename << std::endl;
            if (! drawableDcel.isTriangleMesh()){
                std::cerr << "No Triangle Mesh\n";
                ui->facesWireframeDcelCheckBox->setEnabled(true);
            }
            else {
                std::cerr << "Triangle Mesh\n";
            }
            //drawableDcel->setFacesWireframe(true);
            drawableDcel.setSmoothShading();
            drawableDcel.update();
            mainWindow.pushDrawableObject(&drawableDcel, filename.substr(filename.find_last_of("/") + 1));
			mainWindow.updateCanvas();
			mainWindow.fitSceneCanvas();
            setButtonsDcelLoaded();
            loaded = true;
        }
        else {
            std::cerr << "Error Loading File\n";
        }

    }
}

/**
 * @brief Metodo chiamato quando viene premuto il pulsante cleanDcel
 */
CG3_INLINE void DcelManager::on_cleanDcelButton_clicked()
{
    cleanDcel();
}

/**
 * @brief Metodo chiamato quando viene premuto il pulsante saveDcel
 */
CG3_INLINE void DcelManager::on_saveDcelButton_clicked()
{
    if (loaded) {
        std::string selectedFilter;
        std::string filename = dcells.saveDialog("Save Dcel", selectedFilter);
        if (filename != ""){

            std::cout << "save: " << filename << std::endl;

            if (selectedFilter == "ply") {
                drawableDcel.saveOnPly(filename);
            }
            else  if (selectedFilter == "obj") {
                drawableDcel.saveOnObj(filename);
            }
            else {
                drawableDcel.saveOnDcelFile(filename);
            }
        }
    }
}

CG3_INLINE void DcelManager::on_wireframeDcelCheckBox_stateChanged(int state)
{
    if (loaded) {
        drawableDcel.setWireframe(state == Qt::Checked);
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_wireframeWidthDcelSlider_valueChanged(int value)
{
    if (loaded) {
        drawableDcel.setWireframeWidth(value);
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_wireframeColorDcelButton_clicked()
{
    if (loaded) {
        QColor color = QColorDialog::getColor(Qt::white, this);

        drawableDcel.setWireframeColor(color.redF(), color.greenF(), color.blueF());
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_pointsDcelRadioButton_toggled(bool checked)
{
    if (loaded) {
        if (checked)
            drawableDcel.setPointsShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_flatDcelRadioButton_toggled(bool checked)
{
    if (loaded) {
        if (checked)
            drawableDcel.setFlatShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_smoothDcelRadioButton_toggled(bool checked)
{
    if (loaded) {
        if (checked)
            drawableDcel.setSmoothShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_vertexColorDcelRadioButton_toggled(bool checked)
{
    if (loaded) {
        if (checked)
            drawableDcel.setEnableVertexColor();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_triangleColorDcelRadioButton_toggled(bool checked)
{
    if (loaded) {
        if (checked)
            drawableDcel.setEnableTriangleColor();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_boundingBoxCheckBox_stateChanged(int state)
{
    if (loaded) {
        drawableDcel.setVisibleBoundingBox(state == Qt::Checked);
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void DcelManager::on_facesWireframeDcelCheckBox_stateChanged(int state)
{
    if (loaded) {
        drawableDcel.setFacesWireframe(state == Qt::Checked);
		mainWindow.updateCanvas();
    }
}

/**
 * @brief setta ai valori predefiniti tutti gli oggetti presenti nel QFrame del DcelManager
 */
CG3_INLINE void DcelManager::resetDefaults()
{
    ui->wireframeDcelCheckBox->setChecked(false);
    ui->boundingBoxCheckBox->setChecked(false);
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
CG3_INLINE void DcelManager::setButtonsDcelLoaded()
{
    ui->wireframeColorDcelButton->setEnabled(true);
    ui->boundingBoxCheckBox->setEnabled(true);
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
CG3_INLINE void DcelManager::setButtonsDcelNotLoaded()
{
    ui->boundingBoxCheckBox->setEnabled(false);
    ui->wireframeColorDcelButton->setEnabled(false);
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

} //namespace cg3::viewer
} //namespace cg3
