/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "booleans_manager.h"
#include "ui_booleans_manager.h"

#include <QFileDialog>
#include <cg3/utilities/utils.h>
#include <cg3/geometry/transformations.h>
#include <cg3/meshes/eigenmesh/algorithms/eigenmesh_algorithms.h>
#include <cg3/libigl/booleans.h>

namespace cg3 {

namespace viewer {

BooleansManager::BooleansManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BooleansManager),
    mainWindow((cg3::viewer::MainWindow&)*parent),
    result(nullptr){
    meshes.resize(2);
    meshes[0] = meshes[1] = nullptr;
    ui->setupUi(this);
    objls.addSupportedExtension("obj");
}

BooleansManager::~BooleansManager() {
    delete ui;
    for (unsigned int i = 0; i < meshes.size(); i++) {
        if (meshes[i]!=nullptr){
            mainWindow.deleteObj(meshes[i]);
            delete meshes[i];
        }
    }
}

void BooleansManager::setButtonsMeshLoaded(bool b) {
    ui->loadEigenMeshButton->setEnabled(!b);
    ui->clearEigenMeshButton->setEnabled(b);
    ui->saveEigenMeshButton->setEnabled(b);
    ui->pointsEigenMeshRadioButton->setEnabled(b);
    ui->flatEigenMeshRadioButton->setEnabled(b);
    ui->smoothEigenMeshRadioButton->setEnabled(b);
    ui->wireframeEigenMeshCheckBox->setEnabled(b);
    ui->wireframeEigenMeshCheckBox->setChecked(false);
    ui->smoothEigenMeshRadioButton->setChecked(true);
}

void BooleansManager::setButtonsMeshLoaded_2(bool b) {
    ui->loadEigenMeshButton_2->setEnabled(!b);
    ui->clearEigenMeshButton_2->setEnabled(b);
    ui->saveEigenMeshButton_2->setEnabled(b);
    ui->pointsEigenMeshRadioButton_2->setEnabled(b);
    ui->flatEigenMeshRadioButton_2->setEnabled(b);
    ui->smoothEigenMeshRadioButton_2->setEnabled(b);
    ui->wireframeEigenMeshCheckBox_2->setEnabled(b);
    ui->wireframeEigenMeshCheckBox_2->setChecked(false);
    ui->smoothEigenMeshRadioButton_2->setChecked(true);
}

void BooleansManager::setButtonsResultLoaded(bool b) {
    ui->clearEigenMeshButton_3->setEnabled(b);
    ui->saveEigenMeshButton_3->setEnabled(b);
    ui->pointsEigenMeshRadioButton_3->setEnabled(b);
    ui->flatEigenMeshRadioButton_3->setEnabled(b);
    ui->smoothEigenMeshRadioButton_3->setEnabled(b);
    ui->wireframeEigenMeshCheckBox_3->setEnabled(b);
    ui->wireframeEigenMeshCheckBox_3->setChecked(false);
    ui->smoothEigenMeshRadioButton_3->setChecked(true);
}

void BooleansManager::setMesh1(const EigenMesh& m) {
    if (meshes[0] != nullptr){
        mainWindow.deleteObj(meshes[0]);
        delete meshes[0];
    }
    meshes[0] = new DrawableEigenMesh(m);
    mainWindow.pushObj(meshes[0], "EigenMesh");
    setButtonsMeshLoaded(true);
    mainWindow.updateGlCanvas();
}

void BooleansManager::setMesh2(const EigenMesh& m) {
    if (meshes[1] != nullptr){
        mainWindow.deleteObj(meshes[1]);
        delete meshes[1];
    }
    meshes[1] = new DrawableEigenMesh(m);
    mainWindow.pushObj(meshes[1], "EigenMesh");
    setButtonsMeshLoaded_2(true);
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_loadEigenMeshButton_clicked() {
    std::string filename = objls.loadDialog("Load Mesh 1");
    if (filename != "") {
        DrawableEigenMesh* mesh = new DrawableEigenMesh();
        mesh->readFromObj(filename);
        //mesh->readFromObj(filename.toStdString());
        mainWindow.pushObj(mesh, filename.substr(filename.find_last_of("/") + 1));
        setButtonsMeshLoaded(true);
        mainWindow.updateGlCanvas();
        if (meshes[0] != nullptr){
            mainWindow.deleteObj(meshes[0]);
            delete meshes[0];
        }
        meshes[0] = mesh;
    }
}

void BooleansManager::on_clearEigenMeshButton_clicked() {
    setButtonsMeshLoaded(false);
    mainWindow.deleteObj(meshes[0]);
    delete meshes[0];
    meshes[0] = nullptr;
}

void BooleansManager::on_saveEigenMeshButton_clicked() {
    std::string filename = objls.saveDialog("Save Mesh 1");

    std::cout << "save: " << filename << std::endl;

    meshes[0]->saveOnObj(filename);

}

void BooleansManager::on_setFromResultButton_clicked() {
    if (result != nullptr){
        if (meshes[0] != nullptr){
            mainWindow.deleteObj(meshes[0]);
            delete meshes[0];
        }
        meshes[0] = new DrawableEigenMesh(*result);
        mainWindow.pushObj(meshes[0], "Result");
        setButtonsMeshLoaded(true);
        mainWindow.updateGlCanvas();

    }
}

void BooleansManager::on_pointsEigenMeshRadioButton_toggled(bool checked) {
    if (checked){
        meshes[0]->setPointsShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_flatEigenMeshRadioButton_toggled(bool checked) {
    if (checked){
        meshes[0]->setFlatShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_smoothEigenMeshRadioButton_toggled(bool checked) {
    if (checked){
        meshes[0]->setSmoothShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_wireframeEigenMeshCheckBox_stateChanged(int arg1) {
    meshes[0]->setWireframe(arg1 == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_loadEigenMeshButton_2_clicked() {
    std::string filename = objls.loadDialog("Load Mesh 2");
    if (filename != "") {
        DrawableEigenMesh* mesh = new DrawableEigenMesh();
        mesh->readFromObj(filename);
        mainWindow.pushObj(mesh, filename.substr(filename.find_last_of("/") + 1));
        setButtonsMeshLoaded_2(true);
        mainWindow.updateGlCanvas();
        if (meshes[1] != nullptr){
            mainWindow.deleteObj(meshes[1]);
            delete meshes[1];
        }
        meshes[1] = mesh;
    }
}

void BooleansManager::on_clearEigenMeshButton_2_clicked() {
    setButtonsMeshLoaded_2(false);
    mainWindow.deleteObj(meshes[1]);
    delete meshes[1];
    meshes[1] = nullptr;
}

void BooleansManager::on_saveEigenMeshButton_2_clicked() {
    std::string filename = objls.saveDialog("Save Mesh 2");

    std::cout << "save: " << filename << std::endl;

    meshes[1]->saveOnObj(filename);
}

void BooleansManager::on_setFromResultButton_2_clicked() {
    if (result != nullptr){
        if (meshes[1] != nullptr){
            mainWindow.deleteObj(meshes[1]);
            delete meshes[1];
        }
        meshes[1] = new DrawableEigenMesh(*result);
        mainWindow.pushObj(meshes[1], "Result");
        setButtonsMeshLoaded(true);
        mainWindow.updateGlCanvas();

    }
}

void BooleansManager::on_pointsEigenMeshRadioButton_2_toggled(bool checked) {
    if (checked){
        meshes[1]->setPointsShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_flatEigenMeshRadioButton_2_toggled(bool checked) {
    if (checked){
        meshes[1]->setFlatShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_smoothEigenMeshRadioButton_2_toggled(bool checked) {
    if (checked){
        meshes[1]->setSmoothShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_wireframeEigenMeshCheckBox_2_stateChanged(int arg1) {
    meshes[1]->setWireframe(arg1 == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_intersectionButton_clicked() {
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteObj(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        libigl::intersection(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushObj(result, "Intersection");
        mainWindow.updateGlCanvas();
        setButtonsResultLoaded(true);
    }
}

void BooleansManager::on_differenceButton_clicked() {
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteObj(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        libigl::difference(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushObj(result, "Difference");
        mainWindow.updateGlCanvas();
        setButtonsResultLoaded(true);
    }
}

void BooleansManager::on_unionButton_clicked() {
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteObj(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        libigl::union_(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushObj(result, "Union");
        mainWindow.updateGlCanvas();
        setButtonsResultLoaded(true);
    }
}

void BooleansManager::on_mergePushButton_clicked() {
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteObj(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        EigenMesh::merge(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushObj(result, "Merge");
        mainWindow.updateGlCanvas();
        setButtonsResultLoaded(true);
    }
}

void BooleansManager::on_clearEigenMeshButton_3_clicked() {
    mainWindow.deleteObj(result);
    delete result;
    result = nullptr;
    setButtonsResultLoaded(false);
}

void BooleansManager::on_saveEigenMeshButton_3_clicked() {
    std::string filename = objls.saveDialog("Save Result");

    std::cout << "save: " << filename << std::endl;

    result->saveOnObj(filename);

}

void BooleansManager::on_pointsEigenMeshRadioButton_3_toggled(bool checked) {
    if (checked){
        result->setPointsShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_flatEigenMeshRadioButton_3_toggled(bool checked) {
    if (checked){
        result->setFlatShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_smoothEigenMeshRadioButton_3_toggled(bool checked) {
    if (checked){
        result->setSmoothShading();
        mainWindow.updateGlCanvas();
    }
}

void BooleansManager::on_wireframeEigenMeshCheckBox_3_stateChanged(int arg1) {
    result->setWireframe(arg1 == Qt::Checked);
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_plusXButton_clicked() {
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Pointd(ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Pointd(ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Pointd(ui->stepSpinBox->value(), 0, 0));
    }
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_minusXButton_clicked() {
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Pointd(-ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Pointd(-ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Pointd(-ui->stepSpinBox->value(), 0, 0));
    }
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_plusYButton_clicked() {
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Pointd(0, ui->stepSpinBox->value(), 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Pointd(0, ui->stepSpinBox->value(), 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Pointd(0, ui->stepSpinBox->value(), 0));
    }
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_minusYButton_clicked() {
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Pointd(0, -ui->stepSpinBox->value(), 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Pointd(0, -ui->stepSpinBox->value(), 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Pointd(0, -ui->stepSpinBox->value(), 0));
    }
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_plusZButton_clicked() {
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Pointd(0, 0, ui->stepSpinBox->value()));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Pointd(0, 0, ui->stepSpinBox->value()));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Pointd(0, 0, ui->stepSpinBox->value()));
    }
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_minusZButton_clicked() {
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Pointd(0, 0, -ui->stepSpinBox->value()));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Pointd(0, 0, -ui->stepSpinBox->value()));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Pointd(0, 0, -ui->stepSpinBox->value()));
    }
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_rotateButton_clicked() {
    Vec3 axis(ui->axisXSpinBox->value(), ui->axisYSpinBox->value(), ui->axisZSpinBox->value());
    double angle = ui->angleSpinBox->value()*M_PI/180;
    lastAxis = axis;
    lastAngle = angle;
    Eigen::Matrix3d m;
    cg3::getRotationMatrix(axis, angle, m);
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->rotate(m);
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->rotate(m);
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->rotate(m);
    }
    ui->undoRotateButton->setEnabled(true);
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_undoRotateButton_clicked() {
    Eigen::Matrix3d m;
    cg3::getRotationMatrix(-lastAxis, lastAngle, m);
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->rotate(m);
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->rotate(m);
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->rotate(m);
    }
    ui->undoRotateButton->setEnabled(false);
    mainWindow.updateGlCanvas();
}

void BooleansManager::on_makeBox1PushButton_clicked() {
    double min =  std::min(ui->x1SpinBox->value(),ui->y1SpinBox->value());
    min = std::min(min, ui->z1SpinBox->value());
    min /=10;
    setMesh1(EigenMesh(EigenMeshAlgorithms::makeBox(BoundingBox(Pointd(0,0,0), Pointd(ui->x1SpinBox->value(),ui->y1SpinBox->value(),ui->z1SpinBox->value())))));
}

void BooleansManager::on_makeBox2PushButton_clicked() {
    double min =  std::min(ui->x2SpinBox->value(),ui->y2SpinBox->value());
    min = std::min(min, ui->z2SpinBox->value());
    min /=10;
    setMesh2(EigenMesh(EigenMeshAlgorithms::makeBox(BoundingBox(Pointd(0,0,0), Pointd(ui->x2SpinBox->value(),ui->y2SpinBox->value(),ui->z2SpinBox->value())))));
}

void BooleansManager::on_scalePushButton_clicked() {
    Vec3 scaleFactor(ui->scaleXSpinBox->value(), ui->scaleYSpinBox->value(), ui->scaleZSpinBox->value());

    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->scale(scaleFactor);
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->scale(scaleFactor);
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->scale(scaleFactor);
    }
    mainWindow.updateGlCanvas();
}

}

}
