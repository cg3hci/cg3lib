/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBTREE_H
#define CG3_AABBTREE_H

#include <vector>
#include <algorithm>


namespace cg3 {

enum AABBValueType { MIN, MAX };

/**
 * @brief Auto-balancing (AVL) binary search tree
 *
 * Values are saved only in the leaves.
 * No duplicates are allowed.
 */
template <int D, class K, class T = K>
class AABBTree
{

public:

    /* Typedefs */

    typedef bool (*LessComparator)(const K& key1, const K& key2);

    typedef bool (*KeyOverlapChecker)(const K& key1, const K& key2);

    typedef double (*AABBValueExtractor)(const K& key, const AABBValueType& valueType, const int& dim);


    /* Axis-Aligned Bounding Box class */
    class AABB;



    /* Constructors/destructor */

    AABBTree(const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &defaultComparator);
    AABBTree(const std::vector<std::pair<K,T>>& vec,
             const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &defaultComparator);
    AABBTree(const std::vector<K>& vec,
             const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &defaultComparator);

    ~AABBTree();



    /* Public nested classes */

    class Iterator;



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    Iterator insert(const K& key);
    Iterator insert(const K& key, const T& value);

    bool erase(const K& key);
    void erase(Iterator& it);

    Iterator find(const K& key);

    Iterator getMin();
    Iterator getMax();

    size_t size();
    bool empty();

    void clear();

    size_t getHeight();

    void aabbOverlapQuery(
            const K& key,
            std::vector<Iterator> &out,
            KeyOverlapChecker keyOverlapChecker = nullptr);

    bool aabbOverlapCheck(
            const K& key,
            KeyOverlapChecker keyOverlapChecker = nullptr);


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
    const AABBValueExtractor aabbValueExtractor;



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



    /* AABB helpers */

    void aabbOverlapQueryHelper(
            Node* node,
            const K& key,
            const AABB& aabb,
            std::vector<Node*> &out,
            KeyOverlapChecker keyOverlapChecker);

    bool aabbOverlapCheckHelper(
            Node* node,
            const K& key,
            const AABB& aabb,
            KeyOverlapChecker keyOverlapChecker);






    void updateAABBsHelper(Node* node);



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



    /* AABB utilities */

    inline bool aabbOverlaps(const AABB& a, const AABB& b) {
        for (int i = 1; i <= D; i++) {
            if (!(a.getMin(i) <= b.getMax(i) && a.getMax(i) >= b.getMin(i)))
                return false;
        }
        return true;
    }

    inline void setAABBFromKey(const K& k, AABB& aabb) {
        for (int i = 1; i <= D; i++) {
            aabb.setMin(i, aabbValueExtractor(k, MIN, i));
            aabb.setMax(i, aabbValueExtractor(k, MAX, i));
        }
    }

};

}

#include "aabbtree/aabbtreeaabb.h"
#include "aabbtree/aabbtreeiterator.h"
#include "aabbtree/aabbtreenode.h"

#include "aabbtree.tpp"

#endif // CG3_AABBTREE_H
