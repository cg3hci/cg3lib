/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "aabbtree.h"

#include <stdexcept>
#include <algorithm>
#include <utility>

#include "includes/bstleaf_helpers.h"
#include "includes/avl_helpers.h"

#include "cg3/utilities/const.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */

/**
 * @brief Default constructor
 *
 * @param[in] customAABBValueExtractor Function to extract AABB coordinates from
 * a key
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>::AABBTree(
        const AABBValueExtractor customAABBValueExtractor,
        const C& customComparator) :
    comparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
{
    this->initialize();
}

/**
 * @brief Constructor with a vector of entries (key/value pairs) to be inserted
 *
 * @param[in] vec Vector of pairs of keys/values
 * @param[in] customAABBValueExtractor Function to extract AABB coordinates from
 * a key
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>::AABBTree(
        const std::vector<std::pair<K,T>>& vec,
        const AABBValueExtractor customAABBValueExtractor,
        const C& customComparator) :
    comparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
{
    this->initialize();
    this->construction(vec);
}


/**
 * @brief Constructor with a vector of values to be inserted
 *
 * @param[in] vec Vector of values
 * @param[in] customAABBValueExtractor Function to extract AABB coordinates from
 * a key
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>::AABBTree(
        const std::vector<K>& vec,
        const AABBValueExtractor customAABBValueExtractor,
        const C& customComparator) :
    comparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
{
    this->initialize();
    this->construction(vec);
}

/**
 * @brief Copy constructor
 * @param bst BST
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>::AABBTree(const AABBTree<D,K,T,C>& bst) :
    comparator(bst.comparator),
    aabbValueExtractor(bst.aabbValueExtractor)
{
    this->root = internal::copySubtreeHelper<Node,T>(bst.root);
    this->entries = bst.entries;
}

/**
 * @brief Move constructor
 * @param bst BST
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>::AABBTree(AABBTree<D,K,T,C>&& bst) :
    comparator(bst.comparator),
    aabbValueExtractor(bst.aabbValueExtractor)
{
    this->root = bst.root;
    bst.root = nullptr;
    this->entries = bst.entries;
}

/**
 * @brief Destructor
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>::~AABBTree()
{
    this->clear();
}




/* --------- PUBLIC METHODS --------- */




/**
 * @brief Construction of the BST given the initial values
 *
 * A clear operation is performed before the construction
 *
 * @param[in] vec Vector of values
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::construction(const std::vector<K>& vec)
{
    std::vector<std::pair<K,T>> pairVec;

    for (const K& entry : vec) {
        pairVec.push_back(std::make_pair(entry, entry));
    }

    construction(pairVec);
}

/**
 * @brief Construction of the BST given the initial values (pairs of
 * keys/values)
 *
 * A clear operation is performed before the construction
 *
 * @param[in] vec Vector of pairs of keys/values
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::construction(const std::vector<std::pair<K,T>>& vec)
{
    this->clear();

    if (vec.size() == 0)
        return;

    std::vector<std::pair<K,T>> sortedVec(vec.begin(), vec.end());

    //Sort the collection
    internal::PairComparator<K,T> pairComparator(comparator);
    std::sort(sortedVec.begin(), sortedVec.end(), pairComparator);

    //Create nodes
    std::vector<Node*> sortedNodes;
    for (std::pair<K,T>& pair : sortedVec) {
        Node* node = new Node(pair.first, pair.second);
        sortedNodes.push_back(node);
    }

    //Calling the bottom up helper
    this->entries = internal::constructionBottomUpHelperLeaf<Node,K,C>(
                sortedNodes,
                this->root,
                comparator);

    //Update the height of nodes and create their AABBs
    for (Node*& node : sortedNodes) {
        if (node != nullptr && node->isLeaf()) {
            //Update height
            internal::updateHeightHelper(node);

            //Update AABBs
            this->updateAABBHelper(node, aabbValueExtractor);
        }
    }
}




/**
 * @brief Insert in the BST a given value
 *
 * @param[in] key Key/value to be inserted
 * @return The iterator pointing to the node if it has been
 * successfully inserted, end iterator otherwise
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::insert(const K& key)
{
    return insert(key, key);
}

/**
 * @brief Insert in the BST a given value with the given key
 *
 * If an entry with the same key is already contained, the new
 * entry will be not inserted
 *
 * @param[in] key Key of the entry
 * @param[in] value Value of the entry
 * @return The iterator pointing to the node if it has been
 * successfully inserted, end iterator otherwise
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    //Insert node
    Node* result = internal::insertNodeHelperLeaf<Node,K,C>(newNode, this->root, comparator);

    //If node has been inserted
    if (result != nullptr) {
        //Update height and rebalance
        this->updateHeightAndRebalanceAABBHelper(newNode, aabbValueExtractor);

        //Update AABBs
        this->updateAABBHelper(newNode, aabbValueExtractor);

        //Increment entry number
        this->entries++;

        //Returns the iterator to the node
        return iterator(this, newNode);
    }

    //Returns end iterator
    return this->end();
}






/**
 * @brief Erase value from BST given the key
 *
 * @param[in] key Key of the node
 * @return True if item has been found and then erased, false otherwise
 */
template <int D, class K, class T, class C>
bool AABBTree<D,K,T,C>::erase(const K& key)
{
    //Query the BST to find the node
    Node* node = internal::findNodeHelperLeaf(key, this->root, comparator);

    //If the node has been found
    if (node != nullptr) {
        //Erase node
        Node* replacingNode = internal::eraseNodeHelperLeaf(node, this->root);

        //Update height and rebalance
        this->updateHeightAndRebalanceAABBHelper(replacingNode, aabbValueExtractor);

        //Update AABBs
        this->updateAABBHelper(replacingNode, aabbValueExtractor);

        //Decrease the number of entries
        this->entries--;

        return true;
    }
    return false;
}

/**
 * @brief Erase an entry from BST given the iterator.
 * Note that iterator is not changed after element is removed
 *
 * @param[in] it A generic iterator pointing to the node to be erased
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::erase(generic_iterator it)
{
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }

    //Save node to be deleted
    Node* node = it.node;


    if (node != nullptr) {
        //Erase node
        Node* replacingNode = internal::eraseNodeHelperLeaf(node, this->root);

        //Update height and rebalance
        this->updateHeightAndRebalanceAABBHelper(replacingNode, aabbValueExtractor);

        //Update AABBs
        this->updateAABBHelper(replacingNode, aabbValueExtractor);

        //Decrease the number of entries
        this->entries--;
    }
}



/**
 * @brief Find entry in the BST given the key
 *
 * @param[in] key Key of the node to be found
 * @return The iterator pointing to the BST node if the element
 * is contained in the BST, end iterator otherwise
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::find(const K& key)
{
    //Query the BST to find the node
    Node* node = internal::findNodeHelperLeaf(key, this->root, comparator);

    return iterator(this, node);
}





/**
 * @brief Clear the tree, delete all its elements
 *
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::clear()
{
    //Clear entire tree
    internal::clearHelper(this->root);

    //Decreasing entries
    this->entries = 0;
}




/**
 * @brief Get the number of entries in the BST
 *
 * @return Number of entries in the BST
 */
template <int D, class K, class T, class C>
TreeSize AABBTree<D,K,T,C>::size()
{
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty, false otherwise
 */
template <int D, class K, class T, class C>
bool AABBTree<D,K,T,C>::empty()
{
    return (this->size() == 0);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <int D, class K, class T, class C>
TreeSize AABBTree<D,K,T,C>::getHeight()
{
    return internal::getHeightHelper(this->root);
}



/**
 * @brief Find entries in the BST that are enclosed in a given range.
 * Start and end are included bounds of the range.
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Output iterator for the container containing the iterators
 * pointing to the nodes which have keys enclosed in the input range
 */
template <int D, class K, class T, class C> template <class OutputIterator>
void AABBTree<D,K,T,C>::rangeQuery(
        const K& start, const K& end,
        OutputIterator out)
{
    //Output
    std::vector<Node*> nodeOutput;

    //Execute range query
    internal::rangeQueryHelperLeaf(start, end, nodeOutput, this->root, comparator);

    for (Node* node : nodeOutput) {
        *out = iterator(this, node);
        out++;
    }
}


/**
 * @brief Find elements for which the input bounding box overlaps with the one of the values
 *
 * @param[in] key Input key
 * @param[out] out Vector of iterators pointing to elements that overlap
 */
template <int D, class K, class T, class C> template <class OutputIterator>
void AABBTree<D,K,T,C>::aabbOverlapQuery(
        const K& key,
        OutputIterator out,
        KeyOverlapChecker keyOverlapChecker)
{
    //Get the AABB
    typename Node::AABB aabb;
    this->setAABBFromKeyHelper(key, aabb, aabbValueExtractor);

    //Query the AABB tree
    std::vector<Node*> nodeOutput;
    this->aabbOverlapQueryHelper(this->root, key, aabb, nodeOutput, keyOverlapChecker);

    //Pushing out the results
    for (Node* node : nodeOutput) {
        *out = iterator(this, node);
        out++;
    }
}


/**
 * @brief Check if the given bounding box overlaps with the one of the values
 *
 * @param[in] key Input key
 * @return True if there is an overlapping bounding box in the stored values
 */
template <int D, class K, class T, class C>
bool AABBTree<D,K,T,C>::aabbOverlapCheck(
        const K& key,
        KeyOverlapChecker keyOverlapChecker)
{
    //Get the AABB
    typename Node::AABB aabb;
    this->setAABBFromKeyHelper(key, aabb, aabbValueExtractor);

    //Query the AABB tree
    return this->aabbOverlapCheckHelper(this->root, key, aabb, keyOverlapChecker);
}





/* ----- ITERATOR MIN/MAX NEXT/PREV ----- */

/**
 * @brief Get minimum key entry in the BST
 *
 * @return The iterator pointing to the minimum node
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::getMin()
{
    return iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::getMax()
{
    return iterator(this, internal::getMaximumHelperLeaf(this->root));
}



/**
 * @brief Get successor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the successor node (end
 * iterator if it has no successor)
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::generic_iterator AABBTree<D,K,T,C>::getNext(generic_iterator it)
{
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }
    return generic_iterator(this, internal::getSuccessorHelperLeaf(it.node));
}

/**
 * @brief Get predecessor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the predecessor node (end
 * iterator if it has no predecessor)
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::generic_iterator AABBTree<D,K,T,C>::getPrev(generic_iterator it)
{
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }
    return generic_iterator(this, internal::getPredecessorHelperLeaf(it.node));
}



/* --------- ITERATORS --------- */

/**
 * @brief Begin iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::begin()
{
    return iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief End iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::iterator AABBTree<D,K,T,C>::end()
{
    return iterator(this, nullptr);
}


/**
 * @brief Begin const iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::const_iterator AABBTree<D,K,T,C>::cbegin()
{
    return const_iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief End const iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::const_iterator AABBTree<D,K,T,C>::cend()
{
    return const_iterator(this, nullptr);
}


/**
 * @brief Begin reverse iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::reverse_iterator AABBTree<D,K,T,C>::rbegin()
{
    return reverse_iterator(this, internal::getMaximumHelperLeaf(this->root));
}

/**
 * @brief End reverse iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::reverse_iterator AABBTree<D,K,T,C>::rend()
{
    return reverse_iterator(this, nullptr);
}


/**
 * @brief Begin const reverse iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::const_reverse_iterator AABBTree<D,K,T,C>::crbegin()
{
    return const_reverse_iterator(this, internal::getMaximumHelperLeaf(this->root));
}

/**
 * @brief End const reverse iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::const_reverse_iterator AABBTree<D,K,T,C>::crend()
{
    return const_reverse_iterator(this, nullptr);
}



/**
 * @brief Insert output iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::insert_iterator AABBTree<D,K,T,C>::inserter()
{
    return insert_iterator(this);
}



/**
 * @brief Get range based iterator of the BST
 *
 * @return Range based iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::RangeBasedIterator AABBTree<D,K,T,C>::getIterator()
{
    return RangeBasedIterator(this);
}

/**
 * @brief Get range based const iterator of the BST
 *
 * @return Range based const iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::RangeBasedConstIterator AABBTree<D,K,T,C>::getConstIterator()
{
    return RangeBasedConstIterator(this);
}

/**
 * @brief Get range based reverse iterator of the BST
 *
 * @return Range based reverse iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::RangeBasedReverseIterator AABBTree<D,K,T,C>::getReverseIterator()
{
    return RangeBasedReverseIterator(this);
}

/**
 * @brief Get range based const reverse iterator of the BST
 *
 * @return Range based const reverse iterator
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::RangeBasedConstReverseIterator AABBTree<D,K,T,C>::getConstReverseIterator()
{
    return RangeBasedConstReverseIterator(this);
}


/* ----- SWAP FUNCTION AND ASSIGNMENT ----- */

/**
 * @brief Assignment operator
 * @param[out] bst Parameter BST
 * @return This object
 */
template <int D, class K, class T, class C>
AABBTree<D,K,T,C>& AABBTree<D,K,T,C>::operator= (AABBTree<D,K,T,C> bst)
{
    swap(bst);
    return *this;
}


/**
 * @brief Swap BST with another one
 * @param[out] bst BST to be swapped with this object
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::swap(AABBTree<D,K,T,C>& bst)
{
    using std::swap;
    swap(this->root, bst.root);
    swap(this->entries, bst.entries);
    swap(this->comparator, bst.comparator);
    swap(this->aabbValueExtractor, bst.aabbValueExtractor);
}


/**
 * @brief Swap graph with another one
 * @param b1 First BST
 * @param b2 Second BST
 */
template <int D, class K, class T, class C>
void swap(AABBTree<D,K,T,C>& b1, AABBTree<D,K,T,C>& b2)
{
    b1.swap(b2);
}


/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the BST
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::initialize()
{
    this->root = nullptr;
    this->entries = 0;
}




/* ----- AABB HELPERS ----- */

/**
 * @brief Find elements for which the input bounding box overlaps with the one of the values.
 * Output can be filtered by another optional key overlap filter function.
 *
 * @param[in] node Starting node
 * @param[in] key Input key
 * @param[in] aabb Axis-aligned bounding box of the key
 * @param[out] out Vector of iterators pointing to elements that overlap
 * @param[in] keyOverlapChecker Key overlap filter function
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::aabbOverlapQueryHelper(
        Node* node,
        const K& key,
        const typename Node::AABB& aabb,
        std::vector<Node*> &out,
        KeyOverlapChecker keyOverlapChecker)
{
    if (node == nullptr)
        return;

    //If node is a leaf, then return the node if its bounding box is overlapping
    if (node->isLeaf()) {
        if (aabbOverlapsHelper(aabb, node->aabb)) {
            if (keyOverlapChecker == nullptr || keyOverlapChecker(key, node->key)) {
                out.push_back(node);
            }
        }
    }
    //If node is not a leaf, search on left and right subtrees if the AABB overlaps
    else {
        if (node->right != nullptr && aabbOverlapsHelper(aabb, node->right->aabb)) {
            aabbOverlapQueryHelper(node->right, key, aabb, out, keyOverlapChecker);
        }

        if (node->left != nullptr && aabbOverlapsHelper(aabb, node->left->aabb)) {
            aabbOverlapQueryHelper(node->left, key, aabb, out, keyOverlapChecker);
        }
    }
}

/**
 * @brief Check if the given bounding box overlaps with at least one of the values
 * in the AABB tree. If the optional key overlap filter function is specified, then
 * true is returned iff the bounding box overlaps and the filter function returns true.
 *
 * @param[in] node Starting node
 * @param[in] key Input key
 * @param[in] aabb Axis-aligned bounding box of the key
 * @param[in] keyOverlapChecker Key overlap filter function
 * @return True if there is an overlapping bounding box in the stored values
 */
template <int D, class K, class T, class C>
bool AABBTree<D,K,T,C>::aabbOverlapCheckHelper(
        Node* node,
        const K& key,
        const typename Node::AABB& aabb,
        KeyOverlapChecker keyOverlapChecker)
{
    if (node == nullptr)
        return false;

    //If node is a leaf, then return the node if its bounding box is overlapping
    if (node->isLeaf()) {
        if (aabbOverlapsHelper(aabb, node->aabb)) {
            if (keyOverlapChecker == nullptr || keyOverlapChecker(key, node->key)) {
                return true;
            }
        }
    }
    //If node is not a leaf, search on left and right subtrees if the AABB overlaps
    else {
        if (node->right != nullptr && aabbOverlapsHelper(aabb, node->right->aabb)) {
            if (aabbOverlapCheckHelper(node->right, key, aabb, keyOverlapChecker))
                return true;
        }

        if (node->left != nullptr && aabbOverlapsHelper(aabb, node->left->aabb)) {
            if (aabbOverlapCheckHelper(node->left, key, aabb, keyOverlapChecker))
                return true;
        }
    }
    return false;
}



/**
 * @brief Update AABBs climbing on the parents
 *
 * @param[in] node Starting node
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::updateAABBHelper(
        Node* node,
        AABBValueExtractor aabbValueExtractor)
{
    if (node != nullptr) {
        bool done;
        do {
            done = false;

            //Set AABB for the key
            if (node->isLeaf()) {
                this->setAABBFromKeyHelper(node->key, node->aabb, aabbValueExtractor);
            }
            //Set maximum AABB of the subtree
            else {
                assert(node->left != nullptr);
                assert(node->right != nullptr);

                typename Node::AABB& leftChildAABB = node->left->aabb;
                typename Node::AABB& rightChildAABB = node->right->aabb;

                done = true;

                for (int i = 0; i < D; i++) {
                    double minValue = std::min(leftChildAABB.min[i], rightChildAABB.min[i]);
                    double maxValue = std::max(leftChildAABB.max[i], rightChildAABB.max[i]);

                    if (node->aabb.min[i] != minValue || node->aabb.max[i] != maxValue) {
                        done = false;
                    }

                    node->aabb.min[i] = minValue;
                    node->aabb.max[i] = maxValue;
                }
            }

            //Done flag
            if (node->parent == nullptr) {
                done = true;
            }

            //Next parent
            node = node->parent;
        } while (!done);
    }
}



/* ----- AVL HELPERS FOR AABB ----- */

/**
 * @brief Rebalance with left/right rotations to make the
 * AABBTree satisfy the AVL constraints
 *
 * @param[in] node Starting node
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::rebalanceAABBHelper(
        Node* node,
        AABBValueExtractor aabbValueExtractor)
{
    //Null handler
    if (node == nullptr)
        return;

    //Not balanced node
    Node* n = node;
    int balanceFactor = internal::getHeightHelper(n->right) - internal::getHeightHelper(n->left);

    //Climb on parents to find the not balanced node
    while (n != nullptr && balanceFactor >= -1 && balanceFactor <= 1) {
        n = n->parent;

        if (n != nullptr) {
            //Compute balance factor
            balanceFactor = internal::getHeightHelper(n->right) - internal::getHeightHelper(n->left);

            assert(balanceFactor <= 2 && balanceFactor >= -2);
        }
    }


    if (n != nullptr) {
        assert(balanceFactor == 2 || balanceFactor == -2);
        if (balanceFactor < -1) {
            Node* leftleft = n->left->left;
            Node* leftright = n->left->right;

            //Left left case
            if (internal::getHeightHelper(leftleft) >= internal::getHeightHelper(leftright)) {
                n = this->rightRotateAABBHelper(n, aabbValueExtractor);
            }
            //Left right case
            else {
                n->left = this->leftRotateAABBHelper(n->left, aabbValueExtractor);
                n = this->rightRotateAABBHelper(n, aabbValueExtractor);
            }
        }
        else if (balanceFactor > 1) {
            Node* rightright = n->right->right;
            Node* rightleft = n->right->left;

            //Right right case
            if (internal::getHeightHelper(rightright) >= internal::getHeightHelper(rightleft)) {
                n = this->leftRotateAABBHelper(n, aabbValueExtractor);
            }
            //Left right case
            else {
                n->right = rightRotateAABBHelper(n->right, aabbValueExtractor);
                n = this->leftRotateAABBHelper(n, aabbValueExtractor);
            }
        }


        //Set root
        if (n->parent == nullptr) {
            this->root = n;
        }

        //Update heights on parents and rebalance them if needed
        this->updateHeightAndRebalanceAABBHelper(n->parent, aabbValueExtractor);

        //Update AABBs
        this->updateAABBHelper(n, aabbValueExtractor);
    }
}



/**
 * @brief Update heights climbing on the parents and then
 * rebalance them if needed
 *
 * @param[in] node Starting node
 * @param[in] node Root node of the BST
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::updateHeightAndRebalanceAABBHelper(
        Node* node,
        AABBValueExtractor aabbValueExtractor)
{
    internal::updateHeightHelper(node);
    this->rebalanceAABBHelper(node, aabbValueExtractor);
}



/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @param[in] aabbValueExtractor AABB extractor for key
 * @return New node in the position of the original node after the rotation
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::Node* AABBTree<D,K,T,C>::leftRotateAABBHelper(
        Node* a,
        AABBValueExtractor aabbValueExtractor)
{
    //Rotate left
    Node* b = internal::leftRotateHelper(a);

    //Update AABBs
    this->updateAABBHelper(a, aabbValueExtractor);

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @param[in] aabbValueExtractor AABB extractor for key
 * @return New node in the position of the original node after the rotation
 */
template <int D, class K, class T, class C>
typename AABBTree<D,K,T,C>::Node* AABBTree<D,K,T,C>::rightRotateAABBHelper(
        Node* a,
        AABBValueExtractor aabbValueExtractor)
{
    //Rotate right
    Node* b = internal::rightRotateHelper(a);

    //Update AABBs
    this->updateAABBHelper(a, aabbValueExtractor);

    return b;
}





/* ----- AABB UTILITIES ----- */

/**
 * Check if two bounding boxes overlap
 *
 * @param[in] a First bounding box
 * @param[in] a Second bounding box
 * @returns True if the bounding boxes overlap, false otherwise
 */
template <int D, class K, class T, class C>
bool AABBTree<D,K,T,C>::aabbOverlapsHelper(
        const typename Node::AABB& a,
        const typename Node::AABB& b)
{
    double eps = cg3::CG3_EPSILON*100;

    for (int i = 0; i < D; i++) {
        if (a.min[i] - eps > b.max[i] + eps ||
            b.min[i] - eps > a.max[i] + eps)
        {
            return false;
        }
    }

    return true;
}

/**
 * Set a bounding box for a key
 *
 * @param[in] k Input key
 * @param[out] a Bounding box to be updated
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class T, class C>
void AABBTree<D,K,T,C>::setAABBFromKeyHelper(
        const K& k,
        typename Node::AABB& aabb,
        AABBValueExtractor aabbValueExtractor)
{
    for (int i = 0; i < D; i++) {
        aabb.min[i] = aabbValueExtractor(k, MIN, i+1);
        aabb.max[i] = aabbValueExtractor(k, MAX, i+1);
    }
}


}
