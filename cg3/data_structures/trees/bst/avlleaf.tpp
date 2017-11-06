/**
    @author Stefano Nuvoli
*/
#include "avlleaf.h"

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
AVLLeaf<K,T>::AVLLeaf(const LessComparator customComparator) :
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
AVLLeaf<K,T>::AVLLeaf(const std::vector<std::pair<K,T>>& vec,
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
AVLLeaf<K,T>::AVLLeaf(const std::vector<K>& vec,
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
AVLLeaf<K,T>::~AVLLeaf() {
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
void AVLLeaf<K,T>::construction(const std::vector<K>& vec) {
    std::vector<std::pair<K,T>> pairVec;

    for (const K& entry : vec) {
        pairVec.push_back(std::make_pair(entry, entry));
    }

    construction(pairVec);
}

/**
 * @brief Construction of the BST given the initial values (pair of
 * keys/values)
 *
 * A clear operation is performed before the construction
 *
 * @param[in] vec Vector of pairs of keys/values
 */
template <class K, class T>
void AVLLeaf<K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
    clear();

    if (vec.size() == 0)
        return;

    //Sort the collection
    std::vector<std::pair<K,T>> sortedVec(vec.begin(), vec.end());
    std::sort(sortedVec.begin(), sortedVec.end(), *this);

    //Calling the recursive helper
    this->constructionBottomUpHelper(sortedVec);
}




/**
 * @brief Insert in the BST a given value
 *
 * @param[in] key Key/value to be inserted
 * @return The iterator pointing to the node if it has been
 * successfully inserted, end iterator otherwise
 */
template <class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::insert(const K& key) {
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
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::insert(
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
void AVLLeaf<K,T>::erase(Iterator it) {
    //Save node to be deleted
    Node* node = it.getNode();

    this->eraseNodeHelper(node);
}

/**
 * @brief Erase value from BST given the key
 *
 * @param[in] key Key of the node
 * @return True if item has been found and then erased, false otherwise
 */
template <class K, class T>
bool AVLLeaf<K,T>::erase(const K& key) {
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
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::find(const K& key) {
    Node* node = this->findNodeHelper(key);
    return Iterator(node);
}




/**
 * @brief Get minimum key entry in the BST
 *
 * @return The iterator pointing to the minimum node
 */
template<class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::getMin() {
    return Iterator(getMinimumHelper(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template<class K, class T>
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::getMax() {
    return Iterator(getMaximumHelper(this->root));
}




/**
 * @brief Clear the tree, delete all its elements
 *
 * Recursive implementation
 */
template <class K, class T>
void AVLLeaf<K,T>::clear() {
    this->clearHelper(this->root);
}




/**
 * @brief Get the number of entries in the BST
 *
 * @return Number of entries
 */
template <class K, class T>
size_t AVLLeaf<K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty
 */
template <class K, class T>
bool AVLLeaf<K,T>::empty()
{
    return (this->size() == 0) && (this->root == nullptr);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <class K, class T>
size_t AVLLeaf<K,T>::getHeight()
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
void AVLLeaf<K,T>::rangeQuery(const K& start, const K& end,
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
typename AVLLeaf<K,T>::Iterator AVLLeaf<K,T>::begin() {
    return Iterator(this->getMin());
}

/**
 * @brief End iterator
 */
template <class K, class T>
const typename AVLLeaf<K,T>::Iterator& AVLLeaf<K,T>::end() {
    return this->endIterator;
}




/* --------- HELPERS --------- */

/**
 * @brief Initialization of the BST
 */
template <class K, class T>
void AVLLeaf<K,T>::initHelper()
{
    this->root = nullptr;
    this->entries = 0;
}

/**
 * Construction of the balanced BST given a vector of sorted elements
 *
 * Bottom up construction
 *
 * @param[in] sortedVec Sorted vector of entries (pair of keys/values)
 * @param[in] start Start index of the partition of the vector to be inserted
 * @param[in] end End index of the partition of the vector to be inserted
 */
template <class K, class T>
void AVLLeaf<K,T>::constructionBottomUpHelper(const std::vector<std::pair<K,T>>& sortedVec) {
    std::vector<Node*>* nodes = new std::vector<Node*>();

    //Create leaves
    K lastValue;
    for (size_t i = 0; i < sortedVec.size(); i ++) {
        const std::pair<K,T>& pair = sortedVec.at(i);

        //Avoid duplicates
        if (i == 0 || !isEqual(lastValue, pair.first)) {
            Node* newNode = new Node(pair.first, pair.second);
            nodes->push_back(newNode);

            this->entries++;

            lastValue = pair.first;
        }
    }



    //If there is not an only remaining node
    while (nodes->size() > 1) {
        //Nodes of the new level
        std::vector<Node*>* newLevelNodes = new std::vector<Node*>();

        for (size_t i = 0; i < nodes->size(); i += 2) {
            Node* node1 = nodes->at(i);
            Node* node2 = nullptr;

            //If a second node exists
            if (i+1 < nodes->size()) {
                node2 = nodes->at(i+1);
            }

            //If a second node exists
            if (node2 != nullptr) {
                K& key = this->getMinimumHelper(node2)->key;
                Node* parentNode = new Node(key);

                //Setting children conditions
                parentNode->left = node1;
                parentNode->right = node2;

                //Setting parent
                node1->parent = parentNode;
                node2->parent = parentNode;

                //Setting height
                parentNode->height = 1 + std::max(parentNode->left->height, parentNode->right->height);

                newLevelNodes->push_back(parentNode);
            }
            else {
                newLevelNodes->push_back(node1);
            }
        }


        //Delete vector of nodes
        delete nodes;
        nodes = nullptr;

        //Replacing the nodes with the node of the new level
        nodes = newLevelNodes;
        newLevelNodes = nullptr;
    }

    this->root = nodes->at(0);
    this->root->parent = nullptr;

    //Delete vector of nodes
    delete nodes;
    nodes = nullptr;
}


/**
 * @brief Insert a node in the BST
 *
 * @param[in] node Node to be inserted
 * @return True if the node has been inserted
 */
template <class K, class T>
bool AVLLeaf<K,T>::insertNodeHelper(Node*& newNode) {
    //If the tree is empty
    if (this->root == nullptr) {
        //Insert the node as the root
        this->root = newNode;
        newNode->parent = nullptr;

        //Increment entry number
        this->entries++;

        return true;
    }

    //Find the position in the BST in which
    //the new node must be inserted
    Node* node = this->root;

    //Travel in the BST until the node is a leaf
    while (!node->isLeaf()) {
        if (isLess(newNode->key, node->key)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    //If the value is already in the BST    
    if (isEqual(node->key, newNode->key)) {
        delete newNode;
        newNode = nullptr;

        return false;
    }

    //If the key is not in the BST, perform insert
    Node* newParent;

    if (isLess(newNode->key, node->key)) {
        //Create new parent for the two nodes
        newParent = new Node(node->key);

        //Set the children
        newParent->left = newNode;
        newParent->right = node;

        //Replace the node with the new parent
        replaceSubtreeHelper(node, newParent);
    }
    else {
        //Create new parent for the two nodes
        newParent = new Node(newNode->key);

        //Set the children
        newParent->left = node;
        newParent->right = newNode;

        //Replace the node with the new parent
        replaceSubtreeHelper(node, newParent);
    }

    //Update the parents for the two nodes
    newNode->parent = newParent;
    node->parent = newParent;

    //Update heights and rebalance
    updateHeightHelper(newParent);
    rebalanceHelper(newParent);


    //Increment entry number
    this->entries++;

    return true;
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
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::findNodeHelper(const K& key) const {
    if (this->root == nullptr)
        return nullptr;

    Node* node = this->root;

    //Travel in the BST until a leaf is found
    while (!node->isLeaf()) {
        if (isLess(key, node->key)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    //If node has the input key, then the node is found
    if (isEqual(node->key, key)) {
        return node;
    }

    return nullptr;
}


/**
 * @brief Erase node from BST
 *
 * @param[in] node Node to be erased
 */
template <class K, class T>
void AVLLeaf<K,T>::eraseNodeHelper(Node*& node) {
    //If the node is the root node of the BST
    if (this->root == node) {
        this->root = nullptr;
    }
    //If the node is not the root
    else {
        Node* parent = node->parent;
        Node* replacingChild = nullptr;

        //If node is a left child
        if (parent->left == node) {
            //Replace the parent with his right child
            replacingChild = parent->right;
            parent->left = nullptr;
        }
        //If node is a right child
        else {
            //Replace the parent with his left child
            replacingChild = parent->left;
            parent->right = nullptr;
        }

        //Replace parent with the child
        replaceSubtreeHelper(parent, replacingChild);

        //Update heights and rebalance
        updateHeightHelper(replacingChild);
        rebalanceHelper(replacingChild);
    }

    //Delete the node
    delete node;
    node = nullptr;

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
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::getSuccessorHelper(Node* node) {
    Node* x = node;

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }

    //If it has a right child, get the minimum node of subtree
    //rooted in the right child
    if (y != nullptr && y->right != nullptr)
        return getMinimumHelper(y->right);

    return y;
}


/**
 * @brief Get predecessor of a node
 *
 * @param[in] node Input node
 * @return Predecessor of the node, nullptr if there is no predecessor
 */
template <class K, class T>
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::getPredecessorHelper(Node* node) {
    Node* x = node;

    //Climb on parents
    Node* y = x->parent;
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }

    // If it has a left child, get the maximum node of subtree
    // rooted in the left child
    if (y->left != nullptr)
        return getMaximumHelper(y->left);

    return y;
}


/**
 * @brief Get minimum key node of the subtree
 *
 * @param[in] startingNode Root of the subtree
 * @return Minimum key node pointer
 */
template <class K, class T>
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::getMinimumHelper(Node* rootNode) {
    Node* x = rootNode;

    while (x != nullptr && !x->isLeaf())
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
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::getMaximumHelper(Node* rootNode) {
    Node* x = rootNode;

    while (x != nullptr && !x->isLeaf())
        x = x->right;

    return x;
}


/**
 * @brief Clear a given subtree
 *
 * @param[in] node Root of the subtree
 */
template <class K, class T>
void AVLLeaf<K,T>::clearHelper(Node*& rootNode) {
    //If it is already empty
    if (rootNode == nullptr)
        return;

    if (rootNode->isLeaf()) {
        //Decreasing entries
        this->entries--;
    }

    //Clear subtrees
    this->clearHelper(rootNode->left);
    this->clearHelper(rootNode->right);

    //Delete data
    delete rootNode;
    rootNode = nullptr;
}

/**
 * @brief Replace the subtree rooted at u with
 * the subtree rooted at v
 *
 * @param[in] u Root of the subtree to be replaced
 * @param[in] v Root of the subtree that replaces u
 */
template <class K, class T>
void AVLLeaf<K,T>::replaceSubtreeHelper(const Node* u, Node* v) {
    //If u is the root (no parent)
    if (u->parent == nullptr) {
        this->root = v;
    }

    //If u is the left child of the parent
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    //If u is the right child of the parent
    else {
        u->parent->right = v;
    }

    //If v is not null
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

/**
 * @brief Get max height of the subtree rooted in a node
 *
 * @param[in] node Root node
 * @return Max height of the subtree
 */
template <class K, class T>
size_t AVLLeaf<K,T>::getHeightHelper(const Node* node) {
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
void AVLLeaf<K,T>::rangeQueryHelper(const K& start, const K& end,
                                     std::vector<Node*> &out)
{
    //Find split node
    Node* splitNode = findSplitNodeHelper(start, end);
    if (splitNode == nullptr)
        return;

    //If the split node is a leaf
    if (splitNode->isLeaf()) {
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(splitNode->key, start) && isLessOrEqual(splitNode->key, end)) {
            reportSubTreeHelper(splitNode, out);
        }
    }
    //If the split node is not a leaf
    else {
        //Follow path from splitNode to start and report right subtrees
        Node* vl = splitNode->left;
        while (!vl->isLeaf()) {
            if (isLess(start, vl->key)) {
                reportSubTreeHelper(vl->right, out);
                vl = vl->left;
            }
            else {
                vl = vl->right;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vl->key, start) && isLessOrEqual(vl->key, end)) {
            reportSubTreeHelper(vl, out);
        }

        //Follow path from splitNode to end and report left subtrees
        Node* vr = splitNode->right;
        while (!vr->isLeaf()) {
            if (isGreaterOrEqual(end, vr->key)) {
                reportSubTreeHelper(vr->left, out);
                vr = vr->right;
            }
            else {
                vr = vr->left;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start) && isLessOrEqual(vr->key, end)) {
            reportSubTreeHelper(vr, out);
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
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::findSplitNodeHelper(const K& start, const K& end) {
    if (this->root == nullptr)
        return nullptr;

    Node* v = this->root;
    //Follow path until a leaf is found
    while (!v->isLeaf()) {
        //If both path follow left subtree
        if (isLess(start, v->key) && isLess(end, v->key)) {
            v = v->left;
        }
        //If both path follow right subtree
        else if (isGreaterOrEqual(start, v->key) && isGreaterOrEqual(end, v->key)) {
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
void AVLLeaf<K,T>::reportSubTreeHelper(Node* node, std::vector<Node*>& out) {
    if (node->isLeaf()) {
        out.push_back(node);
    }
    else {
        reportSubTreeHelper(node->left, out);
        reportSubTreeHelper(node->right, out);
    }
}


/* --------- AVL HELPERS --------- */

/**
 * @brief Update heights climbing on the parents
 *
 * @param[in] node Starting node
 */
template <class K, class T>
void AVLLeaf<K,T>::updateHeightHelper(Node* node) {
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
void AVLLeaf<K,T>::rebalanceHelper(Node* node) {
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
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::leftRotate(Node* a) {
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
typename AVLLeaf<K,T>::Node* AVLLeaf<K,T>::rightRotate(Node* a) {
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
