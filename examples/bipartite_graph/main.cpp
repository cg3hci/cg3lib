/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <iostream>

#include <cg3/cg3lib.h>
#include <cg3/data_structures/graphs/bipartite_graph.h>

int main(int argc, char *argv[])
{
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

	std::cout << "------ Bipartite Graph sample ------" << std::endl << std::endl;

	//this bipartite graph connects strings to integers
	//every string represent an integer.
	cg3::BipartiteGraph<std::string, int> bigraph;
	bigraph.addLeftNode("2");
	bigraph.addLeftNode("3");
	bigraph.addLeftNode("4");
	bigraph.addLeftNode("5");
	bigraph.addRightNode(10);
	bigraph.addRightNode(12);
	bigraph.addRightNode(15);
	bigraph.addRightNode(17);
	bigraph.addRightNode(20);
	bigraph.addRightNode(24);

	//every arc between u and v means that u is divisor of v
	bigraph.addArc("2", 10);
	bigraph.addArc("2", 12);
	bigraph.addArc("2", 20);
	bigraph.addArc("2", 24);
	bigraph.addArc("3", 12);
	bigraph.addArc("3", 15);
	bigraph.addArc("3", 24);
	bigraph.addArc("4", 12);
	bigraph.addArc("4", 20);
	bigraph.addArc("4", 24);
	bigraph.addArc("5", 10);
	bigraph.addArc("5", 15);
	bigraph.addArc("5", 20);

	std::cout << "Multiples of 3: \n";
	for (const int& v : bigraph.adjacentLeftNodeIterator("3")){
		std::cout << "\t" << std::to_string(v) << "\n";
	}

	std::cout << "Divisors of 24: \n";
	for (const std::string& u : bigraph.adjacentRightNodeIterator(24)){
		std::cout << "\t" << u << "\n";
	}

	try {
		std::cout << "\nDivisors of 22: \n";
		for (const std::string& u : bigraph.adjacentRightNodeIterator(22)){
			std::cout << "\t" << u << "\n";
		}
	}
	catch(std::out_of_range& e){
		std::cout << e.what() << ": 22 not found.\n\n";
	}

	bigraph.deleteLeftNode("4");
	std::cout << "Divisors of 24 after removing unode 4: \n";
	for (const std::string& u : bigraph.adjacentRightNodeIterator(24)){
		std::cout << "\t" << u << "\n";
	}

	bigraph.addArc("4", 22); //no arcs are added here

	std::cout <<  std::endl << std::endl;
}
