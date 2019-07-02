/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_CONTAINER_DRAWLIST_MANAGER_H
#define CG3_DRAWABLE_CONTAINER_DRAWLIST_MANAGER_H

#include "submanager.h"
#include "../interfaces/abstract_mainwindow.h"

class QSpacerItem;

namespace cg3 {

class DrawableObject;
class DrawableContainer;

namespace viewer {

class DrawableObjectDrawListManager;

namespace Ui {
class DrawableContainerDrawListManager;
}

class DrawableContainerDrawListManager : public SubManager
{
    Q_OBJECT

public:
    explicit DrawableContainerDrawListManager(
            QWidget *parent,
            const DrawableContainer* cont,
            bool visible = true,
            bool closeButtonVisible = false);
    ~DrawableContainerDrawListManager();

    std::vector<const DrawableObject*> selectedDrawableObjects() const;

    // SubManager interface
    void updateObjectProperties();
    void updateManagerProperties();

private slots:
    void addCheckBoxOfDrawableContainer(
            const std::string& name,
            bool visible);
    void removeCheckBoxOfDrawableContainer(const DrawableObject* obj);
    void changeVisibilityObject(const DrawableObject* obj, bool vis);

    void on_visibleButton_clicked();

    void on_hiddenButton_clicked();

private:
    Ui::DrawableContainerDrawListManager *ui;
	AbstractMainWindow& mw;
    const DrawableContainer* cont;
    std::map<const DrawableObject*, DrawableObjectDrawListManager*> mapSubManagers;
    QSpacerItem* m_spacer;
};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_CONTAINER_DRAWLIST_MANAGER_CPP "drawable_container_drawlist_manager.cpp"
#include CG3_DRAWABLE_CONTAINER_DRAWLIST_MANAGER_CPP
#undef CG3_DRAWABLE_CONTAINER_DRAWLIST_MANAGER_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_CONTAINER_DRAWLIST_MANAGER_H
