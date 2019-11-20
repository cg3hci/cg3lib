/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_PICKER_H
#define CG3_PICKER_H

#include <QObject>
#include <cg3/viewer/pickable_objects/pickable_dcel.h>
#include <cg3/viewer/mainwindow.h>

/**
 * @brief The Picker class
 * To catch a picking event, we need a QObject derived class in order to use the qt's
 * connect/signal/slot paradigm.
 */

class Picker : public QObject //could be not public inheritance if the connect is in the constructor
{
	Q_OBJECT
public:
	Picker(cg3::PickableDcel& dcel, cg3::viewer::MainWindow& mw);

public slots:
	void pickedFace(const cg3::PickableObject* obj, unsigned int f);

private:
	cg3::PickableDcel& dcel; //need to have at least a reference to the mesh
							 //to color the picked faces and to check if the
							 //picked object is our mesh
	cg3::viewer::MainWindow& mw; //need the reference (or pointer) to the mainwindow
								 //to update the canvas after every picking
};

#endif // PICKER_H
