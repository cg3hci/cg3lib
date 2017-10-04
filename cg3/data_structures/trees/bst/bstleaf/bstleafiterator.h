/**
    @author Stefano Nuvoli
*/
#ifndef CG3_BSTLEAFITERATOR_H
#define CG3_BSTLEAFITERATOR_H

#include "../bstleaf.h"

namespace cg3 {
/**
 * @brief The iterator for the binary search tree
 */
template <class K, class T>
class BSTLeaf<K,T>::Iterator {

    friend class BSTLeaf<K,T>;

public:

    /* Constructors/destructor */

    Iterator(BSTLeaf<K,T>::Node* node);



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

    BSTLeaf<K,T>::Node* node;


    /* Getters/setters */

    BSTLeaf<K,T>::Node* getNode() const;


    /* Private methods */

    void next();
    void prev();
};


}


#include "bstleafiterator.tpp"

#endif // CG3_BSTLEAFITERATOR_H
