/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container_drawlist_manager.h"
#include "ui_drawable_container_drawlist_manager.h"

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/interfaces/drawable_mesh.h>
#include <cg3/viewer/interfaces/drawable_container.h>
#include <cg3/viewer/internal/drawable_object_drawlist_manager.h>
#include <cg3/viewer/internal/drawable_mesh_drawlist_manager.h>

namespace cg3 {
namespace viewer {

DrawableContainerDrawListManager::DrawableContainerDrawListManager(
        QWidget *parent,
        const DrawableContainer* cont) :
    QFrame(parent),
    ui(new Ui::DrawableContainerDrawListManager),
    mw((MainWindow&)*parent),
    cont(cont)
{
    ui->setupUi(this);
    ui->line->setVisible(false);
    for (unsigned int i = 0; i < cont->size(); i++) {
        DrawableObjectDrawListManager* manager =
                new DrawableObjectDrawListManager(&mw, (*cont)[i], cont->objectName(i));

        const DrawableContainer* cont2 = dynamic_cast<const DrawableContainer*>((*cont)[i]);
        const DrawableMesh* mesh = dynamic_cast<const DrawableMesh*>((*cont)[i]);


        if (mesh){
            DrawableMeshDrawListManager* submanager = new DrawableMeshDrawListManager(&mw, mesh);
            manager->setSubFrame(submanager);
        }
        else  if (cont2) {
            DrawableContainerDrawListManager* subManager = new DrawableContainerDrawListManager(&mw, cont);
            manager->setSubFrame(subManager);
        }

        ui->verticalLayout->addWidget(manager);
        mapSubManagers[(*cont)[i]] = manager;
    }

    connect(cont,
            SIGNAL(drawableContainerPushedObject(
                       const DrawableContainer*,
                       const std::string&,
                       bool)),
            this,
            SLOT(addCheckBoxOfDrawableContainer(
                     const DrawableContainer*,
                     const std::string&,
                     bool)));

    connect(cont,
            SIGNAL(drawableContainerErasedObject
                   (const DrawableContainer*,
                    unsigned int)),
            this,
            SLOT(removeCheckBoxOfDrawableContainer(
                     const DrawableContainer*,
                     unsigned int)));
}

DrawableContainerDrawListManager::~DrawableContainerDrawListManager()
{
    delete ui;
}

} //namespace cg3::viewer
} //namespace cg3
