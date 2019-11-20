/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "picker.h"

Picker::Picker(cg3::PickableDcel& dcel, cg3::viewer::MainWindow& mw) :
	dcel(dcel), mw(mw)
{
	//connects the signal "objectPicked" sent from the canvas to the slot of the picker class.
	//commented because we are connecting in the main.
	//QObject::connect(&mw.canvas, SIGNAL(objectPicked(const cg3::PickableObject*, unsigned int)),
	//		this, SLOT(pickedFace(const cg3::PickableObject*, unsigned int)));
}

/**
 * This member function is executed every time a face is picked in the canvas
 */
void Picker::pickedFace(const cg3::PickableObject* obj, unsigned int f)
{
	if (obj == &dcel){ //first check if the picked object is actually our object (could be others!)

		//here we know that the user picked the face f of the dcel

		dcel.face(f)->setColor(cg3::RED); //color the picked dcel face
		dcel.update();
		mw.canvas.update();
	}
}
