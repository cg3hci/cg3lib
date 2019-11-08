/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <cg3/viewer/mainwindow.h>
#include <cg3/algorithms/convex_hull3.h>
#include <cg3/viewer/drawable_objects/drawable_dcel.h>
#include <random>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    cg3::viewer::MainWindow mw;  //Main window, it contains QGLViewer canvas
	mw.hideDockWidget();

    //number points and extremes
    const unsigned int nPoints = 1000;
	const cg3::BoundingBox3 extremes(cg3::Point3d(-10, -10, -10), cg3::Point3d(10,10,10));

	std::vector<cg3::Point3d> points; //vector of input points
    points.reserve(nPoints);


    std::random_device r; //setting the random device for the generation of random numbers
    static std::mt19937 mt(r());
    std::uniform_real_distribution<> distX(extremes.minX(), extremes.maxX());
    std::uniform_real_distribution<> distY(extremes.minY(), extremes.maxY());
    std::uniform_real_distribution<> distZ(extremes.minZ(), extremes.maxZ());

    for (unsigned int i = 0; i < nPoints; i++){
		points.push_back(cg3::Point3d(distX(mt), distY(mt), distZ(mt))); //generation of a random point
    }

    cg3::DrawableDcel ch = cg3::convexHull(points.begin(), points.end()); //call of the convex hull algorithm
    ch.setWireframe(true); // visualization of the mesh with wireframe
    ch.update(); // call in order to update the renderable mesh of the convex hull

	mw.pushDrawableObject(&ch, "Convex Hull"); // push the convex hull in the mainWindow
	mw.canvas.fitScene();
	mw.canvas.update();

    mw.show();
    return app.exec();
}
