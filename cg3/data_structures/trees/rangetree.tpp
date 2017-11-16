/**
    @author Stefano Nuvoli
*/
#include "rangetree.h"

#include "assert.h"

#include "includes/bstleafhelpers.h"
#include "includes/avlhelpers.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */



/**
 * @brief Default constructor
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] customComparators Vector of comparators for each
 * dimension of the range tree
 */
template <class K, class T>
RangeTree<K,T>::RangeTree(
        const unsigned int dimension,
        const std::vector<LessComparator>& customComparators) :
    dim(dimension),
    lessComparator(customComparators[dimension-1]),
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
template <class K, class T>
RangeTree<K,T>::RangeTree(
        const unsigned int dimension,
        const std::vector<std::pair<K,T>>& vec,
        const std::vector<LessComparator>& customComparators) :
    dim(dimension),
    lessComparator(customComparators[dimension-1]),
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
template <class K, class T>
RangeTree<K,T>::RangeTree(
        const unsigned int dimension,
        const std::vector<K>& vec,
        const std::vector<LessComparator>& customComparators) :
    dim(dimension),
    lessComparator(customComparators[dimension-1]),
    customComparators(customComparators)
{
    this->initialize();
    this->construction(vec);
}


/**
 * @brief Destructor
 */
template <class K, class T>
RangeTree<K,T>::~RangeTree() {
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
template <class K, class T>
void RangeTree<K,T>::construction(const std::vector<K>& vec) {
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
template <class K, class T>
void RangeTree<K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
    this->clear();

    if (vec.size() == 0)
        return;

    std::vector<std::pair<K,T>> sortedVec(vec.begin(), vec.end());

    //Sort the collection
    PairComparator<K,T> pairComparator(lessComparator);
    std::sort(sortedVec.begin(), sortedVec.end(), pairComparator);

    //Create nodes
    std::vector<Node*> sortedNodes;
    for (std::pair<K,T>& pair : sortedVec) {
        Node* node = new Node(pair.first, pair.second);
        sortedNodes.push_back(node);
    }

    //Calling the bottom up helper
    this->entries = constructionBottomUpHelperLeaf(
                sortedNodes,
                this->root,
                lessComparator);

    //Update the height of nodes and create their AABBs
    for (Node*& node : sortedNodes) {
        if (node != nullptr && node->isLeaf()) {
            //Update height
            updateHeightHelper(node);

            //Create associate trees climbing on parents
            createParentAssociatedTreeHelper<Node,K,T>(node, dim, customComparators);

            //Insert new node into associated range trees of the node and the parents
            insertIntoParentAssociatedTreesHelper(node, node->key, *(node->value), dim);
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
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::insert(const K& key) {
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
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    //Insert node
    Node* result = insertNodeHelperLeaf(newNode, this->root, lessComparator);

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
            createAssociatedTreeHelper<Node,K,T>(newParent, dim, customComparators);
            //Insert into associated range tree of the parent the node
            insertIntoAssociatedTreeHelper(newParent, otherNode->key, *(otherNode->value), dim);
        }

        //Create associated tree for the node
        createAssociatedTreeHelper<Node,K,T>(newNode, dim, customComparators);
        //Insert new node into associated range trees of the node and the parents
        insertIntoParentAssociatedTreesHelper(newNode, newNode->key, *(newNode->value), dim);


        //Update height and rebalance
        updateHeightAndRebalanceRangeTreeHelper(newNode, this->root, dim);


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
template <class K, class T>
bool RangeTree<K,T>::erase(const K& key) {
    //Query the BST to find the node
    Node* node = findNodeHelperLeaf(key, this->root, lessComparator);

    //If the node has been found
    if (node != nullptr) {

        //Update associated trees
        eraseFromParentAssociatedTreesHelper(node->parent, node->key, dim);

        //Erase node
        Node* replacingNode = eraseNodeHelperLeaf(node, this->root);


        //Update height and rebalance
        updateHeightAndRebalanceRangeTreeHelper(replacingNode, this->root, dim);

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
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::find(const K& key) {
    //If the range tree is not for the first dimension, go to next dimension
    if (dim > 1)
        return this->root->assRangeTree->find(key);

    //Query the BST to find the node
    Node* node = findNodeHelperLeaf(key, this->root, lessComparator);

    return iterator(this, node);
}





/**
 * @brief Clear the tree, delete all its elements
 *
 */
template <class K, class T>
void RangeTree<K,T>::clear() {
    //Clear entire tree
    clearHelper(this->root);

    //Decreasing entries
    this->entries = 0;
}




/**
 * @brief Get the number of entries in the range tree
 *
 * @return Number of entries
 */
template <class K, class T>
size_t RangeTree<K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if the tree is empty
 *
 * @return True if the range tree is empty
 */
template <class K, class T>
bool RangeTree<K,T>::empty()
{
    return (this->size() == 0);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <class K, class T>
size_t RangeTree<K,T>::getHeight()
{
    return getHeightHelper(this->root);
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
template <class K, class T>template <class OutputIterator>
void RangeTree<K,T>::rangeQuery(
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
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::getMin() {
    if (dim > 1) {
        return this->root->assRangeTree->getMin();
    }
    return iterator(this, getMinimumHelperLeaf(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::getMax() {
    if (dim > 1) {
        return this->root->assRangeTree->getMax();
    }
    return iterator(this, getMaximumHelperLeaf(this->root));
}



/**
 * @brief Get successor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the successor node (end
 * iterator if it has no successor)
 */
template <class K, class T>
typename RangeTree<K,T>::generic_iterator RangeTree<K,T>::getNext(generic_iterator it) {
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }
    return generic_iterator(this, getSuccessorHelperLeaf(it.node));
}

/**
 * @brief Get predecessor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the predecessor node (end
 * iterator if it has no predecessor)
 */
template <class K, class T>
typename RangeTree<K,T>::generic_iterator RangeTree<K,T>::getPrev(generic_iterator it) {
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }
    return generic_iterator(this, getPredecessorHelperLeaf(it.node));
}



/* --------- ITERATORS --------- */

/**
 * @brief Begin iterator
 */
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::begin() {
    if (dim > 1) {
        return this->root->assRangeTree->begin();
    }
    return iterator(this, getMinimumHelperLeaf(this->root));
}

/**
 * @brief End iterator
 */
template <class K, class T>
typename RangeTree<K,T>::iterator RangeTree<K,T>::end() {
    return iterator(this, nullptr);
}


/**
 * @brief Begin const iterator
 */
template <class K, class T>
typename RangeTree<K,T>::const_iterator RangeTree<K,T>::cbegin() {
    if (dim > 1) {
        return this->root->assRangeTree->cbegin();
    }
    return const_iterator(this, getMinimumHelperLeaf(this->root));
}

/**
 * @brief End const iterator
 */
template <class K, class T>
typename RangeTree<K,T>::const_iterator RangeTree<K,T>::cend() {
    return const_iterator(this, nullptr);
}


/**
 * @brief Begin reverse iterator
 */
template <class K, class T>
typename RangeTree<K,T>::reverse_iterator RangeTree<K,T>::rbegin() {
    if (dim > 1) {
        return this->root->assRangeTree->rbegin();
    }
    return reverse_iterator(this, getMaximumHelperLeaf(this->root));
}

/**
 * @brief End reverse iterator
 */
template <class K, class T>
typename RangeTree<K,T>::reverse_iterator RangeTree<K,T>::rend() {
    return reverse_iterator(this, nullptr);
}


/**
 * @brief Begin const reverse iterator
 */
template <class K, class T>
typename RangeTree<K,T>::const_reverse_iterator RangeTree<K,T>::crbegin() {
    if (dim > 1) {
        return this->root->assRangeTree->crbegin();
    }
    return const_reverse_iterator(this, getMaximumHelperLeaf(this->root));
}

/**
 * @brief End const reverse iterator
 */
template <class K, class T>
typename RangeTree<K,T>::const_reverse_iterator RangeTree<K,T>::crend() {
    return const_reverse_iterator(this, nullptr);
}



/**
 * @brief Insert output iterator
 */
template <class K, class T>
typename RangeTree<K,T>::insert_iterator RangeTree<K,T>::inserter() {
    return insert_iterator(this);
}




/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the range tree
 */
template <class K, class T>
void RangeTree<K,T>::initialize()
{
    this->root = nullptr;
    this->entries = 0;
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
template <class K, class T>
inline void RangeTree<K,T>::rangeQueryHelper(
        const K& start, const K& end,
        std::vector<Node*>& out)
{
    //Find split node
    Node* splitNode = findSplitNodeHelperLeaf(start, end, this->root, lessComparator);

    if (splitNode == nullptr)
        return;

    //If the split node is a leaf
    if (splitNode->isLeaf()) {
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(splitNode->key, start, lessComparator) &&
                isLessOrEqual(splitNode->key, end, lessComparator))
        {
            this->rangeSearchInNextDimensionHelper(splitNode, start, end, out);
        }
    }
    //If the split node is not a leaf
    else {
        //Follow path from splitNode to start and report right subtrees
        Node* vl = splitNode->left;
        while (!vl->isLeaf()) {
            if (isLess(start, vl->key, lessComparator)) {
                this->rangeSearchInNextDimensionHelper(vl->right, start, end, out);
                vl = vl->left;
            }
            else {
                vl = vl->right;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vl->key, start, lessComparator) &&
                isLessOrEqual(vl->key, end, lessComparator))
        {
            this->rangeSearchInNextDimensionHelper(vl, start, end, out);
        }

        //Follow path from splitNode to end and report left subtrees
        Node* vr = splitNode->right;
        while (!vr->isLeaf()) {
            if (isGreaterOrEqual(end, vr->key, lessComparator)) {
                this->rangeSearchInNextDimensionHelper(vr->left, start, end, out);
                vr = vr->right;
            }
            else {
                vr = vr->left;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start, lessComparator) && isLessOrEqual(vr->key, end, lessComparator)) {
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
template <class K, class T>
inline void RangeTree<K,T>::rangeSearchInNextDimensionHelper(
        Node* node,
        const K& start,
        const K& end,
        std::vector<Node*>& out)
{

    if (dim > 1) {
        node->assRangeTree->rangeQueryHelper(start, end, out);
    }
    else {
        reportSubTreeHelperLeaf(node, out);
    }
}





}
