/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_tetmesh_control_panel.h"
#include "ui_drawable_tetmesh_control_panel.h"

namespace cg3 {
namespace viewer {

DrawableTetMeshControlPanel::DrawableTetMeshControlPanel(QWidget *parent, cino::DrawableTetMesh* mesh) :
    QDockWidget(parent),
    ui(new Ui::DrawableTetMeshControlPanel),
    mw((MainWindow&)*parent),
    mesh(mesh)
{
    ui->setupUi(this);
}

DrawableTetMeshControlPanel::~DrawableTetMeshControlPanel()
{
    delete ui;
}

} //namespace cg3::viewer
} //namespace cg3
