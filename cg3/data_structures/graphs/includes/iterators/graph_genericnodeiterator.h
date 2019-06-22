#ifndef CG3_GRAPH_GENERICNODEITERATOR_H
#define CG3_GRAPH_GENERICNODEITERATOR_H

#include "../../graph.h"

namespace cg3 {

/**
 * @brief The node iterator of a graph
 */
template <class T>
class Graph<T>::GenericNodeIterator
{

    friend class Graph<T>;

protected:

    /* Constructors */


    inline GenericNodeIterator();

    inline GenericNodeIterator(
            const Graph<T>* graph);

    inline GenericNodeIterator(
            const Graph<T>* graph,
            long long int id);


    /* Fields */

    const Graph<T>* graph;
    long long int id;

};


}

#include "graph_genericnodeiterator.cpp"

#endif // CG3_GRAPH_GENERICNODEITERATOR_H
