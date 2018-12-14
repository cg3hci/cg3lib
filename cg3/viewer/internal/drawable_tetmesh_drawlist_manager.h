/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_TETMESH_DRAWLIST_MANAGER_H
#define CG3_DRAWABLE_TETMESH_DRAWLIST_MANAGER_H

#include "submanager.h"

#include <QFrame>

#include <cg3/viewer/widgets/drawable_tetmesh_control_panel.h>

namespace cg3 {
namespace cino {
    class DrawableTetMesh;
} //namespace cg3::cinolib;

namespace viewer {

class MainWindow;

namespace Ui {
class DrawableTetMeshDrawListManager;
}

class DrawableTetMeshDrawListManager : public SubManager
{
    Q_OBJECT

public:
    explicit DrawableTetMeshDrawListManager(
            QWidget *parent,
            cino::DrawableTetMesh* mesh);
    ~DrawableTetMeshDrawListManager();

    // SubManager interface
    void updateObjectProperties();
    void updateManagerProperties();

private slots:
    void on_showPushButton_clicked();

    void on_pointsRadioButton_toggled(bool checked);

    void on_flatRadioButton_toggled(bool checked);

    void on_smoothRadioButton_toggled(bool checked);

    void on_wireframeCheckBox_stateChanged(int arg1);

private:
    Ui::DrawableTetMeshDrawListManager *ui;
    MainWindow& mw;
    cino::DrawableTetMesh* mesh;
    DrawableTetMeshControlPanel panel;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_DRAWABLE_TETMESH_DRAWLIST_MANAGER_H
