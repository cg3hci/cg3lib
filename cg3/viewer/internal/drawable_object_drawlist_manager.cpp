/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_object_drawlist_manager.h"
#include "ui_drawable_object_drawlist_manager.h"

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/interfaces/drawable_mesh.h>
#include <cg3/viewer/interfaces/drawable_container.h>
#include <cg3/viewer/interfaces/manipulable_object.h>
#include <cg3/viewer/internal/drawable_container_drawlist_manager.h>
#include <cg3/viewer/internal/drawable_mesh_drawlist_manager.h>
#include <cg3/viewer/internal/manipulable_object_drawlist_manager.h>

#ifdef CG3_CINOLIB_DEFINED
#include <cg3/viewer/drawable_objects/drawable_tetmesh.h>
#include <cg3/viewer/internal/drawable_tetmesh_drawlist_manager.h>
#endif

namespace cg3 {
namespace viewer {

DrawableObjectDrawListManager::DrawableObjectDrawListManager(
        QWidget *parent,
        const DrawableObject* object,
        const std::string& name,
        bool visible,
        bool closeButtonVisible) :
    QFrame(parent),
    ui(new Ui::DrawableObjectDrawListManager),
    mw((MainWindow&)*parent),
    object(object),
    subframe(nullptr),
    selected(false),
    container(false)
{
    ui->setupUi(this);
    ui->objectName->setText(QString::fromStdString(name));

    if (!closeButtonVisible)
        ui->closePushButton->setVisible(false);

    //casts
    const DrawableContainer* cont = dynamic_cast<const DrawableContainer*>(object);
    const DrawableMesh* mesh = dynamic_cast<const DrawableMesh*>(object);
    const ManipulableObject* mobj = dynamic_cast<const ManipulableObject*>(object);
    #ifdef CG3_CINOLIB_DEFINED
    const cino::DrawableTetMesh* tetmesh = dynamic_cast<const cino::DrawableTetMesh*>(object);
    #endif

    ui->checkBox->setChecked(visible);
    if (mesh){
        DrawableMeshDrawListManager* submanager =
                new DrawableMeshDrawListManager(&mw, mesh);
        setSubFrame(submanager, false);
        ui->objectType->setText("Mesh");
    }
    #ifdef CG3_CINOLIB_DEFINED
    else if (tetmesh) {
        cino::DrawableTetMesh* mesh = const_cast<cino::DrawableTetMesh*>(tetmesh);
        DrawableTetMeshDrawListManager* subManager =
                new DrawableTetMeshDrawListManager(&mw, mesh);
        setSubFrame(subManager, false);
        ui->objectType->setText("TetMesh");
    }
    #endif
    else if (cont) {
        DrawableContainerDrawListManager* subManager =
                new DrawableContainerDrawListManager(&mw, cont/*, visible*/);
        setSubFrame(subManager, false);
        container = true;
        ui->objectType->setText("Container");
    }
    else if (mobj){
        ManipulableFormDrawlistManager* subManager =
                new ManipulableFormDrawlistManager(&mw, mobj);
        setSubFrame(subManager, false);
        ui->objectType->setText("Manipulable Object");
    }
    else{
        ui->subFrameCheckBox->setVisible(false);
        ui->objectType->setText("Object");
    }
}

DrawableObjectDrawListManager::~DrawableObjectDrawListManager()
{
    delete ui;
}

void DrawableObjectDrawListManager::setDrawableObjectVisibility(bool vis, bool alsoSubframe)
{
    ui->checkBox->setChecked(vis);
    if (alsoSubframe)
        setSubFrameVisibility(vis);
}

void DrawableObjectDrawListManager::setDrawableObjectName(const std::string& newName)
{
    ui->objectName->setText(QString::fromStdString(newName));
}

std::string DrawableObjectDrawListManager::drawableObjectName() const
{
    return  ui->objectName->text().toStdString();
}

bool DrawableObjectDrawListManager::isContainer() const
{
    return container;
}

/**
 * @brief Allows to update the properties of the DrawableObject according to the properties
 * setted in the user interface.
 */
void DrawableObjectDrawListManager::updateObjectProperties()
{
    mw.canvas.setDrawableObjectVisibility(object, ui->checkBox->isChecked());
    if (subframe)
        subframe->updateObjectProperties();
}

/**
 * @brief Allows to update the properties setted in the user interface according to the
 * properties of the DrawableObject.
 */
void DrawableObjectDrawListManager::updateManagerProperties()
{
    if (object->isVisible() == ! ui->checkBox->isChecked())
        setDrawableObjectVisibility(object->isVisible());
    if (subframe)
        subframe->updateManagerProperties();
}

void DrawableObjectDrawListManager::toggleSelection()
{
    if (selected){
        selected = false;
        ui->frame->setStyleSheet("");
    }
    else {
        selected = true;
        ui->frame->setStyleSheet("background-color:yellow;");
    }
}

void DrawableObjectDrawListManager::setSelection(bool b)
{
    if (b){
        selected = true;
        ui->frame->setStyleSheet("background-color:yellow;");
    }
    else {
        selected = false;
        ui->frame->setStyleSheet("");
    }
}

bool DrawableObjectDrawListManager::isSelected() const
{
    return selected;
}

std::vector<const DrawableObject*> DrawableObjectDrawListManager::containedSelectedObjects() const
{
    std::vector<const DrawableObject*> vec;
    if (!container)
        return vec;
    DrawableContainerDrawListManager* contFrame = (DrawableContainerDrawListManager*)subframe;
    return contFrame->selectedDrawableObjects();

}

void DrawableObjectDrawListManager::setSubFrame(SubManager* frame, bool vis)
{
    subframe = frame;
    subframe->setParent(this);
    layout()->addWidget(frame);
    setSubFrameVisibility(vis);
}

void DrawableObjectDrawListManager::setSubFrameVisibility(bool vis)
{
    if (subframe){
        if (vis){
            ui->subFrameCheckBox->setCheckState(Qt::Checked);
        }
        else {
            ui->subFrameCheckBox->setCheckState(Qt::Unchecked);
        }
        subframe->setVisible(vis);
    }
}

void DrawableObjectDrawListManager::on_checkBox_stateChanged(int state)
{
    mw.canvas.setDrawableObjectVisibility(object, state == Qt::Checked);
    mw.canvas.update();
}

void DrawableObjectDrawListManager::on_closePushButton_clicked()
{
    mw.deleteDrawableObject(object);
}

void DrawableObjectDrawListManager::on_subFrameCheckBox_stateChanged(int state)
{
    subframe->setVisible(state == Qt::Checked);
}

void DrawableObjectDrawListManager::on_objectName_clicked()
{
    toggleSelection();
}

void DrawableObjectDrawListManager::on_objectType_clicked()
{
    toggleSelection();
}

} //namespace cg3::viewer
} //namespace cg3
