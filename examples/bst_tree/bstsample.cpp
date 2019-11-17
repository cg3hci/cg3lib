/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "bstsample.h"

#include <iostream>
#include <string>

#include <vector>

#include <cg3/geometry/point2.h>

#include <cg3/data_structures/trees/bst.h>
//#include <cg3/data_structures/trees/avlleaf.h>
//#include <cg3/data_structures/trees/avlinner.h>
//#include <cg3/data_structures/trees/bstinner.h>
//#include <cg3/data_structures/trees/bstleaf.h>

/* Choose the one you prefer, you can use each one in the same way! */

typedef cg3::BST<int> BSTInt; //Default BST

//    typedef cg3::AVLLeaf<int> BSTInt;
//    typedef cg3::BSTLeaf<int> BSTInt;

//    typedef cg3::AVLInner<int> BSTInt;
//    typedef cg3::BSTInner<int> BSTInt;


/* Choose the one you prefer, you can use each one in the same way! */

typedef cg3::BST<int, std::string> BSTIntString; //Default BST

//    typedef cg3::AVLLeaf<int, std::string> BSTIntString;
//    typedef cg3::BSTLeaf<int, std::string> BSTIntString;

//    typedef cg3::AVLInner<int, std::string> BSTIntString;
//    typedef cg3::BSTInner<int, std::string> BSTIntString;


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

void BSTSample::execute()
{

    /* ----- BASIC USAGE ----- */

    //Vector of values for the construction
    std::vector<int> vec;
    vec.push_back(2);
    vec.push_back(10);
    vec.push_back(3);
    vec.push_back(25);

    //Creating BST (int) with default (<) comparator
    std::cout << "Creating BST (int keys and values) with default (<) comparator containing 2, 10, 3, 25..." << std::endl;
    BSTInt bst(vec);

    //Insert numbers: 12, 15, 45, 65, 100, 52
    std::cout << "Inserting numbers: 12, 15, 45, 65, 100, 52" << std::endl;
    bst.insert(12);
    bst.insert(15);
    bst.insert(45);
    bst.insert(65);
    bst.insert(100);
    bst.insert(52);

    //Iteration
    std::cout << "The BST contains:" << std::endl << "    ";
    for (int& number : bst)
        std::cout << number << " ";
    std::cout << std::endl;

    //Find number 2
    BSTInt::iterator queryIterator = bst.find(2);
    if (queryIterator != bst.end())
        std::cout << "Number 2 is in the binary search tree!" << std::endl;
    else
        std::cout << "Number 2 is NOT in the binary search tree!" << std::endl;

    //Erase
    std::cout << "Erasing number 2..." << std::endl;
    bst.erase(2);

    //Find number 2, after it has been erased
    if (bst.find(2) != bst.end())
        std::cout << "Number 2 is in the binary search tree!" << std::endl;
    else
        std::cout << "Number 2 is NOT in the binary search tree!" << std::endl;

    //Iteration with explicit iterators
    std::cout << "The BST contains:" << std::endl << "    ";
    for (BSTInt::iterator it = bst.begin(); it != bst.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    std::cout << std::endl;



    /* ----- RANGE BASED ITERATIONS ----- */

    //Iteration
    std::cout << "The BST contains (default iterator):" << std::endl << "    ";
    for (int& number : bst.getIterator())
        std::cout << number << " ";
    std::cout << std::endl;

    //Const iteration
    std::cout << "The BST contains (const):" << std::endl << "    ";
    for (const int& number : bst.getConstIterator())
        std::cout << number << " ";
    std::cout << std::endl;

    //Reverse iteration
    std::cout << "The BST contains (reverse):" << std::endl << "    ";
    for (int& number : bst.getReverseIterator())
        std::cout << number << " ";
    std::cout << std::endl;

    //Reverse const iteration
    std::cout << "The BST contains (const reverse):" << std::endl << "    ";
    for (const int& number : bst.getConstReverseIterator())
        std::cout << number << " ";
    std::cout << std::endl;



    std::cout << std::endl;


    /* ----- OTHER FUNCTIONS ----- */

    //Get min and max (through iterators)
    BSTInt::iterator minIterator = bst.getMin();
    if (minIterator != bst.end()) {
        int& minInt = *minIterator;
        std::cout << "Minimum node is: " << minInt << std::endl;
    }
    BSTInt::iterator maxIterator = bst.getMax();
    if (maxIterator != bst.end()) {
        std::cout << "Maximum node is: " << *maxIterator << std::endl;
    }

    //Range query in the interval 8 - 45
    std::cout << "Range query in the interval 8 - 45:" << std::endl << "    ";
    std::vector<BSTInt::iterator> rangeQueryResults;
    bst.rangeQuery(8, 45, std::back_inserter(rangeQueryResults));

    //Printing results
    for (BSTInt::iterator& it : rangeQueryResults) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //Erase the next of 52 (erase with iterators)
    std::cout << "Erasing the next of 52..." << std::endl;
    BSTInt::iterator it52 = bst.find(52);
    it52++;
    bst.erase(it52);

    //Erase values less than 30 (erase with iterators)
    std::cout << "Erasing numbers less than 30..." << std::endl;
    for (BSTInt::iterator it = bst.begin(); it != bst.end();) {
        if (*it < 30)
            bst.erase(it++); //When an iterator is erased, iterator is not automatically incremented!
        else
            it++;
    }

    //Size
    std::cout << "The BST contains " << bst.size() << " elements" << std::endl;

    //Clear
    std::cout << "Clear BST..." << std::endl;
    bst.clear();



    std::cout << std::endl;


    /* ----- KEY AND VALUE WITH DIFFERENT TYPES ----- */

    //BST (int, string) with custom comparator (> instead of <) and different key/value types
    std::cout << "Creating BST (int keys and string values) with reverse (>) comparator..." << std::endl;
    BSTIntString bst2(reverseComparator);

    //Insert numbers: 10,50 with their name as value
    std::cout << "Inserting numbers: 1, 5, 3, 10, 7" << std::endl;
    bst2.insert(10, "Ten");
    bst2.insert(50, "Fifty");

    //Reverse iteration (explicit)
    std::cout << "The BST contains (reverse):" << std::endl << "    ";
    for (BSTIntString::reverse_iterator it = bst2.rbegin(); it != bst2.rend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    //Vector of pairs <int, string> for construction with numbers: 1, 5, 3, 10, 7
    std::cout << "Construction with numbers: 1, 5, 3, 10, 7" << std::endl;
    std::vector<std::pair<int,std::string>> pairVec;
    pairVec.push_back(std::make_pair(1, "One"));
    pairVec.push_back(std::make_pair(5, "Five"));
    pairVec.push_back(std::make_pair(3, "Three"));
    pairVec.push_back(std::make_pair(10, "Ten"));
    pairVec.push_back(std::make_pair(7, "Seven"));

    //Construction -> previous values (10 and 50) will be deleted
    bst2.construction(pairVec);

    //Const iterator
    std::cout << "The BST contains:" << std::endl << "    ";
    for (BSTIntString::const_iterator it = bst2.cbegin(); it != bst2.cend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    //Change value with iterators (key is not changed!)
    std::cout << "Changing values: concatenating the string Number" << std::endl << "    ";
    for (std::string& number : bst2)
        number = "Number" + number;

    //Normal iteration
    std::cout << "The BST contains:" << std::endl << "    ";
    for (const std::string& number : bst2)
        std::cout << number << " ";
    std::cout << std::endl;



    std::cout << std::endl;


    /* ----- CUSTOM COMPARATOR (WITH FIELDS) USAGE ----- */

    //Creating BST with custom struct comparator
    std::cout << "Creating BST with custom struct comparator..." << std::endl;
	cg3::BST<cg3::Point2d, cg3::Point2d, CustomPointComparator> bst3(
				CustomPointComparator(cg3::Point2d(1,0)));
    //Adding points
	bst3.insert(cg3::Point2d(1,2));
	bst3.insert(cg3::Point2d(2,5));
	bst3.insert(cg3::Point2d(-4,5));
	bst3.insert(cg3::Point2d(8,8));

    //Normal iteration
    std::cout << "The BST contains:" << std::endl << "    ";
	for (const cg3::Point2d& number : bst3)
        std::cout << number << " ";
    std::cout << std::endl;

    //Creating BST with custom lambda comparator
    std::cout << "Creating BST with custom lambda comparator..." << std::endl;
	cg3::BST<cg3::Point2d> bst4(
				[](const cg3::Point2d& x, const cg3::Point2d& y)
    {
        return x > y;
    });
    //Adding points
	bst4.insert(cg3::Point2d(1,2));
	bst4.insert(cg3::Point2d(2,5));
	bst4.insert(cg3::Point2d(-4,5));
	bst4.insert(cg3::Point2d(8,8));

    //Normal iteration
    std::cout << "The BST contains:" << std::endl << "    ";
	for (const cg3::Point2d& number : bst4)
        std::cout << number << " ";
    std::cout << std::endl;


    std::cout << std::endl;
}

bool reverseComparator(const int& o1, const int& o2) {
    return o1 > o2;
}

