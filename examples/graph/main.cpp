/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <iostream>

#include <cg3/cg3lib.h>
#include "graph_examples.h"

int main(int argc, char *argv[])
{
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

	std::cout << "------ Graph sample ------" << std::endl << std::endl;

	GraphExamples::sampleBasic();
	std::cout << std::endl;
	GraphExamples::sampleDirected();
	std::cout << std::endl;
	GraphExamples::sampleUndirected();
	std::cout << std::endl;
	GraphExamples::sampleWeighted();
	std::cout << std::endl;
	GraphExamples::sampleIterators();
	std::cout << std::endl;
	GraphExamples::sampleDijkstra();
}
