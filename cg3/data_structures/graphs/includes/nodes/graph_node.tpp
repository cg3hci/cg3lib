/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_node.h"

namespace cg3 {

/**
 * @brief Default constructor
 * @param[in] value Value of the node
 * @param[in] id ID of the node in the current graph
 */
template <class T>
Graph<T>::Node::Node() :
    id(-1), value()
{
}

/**
 * @brief Default constructor
 * @param[in] value Value of the node
 * @param[in] id If of the node in the current graph
 */
template <class T>
Graph<T>::Node::Node(const T& value, const size_t id) :
    id(id), value(value)
{
}

template<class T>
void Graph<T>::Node::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3GraphNode", binaryFile, id, value, adjacentNodes);
}

template<class T>
void Graph<T>::Node::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3GraphNode", binaryFile, id, value, adjacentNodes);
}


}
