/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLINNER_H
#define CG3_AVLINNER_H

#include <vector>
#include <algorithm>


namespace cg3 {

/**
 * @brief Auto-balancing (AVL) binary search tree
 *
 * Keys and values are saved in all nodes, not only in the leaves. The implementation
 * is performed following "Introduction to Algorithms" (Cormen, 2011).
 * No duplicates are allowed.
 */
template <class K, class T = K>
class AVLInner
{

public:

    /* Typedefs */

    typedef bool (*LessComparator)(const K& key1, const K& key2);



    /* Constructors/destructor */

    AVLInner(const LessComparator customComparator = &defaultComparator);
    AVLInner(const std::vector<std::pair<K,T>>& vec,
             const LessComparator customComparator = &defaultComparator);
    AVLInner(const std::vector<K>& vec,
             const LessComparator customComparator = &defaultComparator);

    ~AVLInner();



    /* Public nested classes */

    class Iterator;



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    Iterator insert(const K& key);
    Iterator insert(const K& key, const T& value);

    bool erase(const K& key);
    void erase(Iterator it);

    Iterator find(const K& key);

    Iterator getMin();
    Iterator getMax();

    size_t size();
    bool empty();

    void clear();

    size_t getHeight();

    void rangeQuery(const K& start, const K& end,
                    std::vector<Iterator> &out);



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

    const LessComparator lessComparator;



    /* Static helpers */

    static Node* getSuccessorHelper(Node* node);
    static Node* getPredecessorHelper(Node* node);

    static Node* getMinimumHelper(Node* node);
    static Node* getMaximumHelper(Node* node);



    /* Helpers */

    void initHelper();

    void constructionMedianHelper(
            const std::vector<std::pair<K,T>>& sortedVec,
            const size_t start, const size_t end);

    bool insertNodeHelper(Node*& node);

    Node* findNodeHelper(const K& key) const;

    void eraseNodeHelper(Node*& node);

    void clearHelper(Node*& rootNode);

    size_t getHeightHelper(const Node* node);



    /* Range query helpers */

    void rangeQueryHelper(const K& start, const K& end,
                          std::vector<Node*> &out);

    Node* findSplitNodeHelper(const K& start, const K& end);

    void reportSubTreeHelper(Node* node, std::vector<Node*>& out);



    /* AVL Helpers */

    void updateHeightHelper(Node* node);

    void rebalanceHelper(Node* node);

    Node* leftRotate(Node* a);
    Node* rightRotate(Node* a);



    /* Comparator utilities */

    inline bool isEqual(const K& a, const K& b) const {
        return !(isLess(a,b) || isLess(b,a));
    }
    inline bool isLess(const K& a, const K& b) const {
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

#include "avlinner/avlinneriterator.h"
#include "avlinner/avlinnernode.h"

#include "avlinner.tpp"

#endif // CG3_AVLINNER_H




