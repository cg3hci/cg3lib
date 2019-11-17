/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/viewer/interfaces/pickable_object.h>
#include <cg3/viewer/mainwindow.h>
#include <cg3/meshes/dcel/dcel.h>
#include <cg3/viewer/managers/dcel_manager.h>

//Test eigenmesh module and manger
#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
///Test trimeshviewer.pri: uncomment to test trimesh module
#include <cg3/viewer/managers/eigenmesh_manager.h>
#ifdef CG3_CGAL_DEFINED
#ifdef CG3_LIBIGL_DEFINED
#include <cg3/viewer/managers/booleans_manager.h>
#endif
#endif
#endif


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	int id = 0;

	cg3::viewer::MainWindow gui;  //mainwindow, it containes the canvas

	CG3_SUPPRESS_WARNING(id);

	//The EigenMesh manager will be added only if eigen is correctly included
#ifdef CG3_EIGENMESH_DEFINED
	cg3::viewer::EigenMeshManager em(&gui);
	id = gui.addManager(&em, "EigenMesh");


	//The booleans manager will be added only if libigl and cgal are correctly included and linked
#if defined(CG3_LIBIGL_DEFINED) && defined(CG3_CGAL_DEFINED)
	cg3::viewer::BooleansManager bm(&gui);
	id = gui.addManager(&bm, "Booleans");
#endif
#endif

	cg3::viewer::DcelManager dm(&gui);
	id = gui.addManager(&dm, "Dcel");

	gui.setCurrentManager(id);
	gui.update();
	gui.show();

	return app.exec();
}
