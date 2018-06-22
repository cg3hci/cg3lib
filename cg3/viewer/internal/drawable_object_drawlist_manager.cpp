/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_object_drawlist_manager.h"
#include "ui_drawable_object_drawlist_manager.h"

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/interfaces/drawable_object.h>

namespace cg3 {
namespace viewer {

DrawableObjectDrawListManager::DrawableObjectDrawListManager(
        QWidget *parent,
        const DrawableObject* object,
        const std::string& name) :
    QFrame(parent),
    ui(new Ui::DrawableObjectDrawListManager),
    mw((MainWindow&)*parent),
    object(object),
    subframe(nullptr)
{
    ui->setupUi(this);
    ui->checkBox->setText(QString::fromStdString(name));
    ui->checkBox->setChecked(object->isVisible());
}

DrawableObjectDrawListManager::~DrawableObjectDrawListManager()
{
    delete ui;
}

void DrawableObjectDrawListManager::setDrawableObjectVisibility(bool vis)
{
    ui->checkBox->setCheckable(vis);
}

void DrawableObjectDrawListManager::setNameCheckBox(const std::string& newName)
{
    ui->checkBox->setText(QString::fromStdString(newName));
}

void DrawableObjectDrawListManager::setSubFrame(QFrame* frame)
{
    subframe = frame;
    subframe->setParent(this);
    ui->checkBox->setTristate();
    layout()->addWidget(frame);
}

void DrawableObjectDrawListManager::on_checkBox_stateChanged(int state)
{
    if (!(ui->checkBox->isTristate())){
        object->setVisibility(state == Qt::Checked);
    }
    else {
        if (state == Qt::Unchecked){
            object->setVisibility(false);
            subframe->setVisible(false);
        }
        else if (state == Qt::PartiallyChecked){
            object->setVisibility(true);
            subframe->setVisible(false);
        }
        else {
            object->setVisibility(true);
            subframe->setVisible(true);
        }
    }
    mw.canvas.update();
}

} //namespace cg3::viewer
} //namespace cg3
