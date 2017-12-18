/**
    @author Stefano Nuvoli
*/
#include "graph_node.h"

namespace cg3 {

/**
 * @brief Default constructor
 * @param[in] value Value of the node
 * @param[in] id If of the node in the current graph
 */
template <class T>
Graph<T>::Node::Node(const T& value, const size_t id)
{
    this->value = value;
    this->id = id;
}


}
