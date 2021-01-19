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
Graph<T>::GenericNodeIterator::GenericNodeIterator() :
    GenericNodeIterator(nullptr, -1)
{

}


template <class T>
Graph<T>::GenericNodeIterator::GenericNodeIterator(
        const Graph<T>* graph) :
    GenericNodeIterator(graph, -1)
{

}


template <class T>
Graph<T>::GenericNodeIterator::GenericNodeIterator(
        const Graph<T>* graph,
        long long int id) :
    graph(graph),
    id(id)
{

}



}
