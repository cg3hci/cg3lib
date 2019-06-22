#include "booleans_algorithms.h"

#ifdef CG3_CGAL_DEFINED

namespace cg3 {
namespace libigl {
namespace internal {

/**
 * @brief Intersection of two CSG Trees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Intersection CSG Tree
 */
CG3_INLINE igl::copyleft::cgal::CSGTree intersection(
        const igl::copyleft::cgal::CSGTree& c1,
        const igl::copyleft::cgal::CSGTree& c2)
{
    return igl::copyleft::cgal::CSGTree(c1,c2,"i");
}

/**
 * @brief Difference of two CSG Trees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Difference CSG Tree
 */
CG3_INLINE igl::copyleft::cgal::CSGTree difference(
        const igl::copyleft::cgal::CSGTree& c1,
        const igl::copyleft::cgal::CSGTree& c2)
{
    return igl::copyleft::cgal::CSGTree(c1,c2,"m");
}

/**
 * @brief Union of two CSG Trees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Union CSG Tree
 */
CG3_INLINE igl::copyleft::cgal::CSGTree union_(
        const igl::copyleft::cgal::CSGTree& c1,
        const igl::copyleft::cgal::CSGTree& c2)
{
    return igl::copyleft::cgal::CSGTree(c1,c2,"u");
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3

#endif //CGAL_DEFINED
