/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef DRAWABLE_OBJECT_DRAWLIST_MANAGER_H
#define DRAWABLE_OBJECT_DRAWLIST_MANAGER_H

#include <QFrame>

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
            const std::string& name);
    ~DrawableObjectDrawListManager();

    void setDrawableObjectVisibility(bool vis);
    void setNameCheckBox(const std::string& newName);
    void setSubFrame(QFrame* frame);
    void setSubFrameVisibility(bool vis);

private slots:
    void on_checkBox_stateChanged(int state);

private:
    Ui::DrawableObjectDrawListManager *ui;
    MainWindow& mw;
    const DrawableObject* object;
    QFrame* subframe;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // DRAWABLE_OBJECT_DRAWLIST_MANAGER_H
