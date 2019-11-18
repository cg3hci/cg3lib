/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <cg3/cg3lib.h>
#include <cg3/utilities/color.h>
#include <cg3/meshes/dcel/dcel.h>
#include <cg3/viewer/mainwindow.h>
#include <cg3/viewer/drawable_objects/drawable_dcel.h>
#include <random>

int main(int argc, char *argv[])
{
	cg3::Dcel mesh(CG3_STRINGIFY(SOURCE_PATH) "/../../shared/bimba.obj");

	//number of elements
	std::cout << "Number of vertices: " << mesh.numberVertices() << std::endl;
	std::cout << "Number of half edges: " << mesh.numberHalfEdges() << std::endl;
	std::cout << "Number of Faces: " << mesh.numberFaces() << std::endl;

	std::cout << "Barycenter: " << mesh.barycenter() << std::endl;
	std::cout << "Bounding Box: min: " << mesh.boundingBox().min()
			  << "; max: " << mesh.boundingBox().max() << std::endl;

	std::cout << "Surface area: " << mesh.surfaceArea() << std::endl;
	std::cout << "Volume: " << mesh.volume() << std::endl;

	//iterating across all the elements (commented to avoid prints)
//	for (const cg3::Dcel::Vertex* v : mesh.vertexIterator()) { //also non-const vertex is possible
//		std::cout << "Vertex " <<v->id() << " has position " << v->coordinate()
//				  << " and cardinality " << v->cardinality() << std::endl;
//	}

//	for (const cg3::Dcel::Face* f: mesh.faceIterator()) { //also non-const face is possible
//		std::cout << "Face " << f->id() << " has number of vertices "
//				  << f->numberIncidentVertices() << " and normal " << f->normal() << std::endl;
//	}

	//incidences and adjacences
	//iterating along the adjacent vertices of vertex 0
	const cg3::Dcel::Vertex* v0 = mesh.vertex(0);
	std::cout << "Cardinality of vertex " << v0->id() << ": " << v0->cardinality() << "\n";
	for (const cg3::Dcel::Vertex* v : v0->adjacentVertexIterator()) { //also non-const vertex is possible
		std::cout << "\tAdjacent vetex: " << v->id() << std::endl;
	}
	std::cout << std::endl;

	//iterating along the incident faces of vertex 0
	for (const cg3::Dcel::Face* f : v0->incidentFaceIterator()) {
		std::cout << "\tIncident face: " << f->id() << std::endl;
	}

	//iterating along the adjacent faces fo face 0
	const cg3::Dcel::Face* f0 = mesh.face(0);
	std::cout << "Face " << f0->id() << std::endl;
	for (const cg3::Dcel::Face* f : f0->adjacentFaceIterator()) { //also non-const vertex is possible
		std::cout << "\tAdjacent Face: " << f->id() << std::endl;
	}
	std::cout << std::endl;

	//iterating along the incident vertices of face 0
	for(const cg3::Dcel::Vertex* v : f0->incidentVertexIterator()) {
		std::cout << "\tIncident Vertex: " << v->id() << std::endl;
	}

	//coloring faces depending on the dot product between their normals and +X axis
	const unsigned int nRangeColors = 4096;
	cg3::HSVScaleColor scaleColor(nRangeColors);
	for (cg3::Dcel::Face* f : mesh.faceIterator()){
		float rangeFloat = (f->normal().dot(cg3::X_AXIS) + 1) * 0.5; //range between 0 and 1

		f->setColor(scaleColor[(unsigned int)(rangeFloat * nRangeColors)]);
	}

#ifdef CG3_VIEWER_DEFINED
	//viewer part
    QApplication app(argc, argv);
    cg3::viewer::MainWindow mw;  //Main window, it contains QGLViewer canvas
	mw.hideDockWidget();

	cg3::DrawableDcel drawableMesh(mesh);

	mw.pushDrawableObject(&drawableMesh, "Mesh"); // push the input mesh in the mainWindow
	mw.canvas.fitScene();
	mw.canvas.update();

    mw.show();
    return app.exec();
#else
	CG3_SUPPRESS_WARNING(argc);
	CG3_SUPPRESS_WARNING(argv);
	return 0;
#endif //CG3_VIEWER_DEFINED
}
