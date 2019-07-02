/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef DRAWABLE_OBJECT_DRAWLIST_MANAGER_H
#define DRAWABLE_OBJECT_DRAWLIST_MANAGER_H

#include "submanager.h"
#include "../interfaces/abstract_mainwindow.h"

namespace cg3 {

class DrawableObject;

namespace viewer {

namespace Ui {
class DrawableObjectDrawListManager;
}

class DrawableObjectDrawListManager : public QFrame
{
    Q_OBJECT

public:
    explicit DrawableObjectDrawListManager(
            QWidget *parent,
            const DrawableObject* object,
            const std::string& name,
            bool visible = true,
            bool closeButtonVisible = false);
    ~DrawableObjectDrawListManager();

    void setDrawableObjectVisibility(bool vis, bool alsoSubframe = false);
    void setDrawableObjectName(const std::string& newName);
    std::string drawableObjectName() const;
    bool isContainer() const;
    void updateObjectProperties();
    void updateManagerProperties();
    void toggleSelection();
    void setSelection(bool b = true);
    bool isSelected() const;
    std::vector<const cg3::DrawableObject*> containedSelectedObjects() const;

private slots:
    void setSubFrame(SubManager* frame, bool vis = true);
    void setSubFrameVisibility(bool vis);
    void on_checkBox_stateChanged(int state);

    void on_closePushButton_clicked();

    void on_subFrameCheckBox_stateChanged(int state);

    void on_objectName_clicked();

    void on_objectType_clicked();

private:
    Ui::DrawableObjectDrawListManager *ui;
	AbstractMainWindow& mw;
    const DrawableObject* object;
    SubManager* subframe;
    bool selected;
    bool container;
};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_OBJECT_DRAWLIST_MANAGER_CPP "drawable_object_drawlist_manager.cpp"
#include CG3_DRAWABLE_OBJECT_DRAWLIST_MANAGER_CPP
#undef CG3_DRAWABLE_OBJECT_DRAWLIST_MANAGER_CPP
#endif //CG3_STATIC

#endif // DRAWABLE_OBJECT_DRAWLIST_MANAGER_H
