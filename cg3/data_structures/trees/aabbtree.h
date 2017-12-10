/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBTREE_H
#define CG3_AABBTREE_H

#include <vector>
#include <utility>

#include "includes/tree_common.h"

#include "includes/iterators/tree_iterator.h"
#include "includes/iterators/tree_reverseiterator.h"
#include "includes/iterators/tree_insertiterator.h"
#include "includes/iterators/tree_rangebased_iterators.h"

#include "includes/nodes/aabb_node.h"

namespace cg3 {

/* Types */

enum AABBValueType { MIN, MAX };


/**
 * @brief An autobalancing (AVL) AABB tree
 *
 * No duplicates are allowed. It has been implemented as
 * a FAT AABB tree: the AABB of each node is the AABB
 * containing the entire childhood AABBs.
 */
template <int D, class K, class T = K>
class AABBTree
{

public:

    /* Types */

    using KeyOverlapChecker = bool (*)(const K& key1, const K& key2);

    using AABBValueExtractor = double (*)(const K& key, const AABBValueType& valueType, const int& dim);


    /* Typedefs */

    typedef internal::AABBNode<D,K,T> Node;

    typedef LessComparatorType<K> LessComparator;

    typedef TreeGenericIterator<AABBTree<D,K,T>, Node> generic_iterator;

    typedef TreeIterator<AABBTree<D,K,T>, Node, T> iterator;
    typedef TreeIterator<AABBTree<D,K,T>, Node, const T> const_iterator;

    typedef TreeReverseIterator<AABBTree<D,K,T>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<AABBTree<D,K,T>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<AABBTree<D,K,T>, K> insert_iterator;

    typedef TreeRangeBasedIterator<AABBTree<D,K,T>> RangeBasedIterator;
    typedef TreeRangeBasedConstIterator<AABBTree<D,K,T>> RangeBasedConstIterator;
    typedef TreeRangeBasedReverseIterator<AABBTree<D,K,T>> RangeBasedReverseIterator;
    typedef TreeRangeBasedConstReverseIterator<AABBTree<D,K,T>> RangeBasedConstReverseIterator;



    /* Constructors/destructor */

    AABBTree(const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &internal::defaultComparator<K>);
    AABBTree(const std::vector<std::pair<K,T>>& vec,
             const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &internal::defaultComparator<K>);
    AABBTree(const std::vector<K>& vec,
             const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &internal::defaultComparator<K>);

    ~AABBTree();



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    iterator insert(const K& key);
    iterator insert(const K& key, const T& value);

    bool erase(const K& key);
    void erase(generic_iterator it);

    iterator find(const K& key);


    TreeSize size();
    bool empty();

    void clear();

    TreeSize getHeight();


    template <class OutputIterator>
    void rangeQuery(
            const K& start, const K& end,
            OutputIterator out);

    template <class OutputIterator>
    void aabbOverlapQuery(
            const K& key,
            OutputIterator out,
            KeyOverlapChecker keyOverlapChecker = nullptr);

    bool aabbOverlapCheck(
            const K& key,
            KeyOverlapChecker keyOverlapChecker = nullptr);


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

    RangeBasedIterator getIterator();
    RangeBasedConstIterator getConstIterator();
    RangeBasedReverseIterator getReverseIterator();
    RangeBasedConstReverseIterator getConstReverseIterator();


protected:

    /* Protected fields */

    Node* root;

    TreeSize entries;

    const LessComparator lessComparator;

    const AABBValueExtractor aabbValueExtractor;


private:

    /* Private methods */

    void initialize();



    /* AABB helpers */

    inline void aabbOverlapQueryHelper(
            Node* node,
            const K& key,
            const typename Node::AABB& aabb,
            std::vector<Node*> &out,
            KeyOverlapChecker keyOverlapChecker);

    inline bool aabbOverlapCheckHelper(
            Node* node,
            const K& key,
            const typename Node::AABB& aabb,
            KeyOverlapChecker keyOverlapChecker);

    inline void updateAABBHelper(
            Node* node,
            AABBValueExtractor aabbValueExtractor);


    /* AVL helpers for AABB */

    inline void rebalanceAABBHelper(
            Node* node,
            AABBValueExtractor aabbValueExtractor);

    inline void updateHeightAndRebalanceAABBHelper(
            Node* node,
            AABBValueExtractor aabbValueExtractor);

    inline Node* leftRotateAABBHelper(
            Node* a,
            AABBValueExtractor aabbValueExtractor);

    inline Node* rightRotateAABBHelper(
            Node* a,
            AABBValueExtractor aabbValueExtractor);



    /* AABB utilities */

    inline bool aabbOverlapsHelper(
            const typename Node::AABB& a,
            const typename Node::AABB& b);

    inline void setAABBFromKeyHelper(
            const K& k,
            typename Node::AABB& aabb,
            AABBValueExtractor aabbValueExtractor);

};

}


#include "aabbtree.tpp"

#endif // CG3_AABBTREE_H




