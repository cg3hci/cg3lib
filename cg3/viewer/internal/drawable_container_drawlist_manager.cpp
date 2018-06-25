/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_container_drawlist_manager.h"
#include "ui_drawable_container_drawlist_manager.h"

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/internal/drawable_object_drawlist_manager.h>
#include <cg3/viewer/interfaces/drawable_container.h>

namespace cg3 {
namespace viewer {

DrawableContainerDrawListManager::DrawableContainerDrawListManager(
        QWidget *parent,
        const DrawableContainer* cont,
        bool visible) :
    QFrame(parent),
    ui(new Ui::DrawableContainerDrawListManager),
    mw((MainWindow&)*parent),
    cont(cont)
{
    ui->setupUi(this);
    ui->line->setVisible(false);

    for (unsigned int i = 0; i < cont->size(); i++) {
        DrawableObjectDrawListManager* manager =
                new DrawableObjectDrawListManager(&mw, (*cont)[i], cont->objectName(i), visible);

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
                    const DrawableObject*)),
            this,
            SLOT(removeCheckBoxOfDrawableContainer(
                     const DrawableContainer*,
                     const DrawableObject*)));
}

DrawableContainerDrawListManager::~DrawableContainerDrawListManager()
{
    delete ui;
}

void DrawableContainerDrawListManager::addCheckBoxOfDrawableContainer(
        const DrawableContainer* cont,
        const std::string& name,
        bool visible)
{
    unsigned int elem = cont->size()-1;
    DrawableObjectDrawListManager* manager =
            new DrawableObjectDrawListManager(&mw, (*cont)[elem], name, visible);

    ui->verticalLayout->addWidget(manager);
    mapSubManagers[(*cont)[elem]] = manager;
}

void DrawableContainerDrawListManager::removeCheckBoxOfDrawableContainer(
        const DrawableContainer* cont,
        const DrawableObject* obj)
{
    //if (cont == this) {
        mw.canvas.deleteDrawableObject(obj);
        ui->verticalLayout->removeWidget(mapSubManagers[obj]);
        mapSubManagers[obj]->setVisible(false);
        mapSubManagers.erase(obj);
        mw.canvas.update();
    //}
}

} //namespace cg3::viewer
} //namespace cg3
