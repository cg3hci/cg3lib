/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTINNERITERATOR_H
#define CG3_BSTINNERITERATOR_H

#include "../bstinner.h"

namespace cg3 {

/**
 * @brief The iterator for the binary search tree
 */
template <class K, class T>
class BSTInner<K,T>::Iterator {

    friend class BSTInner<K,T>;

public:

    /* Constructors/destructor */

    Iterator(BSTInner<K,T>::Node* node);



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

    BSTInner<K,T>::Node* node;


    /* Getters/setters */

    BSTInner<K,T>::Node* getNode() const;


    /* Private methods */

    void next();
    void prev();
};


}


#include "bstinneriterator.tpp"

#endif // CG3_BSTINNERITERATOR_H
