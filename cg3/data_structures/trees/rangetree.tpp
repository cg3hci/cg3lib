/**
    @author Stefano Nuvoli
*/
#include "rangetree.h"

#include "assert.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */



/**
 * @brief Default constructor
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] customDimensionComparator Custom comparator for different dimensions
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
RangeTree<K,T>::RangeTree(unsigned int dimension,
                          const LessDimensionComparator customDimensionComparator,
                          const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    dim(dimension),
    lessDimensionComparator(customDimensionComparator),
    lessComparator(customComparator)
{
    this->initHelper();
}

/**
 * @brief Constructor with a vector of entries (key/value pairs) to be inserted
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] vec Vector of pairs of keys/values
 * @param[in] customDimensionComparator Custom comparator for different dimensions
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
RangeTree<K,T>::RangeTree(unsigned int dimension,
                          const std::vector<std::pair<K,T>>& vec,
                          const LessDimensionComparator customDimensionComparator,
                          const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    dim(dimension),
    lessDimensionComparator(customDimensionComparator),
    lessComparator(customComparator)
{
    this->initHelper();
    this->construction(vec);
}


/**
 * @brief Constructor with a vector of values to be inserted
 *
 * @param[in] dimension Dimension of the range tree
 * @param[in] vec Vector of values
 * @param[in] customDimensionComparator Custom comparator for different dimensions
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <class K, class T>
RangeTree<K,T>::RangeTree(unsigned int dimension,
                          const std::vector<K>& vec,
                          const LessDimensionComparator customDimensionComparator,
                          const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    dim(dimension),
    lessDimensionComparator(customDimensionComparator),
    lessComparator(customComparator)
{
    this->initHelper();
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
 * @brief Construction of the range tree given the initial values
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
 * @brief Construction of the range tree given the initial values
 * (pairs of keys/values)
 *
 * A clear operation is performed before the construction
 *
 * @param[in] vec Vector of pairs of keys/values
 */
template <class K, class T>
void RangeTree<K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
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
 * @brief Insert in the range tree a given value
 *
 * @param[in] key Key/value to be inserted
 * @return True if item has been inserted
 */
template <class K, class T>
bool RangeTree<K, T>::insert(const K& key) {
    return insert(key, key);
}

/**
 * @brief Insert in the range tree a given value with the given key
 *
 * If an entry with the same key is already contained, the new
 * entry will be not inserted
 *
 * @param[in] key Key of the entry
 * @param[in] value Value of the entry
 * @return True if item has been inserted
 */
template <class K, class T>
bool RangeTree<K, T>::insert(
        const K& key, const T& value)
{
    //Create new node
    Node* newNode = new Node(key, value);

    return this->insertNodeHelper(newNode);
}






/**
 * @brief Erase value from range tree given the key
 *
 * @param[in] key Key of the node
 * @return True if item has been found and then erased, false otherwise
 */
template <class K, class T>
bool RangeTree<K,T>::erase(const K& key) {
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
 * @brief Find entries in the range tree that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of iterators pointing to the elements in the deepest
 * associated range tree enclosed in the input range
 */
template <class K, class T>
void RangeTree<K,T>::rangeQuery(const K& start, const K& end,
                                std::vector<Iterator> &out)
{
    std::vector<Node*> nodeOutput;
    this->rangeQueryHelper(start, end, nodeOutput);
    for (Node* node : nodeOutput) {
        out.push_back(Iterator(node));
    }
}


/**
 * @brief Find entry in the range tree given the key
 *
 * @param[in] key Key of the node to be found
 * @return The iterator pointing to the deepest associated range tree node if
 * the element is contained in the range tree, end iterator otherwise
 */
template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::find(const K& key) {
    //If the range tree is not for the first dimension, go to next dimension
    if (dim > 1)
        return this->root->assRangeTree->find(key);

    Node* node = this->findNodeHelper(key);
    return Iterator(node);
}




/**
 * @brief Get minimum key entry in the range tree
 *
 * @return The iterator pointing to the minimum node in the
 * deepest associated range tree
 */
template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::getMin() {
    //If the range tree is not for the first dimension, go to next dimension
    if (dim > 1)
        return this->root->assRangeTree->getMin();

    return Iterator(getMinimumHelper(this->root));
}

/**
 * @brief Get maximum key entry in the range tree
 *
 * @return The iterator pointing to the maximum node in the
 * deepest associated range tree
 */
template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::getMax() {
    //If the range tree is not for the first dimension, go to next dimension
    if (dim > 1)
        return this->root->assRangeTree->getMax();

    return Iterator(getMaximumHelper(this->root));
}




/**
 * @brief Clear the tree, delete all its elements
 *
 * Recursive implementation
 */
template <class K, class T>
void RangeTree<K,T>::clear() {
    this->clearHelper(this->root);
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
    return (this->size() == 0) && (this->root == nullptr);
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



/* --------- ITERATORS --------- */

/**
 * @brief Begin iterator
 */
template <class K, class T>
typename RangeTree<K,T>::Iterator RangeTree<K,T>::begin() {
    return Iterator(this->getMin());
}

/**
 * @brief End iterator
 */
template <class K, class T>
const typename RangeTree<K,T>::Iterator& RangeTree<K,T>::end() {
    return this->endIterator;
}




/* --------- HELPERS --------- */


/**
 * @brief Initialization of the range tree
 */
template <class K, class T>
void RangeTree<K,T>::initHelper()
{
    this->root = nullptr;
    this->entries = 0;
}


/**
 * Construction of the balanced range tree given a vector of sorted elements
 *
 * Bottom up construction
 *
 * @param[in] sortedVec Sorted vector of entries (pair of keys/values)
 * @param[in] start Start index of the partition of the vector to be inserted
 * @param[in] end End index of the partition of the vector to be inserted
 */
template <class K, class T>
void RangeTree<K,T>::constructionBottomUpHelper(const std::vector<std::pair<K,T>>& sortedVec) {
    std::vector<Node*>* nodes = new std::vector<Node*>();
    std::vector<Node*> leafNodes;

    //Create leaves
    K lastValue;
    for (size_t i = 0; i < sortedVec.size(); i ++) {
        const std::pair<K,T>& pair = sortedVec.at(i);

        //Avoid duplicates
        if (i == 0 || !isEqual(lastValue, pair.first)) {
            Node* newNode = new Node(pair.first, pair.second);

            nodes->push_back(newNode);
            leafNodes.push_back(newNode);

            //Creating associated tree
            createAssociatedTreeHelper(newNode);

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

                //Creating associated tree
                createAssociatedTreeHelper(parentNode);

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

    //Creating associated tree for root
    createAssociatedTreeHelper(this->root);

    //Delete vector of nodes
    delete nodes;
    nodes = nullptr;

    for (Node* leafNode : leafNodes) {
        //Insert new node into associated range trees of the node and the parents
        insertIntoParentAssociatedTreesHelper(leafNode, leafNode->key, *(leafNode->value));
    }
    leafNodes.clear();

    assert(this->dim < 2 || this->root->assRangeTree->entries == this->entries);

}


/**
 * @brief Insert a node in the range tree
 *
 * @param[in] node Node to be inserted
 * @return True if the node has been inserted
 */
template <class K, class T>
bool RangeTree<K,T>::insertNodeHelper(
        typename RangeTree<K,T>::Node*& newNode)
{
    //If the tree is empty
    if (this->root == nullptr) {
        //Insert the node as the root
        this->root = newNode;
        newNode->parent = nullptr;

        //Create associated tree
        createAssociatedTreeHelper(newNode);
        //Insert new node into associated range trees of the node and the parents
        insertIntoParentAssociatedTreesHelper(newNode, newNode->key, *(newNode->value));

        //Increment entry number
        this->entries++;

        return true;
    }

    //Find the position in the range tree in which
    //the new node must be inserted
    Node* node = this->root;

    //Travel in the range tree until the node is a leaf
    while (!node->isLeaf()) {
        if (isLess(newNode->key, node->key)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    //If the value is already in the range tree
    if (isEqual(node->key, newNode->key)) {
        delete newNode;
        newNode = nullptr;

        return false;
    }

    //If the key is not in the range tree, perform insert
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



    //Create associated tree for the parent
    createAssociatedTreeHelper(newParent);
    //Insert the last node into parent associated tree
    insertIntoAssociatedTreeHelper(newParent, node->key, *(node->value));

    //Create associated tree for the node
    createAssociatedTreeHelper(newNode);
    //Insert new node into associated range trees of the node and the parents
    insertIntoParentAssociatedTreesHelper(newNode, newNode->key, *(newNode->value));



    //Update heights and rebalance
    updateHeightHelper(node);
    rebalanceHelper(node);


    //Increment entry number
    this->entries++;

    return true;
}


/**
 * @brief Find an entry on the range tree given a key
 *
 * @param[in] key Key of the node to be found
 *
 * @return If the node with a given value is found, then its pointer
 * is returned. Otherwise a null pointer is returned.
 *
 */
template <class K, class T>
typename RangeTree<K,T>::Node* RangeTree<K,T>::findNodeHelper(
        const K& key) const
{
    if (this->root == nullptr)
        return nullptr;

    Node* node = this->root;

    //Travel in the range tree until a leaf is found
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
 * @brief Erase node from range tree
 *
 * @param[in] node Node to be erased
 */
template <class K, class T>
void RangeTree<K,T>::eraseNodeHelper(Node*& node)
{
    //If the node is the root node of the range tree
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


        //Update associated trees
        eraseFromParentAssociatedTreesHelper(parent, node->key);



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
typename RangeTree<K,T>::Node* RangeTree<K,T>::getSuccessorHelper(
        Node* node)
{
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
typename RangeTree<K,T>::Node* RangeTree<K,T>::getPredecessorHelper(
        RangeTree<K,T>::Node* node)
{
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
typename RangeTree<K,T>::Node* RangeTree<K,T>::getMinimumHelper(
        RangeTree<K,T>::Node* rootNode)
{
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
typename RangeTree<K,T>::Node* RangeTree<K,T>::getMaximumHelper(
        RangeTree<K,T>::Node* rootNode)
{
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
void RangeTree<K,T>::clearHelper(Node*& rootNode) {
    //If it is already empty
    if (rootNode == nullptr)
        return;

    //Getting referencies
    Node*& left = rootNode->left;
    Node*& right = rootNode->right;

    if (rootNode->isLeaf()) {
        //Decreasing entries
        this->entries--;
    }

    //Delete data
    delete rootNode;
    rootNode = nullptr;

    //Clear subtrees
    this->clearHelper(left);
    this->clearHelper(right);
}

/**
 * @brief Replace the subtree rooted at u with
 * the subtree rooted at v
 *
 * @param[in] u Root of the subtree to be replaced
 * @param[in] v Root of the subtree that replaces u
 */
template <class K, class T>
void RangeTree<K,T>::replaceSubtreeHelper(
        const RangeTree<K,T>::Node* u,
        RangeTree<K,T>::Node* v)
{
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
size_t RangeTree<K,T>::getHeightHelper(const Node* node)
{
    if (node == nullptr)
        return 0;

    return node->height;
}




/* --------- RANGE QUERY HELPERS --------- */

/**
 * @brief Find entries in the range tree that are enclosed in a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of node with keys that are enclosed in the input range
 */
template <class K, class T>
void RangeTree<K,T>::rangeQueryHelper(const K& start, const K& end,
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
            rangeSearchInNextDimensionHelper(splitNode, start, end, out);
        }
    }
    //If the split node is not a leaf
    else {
        //Follow path from splitNode to start and report right subtrees
        Node* vl = splitNode->left;
        while (!vl->isLeaf()) {
            if (isLess(start, vl->key)) {
                rangeSearchInNextDimensionHelper(vl->right, start, end, out);
                vl = vl->left;
            }
            else {
                vl = vl->right;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vl->key, start) && isLessOrEqual(vl->key, end)) {
            rangeSearchInNextDimensionHelper(vl, start, end, out);
        }

        //Follow path from splitNode to end and report left subtrees
        Node* vr = splitNode->right;
        while (!vr->isLeaf()) {
            if (isGreaterOrEqual(end, vr->key)) {
                rangeSearchInNextDimensionHelper(vr->left, start, end, out);
                vr = vr->right;
            }
            else {
                vr = vr->left;
            }
        }
        //Report the node if it is contained in the range
        if (isGreaterOrEqual(vr->key, start) && isLessOrEqual(vr->key, end)) {
            rangeSearchInNextDimensionHelper(vr, start, end, out);
        }
    }

}

/**
 * @brief Find split node of the range tree for a given range
 *
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @return Split node of the range tree. Returns nullptr if the tree is empty
 */
template <class K, class T>
typename RangeTree<K,T>::Node* RangeTree<K,T>::findSplitNodeHelper(
        const K& start, const K& end)
{
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
void RangeTree<K,T>::reportSubtreeHelper(Node* node, std::vector<Node*>& out) {
    if (node->isLeaf()) {
        out.push_back(node);
    }
    else {
        reportSubtreeHelper(node->left, out);
        reportSubtreeHelper(node->right, out);
    }
}


/* --------- AVL HELPERS --------- */

/**
 * @brief Update heights climbing on the parents
 *
 * @param[in] node Starting node
 */
template <class K, class T>
void RangeTree<K,T>::updateHeightHelper(Node* node) {
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
void RangeTree<K,T>::rebalanceHelper(Node* node) {
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
typename RangeTree<K,T>::Node* RangeTree<K,T>::leftRotate(RangeTree<K,T>::Node* a) {
    Node* b = a->right;
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


    //Update associated trees
    if (dim > 1) {
        //Referencing subtrees
        Node* c = b->right;
        Node* aLeft = a->left;

        if (aLeft != nullptr) {
            //Insert aLeft into b associated tree
            for (Iterator aLeftIt = aLeft->assRangeTree->begin(); aLeftIt != aLeft->assRangeTree->end(); aLeftIt++) {
                Node* aLeftNode = aLeftIt.node;
                insertIntoAssociatedTreeHelper(b, aLeftNode->key, *(aLeftNode->value));
            }
        }
        //Erase c from a associated tree
        for (Iterator cIt = c->assRangeTree->begin(); cIt != c->assRangeTree->end(); cIt++) {
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
template <class K, class T>
typename RangeTree<K,T>::Node* RangeTree<K,T>::rightRotate(RangeTree<K,T>::Node* a) {
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


    //Update associated trees
    if (dim > 1) {
        //Referencing subtrees
        Node* c = b->left;
        Node* aRight = a->right;

        if (aRight != nullptr) {
            //Insert aRight into b associated tree
            for (Iterator aRightIt = aRight->assRangeTree->begin(); aRightIt != aRight->assRangeTree->end(); aRightIt++) {
                Node* aRightNode = aRightIt.node;
                insertIntoAssociatedTreeHelper(b, aRightNode->key, *(aRightNode->value));
            }
        }
        //Erase c from a associated tree
        for (Iterator cIt = c->assRangeTree->begin(); cIt != c->assRangeTree->end(); cIt++) {
            Node* cNode = cIt.node;
            eraseFromAssociatedTreeHelper(a, cNode->key);
        }
    }

    return b;
}






/* --------- MULTIDIMENSIONAL RANGE TREE HELPERS --------- */


/**
 * @brief Range search in next dimension or report the subtree
 *
 * @param[in] node Root of the subtree
 * @param[in] start Starting value of the range
 * @param[in] end End value of the range
 * @param[out] out Vector of output nodes
 */
template <class K, class T>
void RangeTree<K,T>::rangeSearchInNextDimensionHelper(Node* node, const K& start, const K& end, std::vector<Node*>& out) {
    if (dim > 1) {
        node->assRangeTree->rangeQueryHelper(start, end, out);
    }
    else {
        reportSubtreeHelper(node, out);
    }
}


/**
 * @brief Add to the output vector the entire subtree
 *
 * @param[in] node Node
 */
template <class K, class T>
void RangeTree<K,T>::createAssociatedTreeHelper(Node *node)
{
    if (dim > 1) {
        node->assRangeTree = new RangeTree<K,T>(dim-1, lessDimensionComparator, lessComparator);
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
template<class K, class T>
void RangeTree<K,T>::insertIntoAssociatedTreeHelper(Node* node, const K& key, const T& value)
{
    if (dim > 1) {
        //Insert into associated range tree
        node->assRangeTree->insert(key, value);
    }
}



/**
 * @brief Insert into associated range trees the current key and value
 * climbing on parents (the input node is included)
 *
 * @param[in] node Node from which the climbing starts
 * @param[in] key Key of new node
 * @param[in] value Value of new node
 */
template<class K, class T>
void RangeTree<K,T>::insertIntoParentAssociatedTreesHelper(Node* node, const K& key, const T& value)
{
    if (dim > 1) {
        while (node != nullptr) {
            //Insert into associated range tree
            insertIntoAssociatedTreeHelper(node, key, value);

            //Next parent
            node = node->parent;
        }
    }
}


/**
 * @brief Erase from associated range tree key/value of the node
 *
 * @param[in] node Node for which the node will be erase from its
 * associated range tree
 * @param[in] key Key of the node to be deleted
 */
template<class K, class T>
void RangeTree<K,T>::eraseFromAssociatedTreeHelper(Node* node, const K& key)
{
    if (dim > 1) {
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
template<class K, class T>
void RangeTree<K,T>::eraseFromParentAssociatedTreesHelper(Node* node, const K& key)
{
    if (dim > 1) {
        while (node != nullptr) {
            //Erase from associated range tree
            eraseFromAssociatedTreeHelper(node, key);

            //Next parent
            node = node->parent;
        }
    }
}



}
