/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "debugobjects_manager.h"
#include "ui_debugobjects_manager.h"

#include <cg3/viewer/mainwindow.h>

#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QSpacerItem>

namespace cg3 {
namespace viewer {

CG3_INLINE DebugObjectsManager::DebugObjectsManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DebugObjectsManager),
    tmpColorSphere(128,128,128),
    tmpSpacer(nullptr),
    mw((cg3::viewer::MainWindow&)*parent)
{
    ui->setupUi(this);
    mw.enableDebugObjects();
}

CG3_INLINE DebugObjectsManager::~DebugObjectsManager()
{
    delete ui;
}

CG3_INLINE void DebugObjectsManager::on_colorSpherePushButton_clicked()
{
    tmpColorSphere = QColorDialog::getColor(Qt::white, this);
}

CG3_INLINE void DebugObjectsManager::on_addSpherePushButton_clicked()
{
    int id = mw.debugObjects.addSphere(Point3d(ui->xSphereSpinBox->value(),
                                     ui->ySphereSpinBox->value(),
                                     ui->zSphereSpinBox->value()),
                              ui->radiusSphereSpinBox->value(),
                              tmpColorSphere,
                              ui->precisionSphereSpinBox->value()
                              );

    QCheckBox * cb = new QCheckBox();
    cb->setText("prova");
    cb->setEnabled(true);
    cb->setChecked(true);
    ((QGridLayout*)ui->manageTab->layout())->addWidget(cb, id, 0);
    QSpacerItem* spacer = new QSpacerItem(40, 20,
                                          QSizePolicy::Minimum, QSizePolicy::Expanding);
    if (tmpSpacer != nullptr)
        ((QGridLayout*)ui->manageTab->layout())->removeItem(tmpSpacer);
    ((QGridLayout*)ui->manageTab->layout())->addItem(spacer, id+1, 0);
    tmpSpacer = spacer;
    mw.canvas.update();
}

} //namespace cg3::viewer
} //namespace cg3
