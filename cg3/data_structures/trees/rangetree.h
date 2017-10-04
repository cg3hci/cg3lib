/**
    @author Stefano Nuvoli
*/
#ifndef CG3_RANGETREE_H
#define CG3_RANGETREE_H

#include <vector>
#include <algorithm>


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

    typedef bool (*LessComparator)(const K& key1, const K& key2);
    typedef bool (*LessDimensionComparator)(const K& key1, const K& key2, const unsigned int dim);



    /* Constructors/destructor */

    RangeTree(unsigned int dim,
              const LessDimensionComparator customDimensionComparator,
              const LessComparator customComparator = &defaultComparator);
    RangeTree(unsigned int dim,
              const std::vector<std::pair<K,T>>& vec,
              const LessDimensionComparator customDimensionComparator,
              const LessComparator customComparator = &defaultComparator);
    RangeTree(unsigned int dim,
              const std::vector<K>& vec,
              const LessDimensionComparator customDimensionComparator,
              const LessComparator customComparator = &defaultComparator);

    ~RangeTree();



    /* Public nested classes */

    class Iterator;



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    bool insert(const K& key);
    bool insert(const K& key, const T& value);

    bool erase(const K& key);

    Iterator find(const K& key);

    void rangeQuery(const K& start, const K& end,
                    std::vector<Iterator> &out);

    Iterator getMin();
    Iterator getMax();

    size_t size();
    bool empty();

    void clear();

    size_t getHeight();



    /* Iterators */

    Iterator begin();
    const Iterator& end();



    /* Utilities */

    //Comparators for pairs (needed for std::sort)
    bool operator()(const std::pair<K,T> a, const std::pair<K,T> b) const
    {
        return isLess(a.first, b.first);
    }

protected:

    /* Protected nested classes */

    class Node;



    /* Protected fields */

    Node* root;

    size_t entries;

    const Iterator endIterator;

    const unsigned int dim;
    const LessDimensionComparator lessDimensionComparator;
    const LessComparator lessComparator;




    /* Static helpers */

    static Node* getSuccessorHelper(Node* node);
    static Node* getPredecessorHelper(Node* node);

    static Node* getMinimumHelper(Node* node);
    static Node* getMaximumHelper(Node* node);



    /* Helpers */

    void initHelper();

    void constructionBottomUpHelper(const std::vector<std::pair<K,T>>& sortedVec);

    bool insertNodeHelper(Node*& node);

    Node* findNodeHelper(const K& key) const;

    void eraseNodeHelper(Node*& node);

    void clearHelper(Node*& rootNode);

    void replaceSubtreeHelper(const Node* u, Node* v);

    size_t getHeightHelper(const Node* node);



    /* AVL Helpers */

    void updateHeightHelper(Node* node);

    void rebalanceHelper(Node* node);

    Node* leftRotate(Node* a);
    Node* rightRotate(Node* a);



    /* Range query helpers */

    void rangeQueryHelper(const K& start, const K& end,
                          std::vector<Node*> &out);

    Node* findSplitNodeHelper(const K& start, const K& end);

    void reportSubtreeHelper(Node* node, std::vector<Node*>& out);



    /* Multidimensional range tree helper */

    void rangeSearchInNextDimensionHelper(Node* node, const K& start, const K& end, std::vector<Node*>& out);

    void createAssociatedTreeHelper(Node* node);

    void insertIntoAssociatedTreeHelper(Node* node, const K& key, const T& value);
    void insertIntoParentAssociatedTreesHelper(Node* node, const K& key, const T& value);

    void eraseFromAssociatedTreeHelper(Node* node, const K& key);
    void eraseFromParentAssociatedTreesHelper(Node* node, const K& key);



    /* Comparator utilities */

    inline bool isEqual(const K& a, const K& b) const {
        return !(isLess(a,b) || isLess(b,a));
    }
    inline bool isLess(const K& a, const K& b) const {
        if (lessDimensionComparator(a, b, dim))
            return true;
        if (lessDimensionComparator(b, a, dim))
            return false;
        return lessComparator(a,b);
    }
    inline bool isLessOrEqual(const K& a, const K& b) const {
        return isLess(a,b) || isEqual(a,b);
    }
    inline bool isGreater(const K& a, const K& b) const {
        return isLess(b,a);
    }
    inline bool isGreaterOrEqual(const K& a, const K& b) const {
        return !isLess(a,b);
    }

    static bool defaultComparator(const K& key1, const K& key2) {
        return key1 < key2;
    }


};


}

#include "rangetree/rangetreeiterator.h"
#include "rangetree/rangetreenode.h"

#include "rangetree.tpp"



#endif // CG3_RANGETREE_H
