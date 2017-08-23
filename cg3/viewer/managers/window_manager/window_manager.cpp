/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#include "window_manager.h"
#include "ui_windowmanager.h"

#include <QColorDialog>

WindowManager::WindowManager(QWidget *parent) : QFrame(parent), ui(new Ui::WindowManager), mainWindow(*(MainWindow*)parent) {
    ui->setupUi(this);
}

WindowManager::~WindowManager() {
    delete ui;
}

void WindowManager::on_backgroundColorButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);

    mainWindow.setBackgroundColor(color);
    mainWindow.updateGlCanvas();
}

void WindowManager::on_saveSnapshotButton_clicked() {
    mainWindow.saveSnapshot();
}

void WindowManager::on_fullScreenCheckBox_stateChanged(int state) {
    mainWindow.setFullScreen(state== Qt::Checked);
}

void WindowManager::on_showAxisCheckBox_stateChanged(int state) {
    if (state == Qt::Checked) mainWindow.drawAxis(true);
    else mainWindow.drawAxis(false);
    mainWindow.updateGlCanvas();
}

void WindowManager::on_updateCanvasPushButton_clicked() {
    mainWindow.updateGlCanvas();
}

void WindowManager::on_fitScenePushButton_clicked() {
    mainWindow.fitScene();
}
