/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_manager.h"
#include "ui_eigenmesh_manager.h"

#include <QFileDialog>

namespace cg3 {

namespace viewer {

EigenMeshManager::EigenMeshManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EigenMeshManager),
    mainWindow((cg3::viewer::MainWindow&)*parent),
    mesh (nullptr) {
    ui->setupUi(this);
    objls.addSupportedExtension("obj", "ply");
}

void EigenMeshManager::setButtonsMeshLoaded(bool b) {
    ui->loadMeshButton->setEnabled(!b);
    ui->clearMeshButton->setEnabled(b);
    ui->saveMeshButton->setEnabled(b);
    ui->pointsMeshRadioButton->setEnabled(b);
    ui->flatMeshRadioButton->setEnabled(b);
    ui->smoothMeshRadioButton->setEnabled(b);
    ui->wireframeMeshCheckBox->setEnabled(b);
    ui->boundingBoxCheckBox->setEnabled(b);
    ui->verticesColorRadioButton->setEnabled(b);
    ui->faceColorRadioButton->setEnabled(b);
    ui->wireframeMeshCheckBox->setChecked(false);
    ui->boundingBoxCheckBox->setChecked(false);
    ui->smoothMeshRadioButton->setChecked(true);
    ui->faceColorRadioButton->setChecked(true);
    ui->verticesColorRadioButton->setChecked(false);
}

void EigenMeshManager::setEigenMesh(const EigenMesh& m) {
    if (mesh != nullptr){
        mainWindow.deleteObj(mesh);
        delete mesh;
    }
    mesh = new DrawableEigenMesh(m);
    mainWindow.pushObj(mesh, "EigenMesh");
    setButtonsMeshLoaded(true);
    mainWindow.updateGlCanvas();

}

EigenMeshManager::~EigenMeshManager() {
    delete ui;
    if (mesh != nullptr){
        mainWindow.deleteObj(mesh);
        delete mesh;
    }
}

void EigenMeshManager::on_loadMeshButton_clicked() {
    std::string filename = objls.loadDialog("Open Eigen Mesh");
        if (filename != "") {
            mesh = new DrawableEigenMesh();
            bool loaded = mesh->readFromFile(filename);

            if (loaded) {
                mesh->setEnableTriangleColor();
                mainWindow.pushObj(mesh, filename.substr(filename.find_last_of("/") + 1));
                setButtonsMeshLoaded(true);
                mainWindow.updateGlCanvas();
            }
            else {
                delete mesh;
                mesh = nullptr;
                std::cerr << "Error while loading file " << filename << ".\n";
            }
        }
}

void EigenMeshManager::on_clearMeshButton_clicked() {
    setButtonsMeshLoaded(false);
    mainWindow.deleteObj(mesh);
    delete mesh;
    mesh = nullptr;
}

void EigenMeshManager::on_saveMeshButton_clicked() {
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(nullptr,
                       "Save Eigen Mesh",
                       ".",
                       "PLY(*.ply);;OBJ(*.obj)", &selectedFilter);
    if (!filename.isEmpty()) {
        std::cout << "save: " << filename.toStdString() << std::endl;

        if (selectedFilter == "PLY(*.ply)") {
            mesh->saveOnPly(filename.toStdString());
        }
        else  if (selectedFilter == "OBJ(*.obj)") {
            mesh->saveOnObj(filename.toStdString());
        }
    }
}

void EigenMeshManager::on_pointsMeshRadioButton_toggled(bool checked){
    if (checked){
        mesh->setPointsShading();
        mainWindow.updateGlCanvas();
    }
}

void EigenMeshManager::on_flatMeshRadioButton_toggled(bool checked) {
    if (checked){
        mesh->setFlatShading();
        mainWindow.updateGlCanvas();
    }
}

void EigenMeshManager::on_smoothMeshRadioButton_toggled(bool checked) {
    if (checked){
        mesh->setSmoothShading();
        mainWindow.updateGlCanvas();
    }
}

void EigenMeshManager::on_wireframeMeshCheckBox_stateChanged(int arg1) {
    mesh->setWireframe(arg1 == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void EigenMeshManager::on_verticesColorRadioButton_toggled(bool checked) {
    if (checked){
        mesh->setEnableVertexColor();
        mainWindow.updateGlCanvas();
    }
}

void EigenMeshManager::on_faceColorRadioButton_toggled(bool checked) {
    if (checked){
        mesh->setEnableTriangleColor();
        mainWindow.updateGlCanvas();
    }
}

void EigenMeshManager::on_boundingBoxCheckBox_stateChanged(int arg1) {
    mesh->setVisibleBoundingBox(arg1 == Qt::Checked);
    mainWindow.updateGlCanvas();
}

}

}
