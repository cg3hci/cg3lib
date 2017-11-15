/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREE_H
#define CG3_RANGETREE_H

#include <vector>
#include <algorithm>

#include "includes/treecommon.h"

#include "includes/iterators/treeiterator.h"
#include "includes/iterators/treereverseiterator.h"
#include "includes/iterators/treeinsertiterator.h"

#include "includes/nodes/rangetreenode.h"

#include "includes/rangetreehelpers.h"


namespace cg3 {


/**
 * @brief Auto-balancing (AVL) multi-dimensional range tree
 *
 * Values are saved only in the leaves.
 * No duplicates are allowed.
 * Keys and values are saved (and copied) in each dimension associated range tree.
 * Use pointers as template arguments if it is needed to save memory. This choice has
 * been made because we prefer to allow the user, if needed, to easily implement range
 * searches in just a subset of the dimensions of the object.
 *
 */
template <class K, class T = K>
class RangeTree
{


public:

    /* Typedefs */

    typedef RangeTreeNode<K,T> Node;

    typedef LessComparatorType<K> LessComparator;

    typedef TreeGenericIterator<RangeTree<K,T>, Node> generic_iterator;

    typedef TreeIterator<RangeTree<K,T>, Node, T> iterator;
    typedef TreeIterator<RangeTree<K,T>, Node, const T> const_iterator;

    typedef TreeReverseIterator<RangeTree<K,T>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<RangeTree<K,T>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<RangeTree<K,T>, K> insert_iterator;



    /* Constructors/destructor */

    RangeTree(const unsigned int dim,
              const std::vector<LessComparator>& customComparators);
    RangeTree(const unsigned int dim,
              const std::vector<std::pair<K,T>>& vec,
              const std::vector<LessComparator>& customComparators);
    RangeTree(const unsigned int dim,
              const std::vector<K>& vec,
              const std::vector<LessComparator>& customComparators);

    ~RangeTree();



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    iterator insert(const K& key);
    iterator insert(const K& key, const T& value);

    bool erase(const K& key);

    iterator find(const K& key);


    size_t size();
    bool empty();

    void clear();

    size_t getHeight();


    void rangeQuery(
            const K& start, const K& end,
            std::vector<iterator> &out);


    /* Iterator Min/Max Next/Prev */

    iterator getMin();
    iterator getMax();

    generic_iterator getNext(const generic_iterator it);
    generic_iterator getPrev(const generic_iterator it);


    /* Iterators */

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator crbegin();
    const_reverse_iterator crend();

    insert_iterator inserter();


protected:



    /* Protected fields */

    Node* root;

    size_t entries;

    const unsigned int dim;
    const LessComparator lessComparator;

    const std::vector<LessComparator> customComparators;


    /* Private methods */

    void initialize();


};


}


#include "rangetree.tpp"



#endif // CG3_RANGETREE_H
