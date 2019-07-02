/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_MANIPULABLE_OBJECT_DRAWLIST_MANAGER_H
#define CG3_MANIPULABLE_OBJECT_DRAWLIST_MANAGER_H

#include "submanager.h"
#include "../interfaces/abstract_mainwindow.h"

namespace cg3 {

class ManipulableObject;

namespace viewer {

namespace Ui {
class ManipulableFormDrawlistManager;
} //namespace cg3::viewer::Ui

class ManipulableFormDrawlistManager : public SubManager
{
    Q_OBJECT

public:
    explicit ManipulableFormDrawlistManager(
            QWidget *parent,
            const ManipulableObject* obj);
    ~ManipulableFormDrawlistManager();

    // SubManager interface
    void updateObjectProperties();
    void updateManagerProperties();

private slots:
    void on_subFrameAxisCheckBox_stateChanged(int arg1);

private:
    Ui::ManipulableFormDrawlistManager *ui;
	AbstractMainWindow& mw;
    const ManipulableObject* obj;
};

} //namespace cg3::viewer
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_MANIPULABLE_OBJECT_DRAWLIST_MANAGER_CPP "manipulable_object_drawlist_manager.cpp"
#include CG3_MANIPULABLE_OBJECT_DRAWLIST_MANAGER_CPP
#undef CG3_MANIPULABLE_OBJECT_DRAWLIST_MANAGER_CPP
#endif //CG3_STATIC

#endif // CG3_MANIPULABLE_OBJECT_DRAWLIST_MANAGER_H
