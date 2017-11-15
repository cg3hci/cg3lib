/**
    @author Stefano Nuvoli
*/
#include "aabb.h"
#include "assert.h"

namespace cg3 {


/* --------- CONSTRUCTORS/DESTRUCTOR --------- */

/**
 * Default constructor
 */
template <int D>
AABB<D>::AABB() {
}


/**
 * Constructor with data
 */
template <int D>
AABB<D>::AABB(const double min[D], const double max[D]) {
    set(min, max);
}




/* --------- PUBLIC METHODS --------- */

template<int D>
void AABB<D>::set(const double min[D], const double max[D]) {
    setMin(min);
    setMax(max);
}



template<int D>
void AABB<D>::setMin(const double min[]) {
    for (int i = 0; i < D; i++) {
        this->min[i] = min[i];
    }
}

template<int D>
void AABB<D>::setMax(const double max[]) {
    for (int i = 0; i < D; i++) {
        this->max[i] = max[i];
    }
}



template<int D>
void AABB<D>::setMin(const int& dim, const double& value) {
    assert(dim <= D);
    this->min[dim-1] = value;
}

template<int D>
void AABB<D>::setMax(const int& dim, const double& value) {
    assert(dim <= D);
    this->max[dim-1] = value;
}



template<int D>
double AABB<D>::getMin(const int& dim) const {
    assert(dim <= D && dim > 0);
    return this->min[dim-1];
}

template<int D>
double AABB<D>::getMax(const int& dim) const {
    assert(dim <= D && dim > 0);
    return this->max[dim-1];
}



}
