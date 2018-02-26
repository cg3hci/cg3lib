/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "graph_genericnodeiterator.h"

namespace cg3 {


/* ----- CONSTRUCTORS ----- */

template <class T>
Graph<T>::GenericNodeIterator::GenericNodeIterator(
        Graph<T>* graph) :
    graph(graph)
{
    this->node = nullptr;
}


template <class T>
Graph<T>::GenericNodeIterator::GenericNodeIterator(
        Graph<T>* graph,
        typename Graph<T>::Node* node) :
    graph(graph),
    node(node)
{

}



}
