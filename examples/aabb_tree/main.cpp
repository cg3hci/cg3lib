/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include <iostream>
#include <set>

#include <cg3/cg3lib.h>
#include <cg3/utilities/timer.h>

#include "aabb_functions.h"


int main(int argc, char *argv[])
{
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

	std::cout << "------ Axis Aligned Bounding Box Tree sample ------" << std::endl << std::endl;

	/* ----- BASIC USAGE ----- */

	//Defining an alias for a 2-dimensional AABB tree
	//The second argument type must have the copy constructor
	typedef cg3::AABBTree<2, Segment2D, std::string> AABBTree;


	//Creating vector for construction with object ([2,4], [3,1]) | ([5,9], [8,1])
	std::cout << "Construction objects: ([2,4], [3,1]) | ([5,9], [8,1])" << std::endl;
	std::vector<std::pair<Segment2D, std::string>> segmentVec;
	segmentVec.push_back(std::make_pair(Segment2D(Point2D(2,4),Point2D(3,1)), "([2,4], [3,1])"));
	segmentVec.push_back(std::make_pair(Segment2D(Point2D(5,9),Point2D(8,1)), "([5,9], [8,1])"));


	//Creating AABBtree (for Segment2D)
	std::cout << "Creating AABB trees with comparators..." << std::endl;
	AABBTree aabbTree(
				segmentVec,
				&aabbValueExtractor, //AABB value extractor
				&segment2DCustomComparator); //Comparator (if omitted, < is the default)


	//Insert objects: ([-1,-5], [3,2]) | ([1,2], [4,3]) | ([4,3], [4,8])
	std::cout << "Inserting objects: ([-1,-5], [3,2]) | ([1,2], [4,3]) | ([4,3], [4,8])" << std::endl;
	aabbTree.insert(Segment2D(Point2D(-1,-5),Point2D(3,2)), "([-1,-5], [3,2])");
	aabbTree.insert(Segment2D(Point2D(1,2),Point2D(4,3)), "([1,2], [4,3])");
	aabbTree.insert(Segment2D(Point2D(4,3),Point2D(4,8)), "([4,3], [4,8])");

	//Iteration
	std::cout << "The AABB tree contains:" << std::endl << "    ";
	for (std::string& objectString : aabbTree)
		std::cout << objectString << " | ";
	std::cout << std::endl;


	//Find object ([2,4], [3,1])
	AABBTree::iterator queryIterator = aabbTree.find(Segment2D(Point2D(2,4),Point2D(3,1)));
	if (queryIterator != aabbTree.end())
		std::cout << "Object ([2,4], [3,1]) is in the AABB tree!" << std::endl;
	else
		std::cout << "Object ([2,4], [3,1]) is NOT in the AABB tree!" << std::endl;

	//Erase
	std::cout << "Erasing object ([2,4], [3,1])..." << std::endl;
	aabbTree.erase(Segment2D(Point2D(2,4),Point2D(3,1)));

	//Iteration with explicit iterators
	std::cout << "The AABB tree contains:" << std::endl << "    ";
	for (AABBTree::iterator it = aabbTree.begin(); it != aabbTree.end(); it++) {
		std::cout << *it << " | ";
	}
	std::cout << std::endl;

	std::cout << std::endl;



	 /* ----- QUERY FUNCTIONS ----- */


	//Overlap query (only overlaps of AABBs) for the segment ([0,3], [8,10])
	std::cout << "AABB overlaps: segment ([0,3], [8,10]) -> ";
	if (aabbTree.aabbOverlapCheck(Segment2D(Point2D(0,3),Point2D(8,10)))) {
		std::cout << "Found at least an overlap";
	}
	else {
		std::cout << "Found NO overlaps";
	}
	std::cout << std::endl << " ->    ";

	std::vector<AABBTree::iterator> aabbQueryResults;
	aabbTree.aabbOverlapQuery(
				Segment2D(Point2D(0,3),Point2D(8,10)),
				std::back_inserter(aabbQueryResults));

	for (AABBTree::iterator& it : aabbQueryResults) {
		std::cout << *it << " | ";
	}
	std::cout << std::endl;


	//Overlap query (with custom intersection checker) for the segment ([0,3], [8,10])
	std::cout << "Intersections with custom intersection checker: segment ([0,3], [8,10]) -> ";
	if (aabbTree.aabbOverlapCheck(Segment2D(Point2D(0,3),Point2D(8,10))), &segment2DIntersectionChecker) {
		std::cout << "Found at least an overlap";
	}
	else {
		std::cout << "Found NO overlaps";
	}
	std::cout << std::endl << " ->    ";

	std::vector<AABBTree::iterator> intersectionQueryResults;
	aabbTree.aabbOverlapQuery(
				Segment2D(Point2D(0,3),Point2D(8,10)),
				std::back_inserter(intersectionQueryResults),
				&segment2DIntersectionChecker);

	for (AABBTree::iterator& it : intersectionQueryResults) {
		std::cout << *it << " | ";
	}
	std::cout << std::endl;



	//Overlap query (with custom intersection checker) for the segment ([20,30], [80,10])
	std::cout << "Intersections with custom intersection checker: segment ([20,30], [80,10]) -> ";
	if (aabbTree.aabbOverlapCheck(Segment2D(Point2D(20,30),Point2D(80,10)), &segment2DIntersectionChecker)) {
		std::cout << "Found at least an overlap";
	}
	else {
		std::cout << "Found NO overlaps";
	}
	std::cout << std::endl << " ->    ";

	std::vector<AABBTree::iterator> intersectionQueryResults2;
	aabbTree.aabbOverlapQuery(
				Segment2D(Point2D(20,30),Point2D(80,10)),
				std::back_inserter(intersectionQueryResults2),
				&segment2DIntersectionChecker);

	for (AABBTree::iterator& it : intersectionQueryResults2) {
		std::cout << *it << " | ";
	}
	std::cout << std::endl;

	std::cout << std::endl;



	/* ----- OTHER FUNCTIONS ----- */

	//Get min and max (through iterators)
	AABBTree::iterator minIterator = aabbTree.getMin();
	if (minIterator != aabbTree.end()) {
		std::string& minObjectString = *minIterator;
		std::cout << "Minimum node is: " << minObjectString << std::endl;
	}
	AABBTree::iterator maxIterator = aabbTree.getMax();
	if (maxIterator != aabbTree.end()) {
		std::cout << "Maximum node is: " << *maxIterator << std::endl;
	}

	//Size
	std::cout << "The AABB tree contains " << aabbTree.size() << " elements" << std::endl;

	//Iteration with explicit iterators
	std::cout << "The AABB tree contains (reverse):" << std::endl << "    ";
	for (AABBTree::reverse_iterator it = aabbTree.rbegin(); it != aabbTree.rend(); it++) {
		std::cout << *it << " | ";
	}
	std::cout << std::endl;

	//Clear
	std::cout << "Clear AABB tree..." << std::endl;
	aabbTree.clear();


	std::cout << std::endl;

    std::cout <<  std::endl << std::endl;
}
