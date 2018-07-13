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
#include <cg3/viewer/internal/drawable_container_drawlist_manager.h>
#include <cg3/viewer/internal/drawable_mesh_drawlist_manager.h>

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
    subframe(nullptr)
{
    ui->setupUi(this);
    ui->checkBox->setText(QString::fromStdString(name));

    if (!closeButtonVisible)
        ui->closePushButton->setVisible(false);
    const DrawableContainer* cont = dynamic_cast<const DrawableContainer*>(object);
    const DrawableMesh* mesh = dynamic_cast<const DrawableMesh*>(object);
    ui->checkBox->setChecked(visible);
    if (mesh){
        DrawableMeshDrawListManager* submanager =
                new DrawableMeshDrawListManager(&mw, mesh);
        setSubFrame(submanager, false);
    }
    else if (cont) {
        DrawableContainerDrawListManager* subManager =
                new DrawableContainerDrawListManager(&mw, cont/*, visible*/);
        setSubFrame(subManager, false);
    }
    else{
        ui->subFrameCheckBox->setVisible(false);
    }
}

DrawableObjectDrawListManager::~DrawableObjectDrawListManager()
{
    delete ui;
}

void DrawableObjectDrawListManager::setDrawableObjectVisibility(bool vis)
{
    ui->checkBox->setChecked(vis);
    setSubFrameVisibility(vis);
}

void DrawableObjectDrawListManager::setNameCheckBox(const std::string& newName)
{
    ui->checkBox->setText(QString::fromStdString(newName));
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

} //namespace cg3::viewer
} //namespace cg3


