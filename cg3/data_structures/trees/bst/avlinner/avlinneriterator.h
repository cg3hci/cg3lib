/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLINNERITERATOR_H
#define CG3_AVLINNERITERATOR_H

#include "../avlinner.h"

namespace cg3 {

/**
 * @brief The iterator for the binary search tree
 */
template <class K, class T>
class AVLInner<K,T>::Iterator {

    friend class AVLInner<K,T>;

public:

    /* Constructors/destructor */

    Iterator(AVLInner<K,T>::Node* node);


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

    AVLInner<K,T>::Node* node;


    /* Getters/setters */

    AVLInner<K,T>::Node* getNode() const;


    /* Private methods */

    void next();
    void prev();
};


}


#include "avlinneriterator.tpp"

#endif // CG3_AVLINNERITERATOR_H
