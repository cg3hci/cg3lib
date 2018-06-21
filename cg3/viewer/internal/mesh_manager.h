/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_MESH_MANAGER_H
#define CG3_MESH_MANAGER_H

#include <QFrame>

namespace cg3 {

class DrawableMesh;

namespace viewer {
class MainWindow;

namespace Ui {
class MeshManager;
}

class MeshManager : public QFrame
{
    Q_OBJECT

public:
    explicit MeshManager(QWidget *parent, const DrawableMesh* mesh);
    ~MeshManager();

private slots:

    void on_pointsRadioButton_toggled(bool checked);

    void on_flatRadioButton_toggled(bool checked);

    void on_smoothRadioButton_toggled(bool checked);

    void on_wireframeCheckBox_stateChanged(int arg1);

private:
    Ui::MeshManager *ui;
    MainWindow& mw;
    const DrawableMesh* mesh;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_MESH_MANAGER_H
