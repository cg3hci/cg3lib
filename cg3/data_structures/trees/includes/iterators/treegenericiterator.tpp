/**
    @author Stefano Nuvoli
*/
#include "treegenericiterator.h"

#include <utility>

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <class B, class N>
TreeGenericIterator<B,N>::TreeGenericIterator(B* bst, N* node)
{
    this->bst = bst;
    this->node = node;
}



}
