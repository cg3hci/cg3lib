/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "manipulable_object_drawlist_manager.h"
#include "ui_manipulable_object_drawlist_manager.h"

#include <cg3/viewer/interfaces/manipulable_object.h>

namespace cg3 {
namespace viewer {

CG3_INLINE ManipulableFormDrawlistManager::ManipulableFormDrawlistManager(
        QWidget *parent,
        const ManipulableObject* obj) :
    SubManager(parent),
    ui(new Ui::ManipulableFormDrawlistManager),
	mw((AbstractMainWindow&)*parent),
	obj(obj)
{
    ui->setupUi(this);
}

CG3_INLINE ManipulableFormDrawlistManager::~ManipulableFormDrawlistManager()
{
    delete ui;
}

CG3_INLINE void ManipulableFormDrawlistManager::updateObjectProperties()
{
    obj->setDrawRelativeAxis(ui->subFrameAxisCheckBox->isChecked());
	mw.updateCanvas();
}

CG3_INLINE void ManipulableFormDrawlistManager::updateManagerProperties()
{
    ui->subFrameAxisCheckBox->setChecked(obj->drawRelativeAxis());
}

CG3_INLINE void ManipulableFormDrawlistManager::on_subFrameAxisCheckBox_stateChanged(int arg1)
{
    obj->setDrawRelativeAxis(arg1 == Qt::Checked);
	mw.updateCanvas();
}

} //namespace cg3::viewer
} //namespace cg3
