/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_tetmesh_drawlist_manager.h"
#include "ui_drawable_tetmesh_drawlist_manager.h"

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/drawable_objects/drawable_tetmesh.h>

namespace cg3 {
namespace viewer {

DrawableTetMeshDrawListManager::DrawableTetMeshDrawListManager(
        QWidget *parent,
        cino::DrawableTetMesh* mesh) :
    SubManager(parent),
    ui(new Ui::DrawableTetMeshDrawListManager),
    mw((MainWindow&)*parent),
    mesh(mesh),
    panel(parent, mesh)
{
    panel.setParent(nullptr);
    ui->setupUi(this);
}

DrawableTetMeshDrawListManager::~DrawableTetMeshDrawListManager()
{
    delete ui;
}

void DrawableTetMeshDrawListManager::updateObjectProperties()
{
}

void DrawableTetMeshDrawListManager::updateManagerProperties()
{
}

void DrawableTetMeshDrawListManager::on_pointsRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->show_mesh_points();
        mw.canvas.update();
    }
}

void DrawableTetMeshDrawListManager::on_flatRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->show_mesh_flat();
        mw.canvas.update();
    }
}

void DrawableTetMeshDrawListManager::on_smoothRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->show_mesh_smooth();
        mw.canvas.update();
    }
}

void DrawableTetMeshDrawListManager::on_wireframeCheckBox_stateChanged(int arg1)
{
    mesh->show_out_wireframe(arg1 == Qt::Checked);
    mw.canvas.update();
}

void DrawableTetMeshDrawListManager::on_showPushButton_clicked()
{
    panel.show();
}

} //namespace cg3::viewer
} //namespace cg3
