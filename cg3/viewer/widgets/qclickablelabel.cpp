/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "qclickablelabel.h"
#include <cg3/utilities/const.h>
#include <cg3/cg3lib.h>

CG3_INLINE QClickableLabel::QClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{
    CG3_SUPPRESS_WARNING(f);
}

CG3_INLINE QClickableLabel::~QClickableLabel()
{
}

CG3_INLINE void QClickableLabel::mousePressEvent(QMouseEvent* event)
{
    CG3_SUPPRESS_WARNING(event);
    emit clicked();
}
