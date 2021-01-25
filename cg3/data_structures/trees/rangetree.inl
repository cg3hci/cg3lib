/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "rangetree.h"

#include "assert.h"

#include "includes/bstleaf_helpers.h"
#include "includes/avl_helpers.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */



/**
 * @brief Default constructor
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] customComparators Vector of comparators for each
 * dimension of the range tree
 */
template <class K, class T, class C>
RangeTree<K,T,C>::RangeTree(
        const unsigned int dimension,
        const std::vector<C>& customComparators) :
    dim(dimension),
    comparator(customComparators[dimension-1]),
    customComparators(customComparators)
{
    this->initialize();
}

/**
 * @brief Constructor with a vector of entries (key/value pairs) to be inserted
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] vec Vector of pairs of keys/values
 * @param[in] customComparators Vector of comparators for each
 * dimension of the range tree
 */
template <class K, class T, class C>
RangeTree<K,T,C>::RangeTree(
        const unsigned int dimension,
        const std::vector<std::pair<K,T>>& vec,
        const std::vector<C>& customComparators) :
    dim(dimension),
    comparator(customComparators[dimension-1]),
    customComparators(customComparators)
{
    this->initialize();
    this->construction(vec);
}


/**
 * @brief Constructor with a vector of values to be inserted
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] vec Vector of values
 * @param[in] customComparators Vector of comparators for each
 * dimension of the range tree
 */
template <class K, class T, class C>
RangeTree<K,T,C>::RangeTree(
        const unsigned int dimension,
        const std::vector<K>& vec,
        const std::vector<C>& customComparators) :
    dim(dimension),
    comparator(customComparators[dimension-1]),
    customComparators(customComparators)
{
    this->initialize();
    this->construction(vec);
}

/**
 * @brief Copy constructor
 * @param rangeTree Range tree
 */
template <class K, class T, class C>
RangeTree<K,T,C>::RangeTree(const RangeTree<K,T,C>& bst) :
    dim(bst.dim),
    comparator(bst.comparator),
    customComparators(bst.customComparators)
{
    this->root = this->copyRangeTreeSubtree(bst.root);
    this->entries = bst.entries;
}

/**
 * @brief Move constructor
 * @param rangeTree Range tree
 */
template <class K, class T, class C>
RangeTree<K,T,C>::RangeTree(RangeTree<K,T,C>&& bst) :
    dim(bst.dim),
    comparator(bst.comparator),
    customComparators(bst.customComparators)
{
    this->root = bst.root;
    bst.root = nullptr;
    this->entries = bst.entries;
}

/**
 * @brief Destructor
 */
template <class K, class T, class C>
RangeTree<K,T,C>::~RangeTree()
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
template <class K, class T, class C>
void RangeTree<K,T,C>::construction(const std::vector<K>& vec)
{
    std::vector<std::pair<K,T>> pairVec;

    for (const K& entry : vec) {
        pairVec.push_back(std::make_pair(entry, entry));
    }

    construction(pairVec);
}

/**
 * @brief Construction of the BST given the initial values
 * (pairs of keys/values)
 *
 * A clear operation is performed before the construction
 *
 * @param[in] vec Vector of pairs of keys/values
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::construction(const std::vector<std::pair<K,T>>& vec)
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

            //Create associate trees climbing on parents
            this->createParentAssociatedTreeHelper(node);

            //Insert new node into associated range trees of the node and the parents
            this->insertIntoParentAssociatedTreesHelper(node, node->key, *(node->value));
        }
    }

    assert(this->dim < 2 || this->root->assRangeTree->size() == this->size());
}





/**
 * @brief Insert in the BST a given value
 *
 * @param[in] key Key/value to be inserted
 * @return The iterator pointing to the node if it has been
 * successfully inserted, end iterator otherwise
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::insert(const K& key)
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
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    //Insert node
    Node* result = internal::insertNodeHelperLeaf<Node,K,C>(newNode, this->root, comparator);

    //If node has been inserted
    if (result != nullptr) {
        //New node parent
        Node* newParent = newNode->parent;

        //Getting other child of the parent
        if (newParent != nullptr) {
            Node* otherNode = nullptr;

            if (newParent->left == newNode) {
                otherNode = newParent->right;
            }
            else {
                otherNode = newParent->left;
            }

            //Create associated tree for the parent
            this->createAssociatedTreeHelper(newParent);
            //Insert into associated range tree of the parent the node
            this->insertIntoAssociatedTreeHelper(newParent, otherNode->key, *(otherNode->value));
        }

        //Create associated tree for the node
        this->createAssociatedTreeHelper(newNode);
        //Insert new node into associated range trees of the node and the parents
        Node* deepestNode = this->insertIntoParentAssociatedTreesHelper(newNode, newNode->key, *(newNode->value));


        //Update height and rebalance
        this->updateHeightAndRebalanceRangeTreeHelper(newNode);


        //Increment entry number
        this->entries++;

        //Returns the iterator to the node in the deepest range tree
        return iterator(this, deepestNode);
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
template <class K, class T, class C>
bool RangeTree<K,T,C>::erase(const K& key)
{
    //Query the BST to find the node
    Node* node = internal::findNodeHelperLeaf(key, this->root, comparator);

    //If the node has been found
    if (node != nullptr) {

        //Update associated trees
        this->eraseFromParentAssociatedTreesHelper(node->parent, node->key);

        //Erase node
        Node* replacingNode = internal::eraseNodeHelperLeaf(node, this->root);


        //Update height and rebalance
        this->updateHeightAndRebalanceRangeTreeHelper(replacingNode);

        //Decrease the number of entries
        this->entries--;

        return true;
    }
    return false;
}



/**
 * @brief Find entry in the BST given the key
 *
 * @param[in] key Key of the node to be found
 * @return The iterator pointing to the BST node if the element
 * is contained in the BST, end iterator otherwise
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::find(const K& key)
{
    //If the range tree is not for the first dimension, go to next dimension
    if (dim > 1)
        return this->root->assRangeTree->find(key);

    //Query the BST to find the node
    Node* node = internal::findNodeHelperLeaf(key, this->root, comparator);

    return iterator(this, node);
}





/**
 * @brief Clear the tree, delete all its elements
 *
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::clear()
{
    //Clear entire tree
    internal::clearHelper(this->root);

    //Decreasing entries
    this->entries = 0;
}




/**
 * @brief Get the number of entries in the range tree
 *
 * @return Number of entries
 */
template <class K, class T, class C>
size_t RangeTree<K,T,C>::size()
{
    return this->entries;
}

/**
 * @brief Check if the tree is empty
 *
 * @return True if the range tree is empty
 */
template <class K, class T, class C>
bool RangeTree<K,T,C>::empty()
{
    return (this->size() == 0);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <class K, class T, class C>
size_t RangeTree<K,T,C>::getHeight()
{
    return internal::getHeightHelper(this->root);
}




/**
 * @brief Find entries in the range tree that are enclosed in a given range.
 * Start and end are included bounds of the range.
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Output iterator for the container containing the iterators
 * pointing to the nodes in the deepest range tree which have keys enclosed
 * in the input range
 */
template <class K, class T, class C>template <class OutputIterator>
void RangeTree<K,T,C>::rangeQuery(
        const K& start, const K& end,
        OutputIterator out)
{
    //Output
    std::vector<Node*> nodeOutput;

    //Execute range query
    this->rangeQueryHelper(start, end, nodeOutput);

    for (Node* node : nodeOutput) {
        *out = iterator(this, node);
        out++;
    }
}



/* ----- ITERATOR MIN/MAX NEXT/PREV ----- */

/**
 * @brief Get minimum key entry in the BST
 *
 * @return The iterator pointing to the minimum node
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::getMin()
{
    if (dim > 1) {
        return this->root->assRangeTree->getMin();
    }
    return iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::getMax()
{
    if (dim > 1) {
        return this->root->assRangeTree->getMax();
    }
    return iterator(this, internal::getMaximumHelperLeaf(this->root));
}



/**
 * @brief Get successor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the successor node (end
 * iterator if it has no successor)
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::generic_iterator RangeTree<K,T,C>::getNext(generic_iterator it)
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
template <class K, class T, class C>
typename RangeTree<K,T,C>::generic_iterator RangeTree<K,T,C>::getPrev(generic_iterator it)
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
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::begin()
{
    if (dim > 1) {
        return this->root->assRangeTree->begin();
    }
    return iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief End iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::iterator RangeTree<K,T,C>::end()
{
    return iterator(this, nullptr);
}


/**
 * @brief Begin const iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::const_iterator RangeTree<K,T,C>::cbegin()
{
    if (dim > 1) {
        return this->root->assRangeTree->cbegin();
    }
    return const_iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief End const iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::const_iterator RangeTree<K,T,C>::cend()
{
    return const_iterator(this, nullptr);
}


/**
 * @brief Begin reverse iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::reverse_iterator RangeTree<K,T,C>::rbegin()
{
    if (dim > 1) {
        return this->root->assRangeTree->rbegin();
    }
    return reverse_iterator(this, internal::getMaximumHelperLeaf(this->root));
}

/**
 * @brief End reverse iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::reverse_iterator RangeTree<K,T,C>::rend()
{
    return reverse_iterator(this, nullptr);
}


/**
 * @brief Begin const reverse iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::const_reverse_iterator RangeTree<K,T,C>::crbegin()
{
    if (dim > 1) {
        return this->root->assRangeTree->crbegin();
    }
    return const_reverse_iterator(this, internal::getMaximumHelperLeaf(this->root));
}

/**
 * @brief End const reverse iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::const_reverse_iterator RangeTree<K,T,C>::crend()
{
    return const_reverse_iterator(this, nullptr);
}



/**
 * @brief Insert output iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::insert_iterator RangeTree<K,T,C>::inserter()
{
    return insert_iterator(this);
}



/**
 * @brief Get range based iterator of the BST
 *
 * @return Range based iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::RangeBasedIterator RangeTree<K,T,C>::getIterator()
{
    return RangeBasedIterator(this);
}

/**
 * @brief Get range based const iterator of the BST
 *
 * @return Range based const iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::RangeBasedConstIterator RangeTree<K,T,C>::getConstIterator()
{
    return RangeBasedConstIterator(this);
}

/**
 * @brief Get range based reverse iterator of the BST
 *
 * @return Range based reverse iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::RangeBasedReverseIterator RangeTree<K,T,C>::getReverseIterator()
{
    return RangeBasedReverseIterator(this);
}

/**
 * @brief Get range based const reverse iterator of the BST
 *
 * @return Range based const reverse iterator
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::RangeBasedConstReverseIterator RangeTree<K,T,C>::getConstReverseIterator()
{
    return RangeBasedConstReverseIterator(this);
}


/* ----- SWAP FUNCTION AND ASSIGNMENT ----- */

/**
 * @brief Assignment operator
 * @param[out] bst Parameter BST
 * @return This object
 */
template <class K, class T, class C>
RangeTree<K,T,C>& RangeTree<K,T,C>::operator= (RangeTree<K,T,C> bst)
{
    swap(bst);
    return *this;
}


/**
 * @brief Swap BST with another one
 * @param[out] bst BST to be swapped with this object
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::swap(RangeTree<K,T,C>& bst)
{
    using std::swap;
    swap(this->root, bst.root);
    swap(this->entries, bst.entries);
    swap(this->comparator, bst.comparator);
    swap(this->customComparators, bst.customComparators);
    swap(this->dim, bst.dim);
}


/**
 * @brief Swap graph with another one
 * @param b1 First BST
 * @param b2 Second BST
 */
template <class K, class T, class C>
void swap(RangeTree<K,T,C>& b1, RangeTree<K,T,C>& b2)
{
    b1.swap(b2);
}


/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the range tree
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::initialize()
{
    this->root = nullptr;
    this->entries = 0;
}


template <class K, class T, class C>
typename RangeTree<K,T,C>::Node* RangeTree<K,T,C>::copyRangeTreeSubtree(
        const Node* rootNode,
        Node* parent)
{
    if (rootNode == nullptr)
        return nullptr;

    Node* newNode = new Node(*rootNode);

    newNode->left = this->copyRangeTreeSubtree(rootNode->left, newNode);
    newNode->right = this->copyRangeTreeSubtree(rootNode->right, newNode);
    newNode->parent = parent;
    if (rootNode->value != nullptr)
        newNode->value = new T(*(rootNode->value));

    if (rootNode->assRangeTree != nullptr)
        newNode->assRangeTree = new RangeTree<K,T,C>(*(rootNode->assRangeTree));

    return newNode;
}


/* --------- RANGE QUERY HELPERS --------- */

/**
 * @brief Find entries in the range tree that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Container containing the nodes which have keys enclosed
 * in the input range
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::rangeQueryHelper(
        const K& start, const K& end,
        std::vector<Node*>& out)
{
    //Find split node
    Node* splitNode = internal::findSplitNodeHelperLeaf(start, end, this->root, comparator);

    if (splitNode == nullptr)
        return;

    //If the split node is a leaf
    if (splitNode->isLeaf()) {
        //Report the node if it is contained in the range
        if (internal::isGreaterOrEqual(splitNode->key, start, comparator) &&
                internal::isLessOrEqual(splitNode->key, end, comparator))
        {
            this->rangeSearchInNextDimensionHelper(splitNode, start, end, out);
        }
    }
    //If the split node is not a leaf
    else {
        //Follow path from splitNode to start and report right subtrees
        Node* vl = splitNode->left;
        while (!vl->isLeaf()) {
            if (internal::isLess(start, vl->key, comparator)) {
                this->rangeSearchInNextDimensionHelper(vl->right, start, end, out);
                vl = vl->left;
            }
            else {
                vl = vl->right;
            }
        }
        //Report the node if it is contained in the range
        if (internal::isGreaterOrEqual(vl->key, start, comparator) &&
                internal::isLessOrEqual(vl->key, end, comparator))
        {
            this->rangeSearchInNextDimensionHelper(vl, start, end, out);
        }

        //Follow path from splitNode to end and report left subtrees
        Node* vr = splitNode->right;
        while (!vr->isLeaf()) {
            if (internal::isGreaterOrEqual(end, vr->key, comparator)) {
                this->rangeSearchInNextDimensionHelper(vr->left, start, end, out);
                vr = vr->right;
            }
            else {
                vr = vr->left;
            }
        }
        //Report the node if it is contained in the range
        if (internal::isGreaterOrEqual(vr->key, start, comparator) &&
                internal::isLessOrEqual(vr->key, end, comparator)) {
            this->rangeSearchInNextDimensionHelper(vr, start, end, out);
        }
    }

}


/**
 * @brief Range search in next dimension or report the subtree
 *
 * @param[in] node Root of the subtree
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Container containing the nodes which have keys enclosed
 * in the input range
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::rangeSearchInNextDimensionHelper(
        Node* node,
        const K& start,
        const K& end,
        std::vector<Node*>& out)
{

    if (this->dim > 1) {
        node->assRangeTree->rangeQueryHelper(start, end, out);
    }
    else {
        internal::reportSubTreeHelperLeaf(node, out);
    }
}



/* ----- HELPERS FOR ASSOCIATED RANGE TREE ----- */

/**
 * @brief Create associated tree helper for a node
 *
 * @param[in] node Node
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::createAssociatedTreeHelper(
        Node *node)
{
    if (dim > 1) {
        node->assRangeTree = new RangeTree<K,T,C>(this->dim-1, this->customComparators);
    }
}



/**
 * @brief Create associated tree helper for a node
 * climbing on parents (the input node is included)
 *
 * @param[in] node Node
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::createParentAssociatedTreeHelper(
        Node *node)
{
    if (this->dim > 1) {
        while (node != nullptr && node->assRangeTree == nullptr) {
            //Insert into associated range tree
            createAssociatedTreeHelper(node);

            //Next parent
            node = node->parent;
        }
    }
}


/**
 * @brief Insert into associated range tree key/value of the node
 *
 * @param[in] node Node for which the new node will be inserted into
 * its associated range tree
 * @param[in] key Key of new node
 * @param[in] value Value of new node
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::Node* RangeTree<K,T,C>::insertIntoAssociatedTreeHelper(
        Node* node,
        const K& key,
        const T& value)
{
    if (this->dim > 1) {
        //Insert into associated range tree
        auto it = node->assRangeTree->insert(key, value);
        return it.node;
    }

    return nullptr;
}



/**
 * @brief Insert into associated range trees the current key and value
 * climbing on parents (the input node is included)
 *
 * @param[in] node Node from which the climbing starts
 * @param[in] key Key of new node
 * @param[in] value Value of new node
 * @param[in] dim Dimension of the range tree
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::Node* RangeTree<K,T,C>::insertIntoParentAssociatedTreesHelper(
        Node* node,
        const K& key,
        const T& value)
{
    Node* res = nullptr;
    if (this->dim > 1) {
        while (node != nullptr) {
            //Insert into associated range tree
            res = insertIntoAssociatedTreeHelper(node, key, value);

            //Next parent
            node = node->parent;
        }
    }
    return res;
}


/**
 * @brief Erase from associated range tree key/value of the node
 *
 * @param[in] node Node for which the node will be erase from its
 * associated range tree
 * @param[in] key Key of the node to be deleted
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::eraseFromAssociatedTreeHelper(
        Node* node,
        const K& key)
{
    if (this->dim > 1) {
        //Erase from associated range tree
        node->assRangeTree->erase(key);
    }
}



/**
 * @brief Erase from associated range trees the current key climbing
 * on parents (the input node is included)
 *
 * @param[in] node Node from which the climbing starts
 * @param[in] key Key of new node
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::eraseFromParentAssociatedTreesHelper(
        Node* node,
        const K& key)
{
    if (this->dim > 1) {
        while (node != nullptr) {
            //Erase from associated range tree
            eraseFromAssociatedTreeHelper(node, key);

            //Next parent
            node = node->parent;
        }
    }
}




/* ----- AVL HELPERS FOR RANGE TREE ----- */

/**
 * @brief Rebalance with left/right rotations to make the
 * RangeTree satisfy the AVL constraints
 *
 * @param[in] node Starting node
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::rebalanceRangeTreeHelper(
        Node* node)
{
    //Null handler
    if (node == nullptr)
        return;

    //Not balanced node
    Node* n = node;
    int balanceFactor = (int)(getHeightHelper(n->right) - getHeightHelper(n->left));

    //Climb on parents to find the not balanced node
    while (n != nullptr && balanceFactor >= -1 && balanceFactor <= 1) {
        n = n->parent;

        if (n != nullptr) {
            //Compute balance factor
            balanceFactor = (int)(getHeightHelper(n->right) - getHeightHelper(n->left));

            assert(balanceFactor <= 2 && balanceFactor >= -2);
        }
    }


    if (n != nullptr) {
        assert(balanceFactor == 2 || balanceFactor == -2);
        if (balanceFactor < -1) {
            Node* leftleft = n->left->left;
            Node* leftright = n->left->right;

            //Left left case
            if (getHeightHelper(leftleft) >= getHeightHelper(leftright)) {
                n = rightRotateRangeTreeHelper(n);
            }
            //Left right case
            else {
                n->left = leftRotateRangeTreeHelper(n->left);
                n = rightRotateRangeTreeHelper(n);
            }
        }
        else if (balanceFactor > 1) {
            Node* rightright = n->right->right;
            Node* rightleft = n->right->left;

            //Right right case
            if (getHeightHelper(rightright) >= getHeightHelper(rightleft)) {
                n = leftRotateRangeTreeHelper(n);
            }
            //Left right case
            else {
                n->right = rightRotateRangeTreeHelper(n->right);
                n = leftRotateRangeTreeHelper(n);
            }
        }


        //Set root
        if (n->parent == nullptr) {
            this->root = n;
        }

        //Update heights on parents and rebalance them if needed
        updateHeightAndRebalanceRangeTreeHelper(n->parent);

    }
}



/**
 * @brief Update heights climbing on the parents and then
 * rebalance them if needed
 *
 * @param[in] node Starting node
 * @param[in] node Root node of the BST
 */
template <class K, class T, class C>
void RangeTree<K,T,C>::updateHeightAndRebalanceRangeTreeHelper(
        Node* node)
{
    internal::updateHeightHelper(node);
    this->rebalanceRangeTreeHelper(node);
}



/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @param[in] dim Dimension of the range tree
 * @return New node in the position of the original node after the rotation
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::Node* RangeTree<K,T,C>::leftRotateRangeTreeHelper(Node* a)
{
    //Rotate left
    Node* b = internal::leftRotateHelper(a);


    //Update associated trees
    if (this->dim > 1) {
        //Referencing subtrees
        Node* c = b->right;
        Node* aLeft = a->left;

        if (aLeft != nullptr) {
            //Insert aLeft into b associated tree
            for (auto aLeftIt = aLeft->assRangeTree->begin(); aLeftIt != aLeft->assRangeTree->end(); aLeftIt++) {
                Node* aLeftNode = aLeftIt.node;
                insertIntoAssociatedTreeHelper(b, aLeftNode->key, *(aLeftNode->value));
            }
        }
        //Erase c from a associated tree
        for (auto cIt = c->assRangeTree->begin(); cIt != c->assRangeTree->end(); cIt++) {
            Node* cNode = cIt.node;
            eraseFromAssociatedTreeHelper(a, cNode->key);
        }
    }

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class K, class T, class C>
typename RangeTree<K,T,C>::Node* RangeTree<K,T,C>::rightRotateRangeTreeHelper(Node* a)
{
    //Rotate right
    Node* b = rightRotateHelper(a);


    //Update associated trees
    if (this->dim > 1) {
        //Referencing subtrees
        Node* c = b->left;
        Node* aRight = a->right;

        if (aRight != nullptr) {
            //Insert aRight into b associated tree
            for (auto aRightIt = aRight->assRangeTree->begin(); aRightIt != aRight->assRangeTree->end(); aRightIt++) {
                Node* aRightNode = aRightIt.node;
                insertIntoAssociatedTreeHelper(b, aRightNode->key, *(aRightNode->value));
            }
        }
        //Erase c from a associated tree
        for (auto cIt = c->assRangeTree->begin(); cIt != c->assRangeTree->end(); cIt++) {
            Node* cNode = cIt.node;
            eraseFromAssociatedTreeHelper(a, cNode->key);
        }
    }

    return b;
}



}
