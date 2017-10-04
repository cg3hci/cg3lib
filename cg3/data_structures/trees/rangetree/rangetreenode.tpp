/**
    @author Stefano Nuvoli
*/
#include "rangetreenode.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */


/**
 * @brief Constructor with key and value
 */
template <class K, class T>
RangeTree<K,T>::Node::Node(
        const K& key,
        const T& value)
{
    this->key = key;
    this->value = new T(value);

    this->left = nullptr;
    this->right = nullptr;

    this->height = 1;

    this->assRangeTree = nullptr;
}

/**
 * @brief Constructor with key and value
 */
template <class K, class T>
RangeTree<K,T>::Node::Node(
        const K& key)
{
    this->key = key;
    this->value = nullptr;

    this->left = nullptr;
    this->right = nullptr;

    this->height = 1;

    this->assRangeTree = nullptr;
}

/**
 * @brief Destructor
 */
template<class K, class T>
RangeTree<K, T>::Node::~Node()
{



    if (this->assRangeTree != nullptr)
        delete this->assRangeTree;
}


/* --------- METHODS --------- */

/**
 * @brief Check if the node is a leaf
 *
 * @return True if the node is a leaf
 */
template <class K, class T>
inline bool RangeTree<K,T>::Node::isLeaf() const {
    return (left == nullptr) && (right == nullptr);
}


}
