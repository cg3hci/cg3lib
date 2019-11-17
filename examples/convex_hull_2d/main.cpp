/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include <iostream>
#include <vector>

#include <cg3/cg3lib.h>
#include <cg3/geometry/point2.h>
#include <cg3/algorithms/convex_hull2.h>
#include <cg3/algorithms/convex_hull2_incremental.h>

int main(int argc, char *argv[])
{
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

	const int PLANE_WIDTH  = 10;
	const int PLANE_HEIGHT = 10;

	std::cout << "------ Convex Hull 2D sample ------" << std::endl << std::endl;

	//Insert input points
	std::vector<cg3::Point2i> points;
	points.push_back(cg3::Point2i(3,5));
	points.push_back(cg3::Point2i(0,3));
	points.push_back(cg3::Point2i(4,5));
	points.push_back(cg3::Point2i(2,8));
	points.push_back(cg3::Point2i(6,3));
	points.push_back(cg3::Point2i(4,1));
	points.push_back(cg3::Point2i(0,1));
	points.push_back(cg3::Point2i(2,3));
	points.push_back(cg3::Point2i(2,1));
	points.push_back(cg3::Point2i(8,8));

	//Print input points
	std::cout << "Input points:" << std::endl;
	for (std::vector<cg3::Point2i>::iterator it = points.begin(); it != points.end(); it++) {
		cg3::Point2i point = *it;
		std::cout << "(" << point.x() << "," << point.y() << ")" << " - ";
	}
	std::cout << std::endl;


	//Representation of the cartesian plane
	char plane[PLANE_WIDTH][PLANE_HEIGHT];



	/* ----- GRAHAM SCAN ----- */

	std::cout << std::endl << std::endl;

	std::cout << " >> GRAHAM SCAN" << std::endl << std::endl;

	//Clear/initialize the plane
	for (int x = 0; x < PLANE_WIDTH; x++) {
		for (int y = 0; y < PLANE_HEIGHT; y++) {
			plane[x][y] = ' ';
		}
	}

	//Set all initial points to "o"
	for (std::vector<cg3::Point2i>::iterator it = points.begin(); it != points.end(); it++) {
		plane[it->x()][it->y()] = 'o';
	}

	//Output container
	std::list<cg3::Point2i> outputConvexHull;

	//Computing convex hull
	//Template <double> would be not needed
	cg3::convexHull2D<int>(points.begin(), points.end(), std::back_inserter(outputConvexHull));

	//Alternative with containers
//    cg3::getConvexHull2D<int>(points, outputConvexHull);


	//Set all convex hull points to "x"
	for (std::list<cg3::Point2i>::iterator it = outputConvexHull.begin(); it != outputConvexHull.end(); it++) {
		plane[it->x()][it->y()] = 'x';
	}

	//Draw the plane
	for ( int y = PLANE_HEIGHT-1; y >= 0 ; --y ) {
		std::cout << y << "  " ;
		for ( int x = 0; x < PLANE_WIDTH; ++x ) {
			std::cout << plane[x][y] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "   ";
	for ( int x = 0; x < PLANE_WIDTH; ++x ) {
		std::cout << x << " ";
	}
	std::cout << std::endl << std::endl;

	//Printing solution
	std::cout << "Solution:" << std::endl;
	for (std::list<cg3::Point2i>::iterator it = outputConvexHull.begin(); it != outputConvexHull.end(); it++) {
		cg3::Point2i point = *it;
		std::cout << "(" << point.x() << "," << point.y() << ")" << " - ";
	}
	std::cout << std::endl;



	/* ----- INCREMENTAL CONVEX HULL ----- */

	std::cout << std::endl << std::endl;

	std::cout << " >> INCREMENTAL CONVEX HULL" << std::endl << std::endl;

	//Clear/initialize the plane
	for (int x = 0; x < PLANE_WIDTH; x++) {
		for (int y = 0; y < PLANE_HEIGHT; y++) {
			plane[x][y] = ' ';
		}
	}

	//Set all initial points to "o"
	for (std::vector<cg3::Point2i>::iterator it = points.begin(); it != points.end(); it++) {
		plane[it->x()][it->y()] = 'o';
	}



	//Add points in different ways
	cg3::IncrementalConvexHull<int> incrementalConvexHull(points.begin(), points.end()-4);

	incrementalConvexHull.addPoints(points.end()-4, points.end()-3);

	cg3::Point2i p2 = *(points.end()-2);
	incrementalConvexHull.addPoint(p2);

	cg3::Point2i p1 = *(points.end()-1);
	cg3::addPointToConvexHull(p1, incrementalConvexHull);

	//Alternative with container
//    cg3::IncrementalConvexHull2D<int> incrementalConvexHull(points);

	//Output convex hull
	std::list<cg3::Point2i> outputIncrementalConvexHull;
	incrementalConvexHull.convexHull(std::back_inserter(outputIncrementalConvexHull));

	//Set all convex hull points to "x"
	for (std::list<cg3::Point2i>::iterator it = outputIncrementalConvexHull.begin(); it != outputIncrementalConvexHull.end(); it++) {
		plane[it->x()][it->y()] = 'x';
	}

	//Draw the plane
	for ( int y = PLANE_HEIGHT-1; y >= 0 ; --y ) {
		std::cout << y << "  " ;
		for ( int x = 0; x < PLANE_WIDTH; ++x ) {
			std::cout << plane[x][y] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "   ";
	for ( int x = 0; x < PLANE_WIDTH; ++x ) {
		std::cout << x << " ";
	}
	std::cout << std::endl << std::endl;

	//Printing solution
	std::cout << "Solution:" << std::endl;
	for (std::list<cg3::Point2i>::iterator it = outputIncrementalConvexHull.begin(); it != outputIncrementalConvexHull.end(); it++) {
		cg3::Point2i point = *it;
		std::cout << "(" << point.x() << "," << point.y() << ")" << " - ";
	}
	std::cout << std::endl;

	incrementalConvexHull.clear();

    std::cout <<  std::endl << std::endl;
}
