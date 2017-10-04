/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREEITERATOR_H
#define CG3_RANGETREEITERATOR_H

#include "../rangetree.h"

namespace cg3 {

/**
 * @brief The iterator for the range tree
 */
template <class K, class T>
class RangeTree<K,T>::Iterator {

    friend class RangeTree<K,T>;

public:

    /* Constructors/destructor */

    Iterator(RangeTree<K,T>::Node* node);



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

    RangeTree<K,T>::Node* node;


    /* Getters/setters */

    RangeTree<K,T>::Node* getNode() const;


    /* Private methods */

    void next();
    void prev();
};


}


#include "rangetreeiterator.tpp"

#endif // CG3_RANGETREEITERATOR_H
