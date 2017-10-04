/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBTREEAABB_H
#define CG3_AABBTREEAABB_H

#include "../aabbtree.h"

namespace cg3 {

/**
 * @brief Axis-aligned bounding box
 */
template <int D, class K, class T>
class AABBTree<D,K,T>::AABB {

public:

    /* Constructors */

    AABB();
    AABB(const double min[D], const double max[D]);

    /* Public methods */

    void set(const double min[D], const double max[D]);

    void setMin(const double min[]);
    void setMax(const double max[]);

    void setMin(const int& dim, const double& value);
    void setMax(const int& dim, const double& value);

    double getMin(const int& dim) const;
    double getMax(const int& dim) const;


private:

    /* Fields */

    double min[D];
    double max[D];

};


}


#include "aabbtreeaabb.tpp"

#endif // CG3_AABBTREEAABB_H
