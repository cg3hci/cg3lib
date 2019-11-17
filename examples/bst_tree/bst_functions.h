/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_BST_FUNCTIONS_H
#define CG3_BST_FUNCTIONS_H

#include <cg3/geometry/point2.h>

#include <cg3/data_structures/trees/bst.h>
//#include <cg3/data_structures/trees/avlleaf.h>
//#include <cg3/data_structures/trees/avlinner.h>
//#include <cg3/data_structures/trees/bstinner.h>
//#include <cg3/data_structures/trees/bstleaf.h>

/* Choose the one you prefer, you can use each one in the same way! */

typedef cg3::BST<int> TreeInt; //Default BST (key only)

//    typedef cg3::AVLLeaf<int> TreeInt;
//    typedef cg3::BSTLeaf<int> TreeInt;

//    typedef cg3::AVLInner<int> TreeInt;
//    typedef cg3::BSTInner<int> TreeInt;


/* Choose the one you prefer, you can use each one in the same way! */

typedef cg3::BST<int, std::string> TreeIntString; //Default BST (key-value)

//    typedef cg3::AVLLeaf<int, std::string> TreeIntString;
//    typedef cg3::BSTLeaf<int, std::string> TreeIntString;

//    typedef cg3::AVLInner<int, std::string> TreeIntString;
//    typedef cg3::BSTInner<int, std::string> TreeIntString;

bool reverseComparator(const int& o1, const int& o2);

// Custom comparator for 2D points
struct CustomPointComparator {
	cg3::Point2d p;

	CustomPointComparator(cg3::Point2d p) {
		this->p = p;
	}

	bool operator()(const cg3::Point2d& o1, const cg3::Point2d& o2) {
		return p.dot(o1) < p.dot(o2);
	}
};

#endif // CG3_BST_FUNCTIONS_H
