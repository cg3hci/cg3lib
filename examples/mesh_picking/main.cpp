/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "picker.h"

/**
 * To enable picking, just MAIUSC + click!
 */

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	cg3::viewer::MainWindow gui;

	cg3::PickableDcel mesh(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bimba.obj");

	gui.pushDrawableObject(&mesh, "Pickable Mesh");

	Picker picker(mesh, gui);

	//connects the signal "objectPicked" sent from the canvas to the slot of the picker class.
	//we could do this operation also in the Picker constructor
	QObject::connect(&gui.canvas, SIGNAL(objectPicked(const cg3::PickableObject*, unsigned int)),
			&picker, SLOT(pickedFace(const cg3::PickableObject*, unsigned int)));

	gui.canvas.fitScene();
	gui.canvas.update();
	gui.show();

	return app.exec();
}
