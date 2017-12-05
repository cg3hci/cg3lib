/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABB_NODE_AABB_H
#define CG3_AABB_NODE_AABB_H

namespace cg3 {

namespace internal {

/**
 * @brief D-dimensional axis-aligned bounding box
 */
template <int D>
class AABB {

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

}

#include "aabb_node_aabb.tpp"

#endif // CG3_AABB_NODE_AABB_H
