/**
    @author Stefano Nuvoli
*/
#include "aabbtree.h"

#include "assert.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTORS --------- */



/**
 * @brief Default constructor
 *
 * @param[in] customComparator Custom comparator to be used to compare if a key
 * is less than another one. The default comparator is the < operator
 */
template <int D, class K, class T>
AABBTree<D,K,T>::AABBTree(const AABBValueExtractor customAABBValueExtractor,
                          const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    lessComparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
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
template <int D, class K, class T>
AABBTree<D,K,T>::AABBTree(const std::vector<std::pair<K,T>>& vec,
                          const AABBValueExtractor customAABBValueExtractor,
                          const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    lessComparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
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
template <int D, class K, class T>
AABBTree<D,K,T>::AABBTree(const std::vector<K>& vec,
                          const AABBValueExtractor customAABBValueExtractor,
                          const LessComparator customComparator) :
    endIterator(Iterator(nullptr)),
    lessComparator(customComparator),
    aabbValueExtractor(customAABBValueExtractor)
{
    this->initHelper();
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
 * @brief Construction of the BST given the initial values (pair of
 * keys/values)
 *
 * A clear operation is performed before the construction
 *
 * @param[in] vec Vector of pairs of keys/values
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::construction(const std::vector<std::pair<K,T>>& vec) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::insert(const K& key) {
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
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::insert(
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
template <int D, class K, class T>
void AABBTree<D,K,T>::erase(Iterator it) {
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
template <int D, class K, class T>
bool AABBTree<D,K,T>::erase(const K& key) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::find(const K& key) {
    Node* node = this->findNodeHelper(key);
    return Iterator(node);
}



/**
 * @brief Get minimum key entry in the BST
 *
 * @return The iterator pointing to the minimum node
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::getMin() {
    return Iterator(getMinimumHelper(this->root));
}

/**
 * @brief Get maximum key entry in the BST
 *
 * @return The iterator pointing to the maximum node
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::getMax() {
    return Iterator(getMaximumHelper(this->root));
}




/**
 * @brief Clear the tree, delete all its elements
 *
 * Recursive implementation
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::clear() {
    this->clearHelper(this->root);
}




/**
 * @brief Get the number of entries in the BST
 *
 * @return Number of entries
 */
template <int D, class K, class T>
size_t AABBTree<D,K,T>::size() {
    return this->entries;
}

/**
 * @brief Check if tree in empty
 *
 * @return True if the BST is empty
 */
template <int D, class K, class T>
bool AABBTree<D,K,T>::empty()
{
    return (this->size() == 0) && (this->root == nullptr);
}



/**
 * @brief Get max height of the tree
 *
 * @return Max height of the tree
 */
template <int D, class K, class T>
size_t AABBTree<D,K,T>::getHeight()
{
    return getHeightHelper(this->root);
}


/**
 * @brief Find elements for which the input bounding box overlaps with the one of the values
 *
 * @param[in] key Input key
 * @param[out] out Vector of iterators pointing to elements that overlap
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::aabbOverlapQuery(
        const K& key,
        std::vector<Iterator> &out,
        KeyOverlapChecker keyOverlapChecker)
{
    AABB aabb;
    setAABBFromKey(key, aabb);
    std::vector<Node*> nodeOutput;
    this->aabbOverlapQueryHelper(this->root, key, aabb, nodeOutput, keyOverlapChecker);
    for (Node* node : nodeOutput) {
        out.push_back(Iterator(node));
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
    AABB aabb;
    setAABBFromKey(key, aabb);
    return this->aabbOverlapCheckHelper(this->root, key, aabb, keyOverlapChecker);
}



/* --------- ITERATORS --------- */

/**
 * @brief Begin iterator
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::Iterator AABBTree<D,K,T>::begin() {
    return Iterator(this->getMin());
}

/**
 * @brief End iterator
 */
template <int D, class K, class T>
const typename AABBTree<D,K,T>::Iterator& AABBTree<D,K,T>::end() {
    return this->endIterator;
}




/* --------- HELPERS --------- */

/**
 * @brief Initialization of the BST
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::initHelper()
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
template <int D, class K, class T>
void AABBTree<D,K,T>::constructionBottomUpHelper(const std::vector<std::pair<K,T>>& sortedVec) {
    std::vector<Node*>* nodes = new std::vector<Node*>();
    std::vector<Node*> leaves;

    //Create leaves
    K lastValue;
    for (size_t i = 0; i < sortedVec.size(); i ++) {
        const std::pair<K,T>& pair = sortedVec.at(i);

        //Avoid duplicates
        if (i == 0 || !isEqual(lastValue, pair.first)) {
            Node* newNode = new Node(pair.first, pair.second);
            nodes->push_back(newNode);
            leaves.push_back(newNode);

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

    for (Node* leaf : leaves) {
        //Update AABBs
        updateAABBsHelper(leaf);
    }
}


/**
 * @brief Insert a node in the BST
 *
 * @param[in] node Node to be inserted
 * @return True if the node has been inserted
 */
template <int D, class K, class T>
bool AABBTree<D,K,T>::insertNodeHelper(Node*& newNode) {
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

    //Update AABBs
    updateAABBsHelper(node);
    //Update AABBs
    updateAABBsHelper(newNode);

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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::findNodeHelper(const K& key) const {
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
template <int D, class K, class T>
void AABBTree<D,K,T>::eraseNodeHelper(Node*& node)
{
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

        //Update AABBs
        updateAABBsHelper(replacingChild);
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::getSuccessorHelper(Node* node) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::getPredecessorHelper(Node* node) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::getMinimumHelper(Node* rootNode) {
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
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::getMaximumHelper(Node* rootNode) {
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
template <int D, class K, class T>
void AABBTree<D,K,T>::clearHelper(Node*& rootNode) {
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
template <int D, class K, class T>
void AABBTree<D,K,T>::replaceSubtreeHelper(const Node* u, Node* v) {
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
template <int D, class K, class T>
size_t AABBTree<D,K,T>::getHeightHelper(const Node* node)
{
    if (node == nullptr)
        return 0;

    return node->height;
}


/* --------- AVL HELPERS --------- */

/**
 * @brief Update heights climbing on the parents
 *
 * @param[in] node Starting node
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::updateHeightHelper(Node* node) {
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
template <int D, class K, class T>
void AABBTree<D,K,T>::rebalanceHelper(Node* node) {
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

        //Update AABBs
        updateAABBsHelper(n);

    }
}


/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::leftRotate(Node* a) {
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

    //Update AABBs
    updateAABBsHelper(a);

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 */
template <int D, class K, class T>
typename AABBTree<D,K,T>::Node* AABBTree<D,K,T>::rightRotate(Node* a) {
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

    //Update AABBs
    updateAABBsHelper(a);

    return b;
}



/* --------- AABB HELPERS --------- */


/**
 * @brief Update AABBs climbing on the parents
 *
 * @param[in] node Starting node
 */
template <int D, class K, class T>
void AABBTree<D,K,T>::updateAABBsHelper(Node* node) {
    if (node != nullptr) {
        bool done;
        do {
            done = false;

            //Set AABB for the key
            if (node->isLeaf()) {
                setAABBFromKey(node->key, node->aabb);
            }
            //Set maximum AABB of the subtree
            else {
                AABB& leftChildAABB = node->left->aabb;
                AABB& rightChildAABB = node->right->aabb;

                done = true;

                for (int i = 1; i <= D; i++) {
                    double minValue = std::min(leftChildAABB.getMin(i), rightChildAABB.getMin(i));
                    double maxValue = std::max(leftChildAABB.getMax(i), rightChildAABB.getMax(i));

                    if (node->aabb.getMin(i) != minValue || node->aabb.getMax(i) != maxValue) {
                        done = false;
                    }

                    node->aabb.setMin(i, minValue);
                    node->aabb.setMax(i, maxValue);
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
template <int D, class K, class T>
void AABBTree<D,K,T>::aabbOverlapQueryHelper(
        Node* node,
        const K& key,
        const AABB& aabb,
        std::vector<Node*> &out,
        KeyOverlapChecker keyOverlapChecker)
{
    if (node == nullptr)
        return;

    //If node is a leaf, then return the node if its bounding box is overlapping
    if (node->isLeaf()) {
        if (aabbOverlaps(aabb, node->aabb)) {
            if (keyOverlapChecker == nullptr || keyOverlapChecker(key, node->key)) {
                out.push_back(node);
            }
        }
    }
    //If node is not a leaf, search on left and right subtrees if the AABB overlaps
    else {
        if (node->right != nullptr && aabbOverlaps(aabb, node->right->aabb)) {
            aabbOverlapQueryHelper(node->right, key, aabb, out, keyOverlapChecker);
        }

        if (node->left != nullptr && aabbOverlaps(aabb, node->left->aabb)) {
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
template <int D, class K, class T>
bool AABBTree<D,K,T>::aabbOverlapCheckHelper(
        Node* node,
        const K& key,
        const AABB& aabb,
        KeyOverlapChecker keyOverlapChecker)
{
    if (node == nullptr)
        return false;

    //If node is a leaf, then return the node if its bounding box is overlapping
    if (node->isLeaf()) {
        if (aabbOverlaps(aabb, node->aabb)) {
            if (keyOverlapChecker == nullptr || keyOverlapChecker(key, node->key)) {
                return true;
            }
        }
    }
    //If node is not a leaf, search on left and right subtrees if the AABB overlaps
    else {
        if (node->right != nullptr && aabbOverlaps(aabb, node->right->aabb)) {
            if (aabbOverlapCheckHelper(node->right, key, aabb, keyOverlapChecker))
                return true;
        }

        if (node->left != nullptr && aabbOverlaps(aabb, node->left->aabb)) {
            if (aabbOverlapCheckHelper(node->left, key, aabb, keyOverlapChecker))
                return true;
        }
    }
    return false;
}


}
