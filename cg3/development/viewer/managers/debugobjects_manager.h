/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DEBUGOBJECTS_MANAGER_H
#define CG3_DEBUGOBJECTS_MANAGER_H

#include <QFrame>

class QSpacerItem;

namespace cg3 {
namespace viewer {

class MainWindow;

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

#ifndef CG3_STATIC
#define CG3_DEBUGOBJECTS_MANAGER_CPP "debugobjects_manager.cpp"
#include CG3_DEBUGOBJECTS_MANAGER_CPP
#undef CG3_DEBUGOBJECTS_MANAGER_CPP
#endif //CG3_STATIC

#endif // CG3_DEBUGOBJECTS_MANAGER_H
