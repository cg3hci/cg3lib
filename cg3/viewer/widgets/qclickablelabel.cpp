/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "qclickablelabel.h"
#include <cg3/utilities/const.h>

QClickableLabel::QClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{
    CG3_SUPPRESS_WARNING(f);
}

QClickableLabel::~QClickableLabel()
{
}

void QClickableLabel::mousePressEvent(QMouseEvent* event)
{
    CG3_SUPPRESS_WARNING(event);
    emit clicked();
}
