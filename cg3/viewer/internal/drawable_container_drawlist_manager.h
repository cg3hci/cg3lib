/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CONTAINER_DRAWLIST_MANAGER_H
#define CONTAINER_DRAWLIST_MANAGER_H

#include <QFrame>

namespace cg3 {
namespace viewer {

namespace Ui {
class DrawableContainerDrawListManager;
}

class DrawableContainerDrawListManager : public QFrame
{
    Q_OBJECT

public:
    explicit DrawableContainerDrawListManager(QWidget *parent = 0);
    ~DrawableContainerDrawListManager();

private:
    Ui::DrawableContainerDrawListManager *ui;
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CONTAINER_DRAWLIST_MANAGER_H
