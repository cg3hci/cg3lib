/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_MESH_DRAWLIST_MANAGER_H
#define CG3_DRAWABLE_MESH_DRAWLIST_MANAGER_H

#include "submanager.h"
#include "../interfaces/abstract_mainwindow.h"

#include <cg3/viewer/utilities/loadersaver.h>

namespace cg3 {

class DrawableMesh;

namespace viewer {

namespace Ui {
class DrawableMeshDrawListManager;
}

class DrawableMeshDrawListManager : public SubManager
{
    Q_OBJECT

public:
    explicit DrawableMeshDrawListManager(
            QWidget *parent,
            const DrawableMesh* mesh);
    ~DrawableMeshDrawListManager();

    // SubManager interface
    void updateObjectProperties();
    void updateManagerProperties();

private slots:

    void on_pointsRadioButton_toggled(bool checked);

    void on_flatRadioButton_toggled(bool checked);

    void on_smoothRadioButton_toggled(bool checked);

    void on_wireframeCheckBox_stateChanged(int arg1);

    void on_bboxCheckBox_stateChanged(int arg1);

    void on_vColorRadioButton_toggled(bool checked);

    void on_tColorRadioButton_toggled(bool checked);

    void on_savePushButton_clicked();

    void on_subFrameAxisCheckBox_stateChanged(int arg1);

    void on_wireframeWidthSlider_valueChanged(int value);

    void on_pointWidthSlider_valueChanged(int value);

private:
    Ui::DrawableMeshDrawListManager *ui;
	AbstractMainWindow& mw;
    const DrawableMesh* mesh;
    LoaderSaver ls;
};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_MESH_DRAWLIST_MANAGER_CPP "drawable_mesh_drawlist_manager.cpp"
#include CG3_DRAWABLE_MESH_DRAWLIST_MANAGER_CPP
#undef CG3_DRAWABLE_MESH_DRAWLIST_MANAGER_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_MESH_DRAWLIST_MANAGER_H
