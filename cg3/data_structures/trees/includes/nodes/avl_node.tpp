/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "avl_node.h"

namespace cg3 {

namespace internal {

/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * @brief Constructor with key and value
 *
 * param[in] key Key of the node
 * param[in] value Value of the node
 */
template<class K, class T>
AVLNode<K,T>::AVLNode(
        const K& key,
        const T& value)
{
    init(key, new T(value));
}

/**
 * @brief Constructor with only key
 *
 * param[in] key Key of the node
 */
template<class K, class T>
AVLNode<K,T>::AVLNode(const K& key)
{
    init(key, nullptr);
}

/**
 * @brief Destructor
 */
template<class K, class T>
AVLNode<K,T>::~AVLNode()
{
    if (this->value != nullptr) {
        delete this->value;
        this->value = nullptr;
    }
}


/* --------- PUBLIC METHODS --------- */

/**
 * @brief Check if the node is a leaf
 *
 * @return True if the node is a leaf
 */
template<class K, class T>
bool AVLNode<K,T>::isLeaf() const
{
    return (left == nullptr) && (right == nullptr);
}



/* --------- PRIVATE METHODS --------- */

/**
 * @brief Initialization of the node given key and value
 *
 * param[in] key Key of the node
 * param[in] value Value of the node
 */
template<class K, class T>
void AVLNode<K,T>::init(const K& key, T* value)
{
    this->key = key;
    this->value = value;

    this->left = nullptr;
    this->right = nullptr;

    this->parent = nullptr;

    this->height = 0;
}


}

}
