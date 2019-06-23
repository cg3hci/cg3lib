/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_QCLICKABLELABEL_H
#define CG3_QCLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

/**
 * @brief The QClickableLabel class
 *
 * A QLabel class which can be clicked (clicked event).
 *
 * Usage: just Promote a QLabel to a QClickableLabel
 *
 * @link https://wiki.qt.io/Clickable_QLabel
 */
class QClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~QClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#ifndef CG3_STATIC
#define CG3_QCLICKABLELABEL_CPP "qclickablelabel.cpp"
#include CG3_QCLICKABLELABEL_CPP
#undef CG3_QCLICKABLELABEL_CPP
#endif //CG3_STATIC

#endif // CG3_QCLICKABLELABEL_H
