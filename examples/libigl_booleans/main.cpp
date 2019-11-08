/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <cg3/cg3lib.h>
#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/drawable_objects/drawable_eigenmesh.h>

#include <cg3/libigl/booleans.h>
#include <random>

int main(int argc, char *argv[])
{	
    QApplication app(argc, argv);
    cg3::viewer::MainWindow mw;  //Main window, it contains QGLViewer canvas
	mw.hideDockWidget();

	cg3::DrawableEigenMesh mesh1(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bimba.obj");
	cg3::DrawableEigenMesh mesh2(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bunny.obj");

	mw.pushDrawableObject(&mesh1, "Bimba", false); // push the input mesh in the mainWindow
	mw.pushDrawableObject(&mesh2, "Bunny", false); // push the input mesh in the mainWindow

	cg3::DrawableEigenMesh intersection = cg3::libigl::intersection(mesh1, mesh2);

	mw.pushDrawableObject(&intersection, "Intersection");

	mw.canvas.fitScene();
	mw.canvas.update();

    mw.show();
    return app.exec();
}
