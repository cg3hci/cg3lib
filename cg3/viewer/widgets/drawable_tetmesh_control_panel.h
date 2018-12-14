/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_TETMESH_CONTROL_PANEL_H
#define CG3_DRAWABLE_TETMESH_CONTROL_PANEL_H

#include <QDockWidget>

#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/drawable_objects/drawable_tetmesh.h>

namespace cg3 {
namespace viewer {

namespace Ui {
class DrawableTetMeshControlPanel;
}

class DrawableTetMeshControlPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit DrawableTetMeshControlPanel(QWidget *parent, cino::DrawableTetMesh* mesh);
    ~DrawableTetMeshControlPanel();

private:
    Ui::DrawableTetMeshControlPanel *ui;

    cg3::viewer::MainWindow& mw;
    cg3::cino::DrawableTetMesh* mesh;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_DRAWABLE_TETMESH_CONTROL_PANEL_H
