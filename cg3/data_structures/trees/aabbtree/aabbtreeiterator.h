/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBTREEITERATOR_H
#define CG3_AABBTREEITERATOR_H

#include "../aabbtree.h"

namespace cg3 {

/**
 * @brief The iterator for the binary search tree
 */
template <int D, class K, class T>
class AABBTree<D,K,T>::Iterator {

    friend class AABBTree<D,K,T>;

public:

    /* Constructors/destructor */

    Iterator(AABBTree<D,K,T>::Node* node);



    /* Iterator operators */

    T& operator *() const;
    bool operator == (const Iterator& otherIterator) const;
    bool operator != (const Iterator& otherIterator) const;

    Iterator operator ++ ();
    Iterator operator ++ (int);
    Iterator operator -- ();
    Iterator operator -- (int);


private:

    /* Fields */

    AABBTree<D,K,T>::Node* node;


    /* Getters/setters */

    AABBTree<D,K,T>::Node* getNode() const;


    /* Private methods */

    void next();
    void prev();
};


}

#include "aabbtreeiterator.tpp"

#endif // CG3_AABBTREEITERATOR_H
