/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "mesh_drawlist_manager.h"
#include "ui_mesh_drawlist_manager.h"

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/interfaces/drawable_mesh.h>

namespace cg3 {
namespace viewer {

MeshDrawListManager::MeshDrawListManager(QWidget *parent, const DrawableMesh* mesh) :
    QFrame(parent),
    ui(new Ui::MeshDrawListManager),
    mw((MainWindow&)*parent),
    mesh(mesh)
{
    ui->setupUi(this);
    if (mesh->isPointShadingEnabled())
        ui->pointsRadioButton->toggle();
    else if (mesh->isFlatShadingEnabled())
        ui->flatRadioButton->toggle();
    else
        ui->smoothRadioButton->toggle();
    ui->wireframeCheckBox->setChecked(mesh->isWireframeEnabled());
    ui->bboxCheckBox->setChecked(mesh->isBboxEnabled());
    if (mesh->isTriangleColorEnabled())
        ui->tColorRadioButton->toggle();
    else
        ui->vColorRadioButton->toggle();
}

MeshDrawListManager::~MeshDrawListManager()
{
    delete ui;
}

void MeshDrawListManager::on_pointsRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setPointsShading();
        mw.canvas.update();
    }
}

void MeshDrawListManager::on_flatRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setFlatShading();
        mw.canvas.update();
    }
}

void MeshDrawListManager::on_smoothRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setSmoothShading();
        mw.canvas.update();
    }
}

void MeshDrawListManager::on_wireframeCheckBox_stateChanged(int arg1)
{
    mesh->setWireframe(arg1 == Qt::Checked);
    mw.canvas.update();
}

void MeshDrawListManager::on_bboxCheckBox_stateChanged(int arg1)
{
    mesh->setVisibleBoundingBox(arg1 == Qt::Checked);
    mw.canvas.update();
}

void MeshDrawListManager::on_vColorRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setEnableVertexColor();
        mw.canvas.update();
    }
}

void MeshDrawListManager::on_tColorRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setEnableTriangleColor();
        mw.canvas.update();
    }
}


} //namespace cg3::viewer
} //namespace cg3
