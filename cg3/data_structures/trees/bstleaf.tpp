/**
    @author Stefano Nuvoli
*/
#include "bstleaf.h"

#include "includes/bstleaf_helpers.h"

#include <stdexcept>
#include <algorithm>
#include <utility>

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */

/**
 * @brief Default constructor
 *
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
BSTLeaf<K,T>::BSTLeaf(const LessComparator customComparator) :
    lessComparator(customComparator)
{
    this->initialize();
}

/**
 * @brief Constructor with a vector of entries (key/value pairs) to be inserted
 *
 * @param[in] vec Vector of pairs of keys/values
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
BSTLeaf<K,T>::BSTLeaf(
        const std::vector<std::pair<K,T>>& vec,
        const LessComparator customComparator) :
    lessComparator(customComparator)
{
    this->initialize();
    this->construction(vec);
}


/**
 * @brief Constructor with a vector of values to be inserted
 *
 * @param[in] vec Vector of values
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
BSTLeaf<K,T>::BSTLeaf(
        const std::vector<K>& vec,
        const LessComparator customComparator) :
    lessComparator(customComparator)
{
    this->initialize();
    this->construction(vec);
}


/**
 * @brief Destructor
 */
template <class K, class T>
BSTLeaf<K,T>::~BSTLeaf() {
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
void BSTLeaf<K,T>::construction(const std::vector<K>& vec) {
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
template <class K, class T>
void BSTLeaf<K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
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

    //Calling the bottom up construction helper
    this->entries = constructionBottomUpHelperLeaf(
                sortedNodes,
                this->root,
                lessComparator);
}




/**
 * @brief Insert in the BST a given value
 *
 * @param[in] key Key/value to be inserted
 * @return The iterator pointing to the node if it has been
 * successfully inserted, end iterator otherwise
 */
template <class K, class T>
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::insert(const K& key) {
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
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    //Insert node
    Node* result = insertNodeHelperLeaf(newNode, this->root, lessComparator);

    //If node has been inserted
    if (result != nullptr) {
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
bool BSTLeaf<K,T>::erase(const K& key) {
    //Query the BST to find the node
    Node* node = findNodeHelperLeaf(key, this->root, lessComparator);

    //If the node has been found
    if (node != nullptr) {
        //Erase node
        eraseNodeHelperLeaf(node, this->root);

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
template <class K, class T>
void BSTLeaf<K,T>::erase(generic_iterator it) {
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }

    //Save node to be deleted
    Node* node = it.node;

    if (node != nullptr) {
        //Erase node
        eraseNodeHelperLeaf(node, this->root);

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
template <class K, class T>
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::find(const K& key) {
    //Query the BST to find the node
    Node* node = findNodeHelperLeaf(key, this->root, lessComparator);

    return iterator(this, node);
}





/**
 * @brief Clear the tree, delete all its elements
 *
 */
template <class K, class T>
void BSTLeaf<K,T>::clear() {
    //Clear entire tree
    clearHelper(this->root);

    //Decreasing entries
    this->entries = 0;
}




/**
 * @brief Get the number of entries in the BST
 *
 * @return Number of entries in the BST
 */
template <class K, class T>
TreeSize BSTLeaf<K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty, false otherwise
 */
template <class K, class T>
bool BSTLeaf<K,T>::empty() {
    return (this->size() == 0);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <class K, class T>
TreeSize BSTLeaf<K,T>::getHeight()
{
    return getHeightRecursiveHelper(this->root);
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
template <class K, class T> template <class OutputIterator>
void BSTLeaf<K,T>::rangeQuery(
        const K& start, const K& end,
        OutputIterator out)
{
    //Output
    std::vector<Node*> nodeOutput;

    //Execute range query
    rangeQueryHelperLeaf(start, end, nodeOutput, this->root, lessComparator);

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
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::getMin() {
    return iterator(this, getMinimumHelperLeaf(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <class K, class T>
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::getMax() {
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
typename BSTLeaf<K,T>::generic_iterator BSTLeaf<K,T>::getNext(generic_iterator it) {
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
typename BSTLeaf<K,T>::generic_iterator BSTLeaf<K,T>::getPrev(generic_iterator it) {
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
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::begin() {
    return iterator(this, getMinimumHelperLeaf(this->root));
}

/**
 * @brief End iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::iterator BSTLeaf<K,T>::end() {
    return iterator(this, nullptr);
}


/**
 * @brief Begin const iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::const_iterator BSTLeaf<K,T>::cbegin() {
    return const_iterator(this, getMinimumHelperLeaf(this->root));
}

/**
 * @brief End const iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::const_iterator BSTLeaf<K,T>::cend() {
    return const_iterator(this, nullptr);
}


/**
 * @brief Begin reverse iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::reverse_iterator BSTLeaf<K,T>::rbegin() {
    return reverse_iterator(this, getMaximumHelperLeaf(this->root));
}

/**
 * @brief End reverse iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::reverse_iterator BSTLeaf<K,T>::rend() {
    return reverse_iterator(this, nullptr);
}


/**
 * @brief Begin const reverse iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::const_reverse_iterator BSTLeaf<K,T>::crbegin() {
    return const_reverse_iterator(this, getMaximumHelperLeaf(this->root));
}

/**
 * @brief End const reverse iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::const_reverse_iterator BSTLeaf<K,T>::crend() {
    return const_reverse_iterator(this, nullptr);
}



/**
 * @brief Insert output iterator
 */
template <class K, class T>
typename BSTLeaf<K,T>::insert_iterator BSTLeaf<K,T>::inserter() {
    return insert_iterator(this);
}



/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the BST
 */
template <class K, class T>
void BSTLeaf<K,T>::initialize()
{
    this->root = nullptr;
    this->entries = 0;
}


}
