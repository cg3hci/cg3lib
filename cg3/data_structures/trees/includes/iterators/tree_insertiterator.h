/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREEINSERTITERATOR_H
#define CG3_TREEINSERTITERATOR_H


#include <iterator>

namespace cg3 {

/**
 * @brief The iterator class for BST
 */
template <class B, class K>
class TreeInsertIterator :
        public std::iterator<std::output_iterator_tag,void,void,void,void>  {
public:

    /* Constructors/destructor */

    TreeInsertIterator(B* bst);


    /* Iterator operators */

    TreeInsertIterator& operator *();
    TreeInsertIterator& operator ++();
    TreeInsertIterator& operator ++(int);

    TreeInsertIterator& operator=(const K key);

private:

    /* Fields */

    B* bst;
};



}


#include "tree_insertiterator.tpp"

#endif // CG3_TREEINSERTITERATOR_H
