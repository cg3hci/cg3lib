/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCELMANAGER_H
#define CG3_DCELMANAGER_H

#include <QFrame>
#include <QColor>
#include "../drawable_objects/drawable_dcel.h"
#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/utilities/loadersaver.h>

namespace cg3 {

namespace viewer {

namespace Ui {
    class DcelManager;
}

/**
 * @brief QFrame che gestisce una DrawableDcel visualizzata nella mainWindow
 */
class DcelManager : public QFrame {
        Q_OBJECT

    public:
        explicit DcelManager(QWidget* parent = 0);
        ~DcelManager();

        cg3::DrawableDcel* getDcel();
        void setDcel(const cg3::Dcel& dcel, const std::string& name = "Dcel", bool b = false);
        void cleanDcel();
        void updateDcel();
        void resetDefaults();
        void setButtonsDcelLoaded();
        void setButtonsDcelNotLoaded();

    private slots:
        void on_loadDcelButton_clicked();
        void on_cleanDcelButton_clicked();
        void on_saveDcelButton_clicked();
        void on_wireframeDcelCheckBox_stateChanged(int state);
        void on_wireframeWidthDcelSlider_valueChanged(int value);
        void on_wireframeColorDcelButton_clicked();
        void on_drawDcelCheckBox_stateChanged(int state);
        void on_pointsDcelRadioButton_toggled(bool checked);
        void on_flatDcelRadioButton_toggled(bool checked);
        void on_smoothDcelRadioButton_toggled(bool checked);
        void on_vertexColorDcelRadioButton_toggled(bool checked);
        void on_triangleColorDcelRadioButton_toggled(bool checked);
        void on_boundingBoxCheckBox_stateChanged(int state);
        void on_facesWireframeDcelCheckBox_stateChanged(int state);

    private:
        Ui::DcelManager* ui; //puntatore al QFrame (da cui è possibile richiamare gli oggetti della ui)
        cg3::viewer::MainWindow& mainWindow; //puntatore alla mainWindow
        cg3::DrawableDcel* drawableDcel; //puntatore alla DrawableDcel gestita dal DcelManager
        cg3::viewer::LoaderSaver dcells;
};

}

}

#endif // CG3_DCELMANAGER_H
