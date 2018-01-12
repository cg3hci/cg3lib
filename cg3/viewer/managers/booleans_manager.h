/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_BOOLEANS_MANAGER_H
#define CG3_BOOLEANS_MANAGER_H

#include <QFrame>
#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/utilities/loadersaver.h>
#include "../drawable_objects/drawable_eigenmesh.h"

namespace cg3 {

namespace viewer {

namespace Ui {
    class BooleansManager;
}

class BooleansManager : public QFrame {
        Q_OBJECT

    public:
        explicit BooleansManager(QWidget *parent = 0);
        ~BooleansManager();
        void setButtonsMeshLoaded(bool b);
        void setButtonsMeshLoaded_2(bool b);
        void setButtonsResultLoaded(bool b);
        void setMesh1(const cg3::EigenMesh &m);
        void setMesh2(const cg3::EigenMesh &m);

    private slots:
        void on_loadEigenMeshButton_clicked();

        void on_clearEigenMeshButton_clicked();

        void on_saveEigenMeshButton_clicked();

        void on_setFromResultButton_clicked();

        void on_pointsEigenMeshRadioButton_toggled(bool checked);

        void on_flatEigenMeshRadioButton_toggled(bool checked);

        void on_smoothEigenMeshRadioButton_toggled(bool checked);

        void on_wireframeEigenMeshCheckBox_stateChanged(int arg1);

        void on_loadEigenMeshButton_2_clicked();

        void on_clearEigenMeshButton_2_clicked();

        void on_saveEigenMeshButton_2_clicked();

        void on_setFromResultButton_2_clicked();

        void on_pointsEigenMeshRadioButton_2_toggled(bool checked);

        void on_flatEigenMeshRadioButton_2_toggled(bool checked);

        void on_smoothEigenMeshRadioButton_2_toggled(bool checked);

        void on_wireframeEigenMeshCheckBox_2_stateChanged(int arg1);

        void on_intersectionButton_clicked();

        void on_differenceButton_clicked();

        void on_unionButton_clicked();

        void on_mergePushButton_clicked();

        void on_clearEigenMeshButton_3_clicked();

        void on_saveEigenMeshButton_3_clicked();

        void on_pointsEigenMeshRadioButton_3_toggled(bool checked);

        void on_flatEigenMeshRadioButton_3_toggled(bool checked);

        void on_smoothEigenMeshRadioButton_3_toggled(bool checked);

        void on_wireframeEigenMeshCheckBox_3_stateChanged(int arg1);

        void on_plusXButton_clicked();

        void on_minusXButton_clicked();

        void on_plusYButton_clicked();

        void on_minusYButton_clicked();

        void on_plusZButton_clicked();

        void on_minusZButton_clicked();

        void on_rotateButton_clicked();

        void on_undoRotateButton_clicked();

        void on_makeBox1PushButton_clicked();

        void on_makeBox2PushButton_clicked();

        void on_scalePushButton_clicked();

    private:
        Ui::BooleansManager *ui;
        cg3::viewer::MainWindow& mainWindow;
        std::vector<cg3::DrawableEigenMesh*> meshes;
        cg3::DrawableEigenMesh* result;
        cg3::Vec3 lastAxis;
        double lastAngle;
        cg3::viewer::LoaderSaver objls;
};

}

}

#endif // CG3_BOOLEANS_MANAGER_H
