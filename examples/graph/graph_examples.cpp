/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_examples.h"

#include <iostream>
#include <vector>

#include <cg3/data_structures/graphs/graph.h>
#include <cg3/algorithms/graph_algorithms.h>

/**
 * @brief Directed graph sample
 */
void GraphExamples::sampleBasic() {

    std::cout<< std::endl << " >> BASIC" << std::endl << std::endl;

    std::cout << "Create a directed graph..." << std::endl;
    //In constructor, cg3::GraphType::DIRECTED is the default type
	cg3::Graph<int> graph(cg3::Graph<int>::DIRECTED);

    //Add node 1 and 2
    std::cout << "Add node 1 and 2" << std::endl;
    cg3::Graph<int>::iterator it1 = graph.addNode(1);
    //"iterator" is a wrapper for NodeIterator
    cg3::Graph<int>::NodeIterator it2 = graph.addNode(2);


    if (graph.isAdjacent(1, 2))
        std::cout << "1 is adjacent to 2" << std::endl;
    else
        std::cout << "1 is NOT adjacent to 2" << std::endl;

    //Add edge (1,2) with weight 15.5
    std::cout << "Add edge (1,2) with weight 15.5" << std::endl;
    graph.addEdge(1, 2, 15.5);

    if (graph.isAdjacent(it1, it2))
        std::cout << "1 is adjacent to 2" << std::endl;
    else
        std::cout << "1 is NOT adjacent to 2" << std::endl;

    if (graph.isAdjacent(2, 1))
        std::cout << "2 is adjacent to 1" << std::endl;
    else
        std::cout << "2 is NOT adjacent to 1" << std::endl;


    //Change edge (1,2) weight to 10
    std::cout << "Change weight of (1,2) to 10" << std::endl;
    graph.setWeight(1, 2, 10.0);

    //Add edge (1,2) with weight 5
    std::cout << "Add edge (2,1) with weight 5" << std::endl;
    graph.addEdge(it2, it1, 5);

    //Print weights
    std::cout << "(1,2) weight is " << graph.getWeight(it1,it2) << std::endl;
    std::cout << "(2,1) weight is " << graph.getWeight(2,1) << std::endl;


    //Add node 3 and edge (3,2)
    std::cout << "Add node 3 and edge (3,2) with no weight" << std::endl;
    graph.addNode(3);
    cg3::Graph<int>::iterator it3 = graph.findNode(3); //We can use find to get iterators
    graph.addEdge(it3,it2);

    std::cout << "(3,2) weight is " << graph.getWeight(3,2) << " (default weight)" << std::endl;
    std::cout << "(2,3) weight is " << graph.getWeight(2,3) << " (infinite because the edge does not exists)" << std::endl;

    //Iteration on graph nodes
    std::cout << "Nodes of the graph: ";
    for (const int& node : graph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: " << std::endl;
    for (std::pair<const int, const int> pair : graph.edgeIterator()) {
        std::cout << "\t(" << pair.first << "," << pair.second << ") with weight " << graph.getWeight(pair.first, pair.second) << std::endl;
    }


    //Delete node 3
    std::cout << "Delete node 3" << std::endl;
    graph.deleteNode(it3);
    std::cout << "(3,2) weight is " << graph.getWeight(3,2) << " (infinite)" << std::endl;

    //Print data
    std::cout << "Graph: " << std::endl;
    for (const int& node : graph) {
        std::cout << node << " -> adjacent to: ";
        for (const int& adjacentNode : graph.adjacentIterator(node)) {
            std::cout << adjacentNode << " ";
        }
        std::cout << std::endl;
    }


    //Recompact the graph to save memory after node delete operations.
    //Read description in graph.h for further informations.
    std::cout << "Recompacting graph..." << std::endl;
    graph.recompact();


    //Print data
    std::cout << "Graph: " << std::endl;
    for (const int& node : graph) {
        std::cout << node << " -> adjacent to: ";
        for (const int& adjacentNode : graph.adjacentIterator(node)) {
            std::cout << adjacentNode << " ";
        }
        std::cout << std::endl;
    }

    //Iteration on graph edges
    std::cout << "Edges of the graph: " << std::endl;
    for (std::pair<const int, const int> pair : graph.edgeIterator()) {
        std::cout << "\t(" << pair.first << "," << pair.second << ") with weight " << graph.getWeight(pair.first, pair.second) << std::endl;
    }


    //Delete edge
    std::cout << "Delete nodes and edges" << std::endl;
    graph.deleteEdge(1,2);
    graph.deleteEdge(it2,it1);
    graph.deleteNode(2);
    graph.deleteNode(it1);


    //Iteration on graph nodes
    std::cout << "Nodes of the graph: ";
    for (const int& node : graph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: " << std::endl;
    for (std::pair<const int, const int> pair : graph.edgeIterator()) {
        std::cout << "\t(" << pair.first << "," << pair.second << ") with weight " << graph.getWeight(pair.first, pair.second) << std::endl;
    }

}

/**
 * @brief Directed graph sample
 */
void GraphExamples::sampleDirected() {

    std::cout<< std::endl << " >> DIRECTED" << std::endl << std::endl;

    std::cout << "Create a directed graph..." << std::endl;
    //In constructor, cg3::GraphType::DIRECTED is the default type
    cg3::Graph<int> dGraph;
    //cg3::Graph<int> dGraph(cg3::GraphType::DIRECTED);


    //Create the nodes
    std::cout << "Create nodes 1 and 2..." << std::endl;
    //Note that if you use the iterators in the operations, then
    //you have to be sure that they are pointing to an existing node
    //(that has not been deleted for example)
    cg3::Graph<int>::iterator it1 = dGraph.addNode(1);
    cg3::Graph<int>::iterator it2 = dGraph.addNode(2);



    //Check adjacency with iterators (faster)
    if (dGraph.isAdjacent(it1, it2)) {
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    }
    else {
        std::cout << "Node 1 has not an edge to node 2." << std::endl;
    }

    //Check adjacency with values (slower)
    if (dGraph.isAdjacent(1,2)) {
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    }
    else {
        std::cout << "Node 1 has not an edge to node 2." << std::endl;
    }


    //Create edge
    std::cout << "Create edge between 1 and 2..." << std::endl;

    //Faster using iterators
    dGraph.addEdge(it1, it2);

    //No changes: the graph has already that edge
    //Slow using values
    dGraph.addEdge(1, 2);



    //Iteration on graph nodes
    std::cout << "Nodes of the graph: ";
    for (const int& node : dGraph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: " << std::endl;
    for (std::pair<const int, const int> pair : dGraph.edgeIterator()) {
        std::cout << "\t(" << pair.first << "," << pair.second << ") with weight " << dGraph.getWeight(pair.first, pair.second) << std::endl;
    }



    //Check adjacency (slow)
    if (dGraph.isAdjacent(1, 2))
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    else
        std::cout << "Node 1 has not an edge to node 2." << std::endl;

    if (dGraph.isAdjacent(2, 1))
        std::cout << "Node 2 has an edge to node 1." << std::endl;
    else
        std::cout << "Node 2 has not an edge to node 1." << std::endl;




    std::cout << "Delete edge between node 1 and node 2" << std::endl;
    //Delete edge (fast with iterators)
    dGraph.deleteEdge(it1, it2);

    //No changes: the graph has already that edge
    //Slow using values
    dGraph.deleteEdge(1, 2);



    //Check adjacency (fast)
    if (dGraph.isAdjacent(it1, it2))
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    else
        std::cout << "Node 1 has not an edge to node 2." << std::endl;

    //Check adjacency (slow)
    if (dGraph.isAdjacent(2, 1))
        std::cout << "Node 2 has an edge to node 1." << std::endl;
    else
        std::cout << "Node 2 has not an edge to node 1." << std::endl;



    //Find node
    cg3::Graph<int>::iterator itFind = dGraph.findNode(2);
    if (itFind != dGraph.end())
        std::cout << "Node 2 is in the graph." << std::endl;
    else
        std::cout << "Node 2 is not in the graph." << std::endl;




    //Delete node with iterator (it is not slower)
    bool deleteResult = dGraph.deleteNode(2);
    if (deleteResult)
        std::cout << "Node 2 has been found in the graph and it has been deleted." << std::endl;
    else
        std::cout << "Node 2 has not been found in the graph. No changes." << std::endl;

    //Delete node with iterator (it is not faster)
    deleteResult = dGraph.deleteNode(itFind);
    if (deleteResult)
        std::cout << "Node 2 has been found in the graph and it has been deleted." << std::endl;
    else
        std::cout << "Node 2 has not been found in the graph. No changes." << std::endl;


    //Find node
    cg3::Graph<int>::iterator itFind2 = dGraph.findNode(2);
    if (itFind2 != dGraph.end())
        std::cout << "Node 2 is in the graph." << std::endl;
    else
        std::cout << "Node 2 is not in the graph." << std::endl;

}

/**
 * @brief Undirected graph sample
 */
void GraphExamples::sampleUndirected() {

    std::cout << std::endl << " >> UNDIRECTED" << std::endl << std::endl;

    //Create graph
    std::cout << "Create undirected graph..." << std::endl;
	cg3::Graph<int> uGraph(cg3::Graph<int>::UNDIRECTED); //cg3::GraphType::DIRECTED is the default type



    //Create the nodes
    std::cout << "Create nodes 1 and 2..." << std::endl;
    //Note that if you use the iterators in the operations, then
    //you have to be sure that they are pointing to an existing node
    //(that has not been deleted for example)
    cg3::Graph<int>::iterator it1 = uGraph.addNode(1);
    cg3::Graph<int>::iterator it2 = uGraph.addNode(2);




    //Check adjacency with iterators (faster)
    if (uGraph.isAdjacent(it1, it2)) {
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    }
    else {
        std::cout << "Node 1 has not an edge to node 2." << std::endl;
    }

    //Check adjacency with values (slower)
    if (uGraph.isAdjacent(1,2)) {
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    }
    else {
        std::cout << "Node 1 has not an edge to node 2." << std::endl;
    }



    //Create edge
    std::cout << "Create edge between 1 and 2..." << std::endl;

    //Faster using iterators
    uGraph.addEdge(it1, it2);

    //No changes: the graph has already that edge
    //Slow using values
    uGraph.addEdge(1, 2);



    //Iteration on graph nodes
    std::cout << "Nodes of the graph: ";
    for (const int& node : uGraph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: " << std::endl;
    for (std::pair<const int, const int> pair : uGraph.edgeIterator()) {
        std::cout << "\t(" << pair.first << "," << pair.second << ") with weight " << uGraph.getWeight(pair.first, pair.second) << std::endl;
    }




    //Check adjacency (slow)
    if (uGraph.isAdjacent(1, 2))
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    else
        std::cout << "Node 1 has not an edge to node 2." << std::endl;

    if (uGraph.isAdjacent(2, 1))
        std::cout << "Node 2 has an edge to node 1." << std::endl;
    else
        std::cout << "Node 2 has not an edge to node 1." << std::endl;



    std::cout << "Delete edge between node 1 and node 2" << std::endl;
    //Delete edge (fast with iterators)
    uGraph.deleteEdge(it1, it2);

    //No changes: the graph has already that edge
    //Slow using values
    uGraph.deleteEdge(1, 2);



    //Check adjacency (fast)
    if (uGraph.isAdjacent(it1, it2))
        std::cout << "Node 1 has an edge to node 2." << std::endl;
    else
        std::cout << "Node 1 has not an edge to node 2." << std::endl;

    //Check adjacency (slow)
    if (uGraph.isAdjacent(2, 1))
        std::cout << "Node 2 has an edge to node 1." << std::endl;
    else
        std::cout << "Node 2 has not an edge to node 1." << std::endl;



    //Find node
    cg3::Graph<int>::iterator itFind = uGraph.findNode(2);
    if (itFind != uGraph.end())
        std::cout << "Node 2 is in the graph." << std::endl;
    else
        std::cout << "Node 2 is not in the graph." << std::endl;



    //Delete node with iterator (it is not faster)
    bool deleteResult = uGraph.deleteNode(itFind);
    if (deleteResult)
        std::cout << "Node 2 has been found in the graph and it has been deleted." << std::endl;
    else
        std::cout << "Node 2 has not been found in the graph. No changes." << std::endl;

    //Delete node with value (it is not slower)
    deleteResult = uGraph.deleteNode(2);
    if (deleteResult)
        std::cout << "Node 2 has been found in the graph and it has been deleted." << std::endl;
    else
        std::cout << "Node 2 has not been found in the graph. No changes." << std::endl;



    //Find node
    cg3::Graph<int>::iterator itFind2 = uGraph.findNode(2);
    if (itFind2 != uGraph.end())
        std::cout << "Node 2 is in the graph." << std::endl;
    else
        std::cout << "Node 2 is not in the graph." << std::endl;

}


/**
 * @brief Undirected weight graph sample
 */
void GraphExamples::sampleWeighted() {

    std::cout << std::endl << " >> UNDIRECTED WEIGHTED" << std::endl << std::endl;

    //Create graph
    std::cout << "Create undirected graph..." << std::endl;
	cg3::Graph<int> graph(cg3::Graph<int>::UNDIRECTED); //cg3::GraphType::DIRECTED is the default type


    double weight;


    //Create the nodes
    std::cout << "Create nodes 1 and 2..." << std::endl;
    //Note that if you use the iterators in the operations, then
    //you have to be sure that they are pointing to an existing node
    //(that has not been deleted for example)
    cg3::Graph<int>::iterator it1 = graph.addNode(1);
    cg3::Graph<int>::iterator it2 = graph.addNode(2);



    //No weight
    weight = graph.getWeight(it1, it2);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 2 are not adjacent! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,2): Weight is: " << weight << std::endl;


    //Add edge with undefined weight
    std::cout << "Add edge between nodes 1 and 2 (no weight defined)..." << std::endl;
    graph.addEdge(1, 2); //Default weight: 0

    weight = graph.getWeight(it1, it2);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 2 are not adjacent! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,2): Weight is: " << weight << std::endl;



    //Add edge with weight 10 (replacing)
    std::cout << "Add edge between nodes 1 and 2 (weight 10)... It replaces the last weight of the edge." << std::endl;
    graph.addEdge(1, 2, 10); //It replaces the weight

    weight = graph.getWeight(it1, it2);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 2 are not adjacent! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,2): Weight is: " << weight << std::endl;



    //Add edge with weight 10
    std::cout << "Set weight to 27..." << std::endl;
    graph.setWeight(it1, it2, 27);

    weight = graph.getWeight(it1, it2);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 2 are not adjacent! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,2): Weight is: " << weight << std::endl;



    //Using no iterators (slower)
    std::cout << "Double the weight (not using the iterators)..." << std::endl;
    graph.setWeight(1, 2, graph.getWeight(1, 2) * 2); //Double the weight

    weight = graph.getWeight(1, 2);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 2 are not adjacent! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,2): Weight is: " << weight << std::endl;



    std::cout << "Setting weight of an edge of the node 3 (that is not in the graph)..." << std::endl;
    //Setting the weight with a node (3) that is not in the graph
    graph.setWeight(1, 3, 10); //No effect

    //Getting the weight with a node (3) that is not in the graph
    weight = graph.getWeight(1, 3);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 3 are not adjacent or a node does not exist! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,3): Weight is: " << weight << std::endl;


    // Add the node 3
    std::cout << "Add node 3..." << std::endl;
    graph.addNode(3);



    std::cout << "Setting weight of the edge (1,3) (that is not in the graph)..." << std::endl;
    //Setting the weight of an edge (1,3) that is not in the graph
    graph.setWeight(1, 3, 10); //No effect

    //Getting the weight of an edge (1,3) that is not in the graph
    weight = graph.getWeight(1, 3);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 3 are not adjacent or a node does not exist! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,3): Weight is: " << weight << std::endl;



    //Add edge
    std::cout << "Add edge (3,1) with weight 20..." << std::endl;
    graph.addEdge(3, 1, 20);

    //Getting the weight of an edge (1,3) that is not in the graph
    weight = graph.getWeight(1, 3);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 3 are not adjacent or a node does not exist! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,3): Weight is: " << weight << std::endl;




    std::cout << "Setting weight of the edge (1,3) to 40 (the graph is undirected)..." << std::endl;
    //Setting the weight of an edge (1,3) that is not in the graph
    graph.setWeight(1, 3, 40); //No effect

    //Getting the weight of an edge (1,3) that is not in the graph
    weight = graph.getWeight(1, 3);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 1 and 3 are not adjacent or a node does not exist! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(1,3): Weight is: " << weight << std::endl;

    //Getting the weight of an edge (1,3) that is not in the graph
    weight = graph.getWeight(3,1);
    if (weight == cg3::Graph<int>::MAX_WEIGHT)
        std::cout << "The nodes 3 and 1 are not adjacent or a node does not exist! Weight returned is: " << weight << std::endl;
    else
        std::cout << "(3,1): Weight is: " << weight << std::endl;



    //Iteration on graph nodes
    std::cout << "Nodes of the graph: ";
    for (const int& node : graph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: " << std::endl;
    for (std::pair<const int, const int> pair : graph.edgeIterator()) {
        std::cout << "\t(" << pair.first << "," << pair.second << ") with weight " << graph.getWeight(pair.first, pair.second) << std::endl;
    }

}



/**
 * @brief Directed graph iteration sample
 */
void GraphExamples::sampleIterators() {

    std::cout<< std::endl << " >> ITERATORS" << std::endl << std::endl;

    //Create directed graph
    std::cout << "Create directed graph..." << std::endl;
    cg3::Graph<int> graph;

    //Iteration on nodes of the empty graph
    std::cout << "Nodes of the graph: ";
    for (const int& node : graph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: ";
    for (std::pair<const int, const int> pair : graph.edgeIterator()) {
        std::cout << "(" << pair.first << "," << pair.second << ") - ";
    }
    std::cout << std::endl;


    std::cout << std::endl;


    //Add elements to the graphs
    std::cout << "Add nodes 1, 2, 4, 3 and edges (1,1) - (1,2) - (1,3) - (1,4) - (2,1) - (3,1) - (3,2) - (4,3)" << std::endl;
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(4);
    graph.addNode(3);
    graph.addEdge(1,1);
    graph.addEdge(1,2);
    graph.addEdge(1,3);
    graph.addEdge(1,4);
    graph.addEdge(2,1);    
    graph.addEdge(3,1);
    graph.addEdge(3,2);
    graph.addEdge(4,3);

    //Iteration on graph nodes
    std::cout << "Nodes of the graph: ";
    for (const int& node : graph) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    //Iteration on graph edges
    std::cout << "Edges of the graph: ";
    for (std::pair<const int, const int> pair : graph.edgeIterator()) {
        std::cout << "(" << pair.first << "," << pair.second << ") - ";
    }
    std::cout << std::endl;

    std::cout << std::endl;



    //Adjacencies
    std::cout << "Adjacencies: " << std::endl;
    for (const int& node : graph) {
        std::cout << node << " -> ";
        for (const int& adjacentNode : graph.adjacentIterator(node)) {
            std::cout << adjacentNode << " ";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;

    //Adjacencies with explicit iterators
    std::cout << "Adjacencies (explicit iterators): " << std::endl;
    for (cg3::Graph<int>::iterator it = graph.begin(); it != graph.end(); it++) {
        std::cout << *it << " -> ";
        for (cg3::Graph<int>::AdjacentIterator itAdj = graph.adjacentBegin(it);
             itAdj != graph.adjacentEnd(it); itAdj++)
        {
            std::cout << *itAdj << " ";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;


    //Iteration on graph using explicit node iterators
    std::cout << "Nodes of the graph (explicit): ";
    for (cg3::Graph<int>::iterator it = graph.begin(); it != graph.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //Iteration on graph using explicit edge iterators
    std::cout << "Edges of the graph (explicit): ";
    for (cg3::Graph<int>::EdgeIterator it = graph.edgeBegin(); it != graph.edgeEnd(); it++) {
        std::pair<const int, const int> edge = *it;
        std::cout << "(" << edge.first << "," << edge.second << ") - ";
    }
    std::cout << std::endl;


    std::cout << std::endl;



    //Iteration on adjacent nodes of node "1"
    std::cout << "Node 1 -> ";
    for (const int& adjacentNode : graph.adjacentIterator(1)) {
        std::cout << adjacentNode << " ";
    }
    std::cout << std::endl;

    //Iteration on adjacent nodes of node "2" using iterators
    std::cout << "Node 2 -> ";
    cg3::Graph<int>::iterator nodeIt2 = graph.findNode(2);
    for (const int& adjacentNode : graph.adjacentIterator(nodeIt2)) {
        std::cout << adjacentNode << " ";
    }
    std::cout << std::endl;

    //Iteration on adjacent nodes of node "3" using explicit iterators
    std::cout << "Node 3 -> ";
    for (cg3::Graph<int>::AdjacentIterator itAdj = graph.adjacentBegin(3);
         itAdj != graph.adjacentEnd(3); itAdj++)
    {
        std::cout << *itAdj << " ";
    }
    std::cout << std::endl;

    //Iteration on adjacent nodes of node "4" using explicit iterators with a node iterator
    std::cout << "Node 4 -> ";
    cg3::Graph<int>::iterator nodeIt4 = graph.findNode(4);
    for (cg3::Graph<int>::AdjacentIterator itAdj = graph.adjacentBegin(nodeIt4);
         itAdj != graph.adjacentEnd(nodeIt4); itAdj++)
    {
        std::cout << *itAdj << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;



    //Delete nodes using adjacent node iterators
    std::cout << "Delete nodes adjacent to node 4...";
    for (cg3::Graph<int>::AdjacentIterator it = graph.adjacentBegin(nodeIt4);
         it != graph.adjacentEnd(nodeIt4);)
    {
        graph.deleteNode(it++);
    }
    std::cout << std::endl;

    //Adjacencies
    std::cout << "Adjacencies: " << std::endl;
    for (const int& node : graph) {
        std::cout << node << " -> ";
        for (const int& adjacentNode : graph.adjacentIterator(node)) {
            std::cout << adjacentNode << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;



    //Delete edges using adjacent node iterators
    std::cout << "Delete edges of node 1...";
    cg3::Graph<int>::iterator nodeIt1 = graph.findNode(1);
    for (cg3::Graph<int>::AdjacentIterator it = graph.adjacentBegin(nodeIt1);
         it != graph.adjacentEnd(nodeIt1);)
    {
        graph.deleteEdge(nodeIt1, it++);
    }
    std::cout << std::endl;

    //Adjacencies
    std::cout << "Adjacencies: " << std::endl;
    for (const int& node : graph) {
        std::cout << node << " -> ";
        for (const int& adjacentNode : graph.adjacentIterator(node)) {
            std::cout << adjacentNode << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}




/**
 * @brief Dijkstra sample
 */
void GraphExamples::sampleDijkstra() {

    std::cout << std::endl << " >> DIJKSTRA" << std::endl << std::endl;

    std::cout << "Create a graph of 10 nodes with some edges..." << std::endl;

	cg3::Graph<int> g(cg3::Graph<int>::UNDIRECTED);

    //Add nodes
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    g.addNode(6);
    g.addNode(7);
    g.addNode(8);
    g.addNode(9);

    //Add edges
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    std::cout << std::endl;


    //Execute dijkstra
    std::cout << "Execute Dijkstra algorithm (source is 0)..." << std::endl;
    cg3::DijkstraResult<int> pathMap0 = cg3::dijkstra(g, 0);

    std::cout << std::endl;

    for (const int& node : g) {
        cg3::DijkstraResult<int>::iterator findIt = pathMap0.find(node);

        std::cout << "0 to " << node << "\t->\t";

        if (findIt != pathMap0.end()) {
            cg3::GraphPath<int>& graphPath = findIt->second;

            std::cout << "Cost: " << graphPath.cost << "\tPath: ";

            for (int pathNode : graphPath.path) {
                std::cout << pathNode << " ";
            }
        }
        else {
            std::cout << "No path found!";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    //Execute dijkstra using source iterator (we use std::map<int, cg3::GraphPath<int>>
    //instead of DijkstraResult<int>)
    std::cout << "Execute Dijkstra algorithm (source is 2) using iterators..." << std::endl;
    cg3::Graph<int>::iterator it2 = g.findNode(2);
    std::map<int, cg3::GraphPath<int>> pathMap1 = cg3::dijkstra(g, it2);

    std::cout << std::endl;

    for (const int& node : g.nodeIterator()) {
        std::map<int, cg3::GraphPath<int>>::iterator findIt = pathMap1.find(node);

        std::cout << *it2 << " to " << node << "\t->\t";

        if (findIt != pathMap1.end()) {
            cg3::GraphPath<int>& graphPath = findIt->second;

            std::cout << "Cost: " << graphPath.cost << "\tPath: ";

            for (int pathNode : graphPath.path) {
                std::cout << pathNode << " ";
            }
        }
        else {
            std::cout << "No path found!";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;

    //Execute dijkstra to get the shortest path from source to destination.
    //We do not need a map
    cg3::GraphPath<int> path14 = cg3::dijkstra(g, 1, 4);
    std::cout << "Single path: \t 1 to 4 -> ";
    if (!path14.path.empty()) {
        std::cout << "Cost: " << path14.cost << "\tPath: ";

        for (int pathNode : path14.path) {
            std::cout << pathNode << " ";
        }
    }
    else {
        std::cout << "No path found!";
    }

    std::cout << std::endl;

    //Execute dijkstra to get the shortest path from source to destination.
    //We do not need a map
    cg3::GraphPath<int> path29 = cg3::dijkstra(g, 2, 9);
    std::cout << "Single path: \t 2 to 9 -> ";
    if (!path29.path.empty()) {
        std::cout << "Cost: " << path29.cost << "\tPath: ";

        for (int pathNode : path29.path) {
            std::cout << pathNode << " ";
        }
    }
    else {
        std::cout << "No path found!";
    }

    std::cout << std::endl;

    //Execute dijkstra to get the shortest path from source to destination using iterators
    //We do not need a map
    cg3::Graph<int>::iterator it1 = g.findNode(1);
    cg3::Graph<int>::iterator it6 = g.findNode(6);
    cg3::GraphPath<int> path16 = cg3::dijkstra(g, it1, it6);
    std::cout << "Single path (it): \t 1 to 6 -> ";
    if (!path16.path.empty()) {
        std::cout << "Cost: " << path16.cost << "\tPath: ";

        for (int pathNode : path16.path) {
            std::cout << pathNode << " ";
        }
    }
    else {
        std::cout << "No path found!";
    }

    std::cout << std::endl;
}
