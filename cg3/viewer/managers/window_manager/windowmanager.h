/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef CG3_WINDOW_MANAGER_H
#define CG3_WINDOW_MANAGER_H

#include <QFrame>
#include <QColor>
#include <iostream>
#include "../../mainwindow.h"

namespace Ui {
    class WindowManager;
}

class WindowManager : public QFrame {
        Q_OBJECT

    public:
        explicit WindowManager(QWidget *parent = 0);
        ~WindowManager();

    private slots:
        void on_backgroundColorButton_clicked();

        void on_saveSnapshotButton_clicked();

        void on_fullScreenCheckBox_stateChanged(int state);

        void on_showAxisCheckBox_stateChanged(int state);

        void on_updateCanvasPushButton_clicked();

        void on_fitScenePushButton_clicked();

    private:
        Ui::WindowManager* ui;
        MainWindow& mainWindow;
};

#endif // CG3_WINDOW_MANAGER_H
