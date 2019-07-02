/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_mesh_drawlist_manager.h"
#include "ui_drawable_mesh_drawlist_manager.h"

#include <cg3/viewer/interfaces/drawable_mesh.h>
#include <cg3/viewer/interfaces/manipulable_object.h>

namespace cg3 {
namespace viewer {

CG3_INLINE DrawableMeshDrawListManager::DrawableMeshDrawListManager(
        QWidget *parent,
        const DrawableMesh* mesh) :
    SubManager(parent),
    ui(new Ui::DrawableMeshDrawListManager),
	mw((AbstractMainWindow&)*parent),
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

    ui->nVerticesLabel->setText(QString("N. Vertices: ") + QString::number(mesh->numberVertices()));
    ui->nFacesLabel->setText(QString("N. Faces: ") + QString::number(mesh->numberFaces()));

    const ManipulableObject* mobj = dynamic_cast<const ManipulableObject*>(mesh);

    if (!mobj)
        ui->subFrameAxisCheckBox->setVisible(false);

    ls.addSupportedExtension("obj", "ply");
}

CG3_INLINE DrawableMeshDrawListManager::~DrawableMeshDrawListManager()
{
    delete ui;
}

CG3_INLINE void DrawableMeshDrawListManager::updateObjectProperties()
{
	if (ui->pointsRadioButton->isChecked()) {
        mesh->setPointsShading();
	}
	else if (ui->flatRadioButton->isChecked()) {
        mesh->setFlatShading();
	}
	else {
        mesh->setSmoothShading();
	}
    mesh->setWireframe(ui->wireframeCheckBox->isChecked());
    mesh->setVisibleBoundingBox(ui->bboxCheckBox->isChecked());
	if (ui->vColorRadioButton->isChecked()) {
        mesh->setEnableVertexColor();
	}
	else {
        mesh->setEnableTriangleColor();	
	}
	mw.updateCanvas();
}

CG3_INLINE void DrawableMeshDrawListManager::updateManagerProperties()
{
    ui->pointsRadioButton->setChecked(mesh->isPointShadingEnabled());
    ui->flatRadioButton->setChecked(mesh->isFlatShadingEnabled());
    ui->smoothRadioButton->setChecked(mesh->isSmoothShadingEnabled());
    ui->wireframeCheckBox->setChecked(mesh->isWireframeEnabled());
    ui->bboxCheckBox->setChecked(mesh->isBboxEnabled());
    ui->vColorRadioButton->setChecked(mesh->isVertexColorEnabled());
    ui->tColorRadioButton->setChecked(mesh->isTriangleColorEnabled());
}

CG3_INLINE void DrawableMeshDrawListManager::on_pointsRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setPointsShading();
		mw.updateCanvas();
    }
}

CG3_INLINE void DrawableMeshDrawListManager::on_flatRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setFlatShading();
		mw.updateCanvas();
    }
}

CG3_INLINE void DrawableMeshDrawListManager::on_smoothRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setSmoothShading();
		mw.updateCanvas();
    }
}

CG3_INLINE void DrawableMeshDrawListManager::on_wireframeCheckBox_stateChanged(int arg1)
{
    mesh->setWireframe(arg1 == Qt::Checked);
	mw.updateCanvas();
}

CG3_INLINE void DrawableMeshDrawListManager::on_bboxCheckBox_stateChanged(int arg1)
{
    mesh->setVisibleBoundingBox(arg1 == Qt::Checked);
	mw.updateCanvas();
}

CG3_INLINE void DrawableMeshDrawListManager::on_vColorRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setEnableVertexColor();
		mw.updateCanvas();
    }
}

CG3_INLINE void DrawableMeshDrawListManager::on_tColorRadioButton_toggled(bool checked)
{
    if (checked){
        mesh->setEnableTriangleColor();
		mw.updateCanvas();
    }
}

CG3_INLINE void DrawableMeshDrawListManager::on_savePushButton_clicked()
{
    std::string ext;
    std::string filename = ls.saveDialog("Save Mesh", ext);
    if (filename != ""){
        if (ext == "obj"){
            mesh->saveOnObj(filename);
        }
        else{
            mesh->saveOnPly(filename);
        }
    }
}

CG3_INLINE void DrawableMeshDrawListManager::on_subFrameAxisCheckBox_stateChanged(int arg1)
{
    ((ManipulableObject*)mesh)->setDrawRelativeAxis(arg1 == Qt::Checked);
}

CG3_INLINE void DrawableMeshDrawListManager::on_wireframeWidthSlider_valueChanged(int value)
{
    mesh->setWireframeWidth(value);
	mw.updateCanvas();
}

CG3_INLINE void DrawableMeshDrawListManager::on_pointWidthSlider_valueChanged(int value)
{
    mesh->setPointWidth(value);
	mw.updateCanvas();
}


} //namespace cg3::viewer
} //namespace cg3
