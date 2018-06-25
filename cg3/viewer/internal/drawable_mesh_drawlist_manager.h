/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_MESH_MANAGER_H
#define CG3_MESH_MANAGER_H

#include <QFrame>

#include <cg3/viewer/utilities/loadersaver.h>

namespace cg3 {

class DrawableMesh;

namespace viewer {

class MainWindow;

namespace Ui {
class DrawableMeshDrawListManager;
}

class DrawableMeshDrawListManager : public QFrame
{
    Q_OBJECT

public:
    explicit DrawableMeshDrawListManager(
            QWidget *parent,
            const DrawableMesh* mesh);
    ~DrawableMeshDrawListManager();

private slots:

    void on_pointsRadioButton_toggled(bool checked);

    void on_flatRadioButton_toggled(bool checked);

    void on_smoothRadioButton_toggled(bool checked);

    void on_wireframeCheckBox_stateChanged(int arg1);

    void on_bboxCheckBox_stateChanged(int arg1);

    void on_vColorRadioButton_toggled(bool checked);

    void on_tColorRadioButton_toggled(bool checked);

    void on_savePushButton_clicked();

private:
    Ui::DrawableMeshDrawListManager *ui;
    MainWindow& mw;
    const DrawableMesh* mesh;
    LoaderSaver ls;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_MESH_MANAGER_H
