/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "booleans.h"

#include "internal/eigenmesh_libigl_algorithms.h"

#ifdef  CG3_CGAL_DEFINED
namespace cg3 {
namespace libigl {

/* ----- CONVERSIONS ----- */

/**
 * @ingroup cg3libigl
 * @brief Get CSGTree from an EigenMesh
 * @param m Input mesh
 * @return CSG tree of the mesh
 */
CG3_INLINE CSGTree eigenMeshToCSGTree(const SimpleEigenMesh& m)
{
    return internal::EigenMeshLibIglAlgorithms::eigenMeshToCSGTree(m);
}

/**
 * @ingroup cg3libigl
 * @brief Get CSGTree from an EigenMesh
 * @param m Input mesh
 * @return CSG tree of the mesh
 */
CG3_INLINE SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree& tree)
{
    return internal::EigenMeshLibIglAlgorithms::CSGTreeToEigenMesh(tree);
}


/* ----- CONVERSIONS ----- */

/**
 * @ingroup cg3libigl
 * @brief Intersection of two CSGTrees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Resulting CSGTree
 */
CG3_INLINE CSGTree intersection(const CSGTree& c1, const CSGTree& c2)
{
    return internal::intersection(c1, c2);
}

/**
 * @ingroup cg3libigl
 * @brief Intersection of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 * @return Resulting mesh
 */
CG3_INLINE SimpleEigenMesh intersection(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Intersection of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 * @return Resulting mesh
 */
CG3_INLINE EigenMesh intersection(
        const EigenMesh& m1,
        const EigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Intersection of two CSGTrees
 * @param[out] Resulting CSGTree
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 */
CG3_INLINE void intersection(CSGTree& result, const CSGTree& c1, const CSGTree& c2)
{
    result = intersection(c1, c2);
}

/**
 * @ingroup cg3libigl
 * @brief Intersection of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 */
CG3_INLINE void intersection(
        SimpleEigenMesh& result,
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    result = intersection(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Intersection of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 */
CG3_INLINE void intersection(
        EigenMesh& result,
        const EigenMesh& m1,
        const EigenMesh& m2,
        std::vector<uint>& birthFaces) {
    result = intersection(m1, m2, birthFaces);
}


/* ----- DIFFERENCE ----- */

/**
 * @ingroup cg3libigl
 * @brief Difference of two CSGTrees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Resulting CSGTree
 */
CG3_INLINE CSGTree difference(const CSGTree& c1, const CSGTree& c2)
{
    return internal::difference(c1, c2);
}

/**
 * @ingroup cg3libigl
 * @brief Difference of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 * @return Resulting mesh
 */
CG3_INLINE SimpleEigenMesh difference(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Difference of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 * @return Resulting mesh
 */
CG3_INLINE EigenMesh difference(
        const EigenMesh& m1,
        const EigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Difference of two CSGTrees
 * @param[out] Resulting CSGTree
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 */
CG3_INLINE void difference(CSGTree& result, const CSGTree& c1, const CSGTree& c2)
{
    result = difference(c1, c2);
}

/**
 * @ingroup cg3libigl
 * @brief Difference of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 */
CG3_INLINE void difference(
        SimpleEigenMesh& result,
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    result = difference(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Difference of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 */
CG3_INLINE void difference(
        EigenMesh& result,
        const EigenMesh& m1,
        const EigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    result = difference(m1, m2, birthFaces);
}


/* ----- UNION ----- */

/**
 * @ingroup cg3libigl
 * @brief Union of two CSGTrees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Resulting CSGTree
 */
CG3_INLINE CSGTree union_(const CSGTree& c1, const CSGTree& c2)
{
    return internal::union_(c1, c2);
}

/**
 * @ingroup cg3libigl
 * @brief Union of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 * @return Resulting mesh
 */
CG3_INLINE SimpleEigenMesh union_(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Union of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 * @return Resulting mesh
 */
CG3_INLINE EigenMesh union_(
        const EigenMesh& m1,
        const EigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Union of two CSGTrees
 * @param[out] Resulting CSGTree
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 */
CG3_INLINE void union_(CSGTree& result, const CSGTree& c1, const CSGTree& c2)
{
    result = union_(c1, c2);
}

/**
 * @ingroup cg3libigl
 * @brief Union of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 */
CG3_INLINE void union_(
        SimpleEigenMesh& result,
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    result = union_(m1, m2, birthFaces);
}

/**
 * @ingroup cg3libigl
 * @brief Union of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[out] birthFaces vector of indices indicating the birth faces of the resulting mesh
 */
CG3_INLINE void union_(
        EigenMesh& result,
        const EigenMesh& m1,
        const EigenMesh& m2,
        std::vector<uint>& birthFaces)
{
    result = union_(m1, m2, birthFaces);
}


} //namespace cg3::libigl
} //namespace cg3
#endif // CG3_CGAL_DEFINED
