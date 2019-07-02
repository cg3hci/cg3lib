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
#include <cg3/geometry/transformations3.h>
#include <cg3/meshes/eigenmesh/algorithms/eigenmesh_algorithms.h>
#include <cg3/libigl/booleans.h>

namespace cg3 {
namespace viewer {

CG3_INLINE BooleansManager::BooleansManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BooleansManager),
	mainWindow((cg3::viewer::AbstractMainWindow&)*parent),
    result(nullptr)
{
    meshes.resize(2);
    meshes[0] = meshes[1] = nullptr;
    ui->setupUi(this);
    objls.addSupportedExtension("obj");
}

CG3_INLINE BooleansManager::~BooleansManager()
{
    delete ui;
    for (unsigned int i = 0; i < meshes.size(); i++) {
        if (meshes[i]!=nullptr){
            mainWindow.deleteDrawableObject(meshes[i]);
            delete meshes[i];
        }
    }
}

CG3_INLINE void BooleansManager::setButtonsMeshLoaded(bool b)
{
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

CG3_INLINE void BooleansManager::setButtonsMeshLoaded_2(bool b)
{
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

CG3_INLINE void BooleansManager::setButtonsResultLoaded(bool b)
{
    ui->clearEigenMeshButton_3->setEnabled(b);
    ui->saveEigenMeshButton_3->setEnabled(b);
    ui->pointsEigenMeshRadioButton_3->setEnabled(b);
    ui->flatEigenMeshRadioButton_3->setEnabled(b);
    ui->smoothEigenMeshRadioButton_3->setEnabled(b);
    ui->wireframeEigenMeshCheckBox_3->setEnabled(b);
    ui->wireframeEigenMeshCheckBox_3->setChecked(false);
    ui->smoothEigenMeshRadioButton_3->setChecked(true);
}

CG3_INLINE void BooleansManager::setMesh1(const EigenMesh& m)
{
    if (meshes[0] != nullptr){
        mainWindow.deleteDrawableObject(meshes[0]);
        delete meshes[0];
    }
    meshes[0] = new DrawableEigenMesh(m);
    mainWindow.pushDrawableObject(meshes[0], "EigenMesh");
    setButtonsMeshLoaded(true);
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::setMesh2(const EigenMesh& m)
{
    if (meshes[1] != nullptr){
        mainWindow.deleteDrawableObject(meshes[1]);
        delete meshes[1];
    }
    meshes[1] = new DrawableEigenMesh(m);
    mainWindow.pushDrawableObject(meshes[1], "EigenMesh");
    setButtonsMeshLoaded_2(true);
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_loadEigenMeshButton_clicked()
{
    std::string filename = objls.loadDialog("Load Mesh 1");
    if (filename != "") {
        DrawableEigenMesh* mesh = new DrawableEigenMesh();
        mesh->loadFromObj(filename);
        //mesh->readFromObj(filename.toStdString());
        mainWindow.pushDrawableObject(mesh, filename.substr(filename.find_last_of("/") + 1));
        setButtonsMeshLoaded(true);
		mainWindow.updateCanvas();
        if (meshes[0] != nullptr){
            mainWindow.deleteDrawableObject(meshes[0]);
            delete meshes[0];
        }
        meshes[0] = mesh;
    }
}

CG3_INLINE void BooleansManager::on_clearEigenMeshButton_clicked()
{
    setButtonsMeshLoaded(false);
    mainWindow.deleteDrawableObject(meshes[0]);
    delete meshes[0];
    meshes[0] = nullptr;
}

CG3_INLINE void BooleansManager::on_saveEigenMeshButton_clicked()
{
    std::string filename = objls.saveDialog("Save Mesh 1");

    std::cout << "save: " << filename << std::endl;

    meshes[0]->saveOnObj(filename);

}

CG3_INLINE void BooleansManager::on_setFromResultButton_clicked()
{
    if (result != nullptr){
        if (meshes[0] != nullptr){
            mainWindow.deleteDrawableObject(meshes[0]);
            delete meshes[0];
        }
        meshes[0] = new DrawableEigenMesh(*result);
        mainWindow.pushDrawableObject(meshes[0], "Result");
        setButtonsMeshLoaded(true);
		mainWindow.updateCanvas();

    }
}

CG3_INLINE void BooleansManager::on_pointsEigenMeshRadioButton_toggled(bool checked)
{
    if (checked){
        meshes[0]->setPointsShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_flatEigenMeshRadioButton_toggled(bool checked)
{
    if (checked){
        meshes[0]->setFlatShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_smoothEigenMeshRadioButton_toggled(bool checked)
{
    if (checked){
        meshes[0]->setSmoothShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_wireframeEigenMeshCheckBox_stateChanged(int arg1)
{
    meshes[0]->setWireframe(arg1 == Qt::Checked);
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_loadEigenMeshButton_2_clicked()
{
    std::string filename = objls.loadDialog("Load Mesh 2");
    if (filename != "") {
        DrawableEigenMesh* mesh = new DrawableEigenMesh();
        mesh->loadFromObj(filename);
        mainWindow.pushDrawableObject(mesh, filename.substr(filename.find_last_of("/") + 1));
        setButtonsMeshLoaded_2(true);
		mainWindow.updateCanvas();
        if (meshes[1] != nullptr){
            mainWindow.deleteDrawableObject(meshes[1]);
            delete meshes[1];
        }
        meshes[1] = mesh;
    }
}

CG3_INLINE void BooleansManager::on_clearEigenMeshButton_2_clicked()
{
    setButtonsMeshLoaded_2(false);
    mainWindow.deleteDrawableObject(meshes[1]);
    delete meshes[1];
    meshes[1] = nullptr;
}

CG3_INLINE void BooleansManager::on_saveEigenMeshButton_2_clicked()
{
    std::string filename = objls.saveDialog("Save Mesh 2");

    std::cout << "save: " << filename << std::endl;

    meshes[1]->saveOnObj(filename);
}

CG3_INLINE void BooleansManager::on_setFromResultButton_2_clicked()
{
    if (result != nullptr){
        if (meshes[1] != nullptr){
            mainWindow.deleteDrawableObject(meshes[1]);
            delete meshes[1];
        }
        meshes[1] = new DrawableEigenMesh(*result);
        mainWindow.pushDrawableObject(meshes[1], "Result");
        setButtonsMeshLoaded(true);
		mainWindow.updateCanvas();

    }
}

CG3_INLINE void BooleansManager::on_pointsEigenMeshRadioButton_2_toggled(bool checked)
{
    if (checked){
        meshes[1]->setPointsShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_flatEigenMeshRadioButton_2_toggled(bool checked)
{
    if (checked){
        meshes[1]->setFlatShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_smoothEigenMeshRadioButton_2_toggled(bool checked)
{
    if (checked){
        meshes[1]->setSmoothShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_wireframeEigenMeshCheckBox_2_stateChanged(int arg1)
{
    meshes[1]->setWireframe(arg1 == Qt::Checked);
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_intersectionButton_clicked()
{
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteDrawableObject(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        libigl::intersection(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushDrawableObject(result, "Intersection");
		mainWindow.updateCanvas();
        setButtonsResultLoaded(true);
    }
}

CG3_INLINE void BooleansManager::on_differenceButton_clicked()
{
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteDrawableObject(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        libigl::difference(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushDrawableObject(result, "Difference");
		mainWindow.updateCanvas();
        setButtonsResultLoaded(true);
    }
}

CG3_INLINE void BooleansManager::on_unionButton_clicked()
{
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteDrawableObject(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        libigl::union_(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushDrawableObject(result, "Union");
		mainWindow.updateCanvas();
        setButtonsResultLoaded(true);
    }
}

CG3_INLINE void BooleansManager::on_mergePushButton_clicked()
{
    if (meshes[0] != nullptr && meshes[1] != nullptr){
        if (result != nullptr) {
            mainWindow.deleteDrawableObject(result);
            delete result;
        }
        result = new DrawableEigenMesh();
        EigenMesh::merge(*result, *(meshes[0]), *(meshes[1]));
        mainWindow.pushDrawableObject(result, "Merge");
		mainWindow.updateCanvas();
        setButtonsResultLoaded(true);
    }
}

CG3_INLINE void BooleansManager::on_clearEigenMeshButton_3_clicked()
{
    mainWindow.deleteDrawableObject(result);
    delete result;
    result = nullptr;
    setButtonsResultLoaded(false);
}

CG3_INLINE void BooleansManager::on_saveEigenMeshButton_3_clicked()
{
    std::string filename = objls.saveDialog("Save Result");

    std::cout << "save: " << filename << std::endl;

    result->saveOnObj(filename);

}

CG3_INLINE void BooleansManager::on_pointsEigenMeshRadioButton_3_toggled(bool checked)
{
    if (checked){
        result->setPointsShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_flatEigenMeshRadioButton_3_toggled(bool checked)
{
    if (checked){
        result->setFlatShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_smoothEigenMeshRadioButton_3_toggled(bool checked)
{
    if (checked){
        result->setSmoothShading();
		mainWindow.updateCanvas();
    }
}

CG3_INLINE void BooleansManager::on_wireframeEigenMeshCheckBox_3_stateChanged(int arg1)
{
    result->setWireframe(arg1 == Qt::Checked);
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_plusXButton_clicked()
{
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Point3d(ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Point3d(ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Point3d(ui->stepSpinBox->value(), 0, 0));
    }
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_minusXButton_clicked()
{
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Point3d(-ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Point3d(-ui->stepSpinBox->value(), 0, 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Point3d(-ui->stepSpinBox->value(), 0, 0));
    }
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_plusYButton_clicked()
{
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Point3d(0, ui->stepSpinBox->value(), 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Point3d(0, ui->stepSpinBox->value(), 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Point3d(0, ui->stepSpinBox->value(), 0));
    }
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_minusYButton_clicked()
{
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Point3d(0, -ui->stepSpinBox->value(), 0));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Point3d(0, -ui->stepSpinBox->value(), 0));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Point3d(0, -ui->stepSpinBox->value(), 0));
    }
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_plusZButton_clicked()
{
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Point3d(0, 0, ui->stepSpinBox->value()));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Point3d(0, 0, ui->stepSpinBox->value()));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Point3d(0, 0, ui->stepSpinBox->value()));
    }
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_minusZButton_clicked()
{
    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->translate(Point3d(0, 0, -ui->stepSpinBox->value()));
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->translate(Point3d(0, 0, -ui->stepSpinBox->value()));
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->translate(Point3d(0, 0, -ui->stepSpinBox->value()));
    }
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_rotateButton_clicked()
{
    Vec3d axis(ui->axisXSpinBox->value(), ui->axisYSpinBox->value(), ui->axisZSpinBox->value());
    double angle = ui->angleSpinBox->value()*M_PI/180;
    lastAxis = axis;
    lastAngle = angle;
    Eigen::Matrix3d m;
    cg3::rotationMatrix(axis, angle, m);
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
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_undoRotateButton_clicked()
{
    Eigen::Matrix3d m;
    cg3::rotationMatrix(-lastAxis, lastAngle, m);
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
	mainWindow.updateCanvas();
}

CG3_INLINE void BooleansManager::on_makeBox1PushButton_clicked()
{
    double min =  std::min(ui->x1SpinBox->value(),ui->y1SpinBox->value());
    min = std::min(min, ui->z1SpinBox->value());
    min /=10;
    setMesh1(EigenMesh(EigenMeshAlgorithms::makeBox(BoundingBox3(Point3d(0,0,0), Point3d(ui->x1SpinBox->value(),ui->y1SpinBox->value(),ui->z1SpinBox->value())))));
}

CG3_INLINE void BooleansManager::on_makeBox2PushButton_clicked()
{
    double min =  std::min(ui->x2SpinBox->value(),ui->y2SpinBox->value());
    min = std::min(min, ui->z2SpinBox->value());
    min /=10;
    setMesh2(EigenMesh(EigenMeshAlgorithms::makeBox(BoundingBox3(Point3d(0,0,0), Point3d(ui->x2SpinBox->value(),ui->y2SpinBox->value(),ui->z2SpinBox->value())))));
}

CG3_INLINE void BooleansManager::on_scalePushButton_clicked()
{
    Vec3d scaleFactor(ui->scaleXSpinBox->value(), ui->scaleYSpinBox->value(), ui->scaleZSpinBox->value());

    if (ui->mesh1CheckBox->isChecked() && meshes[0] != nullptr){
        meshes[0]->scale(scaleFactor);
    }
    if (ui->mesh2CheckBox->isChecked() && meshes[1] != nullptr){
        meshes[1]->scale(scaleFactor);
    }
    if (ui->resultCheckBox->isChecked() && result != nullptr){
        result->scale(scaleFactor);
    }
	mainWindow.updateCanvas();
}

} //namespace cg3::viewer
} //namespace cg3
