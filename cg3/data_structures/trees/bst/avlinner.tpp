/**
    @author Stefano Nuvoli
*/
#include "avlinner.h"

#include "assert.h"

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
    endIterator(Iterator(nullptr)),
    lessComparator(customComparator)
{
    this->initHelper();
}

/**
 * @brief Constructor with a vector of entries (key/value pairs) to be inserted
 *
 * @param[in] vec Vector of pairs of keys/values
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
AVLInner<K,T>::AVLInner(const std::vector<std::pair<K,T>>& vec,
                        const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    lessComparator(customComparator)
{
    this->initHelper();
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
AVLInner<K,T>::AVLInner(const std::vector<K>& vec,
                        const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    lessComparator(customComparator)
{
    this->initHelper();
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
    clear();

    if (vec.size() == 0)
        return;

    //Sort the collection
    std::vector<std::pair<K,T>> sortedVec(vec.begin(), vec.end());
    std::sort(sortedVec.begin(), sortedVec.end(), *this);

    //Calling the recursive helper
    this->constructionMedianHelper(sortedVec, 0, sortedVec.size());
}




/**
 * @brief Insert in the BST a given value
 *
 * @param[in] key Key/value to be inserted
 * @return The iterator pointing to the node if it has been
 * successfully inserted, end iterator otherwise
 */
template <class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::insert(const K& key) {
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
typename AVLInner<K,T>::Iterator AVLInner<K,T>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    if (this->insertNodeHelper(newNode)) {
        return Iterator(newNode);
    }

    return this->end();
}





/**
 * @brief Erase an entry from BST given the iterator
 *
 * The iterator is incremented after element is removed
 *
 * @param[in] it Iterator pointing to the node to be erased
 */
template <class K, class T>
void AVLInner<K,T>::erase(Iterator& it) {
    //Save node to be deleted
    Node* node = it.getNode();

    it++;

    this->eraseNodeHelper(node);
}

/**
 * @brief Erase value from BST given the key
 *
 * @param[in] key Key of the node
 * @return True if item has been found and then erased, false otherwise
 */
template <class K, class T>
bool AVLInner<K,T>::erase(const K& key) {
    //Query to find the node
    Node* node = this->findNodeHelper(key);

    //If the node has been found
    if (node != nullptr) {
        this->eraseNodeHelper(node);
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
typename AVLInner<K,T>::Iterator AVLInner<K,T>::find(const K& key) {
    Node* node = this->findNodeHelper(key);
    return Iterator(node);
}




/**
 * @brief Get minimum key entry in the BST
 *
 * @return The iterator pointing to the minimum node
 */
template<class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::getMin() {
    return Iterator(getMinimumHelper(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template<class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::getMax() {
    return Iterator(getMaximumHelper(this->root));
}




/**
 * @brief Clear the tree, delete all its elements
 *
 * Recursive implementation
 */
template <class K, class T>
void AVLInner<K,T>::clear() {
    this->clearHelper(this->root);
}




/**
 * @brief Get the number of entries in the BST
 *
 * @return Number of entries
 */
template <class K, class T>
size_t AVLInner<K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty
 */
template <class K, class T>
bool AVLInner<K,T>::empty()
{
    return (this->size() == 0) && (this->root == nullptr);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <class K, class T>
size_t AVLInner<K,T>::getHeight()
{
    return getHeightHelper(this->root);
}

/**
 * @brief Find entries in the BST that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of iterators pointing to the
 * elements enclosed in the input range
 */
template<class K, class T>
void AVLInner<K,T>::rangeQuery(const K& start, const K& end,
                               std::vector<Iterator> &out)
{
    std::vector<Node*> nodeOutput;
    this->rangeQueryHelper(start, end, nodeOutput);
    for (Node* node : nodeOutput) {
        out.push_back(Iterator(node));
    }
}



/* --------- ITERATORS --------- */

/**
 * @brief Begin iterator
 */
template <class K, class T>
typename AVLInner<K,T>::Iterator AVLInner<K,T>::begin() {
    return Iterator(this->getMin());
}

/**
 * @brief End iterator
 */
template <class K, class T>
const typename AVLInner<K,T>::Iterator& AVLInner<K,T>::end() {
    return this->endIterator;
}




/* --------- HELPERS --------- */

/**
 * @brief Initialization of the BST
 */
template <class K, class T>
void AVLInner<K,T>::initHelper()
{
    this->root = nullptr;
    this->entries = 0;
}


/**
 * Construction of the balanced BST given a vector of sorted elements
 *
 * Recursive implementation
 *
 * @param[in] sortedVec Sorted vector of entries (pair of keys/values)
 * @param[in] start Start index of the partition of the vector to be inserted
 * @param[in] end End index of the partition of the vector to be inserted
 */
template <class K, class T>
void AVLInner<K,T>::constructionMedianHelper(
        const std::vector<std::pair<K,T>>& sortedVec,
        const size_t start, const size_t end)
{
    if (end <= start)
        return;

    //Median
    size_t mid = start + (end-start)/2;

    //Taking median value
    const std::pair<K,T>& pair = sortedVec.at(mid);

    this->insert(pair.first, pair.second);

    //Calculate next partitions of the vector
    size_t firstHalfEnd = mid;
    size_t secondHalfStart = mid + 1;

    //Recursive calls
    this->constructionMedianHelper(sortedVec, start, firstHalfEnd);
    this->constructionMedianHelper(sortedVec, secondHalfStart, end);
}


/**
 * @brief Insert a node in the BST
 *
 * @param[in] node Node to be inserted
 * @return True if the node has been inserted
 */
template <class K, class T>
bool AVLInner<K,T>::insertNodeHelper(
        Node*& newNode)
{
    //Find the position in the BST in which
    //the new node must be inserted
    Node* lastVisitedNode = nullptr;
    Node* node = this->root;

    while (node != nullptr && !isEqual(node->key, newNode->key)) {
        lastVisitedNode = node;

        if (isLess(newNode->key, node->key)) {
            node = node->left;
        }
        else {                        
            node = node->right;
        }
    }

    //If the value is not contained in the BST
    if (node == nullptr) {

        //If the tree is empty: insert the node as the root
        if (lastVisitedNode == nullptr) {
            newNode->parent = nullptr;
            this->root = newNode;
        }
        //If the tree is not empty
        else {
            newNode->parent = lastVisitedNode;

            //Insert the node as a child of the last visited node
            if (isLess(newNode->key, lastVisitedNode->key)) {
                lastVisitedNode->left = newNode;
            }
            else {
                lastVisitedNode->right = newNode;
            }
        }

        //Update heights and rebalance
        updateHeightHelper(lastVisitedNode);
        rebalanceHelper(lastVisitedNode);


        //Increment entry number
        this->entries++;

        return true;
    }


    //If the value is already in the BST
    delete newNode;
    newNode = nullptr;

    return false;
}


/**
 * @brief Find an entry on the BST given a key
 *
 * @param[in] key Key of the node to be found
 *
 * @return If the node with a given value is found, then its pointer
 * is returned. Otherwise a null pointer is returned.
 *
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::findNodeHelper(const K& key) const {
    Node* node = this->root;

    //Follow a path until the node is found
    while (node != nullptr && !isEqual(node->key, key)) {
        if (isLess(key, node->key)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return node;
}


/**
 * @brief Erase node from BST
 *
 * @param[in] node Node to be erased
 */
template <class K, class T>
void AVLInner<K,T>::eraseNodeHelper(Node*& node) {
    //Node that will replace the node to be erased
    Node* y;

    //Child of the node that will replace the node to be erased
    Node* x;

    //If the node is a leaf
    if (node->left == nullptr || node->right == nullptr) {
        y = node;
    }
    //If the node is not a leaf, get the successor
    else {
        y = getSuccessorHelper(node);
    }

    //If y has a left child
    if (y->left != nullptr) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    //If x is a node, set the parent
    if (x != nullptr) {
        x->parent = y->parent;
    }

    //Setting relationships between nodes
    if (y->parent == nullptr) {
        this->root = x;
    }
    else {
        if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }

    //If the node was not a leaf, copy (replace)
    //keys and values of y in the node to be deleted
    if (y != node) {
        //Switch values (delete operation on value pointer)
        T* nodeValue = node->value;
        node->value = y->value;
        y->value = nodeValue;

        //Set new key
        node->key = y->key;
    }

    //Update heights and rebalance
    updateHeightHelper(y->parent);
    rebalanceHelper(y->parent);


    //Delete the node
    delete y;
    y = nullptr;

    //Decrease the number of entries
    this->entries--;
}



/**
 * @brief Get the successor of a node
 *
 * @param[in] node Input node
 * @return Successor of the node, nullptr if there is no successor
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::getSuccessorHelper(Node* node) {
    Node* x = node;

    //If it has a right child, get the minimum node of subtree
    //rooted in the right child
    if (x->right != nullptr)
        return getMinimumHelper(x->right);

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }

    return y;
}


/**
 * @brief Get predecessor of a node
 *
 * @param[in] node Input node
 * @return Predecessor of the node, nullptr if there is no predecessor
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::getPredecessorHelper(Node* node) {
    Node* x = node;

    // If it has a left child, get the maximum node of subtree
    // rooted in the left child
    if (x->left != nullptr)
        return getMaximumHelper(x->left);

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}


/**
 * @brief Get minimum key node of the subtree
 *
 * @param[in] startingNode Root of the subtree
 * @return Minimum key node pointer
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::getMinimumHelper(Node* rootNode) {
    Node* x = rootNode;

    while (x != nullptr && x->left != nullptr)
        x = x->left;

    return x;
}


/**
 * @brief Get maximum key node of the subtree
 *
 * @param[in] startingNode Root of the subtree
 * @return Maximum key node pointer
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::getMaximumHelper(Node* rootNode) {
    Node* x = rootNode;

    while (x != nullptr && x->right != nullptr)
        x = x->right;

    return x;
}


/**
 * @brief Clear a given subtree
 *
 * @param[in] node Root of the subtree
 */
template <class K, class T>
void AVLInner<K,T>::clearHelper(Node*& rootNode) {
    //If it is already empty
    if (rootNode == nullptr)
        return;

    //Getting referencies
    Node*& left = rootNode->left;
    Node*& right = rootNode->right;

    //Delete data
    delete rootNode;
    rootNode = nullptr;

    //Decreasing entries
    this->entries--;

    //Clear subtrees
    this->clearHelper(left);
    this->clearHelper(right);
}



/**
 * @brief Get max height of the subtree rooted in a node
 *
 * @param[in] node Root node
 * @return Max height of the subtree
 */
template <class K, class T>
size_t AVLInner<K,T>::getHeightHelper(const Node* node)
{
    if (node == nullptr)
        return 0;

    return node->height;
}


/* --------- RANGE QUERY HELPERS --------- */

/**
 * @brief Find entries in the BST that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of node with keys that are enclosed in the input range
 */
template <class K, class T>
void AVLInner<K,T>::rangeQueryHelper(const K& start, const K& end,
                                     std::vector<Node*> &out)
{
    //Find split node
    Node* splitNode = findSplitNodeHelper(start, end);
    if (splitNode == nullptr)
        return;


    //Report node if it is contained in the range
    if (isGreaterOrEqual(splitNode->key, start) && isLessOrEqual(splitNode->key, end)) {
        out.push_back(splitNode);
    }

    //Follow path from splitNode to start and report right subtrees
    Node* vl = splitNode->left;
    while (vl != nullptr) {
        //Report node if it is contained in the range
        if (isGreaterOrEqual(vl->key, start) && isLessOrEqual(vl->key, end)) {
            out.push_back(vl);
        }

        //Report left child if it is contained in the range
        if (isLess(start, vl->key)) {
            reportSubTreeHelper(vl->right, out);
            vl = vl->left;
        }
        //Go to right child
        else {
            vl = vl->right;
        }
    }

    //Follow path from splitNode to end and report left subtrees
    Node* vr = splitNode->right;
    while (vr != nullptr) {

        //Report node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start) && isLessOrEqual(vr->key, end)) {
            out.push_back(vr);
        }

        //Report right child if it is contained in the range
        if (isGreaterOrEqual(end, vr->key)) {
            reportSubTreeHelper(vr->left, out);
            vr = vr->right;
        }
        //Go to left child
        else {
            vr = vr->left;
        }
    }

}

/**
 * @brief Find split node of the BST for a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @return Split node of the BST. Returns nullptr if the tree is empty
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::findSplitNodeHelper(const K& start, const K& end) {
    if (this->root == nullptr)
        return nullptr;

    Node* v = this->root;
    //Follow path until a leaf is found
    while (v != nullptr) {
        //If both path follow left subtree
        if (isLess(start, v->key) && isLess(end, v->key)) {
            v = v->left;
        }
        //If both path follow right subtree
        else if (isGreater(start, v->key) && isGreater(end, v->key)) {
            v = v->right;
        }
        else {
            return v;
        }
    }

    return v;
}

/**
 * @brief Add to the output vector the entire subtree
 *
 * @param[in] node Root of the subtree
 * @param[out] out Vector of output nodes
 */
template <class K, class T>
void AVLInner<K,T>::reportSubTreeHelper(Node* node, std::vector<Node*>& out) {
    if (node == nullptr)
        return;

    out.push_back(node);

    reportSubTreeHelper(node->left, out);
    reportSubTreeHelper(node->right, out);
}


/* --------- AVL HELPERS --------- */

/**
 * @brief Update heights climbing on the parents
 *
 * @param[in] node Starting node
 */
template <class K, class T>
void AVLInner<K,T>::updateHeightHelper(Node* node) {
    if (node != nullptr) {
        bool done;
        do {
            //Update height
            node->height = 1 + std::max(getHeightHelper(node->left),
                                        getHeightHelper(node->right));

            //Done flag
            done = (node->parent == nullptr || node->height+1 == node->parent->height);

            //Next parent
            node = node->parent;
        } while (!done);
    }
}

/**
 * @brief Rebalance with rotations
 *
 * @param[in] node Starting node
 */
template <class K, class T>
void AVLInner<K,T>::rebalanceHelper(Node* node) {
    //Null handler
    if (node == nullptr)
        return;

    //Not balanced node
    Node* n = node;
    int balanceFactor = getHeightHelper(n->right) - getHeightHelper(n->left);

    //Climb on parents to find the not balanced node
    while (n != nullptr && balanceFactor >= -1 && balanceFactor <= 1) {
        n = n->parent;

        if (n != nullptr) {
            //Compute balance factor
            balanceFactor = getHeightHelper(n->right) - getHeightHelper(n->left);

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
                n = rightRotate(n);
            }
            //Left right case
            else {
                n->left = leftRotate(n->left);
                n = rightRotate(n);
            }
        }
        else if (balanceFactor > 1) {
            Node* rightright = n->right->right;
            Node* rightleft = n->right->left;

            //Right right case
            if (getHeightHelper(rightright) >= getHeightHelper(rightleft)) {
                n = leftRotate(n);
            }
            //Left right case
            else {
                n->right = rightRotate(n->right);
                n = leftRotate(n);
            }
        }


        //Set root
        if (n->parent == nullptr) {
            this->root = n;
        }

        //Update heights
        updateHeightHelper(n);
        //Rebalance parent
        rebalanceHelper(n->parent);
    }
}


/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::leftRotate(Node* a) {
    Node *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != nullptr)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    //Update heights
    updateHeightHelper(a);

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <class K, class T>
typename AVLInner<K,T>::Node* AVLInner<K,T>::rightRotate(Node* a) {
    Node* b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != nullptr)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    //Update heights
    updateHeightHelper(a);

    return b;
}



}
