/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_MANAGER_H
#define CG3_DCEL_MANAGER_H

#include <QFrame>
#include <QColor>
#include "../drawable_objects/drawable_dcel.h"
#include <cg3/viewer/interfaces/abstract_mainwindow.h>
#include <cg3/viewer/utilities/loadersaver.h>

namespace cg3 {
namespace viewer {
namespace Ui {
class DcelManager;
} //namespace cg3::viewer::Ui

/**
 * @ingroup cg3viewer
 * @brief QFrame that manages a DrawableDcel which will be drawn in the cg3::viewer::MainWindow
 */
class DcelManager : public QFrame
{
    Q_OBJECT

public:
    explicit DcelManager(QWidget* parent = 0);
    ~DcelManager();

    cg3::DrawableDcel& dcel();
    void setDcel(const cg3::Dcel& dcel, const std::string& name = "Dcel");
    void cleanDcel();
    void updateDcel();
    bool isDcelLoaded() const;

public slots:
    void on_loadDcelButton_clicked();
    void on_cleanDcelButton_clicked();
    void on_saveDcelButton_clicked();
private slots:
    void on_wireframeDcelCheckBox_stateChanged(int state);
    void on_wireframeWidthDcelSlider_valueChanged(int value);
    void on_wireframeColorDcelButton_clicked();
    void on_pointsDcelRadioButton_toggled(bool checked);
    void on_flatDcelRadioButton_toggled(bool checked);
    void on_smoothDcelRadioButton_toggled(bool checked);
    void on_vertexColorDcelRadioButton_toggled(bool checked);
    void on_triangleColorDcelRadioButton_toggled(bool checked);
    void on_boundingBoxCheckBox_stateChanged(int state);
    void on_facesWireframeDcelCheckBox_stateChanged(int state);

private:
    void resetDefaults();
    void setButtonsDcelLoaded();
    void setButtonsDcelNotLoaded();

    Ui::DcelManager* ui; //puntatore al QFrame (da cui è possibile richiamare gli oggetti della ui)
	cg3::viewer::AbstractMainWindow& mainWindow; //puntatore alla mainWindow
    cg3::DrawableDcel drawableDcel; //puntatore alla DrawableDcel gestita dal DcelManager
    cg3::viewer::LoaderSaver dcells;
    bool loaded;

};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DCEL_MANAGER_CPP "dcel_manager.cpp"
#include CG3_DCEL_MANAGER_CPP
#undef CG3_DCEL_MANAGER_CPP
#endif //CG3_STATIC

#endif // CG3_DCEL_MANAGER_H
