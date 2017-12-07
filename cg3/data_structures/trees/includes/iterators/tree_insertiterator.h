/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREEINSERTITERATOR_H
#define CG3_TREEINSERTITERATOR_H


#include <iterator>

namespace cg3 {

/**
 * @brief The insert iterator class for BST
 */
template <class B, class K>
class TreeInsertIterator :
        public std::iterator<std::output_iterator_tag,void,void,void,void>  {
public:

    /* Constructors */

    inline TreeInsertIterator(B* bst);


    /* Iterator operators */

    inline TreeInsertIterator& operator *();
    inline TreeInsertIterator& operator ++();
    inline TreeInsertIterator& operator ++(int);

    inline TreeInsertIterator& operator=(const K key);

private:

    /* Fields */

    B* bst;
};



}


#include "tree_insertiterator.tpp"

#endif // CG3_TREEINSERTITERATOR_H
