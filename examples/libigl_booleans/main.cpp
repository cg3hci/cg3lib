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

	//loading the two meshes
	cg3::DrawableEigenMesh mesh1(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bimba.obj");
	cg3::DrawableEigenMesh mesh2(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bunny.obj");

	//push the two meshes into the main window, both not visible
	mw.pushDrawableObject(&mesh1, "Bimba", false);
	mw.pushDrawableObject(&mesh2, "Bunny", false);

	//computing the boolena operations between the two meshes
	cg3::DrawableEigenMesh intersection = cg3::libigl::intersection(mesh1, mesh2);
	cg3::DrawableEigenMesh _union = cg3::libigl::union_(mesh1, mesh2);
	cg3::DrawableEigenMesh difference = cg3::libigl::difference(mesh1, mesh2);

	//push the results into the main window, only the intersection will be visible
	mw.pushDrawableObject(&intersection, "Intersection");
	mw.pushDrawableObject(&_union, "Union", false);
	mw.pushDrawableObject(&difference, "difference", false);

	mw.canvas.fitScene();
	mw.canvas.update();

    mw.show();
    return app.exec();
}
