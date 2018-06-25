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
        bool visible) :
    QFrame(parent),
    ui(new Ui::DrawableObjectDrawListManager),
    mw((MainWindow&)*parent),
    object(object),
    subframe(nullptr)
{
    ui->setupUi(this);
    mw.canvas.pushDrawableObject(object, visible);
    ui->checkBox->setText(QString::fromStdString(name));

    const DrawableContainer* cont = dynamic_cast<const DrawableContainer*>(object);
    const DrawableMesh* mesh = dynamic_cast<const DrawableMesh*>(object);

    if (mesh){
        DrawableMeshDrawListManager* submanager =
                new DrawableMeshDrawListManager(&mw, mesh);
        setSubFrame(submanager);
    }
    else if (cont) {
        DrawableContainerDrawListManager* subManager =
                new DrawableContainerDrawListManager(&mw, cont, visible);
        setSubFrame(subManager);
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

void DrawableObjectDrawListManager::setSubFrame(QFrame* frame, bool vis)
{
    subframe = frame;
    subframe->setParent(this);
    ui->checkBox->setTristate();
    layout()->addWidget(frame);
    setSubFrameVisibility(vis);
}

void DrawableObjectDrawListManager::setSubFrameVisibility(bool vis)
{
    if (subframe){
        if (vis){
            ui->checkBox->setCheckState(Qt::PartiallyChecked);
            subframe->setVisible(false);
        }
        else {
            ui->checkBox->setCheckState(Qt::Unchecked);
            subframe->setVisible(false);
        }
    }
}

void DrawableObjectDrawListManager::on_checkBox_stateChanged(int state)
{
    if (!(ui->checkBox->isTristate())){
        mw.canvas.setDrawableObjectVisibility(object, state == Qt::Checked);
    }
    else {
        if (state == Qt::Unchecked){
            mw.canvas.setDrawableObjectVisibility(object, false);
            subframe->setVisible(false);
        }
        else if (state == Qt::PartiallyChecked){
            mw.canvas.setDrawableObjectVisibility(object, true);
            subframe->setVisible(false);
        }
        else {
            mw.canvas.setDrawableObjectVisibility(object, true);
            subframe->setVisible(true);
        }
    }
    mw.canvas.update();
}

} //namespace cg3::viewer
} //namespace cg3
