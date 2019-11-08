/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_EXAMPLE_MANAGER_H
#define CG3_EXAMPLE_MANAGER_H

#include <QFrame>
#include <cg3/viewer/mainwindow.h>

namespace Ui {
class ExampleManager;
}

class ExampleManager : public QFrame
{
    Q_OBJECT

public:
    explicit ExampleManager(QWidget *parent = 0);
    ~ExampleManager();

private slots:
	void on_helloWorldPushButton_clicked();

private:
    Ui::ExampleManager *ui;

    //reference to the MainWindow
    cg3::viewer::MainWindow& mw;
};

#endif // CG3_EXAMPLE_MANAGER_H
