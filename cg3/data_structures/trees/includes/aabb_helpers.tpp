/**
    @author Stefano Nuvoli
*/
#include "aabb_helpers.h"

#include "avl_helpers.h"

#include "assert.h"

namespace cg3 {



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
template <int D, class K, class Node>
inline void aabbOverlapQueryHelper(
        Node* node,
        const K& key,
        const AABB<D>& aabb,
        std::vector<Node*> &out,
        KeyOverlapCheckerType<K> keyOverlapChecker)
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
template <int D, class K, class Node>
inline bool aabbOverlapCheckHelper(
        Node* node,
        const K& key,
        const AABB<D>& aabb,
        KeyOverlapCheckerType<K> keyOverlapChecker)
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
template <int D, class K, class Node>
inline void updateAABBHelper(
        Node* node,
        AABBValueExtractorType<K> aabbValueExtractor)
{
    if (node != nullptr) {
        bool done;
        do {
            done = false;

            //Set AABB for the key
            if (node->isLeaf()) {
                setAABBFromKeyHelper(node->key, node->aabb, aabbValueExtractor);
            }
            //Set maximum AABB of the subtree
            else {
                AABB<D>& leftChildAABB = node->left->aabb;
                AABB<D>& rightChildAABB = node->right->aabb;

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



/* ----- AVL HELPERS FOR AABB ----- */

/**
 * @brief Rebalance with left/right rotations to make the
 * AABBTree satisfy the AVL constraints
 *
 * @param[in] node Starting node
 * @param[in] node Root node of the BST
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class Node>
inline void rebalanceAABBHelper(
        Node* node,
        Node*& rootNode,
        AABBValueExtractorType<K> aabbValueExtractor)
{
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
                n = rightRotateAABBHelper<D>(n, aabbValueExtractor);
            }
            //Left right case
            else {
                n->left = leftRotateAABBHelper<D>(n->left, aabbValueExtractor);
                n = rightRotateAABBHelper<D>(n, aabbValueExtractor);
            }
        }
        else if (balanceFactor > 1) {
            Node* rightright = n->right->right;
            Node* rightleft = n->right->left;

            //Right right case
            if (getHeightHelper(rightright) >= getHeightHelper(rightleft)) {
                n = leftRotateAABBHelper<D>(n, aabbValueExtractor);
            }
            //Left right case
            else {
                n->right = rightRotateAABBHelper<D>(n->right, aabbValueExtractor);
                n = leftRotateAABBHelper<D>(n, aabbValueExtractor);
            }
        }


        //Set root
        if (n->parent == nullptr) {
            rootNode = n;
        }

        //Update heights on parents and rebalance them if needed
        updateHeightAndRebalanceAABBHelper<D>(n->parent, rootNode, aabbValueExtractor);

        //Update AABBs
        updateAABBHelper<D>(n, aabbValueExtractor);
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
template <int D, class K, class Node>
inline void updateHeightAndRebalanceAABBHelper(
        Node* node,
        Node*& rootNode,
        AABBValueExtractorType<K> aabbValueExtractor)
{
    updateHeightHelper(node);
    rebalanceAABBHelper<D>(node, rootNode, aabbValueExtractor);
}



/**
 * @brief Left rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class Node>
inline Node* leftRotateAABBHelper(
        Node* a,
        AABBValueExtractorType<K> aabbValueExtractor)
{
    //Rotate left
    Node* b = leftRotateHelper(a);

    //Update AABBs
    updateAABBHelper<D>(a, aabbValueExtractor);

    return b;
}

/**
 * @brief Right rotation
 *
 * @param[in] a Node to be rotated
 * @return New node in the position of the original node after the rotation
 * @param[in] aabbValueExtractor AABB extractor for key
 */
template <int D, class K, class Node>
inline Node* rightRotateAABBHelper(
        Node* a,
        AABBValueExtractorType<K> aabbValueExtractor)
{
    //Rotate right
    Node* b = rightRotateHelper(a);

    //Update AABBs
    updateAABBHelper<D>(a, aabbValueExtractor);

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
template <int D>
inline bool aabbOverlapsHelper(
        const AABB<D>& a,
        const AABB<D>& b)
{
    for (int i = 1; i <= D; i++) {
        if (!(a.getMin(i) <= b.getMax(i) && a.getMax(i) >= b.getMin(i)))
            return false;
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
template <int D, class K>
inline void setAABBFromKeyHelper(
        const K& k,
        AABB<D>& aabb,
        AABBValueExtractorType<K> aabbValueExtractor)
{
    for (int i = 1; i <= D; i++) {
        aabb.setMin(i, aabbValueExtractor(k, MIN, i));
        aabb.setMax(i, aabbValueExtractor(k, MAX, i));
    }
}


}
