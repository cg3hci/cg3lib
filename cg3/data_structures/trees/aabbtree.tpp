/**
    @author Stefano Nuvoli
*/
#include "aabbtree.h"

#include <stdexcept>
#include <algorithm>
#include <utility>

#include "includes/bstleaf_helpers.h"

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
template <int D, class K, class T>
AABBTree<D,K,T>::AABBTree(
        const AABBValueExtractor customAABBValueExtractor,
        const LessComparator customComparator) :
    lessComparator(customComparator),
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
template <int D, class K, class T>
AABBTree<D,K,T>::AABBTree(
        const std::vector<std::pair<K,T>>& vec,
        const AABBValueExtractor customAABBValueExtractor,
        const LessComparator customComparator) :
    lessComparator(customComparator),
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
template <int D, class K, class T>
AABBTree<D,K,T>::AABBTree(
        const std::vector<K>& vec,
        const AABBValueExtractor customAABBValueExtractor,
        const LessComparator customComparator) :
    lessComparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
{
    this->initialize();
    this->construction(vec);
}


/**
 * @brief Destructor
 */
template <int D, class K, class T>
AABBTree<D,K,T>::~AABBTree() {
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
template <int D, class K, class T>
void AABBTree<D,K,T>::construction(const std::vector<K>& vec) {
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
template <int D, class K, class T>
void AABBTree<D,K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
    this->clear();

    if (vec.size() == 0)
        return;

    std::vector<std::pair<K,T>> sortedVec(vec.begin(), vec.end());

    //Sort the collection
    internal::PairComparator<K,T> pairComparator(lessComparator);
    std::sort(sortedVec.begin(), sortedVec.end(), pairComparator);

    //Create nodes
    std::vector<Node*> sortedNodes;
    for (std::pair<K,T>& pair : sortedVec) {
        Node* node = new Node(pair.first, pair.second);
        sortedNodes.push_back(node);
    }

    //Calling the bottom up helper
    this->entries = internal::constructionBottomUpHelperLeaf(
                sortedNodes,
                this->root,
                lessComparator);

    //Update the height of nodes and create their AABBs
    for (Node*& node : sortedNodes) {
        if (node != nullptr && node->isLeaf()) {
            //Update height
            internal::updateHeightHelper(node);

            //Update AABBs
            internal::updateAABBHelper<D>(node, aabbValueExtractor);
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::insert(const K& key) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    //Insert node
    Node* result = internal::insertNodeHelperLeaf(newNode, this->root, lessComparator);

    //If node has been inserted
    if (result != nullptr) {
        //Update height and rebalance
        internal::updateHeightAndRebalanceAABBHelper<D>(newNode, this->root, aabbValueExtractor);

        //Update AABBs
        internal::updateAABBHelper<D>(newNode, aabbValueExtractor);

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
template <int D, class K, class T>
bool AABBTree<D,K,T>::erase(const K& key) {
    //Query the BST to find the node
    Node* node = internal::findNodeHelperLeaf(key, this->root, lessComparator);

    //If the node has been found
    if (node != nullptr) {
        //Erase node
        Node* replacingNode = internal::eraseNodeHelperLeaf(node, this->root);

        //Update height and rebalance
        internal::updateHeightAndRebalanceAABBHelper<D>(replacingNode, this->root, aabbValueExtractor);

        //Update AABBs
        internal::updateAABBHelper<D>(replacingNode, aabbValueExtractor);

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
template <int D, class K, class T>
void AABBTree<D,K,T>::erase(generic_iterator it) {
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
        internal::updateHeightAndRebalanceAABBHelper(replacingNode, this->root, aabbValueExtractor);

        //Update AABBs
        internal::updateAABBHelper(replacingNode, aabbValueExtractor);

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
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::find(const K& key) {
    //Query the BST to find the node
    Node* node = internal::findNodeHelperLeaf(key, this->root, lessComparator);

    return iterator(this, node);
}





/**
 * @brief Clear the tree, delete all its elements
 *
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::clear() {
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
template <int D, class K, class T>
TreeSize AABBTree<D,K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty, false otherwise
 */
template <int D, class K, class T>
bool AABBTree<D,K,T>::empty() {
    return (this->size() == 0);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <int D, class K, class T>
TreeSize AABBTree<D,K,T>::getHeight()
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
template <int D, class K, class T> template <class OutputIterator>
void AABBTree<D,K,T>::rangeQuery(
        const K& start, const K& end,
        OutputIterator out)
{
    //Output
    std::vector<Node*> nodeOutput;

    //Execute range query
    internal::rangeQueryHelperLeaf(start, end, nodeOutput, this->root, lessComparator);

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
template <int D, class K, class T> template <class OutputIterator>
void AABBTree<D,K,T>::aabbOverlapQuery(
        const K& key,
        OutputIterator out,
        KeyOverlapChecker keyOverlapChecker)
{
    //Get the AABB
    internal::AABB<D> aabb;
    internal::setAABBFromKeyHelper(key, aabb, aabbValueExtractor);

    //Query the AABB tree
    std::vector<Node*> nodeOutput;
    internal::aabbOverlapQueryHelper(this->root, key, aabb, nodeOutput, keyOverlapChecker);

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
template <int D, class K, class T>
bool AABBTree<D,K,T>::aabbOverlapCheck(
        const K& key,
        KeyOverlapChecker keyOverlapChecker)
{
    //Get the AABB
    internal::AABB<D> aabb;
    internal::setAABBFromKeyHelper(key, aabb, aabbValueExtractor);

    //Query the AABB tree
    return internal::aabbOverlapCheckHelper(this->root, key, aabb, keyOverlapChecker);
}





/* ----- ITERATOR MIN/MAX NEXT/PREV ----- */

/**
 * @brief Get minimum key entry in the BST
 *
 * @return The iterator pointing to the minimum node
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::getMin() {
    return iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::getMax() {
    return iterator(this, internal::getMaximumHelperLeaf(this->root));
}



/**
 * @brief Get successor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the successor node (end
 * iterator if it has no successor)
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::generic_iterator AABBTree<D,K,T>::getNext(generic_iterator it) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::generic_iterator AABBTree<D,K,T>::getPrev(generic_iterator it) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::begin() {
    return iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief End iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::iterator AABBTree<D,K,T>::end() {
    return iterator(this, nullptr);
}


/**
 * @brief Begin const iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::const_iterator AABBTree<D,K,T>::cbegin() {
    return const_iterator(this, internal::getMinimumHelperLeaf(this->root));
}

/**
 * @brief End const iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::const_iterator AABBTree<D,K,T>::cend() {
    return const_iterator(this, nullptr);
}


/**
 * @brief Begin reverse iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::reverse_iterator AABBTree<D,K,T>::rbegin() {
    return reverse_iterator(this, internal::getMaximumHelperLeaf(this->root));
}

/**
 * @brief End reverse iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::reverse_iterator AABBTree<D,K,T>::rend() {
    return reverse_iterator(this, nullptr);
}


/**
 * @brief Begin const reverse iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::const_reverse_iterator AABBTree<D,K,T>::crbegin() {
    return const_reverse_iterator(this, internal::getMaximumHelperLeaf(this->root));
}

/**
 * @brief End const reverse iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::const_reverse_iterator AABBTree<D,K,T>::crend() {
    return const_reverse_iterator(this, nullptr);
}



/**
 * @brief Insert output iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::insert_iterator AABBTree<D,K,T>::inserter() {
    return insert_iterator(this);
}



/**
 * @brief AABBTree<D,K,T>::getIterator
 * Get range based iterator of the BST
 *
 * @return Range based iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::RangeBasedIterator AABBTree<D,K,T>::getIterator() {
    return RangeBasedIterator(this);
}

/**
 * @brief AABBTree<D,K,T>::getConstIterator
 * Get range based const iterator of the BST
 *
 * @return Range based const iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::RangeBasedConstIterator AABBTree<D,K,T>::getConstIterator() {
    return RangeBasedConstIterator(this);
}

/**
 * @brief AABBTree<D,K,T>::getReverseIterator
 * Get range based reverse iterator of the BST
 *
 * @return Range based reverse iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::RangeBasedReverseIterator AABBTree<D,K,T>::getReverseIterator() {
    return RangeBasedReverseIterator(this);
}

/**
 * @brief AABBTree<D,K,T>::getConstReverseIterator
 * Get range based const reverse iterator of the BST
 *
 * @return Range based const reverse iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::RangeBasedConstReverseIterator AABBTree<D,K,T>::getConstReverseIterator() {
    return RangeBasedConstReverseIterator(this);
}



/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the BST
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::initialize()
{
    this->root = nullptr;
    this->entries = 0;
}


}
