/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_ABSTRACT_MAINWINDOW_H
#define CG3_ABSTRACT_MAINWINDOW_H

#include <string>
#include <QMainWindow>

namespace cg3 {

class DrawableObject;

namespace viewer {

/**
 * @brief The AbstractMainWindow class allows to create different MainWindow classes
 * that can be all recognised by the other classes of cg3lib
 */
class AbstractMainWindow : public QMainWindow
{
public:
	AbstractMainWindow(QWidget* parent) : QMainWindow(parent) {}
	virtual ~AbstractMainWindow() {}

	virtual void updateCanvas() = 0;
	virtual void fitSceneCanvas() = 0;

	virtual void pushDrawableObject(
			const cg3::DrawableObject* obj,
			std::string checkBoxName,
			bool checkBoxChecked = true,
			bool closeButtonVisible = false) = 0;
	virtual bool deleteDrawableObject(const cg3::DrawableObject* obj) = 0;
	virtual void setDrawableObjectVisibility(
			const cg3::DrawableObject* obj,
			bool visible) = 0;
};

}
}

#endif // CG3_ABSTRACT_MAINWINDOW_H
