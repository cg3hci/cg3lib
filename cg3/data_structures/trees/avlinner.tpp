/**
    @author Stefano Nuvoli
*/
#include "avlinner.h"

#include <stdexcept>
#include <algorithm>
#include <utility>

#include "includes/bstinner_helpers.h"
#include "includes/avl_helpers.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */

/**
 * @brief Default constructor
 *
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
AVLInner<K,T>::AVLInner(const LessComparator customComparator) :
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
AVLInner<K,T>::AVLInner(
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
AVLInner<K,T>::AVLInner(
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
AVLInner<K,T>::~AVLInner() {
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
void AVLInner<K,T>::construction(const std::vector<K>& vec) {
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
void AVLInner<K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
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

    //Calling the recursive helper
    this->entries = internal::constructionMedianHelperInner(
                sortedNodes,
                0,
                sortedNodes.size(),
                this->root,
                lessComparator);

    //Update the height of nodes
    for (Node*& node : sortedNodes) {
        if (node != nullptr && node->isLeaf()) {
            internal::updateHeightHelper(node);
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
template <class K, class T>
typename AVLInner<K,T>::iterator AVLInner<K,T>::insert(const K& key) {
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
typename AVLInner<K,T>::iterator AVLInner<K,T>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    //Insert node
    Node* result = internal::insertNodeHelperInner(newNode, this->root, lessComparator);

    //If node has been inserted
    if (result != nullptr) {
        //Update height and rebalance
        internal::updateHeightAndRebalanceHelper(newNode, this->root);

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
bool AVLInner<K,T>::erase(const K& key) {
    //Query the BST to find the node
    Node* node = internal::findNodeHelperInner(key, this->root, lessComparator);

    //If the node has been found
    if (node != nullptr) {
        //Erase node
        Node* replacingNode = internal::eraseNodeHelperInner(node, this->root);

        //Update height and rebalance
        internal::updateHeightAndRebalanceHelper(replacingNode, this->root);

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
void AVLInner<K,T>::erase(generic_iterator it) {
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }

    //Save node to be deleted
    Node* node = it.node;


    if (node != nullptr) {
        //Erase node
        Node* replacingNode = internal::eraseNodeHelperInner(node, this->root);

        //Update height and rebalance
        internal::updateHeightAndRebalanceHelper(replacingNode, this->root);

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
typename AVLInner<K,T>::iterator AVLInner<K,T>::find(const K& key) {
    //Query the BST to find the node
    Node* node = internal::findNodeHelperInner(key, this->root, lessComparator);

    return iterator(this, node);
}


/**
 * @brief Find the entry in the BST which is right lower than (or equal to)
 * a given key
 *
 * @param[in] key Input key
 * @return The iterator pointing to the BST node if the element (lower/equal)
 * exists in the BST, end iterator otherwise
 */
template <class K, class T>
typename AVLInner<K,T>::iterator AVLInner<K,T>::findLower(const K& key) {
    //Query the BST to find the node
    Node* node = internal::findLowerHelperInner(key, this->root, lessComparator);

    return iterator(this, node);
}



/**
 * @brief Find the entry in the BST which is right upper than a given key
 *
 * @param[in] key Key of the node to be found
 * @return The iterator pointing to the BST node if the element (upper)
 * exists in the BST, end iterator otherwise
 */
template <class K, class T>
typename AVLInner<K,T>::iterator AVLInner<K,T>::findUpper(const K& key) {
    //Query the BST to find the node
    Node* node = internal::findUpperHelperInner(key, this->root, lessComparator);

    return iterator(this, node);
}





/**
 * @brief Clear the tree, delete all its elements
 *
 */
template <class K, class T>
void AVLInner<K,T>::clear() {
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
template <class K, class T>
TreeSize AVLInner<K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty, false otherwise
 */
template <class K, class T>
bool AVLInner<K,T>::empty() {
    return (this->size() == 0);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <class K, class T>
TreeSize AVLInner<K,T>::getHeight()
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
template <class K, class T> template <class OutputIterator>
void AVLInner<K,T>::rangeQuery(
        const K& start, const K& end,
        OutputIterator out)
{
    //Output
    std::vector<Node*> nodeOutput;

    //Execute range query
    internal::rangeQueryHelperInner(start, end, nodeOutput, this->root, lessComparator);

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
typename AVLInner<K,T>::iterator AVLInner<K,T>::getMin() {
    return iterator(this, internal::getMinimumHelperInner(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <class K, class T>
typename AVLInner<K,T>::iterator AVLInner<K,T>::getMax() {
    return iterator(this, internal::getMaximumHelperInner(this->root));
}



/**
 * @brief Get successor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the successor node (end
 * iterator if it has no successor)
 */
template <class K, class T>
typename AVLInner<K,T>::generic_iterator AVLInner<K,T>::getNext(generic_iterator it) {
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }
    return generic_iterator(this, internal::getSuccessorHelperInner(it.node));
}

/**
 * @brief Get predecessor of a element pointed by iterator
 *
 * @param[in] it Iterator pointing to the node
 * @return The iterator pointing to the predecessor node (end
 * iterator if it has no predecessor)
 */
template <class K, class T>
typename AVLInner<K,T>::generic_iterator AVLInner<K,T>::getPrev(generic_iterator it) {
    //Throw exception if the iterator does not belong to this BST
    if (it.bst != this) {
        throw new std::runtime_error("A tree can only use its own nodes.");
    }
    return generic_iterator(this, internal::getPredecessorHelperInner(it.node));
}



/* --------- ITERATORS --------- */

/**
 * @brief Begin iterator
 */
template <class K, class T>
typename AVLInner<K,T>::iterator AVLInner<K,T>::begin() {
    return iterator(this, internal::getMinimumHelperInner(this->root));
}

/**
 * @brief End iterator
 */
template <class K, class T>
typename AVLInner<K,T>::iterator AVLInner<K,T>::end() {
    return iterator(this, nullptr);
}


/**
 * @brief Begin const iterator
 */
template <class K, class T>
typename AVLInner<K,T>::const_iterator AVLInner<K,T>::cbegin() {
    return const_iterator(this, internal::getMinimumHelperInner(this->root));
}

/**
 * @brief End const iterator
 */
template <class K, class T>
typename AVLInner<K,T>::const_iterator AVLInner<K,T>::cend() {
    return const_iterator(this, nullptr);
}


/**
 * @brief Begin reverse iterator
 */
template <class K, class T>
typename AVLInner<K,T>::reverse_iterator AVLInner<K,T>::rbegin() {
    return reverse_iterator(this, internal::getMaximumHelperInner(this->root));
}

/**
 * @brief End reverse iterator
 */
template <class K, class T>
typename AVLInner<K,T>::reverse_iterator AVLInner<K,T>::rend() {
    return reverse_iterator(this, nullptr);
}


/**
 * @brief Begin const reverse iterator
 */
template <class K, class T>
typename AVLInner<K,T>::const_reverse_iterator AVLInner<K,T>::crbegin() {
    return const_reverse_iterator(this, internal::getMaximumHelperInner(this->root));
}

/**
 * @brief End const reverse iterator
 */
template <class K, class T>
typename AVLInner<K,T>::const_reverse_iterator AVLInner<K,T>::crend() {
    return const_reverse_iterator(this, nullptr);
}



/**
 * @brief Insert output iterator
 */
template <class K, class T>
typename AVLInner<K,T>::insert_iterator AVLInner<K,T>::inserter() {
    return insert_iterator(this);
}



/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the BST
 */
template <class K, class T>
void AVLInner<K,T>::initialize()
{
    this->root = nullptr;
    this->entries = 0;
}


}
