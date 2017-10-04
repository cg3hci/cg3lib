/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLLEAFITERATOR_H
#define CG3_AVLLEAFITERATOR_H

#include "../avlleaf.h"

namespace cg3 {

/**
 * @brief The iterator for the binary search tree
 */
template <class K, class T>
class AVLLeaf<K,T>::Iterator {

    friend class AVLLeaf<K,T>;

public:

    /* Constructors/destructor */

    Iterator(AVLLeaf<K,T>::Node* node);



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

    AVLLeaf<K,T>::Node* node;


    /* Getters/setters */

    AVLLeaf<K,T>::Node* getNode() const;


    /* Private methods */

    void next();
    void prev();
};


}


#include "avlleafiterator.tpp"

#endif // CG3_AVLLEAFITERATOR_H
