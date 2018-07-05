/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef DRAWABLE_OBJECT_DRAWLIST_MANAGER_H
#define DRAWABLE_OBJECT_DRAWLIST_MANAGER_H

#include "submanager.h"

namespace cg3 {

class DrawableObject;

namespace viewer {

class MainWindow;

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

    void setDrawableObjectVisibility(bool vis);
    void setNameCheckBox(const std::string& newName);
    void updateObjctProperties();
    void updateManagerProperties();

private slots:
    void setSubFrame(SubManager* frame, bool vis = true);
    void setSubFrameVisibility(bool vis);
    void on_checkBox_stateChanged(int state);

    void on_closePushButton_clicked();

private:
    Ui::DrawableObjectDrawListManager *ui;
    MainWindow& mw;
    const DrawableObject* object;
    SubManager* subframe;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // DRAWABLE_OBJECT_DRAWLIST_MANAGER_H
