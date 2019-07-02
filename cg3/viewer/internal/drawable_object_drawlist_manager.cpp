/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_object_drawlist_manager.h"
#include "ui_drawable_object_drawlist_manager.h"

#include <cg3/viewer/interfaces/drawable_mesh.h>
#include <cg3/viewer/interfaces/drawable_container.h>
#include <cg3/viewer/interfaces/manipulable_object.h>
#include <cg3/viewer/internal/drawable_container_drawlist_manager.h>
#include <cg3/viewer/internal/drawable_mesh_drawlist_manager.h>
#include <cg3/viewer/internal/manipulable_object_drawlist_manager.h>

namespace cg3 {
namespace viewer {

CG3_INLINE DrawableObjectDrawListManager::DrawableObjectDrawListManager(
        QWidget *parent,
        const DrawableObject* object,
        const std::string& name,
        bool visible,
        bool closeButtonVisible) :
    QFrame(parent),
    ui(new Ui::DrawableObjectDrawListManager),
	mw((AbstractMainWindow&)*parent),
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

    ui->checkBox->setChecked(visible);
    if (mesh){
        DrawableMeshDrawListManager* submanager =
                new DrawableMeshDrawListManager(&mw, mesh);
        setSubFrame(submanager, false);
        ui->objectType->setText("Mesh");
    }
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

CG3_INLINE DrawableObjectDrawListManager::~DrawableObjectDrawListManager()
{
    delete ui;
}

CG3_INLINE void DrawableObjectDrawListManager::setDrawableObjectVisibility(bool vis, bool alsoSubframe)
{
    ui->checkBox->setChecked(vis);
    if (alsoSubframe)
        setSubFrameVisibility(vis);
}

CG3_INLINE void DrawableObjectDrawListManager::setDrawableObjectName(const std::string& newName)
{
    ui->objectName->setText(QString::fromStdString(newName));
}

CG3_INLINE std::string DrawableObjectDrawListManager::drawableObjectName() const
{
    return  ui->objectName->text().toStdString();
}

CG3_INLINE bool DrawableObjectDrawListManager::isContainer() const
{
    return container;
}

/**
 * @brief Allows to update the properties of the DrawableObject according to the properties
 * setted in the user interface.
 */
CG3_INLINE void DrawableObjectDrawListManager::updateObjectProperties()
{
	mw.setDrawableObjectVisibility(object, ui->checkBox->isChecked());
    if (subframe)
        subframe->updateObjectProperties();
}

/**
 * @brief Allows to update the properties setted in the user interface according to the
 * properties of the DrawableObject.
 */
CG3_INLINE void DrawableObjectDrawListManager::updateManagerProperties()
{
    if (object->isVisible() == ! ui->checkBox->isChecked())
        setDrawableObjectVisibility(object->isVisible());
    if (subframe)
        subframe->updateManagerProperties();
}

CG3_INLINE void DrawableObjectDrawListManager::toggleSelection()
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

CG3_INLINE void DrawableObjectDrawListManager::setSelection(bool b)
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

CG3_INLINE bool DrawableObjectDrawListManager::isSelected() const
{
    return selected;
}

CG3_INLINE std::vector<const DrawableObject*> DrawableObjectDrawListManager::containedSelectedObjects() const
{
    std::vector<const DrawableObject*> vec;
    if (!container)
        return vec;
    DrawableContainerDrawListManager* contFrame = (DrawableContainerDrawListManager*)subframe;
    return contFrame->selectedDrawableObjects();

}

CG3_INLINE void DrawableObjectDrawListManager::setSubFrame(SubManager* frame, bool vis)
{
    subframe = frame;
    subframe->setParent(this);
    layout()->addWidget(frame);
    setSubFrameVisibility(vis);
}

CG3_INLINE void DrawableObjectDrawListManager::setSubFrameVisibility(bool vis)
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

CG3_INLINE void DrawableObjectDrawListManager::on_checkBox_stateChanged(int state)
{
	mw.setDrawableObjectVisibility(object, state == Qt::Checked);
	mw.updateCanvas();
}

CG3_INLINE void DrawableObjectDrawListManager::on_closePushButton_clicked()
{
    mw.deleteDrawableObject(object);
}

CG3_INLINE void DrawableObjectDrawListManager::on_subFrameCheckBox_stateChanged(int state)
{
    subframe->setVisible(state == Qt::Checked);
}

CG3_INLINE void DrawableObjectDrawListManager::on_objectName_clicked()
{
    toggleSelection();
}

CG3_INLINE void DrawableObjectDrawListManager::on_objectType_clicked()
{
    toggleSelection();
}

} //namespace cg3::viewer
} //namespace cg3
