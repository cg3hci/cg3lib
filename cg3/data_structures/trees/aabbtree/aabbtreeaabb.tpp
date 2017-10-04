/**
    @author Stefano Nuvoli
*/

#include "aabbtreeaabb.h"
#include "assert.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <int D, class K, class T>
AABBTree<D,K,T>::AABB::AABB() {
}


/**
 * Constructor with data
 */
template <int D, class K, class T>
AABBTree<D,K,T>::AABB::AABB(const double min[D], const double max[D]) {
    set(min, max);
}




/* --------- PUBLIC METHODS --------- */

template<int D, class K, class T>
void AABBTree<D,K,T>::AABB::set(const double min[D], const double max[D]) {
    setMin(min);
    setMax(max);
}



template<int D, class K, class T>
void AABBTree<D,K,T>::AABB::setMin(const double min[]) {
    for (int i = 0; i < D; i++) {
        this->min[i] = min[i];
    }
}

template<int D, class K, class T>
void AABBTree<D,K,T>::AABB::setMax(const double max[]) {
    for (int i = 0; i < D; i++) {
        this->max[i] = max[i];
    }
}



template<int D, class K, class T>
void AABBTree<D,K,T>::AABB::setMin(const int& dim, const double& value) {
    assert(dim <= D);
    this->min[dim-1] = value;
}

template<int D, class K, class T>
void AABBTree<D,K,T>::AABB::setMax(const int& dim, const double& value) {
    assert(dim <= D);
    this->max[dim-1] = value;
}



template<int D, class K, class T>
double AABBTree<D,K,T>::AABB::getMin(const int& dim) const {
    assert(dim <= D && dim > 0);
    return this->min[dim-1];
}

template<int D, class K, class T>
double AABBTree<D,K,T>::AABB::getMax(const int& dim) const {
    assert(dim <= D && dim > 0);
    return this->max[dim-1];
}



}
