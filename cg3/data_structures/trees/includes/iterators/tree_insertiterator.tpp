/**
    @author Stefano Nuvoli
*/
#include "tree_insertiterator.h"


namespace cg3 {


/* --------- ITERATOR OPERATOR OVERLOAD --------- */

template <class B, class K>
TreeInsertIterator<B,K>& TreeInsertIterator<B,K>::operator=(const K key)
{
    this->bst->insert(key);

    return *this;
}

template <class B, class K>
TreeInsertIterator<B,K>& TreeInsertIterator<B,K>::operator*() {
    return *this;
}
template <class B, class K>
TreeInsertIterator<B,K>& TreeInsertIterator<B,K>::operator++() {
    return *this;
}
template <class B, class K>
TreeInsertIterator<B,K>& TreeInsertIterator<B,K>::operator++(int) {
    return *this;
}



}
