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
        bool visible,
        bool closeButtonVisible) :
    SubManager(parent),
    ui(new Ui::DrawableContainerDrawListManager),
    mw((MainWindow&)*parent),
    cont(cont)
{
    ui->setupUi(this);
    ui->line->setVisible(false);

    for (unsigned int i = 0; i < cont->size(); i++) {
        DrawableObjectDrawListManager* manager =
                new DrawableObjectDrawListManager(&mw, (*cont)[i], cont->objectName(i), visible, closeButtonVisible);
        ui->verticalLayout->addWidget(manager);
        mapSubManagers[(*cont)[i]] = manager;
    }

    connect(cont,
            SIGNAL(drawableContainerPushedObject(
                       const std::string&,
                       bool)),
            this,
            SLOT(addCheckBoxOfDrawableContainer(
                     const std::string&,
                     bool)));

    connect(cont,
            SIGNAL(drawableContainerErasedObject(
                       const DrawableObject*)),
            this,
            SLOT(removeCheckBoxOfDrawableContainer(
                     const DrawableObject*)));

    connect(cont,
            SIGNAL(drawableContainerVisibilityObjectChanged(
                       const DrawableObject*,
                       bool)),
            SLOT(changeVisibilityObject(
                     const DrawableObject*,
                     bool)));
}

DrawableContainerDrawListManager::~DrawableContainerDrawListManager()
{
    delete ui;
}

std::vector<const DrawableObject*> DrawableContainerDrawListManager::selectedDrawableObjects() const
{
    std::vector<const DrawableObject*> vec;
    for (auto iter = mapSubManagers.begin(); iter != mapSubManagers.end(); ++iter){
        if (iter->second->isSelected()){
            vec.push_back(iter->first);
        }
        if (iter->second->isContainer()){
            std::vector<const DrawableObject*> tmp = iter->second->containedSelectedObjects();
            vec.insert(vec.end(), tmp.begin(), tmp.end());
        }
    }
    return vec;
}

void DrawableContainerDrawListManager::updateObjectProperties()
{
    for (auto iter = mapSubManagers.begin(); iter != mapSubManagers.end(); ++iter)
        iter->second->updateObjectProperties();
}

void DrawableContainerDrawListManager::updateManagerProperties()
{
    for (auto iter = mapSubManagers.begin(); iter != mapSubManagers.end(); ++iter)
        iter->second->updateManagerProperties();
}

void DrawableContainerDrawListManager::addCheckBoxOfDrawableContainer(
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
        const DrawableObject* obj)
{

    mw.canvas.deleteDrawableObject(obj);
    ui->verticalLayout->removeWidget(mapSubManagers[obj]);
    mapSubManagers[obj]->setVisible(false);
    mapSubManagers.erase(obj);
    mw.canvas.update();
}

void DrawableContainerDrawListManager::changeVisibilityObject(
        const DrawableObject* obj,
        bool vis)
{
    mw.canvas.setDrawableObjectVisibility(obj, vis);
    mapSubManagers[obj]->setDrawableObjectVisibility(vis);
    mw.canvas.update();
}

void DrawableContainerDrawListManager::on_visibleButton_clicked()
{
    for (const std::pair<const DrawableObject*, DrawableObjectDrawListManager*>& p : mapSubManagers){
        mw.canvas.setDrawableObjectVisibility(p.first, true);
        p.second->setDrawableObjectVisibility(true);
    }
    mw.canvas.update();
}

void DrawableContainerDrawListManager::on_hiddenButton_clicked()
{
    for (const std::pair<const DrawableObject*, DrawableObjectDrawListManager*>& p : mapSubManagers){
        mw.canvas.setDrawableObjectVisibility(p.first, false);
        p.second->setDrawableObjectVisibility(false);
    }
    mw.canvas.update();
}

} //namespace cg3::viewer
} //namespace cg3
