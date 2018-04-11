/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DEBUGOBJECTS_MANAGER_H
#define CG3_DEBUGOBJECTS_MANAGER_H

#include <QFrame>
#include <cg3/viewer/mainwindow.h>

namespace cg3 {
namespace viewer {
namespace Ui {
class DebugObjectsManager;
} //namespace cg3::viewer::Ui

class DebugObjectsManager : public QFrame
{
    Q_OBJECT

public:
    explicit DebugObjectsManager(QWidget *parent = 0);
    ~DebugObjectsManager();

private slots:
    void on_colorSpherePushButton_clicked();

    void on_addSpherePushButton_clicked();

private:
    Ui::DebugObjectsManager *ui;
    QColor tmpColorSphere;
    QSpacerItem* tmpSpacer;

    //reference to the MainWindow
    cg3::viewer::MainWindow& mw;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_DEBUGOBJECTS_MANAGER_H
