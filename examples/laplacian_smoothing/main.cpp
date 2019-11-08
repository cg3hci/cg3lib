/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <cg3/cg3lib.h>
#include <cg3/viewer/mainwindow.h>
#include <cg3/algorithms/laplacian_smoothing.h>
#include <cg3/viewer/drawable_objects/drawable_dcel.h>
#include <random>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    cg3::viewer::MainWindow mw;  //Main window, it contains QGLViewer canvas
	mw.hideDockWidget();

	cg3::DrawableDcel inputMesh(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bimba.obj");

	cg3::DrawableDcel smoothedMesh = cg3::laplacianSmoothing((const cg3::Dcel&)inputMesh, 10); //call of the laplacian smoothing algorithm

	mw.pushDrawableObject(&inputMesh, "Input Mesh", false); // push the input mesh in the mainWindow
	mw.pushDrawableObject(&smoothedMesh, "Smoothed Mesh"); // push the smoothed mesh in the mainWindow
	mw.canvas.fitScene();
	mw.canvas.update();

    mw.show();
    return app.exec();
}
