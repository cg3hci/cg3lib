/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container_drawlist_manager.h"
#include "ui_drawable_container_drawlist_manager.h"

namespace cg3 {
namespace viewer {

DrawableContainerDrawListManager::DrawableContainerDrawListManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DrawableContainerDrawListManager)
{
    ui->setupUi(this);
}

DrawableContainerDrawListManager::~DrawableContainerDrawListManager()
{
    delete ui;
}

} //namespace cg3::viewer
} //namespace cg3
