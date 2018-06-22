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
    object(object)
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

void DrawableObjectDrawListManager::on_checkBox_stateChanged(int arg1)
{
    object->setVisibility(arg1 == Qt::Checked);
}

} //namespace cg3::viewer
} //namespace cg3
