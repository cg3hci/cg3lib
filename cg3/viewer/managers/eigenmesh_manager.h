/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_EIGENMESH_MANAGER_H
#define CG3_EIGENMESH_MANAGER_H

#include <QFrame>
#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/utilities/loadersaver.h>
#include "../drawable_objects/drawable_eigenmesh.h"

namespace cg3 {

namespace viewer {

namespace Ui {
    class EigenMeshManager;
}

class EigenMeshManager : public QFrame
{
        Q_OBJECT

    public:
        explicit EigenMeshManager(QWidget *parent = 0);
        void setButtonsMeshLoaded(bool b);
        void setEigenMesh(const cg3::EigenMesh &m);
        ~EigenMeshManager();

    private slots:

        void on_loadMeshButton_clicked();

        void on_clearMeshButton_clicked();

        void on_saveMeshButton_clicked();

        void on_pointsMeshRadioButton_toggled(bool checked);

        void on_flatMeshRadioButton_toggled(bool checked);

        void on_smoothMeshRadioButton_toggled(bool checked);

        void on_wireframeMeshCheckBox_stateChanged(int arg1);

        void on_verticesColorRadioButton_toggled(bool checked);

        void on_faceColorRadioButton_toggled(bool checked);

        void on_boundingBoxCheckBox_stateChanged(int arg1);

    private:
        Ui::EigenMeshManager *ui;
        cg3::viewer::MainWindow& mainWindow;
        cg3::DrawableEigenMesh* mesh;
        cg3::viewer::LoaderSaver objls;
};

}

}

#endif // EIGENMESHMANAGER_H
