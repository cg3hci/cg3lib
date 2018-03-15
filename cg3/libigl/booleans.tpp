/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "booleans.h"

#ifdef CG3_CGAL_DEFINED
#include "internal/eigenmesh_libigl_algorithms.h"
#include "internal/booleans_algorithms.h"

namespace cg3 {

namespace libigl {

/* ----- CONVERSIONS ----- */

/**
 * @brief Get CSGTree from an EigenMesh
 * @param m Input mesh
 * @return CSG tree of the mesh
 */
inline CSGTree eigenMeshToCSGTree(const SimpleEigenMesh& m) {
    return internal::EigenMeshLibIglAlgorithms::eigenMeshToCSGTree(m);
}

/**
 * @brief Get CSGTree from an EigenMesh
 * @param m Input mesh
 * @return CSG tree of the mesh
 */
inline SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree& tree) {
    return internal::EigenMeshLibIglAlgorithms::CSGTreeToEigenMesh(tree);
}


/* ----- CONVERSIONS ----- */

/**
 * @brief Intersection of two CSGTrees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Resulting CSGTree
 */
inline CSGTree intersection(const CSGTree& c1, const CSGTree& c2) {
    return internal::BooleansAlgorithms::intersection(c1, c2);
}

/**
 * @brief Intersection of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
inline SimpleEigenMesh intersection(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

/**
 * @brief Intersection of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
inline EigenMesh intersection(const EigenMesh& m1, const EigenMesh& m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

/**
 * @brief Intersection of two CSGTrees
 * @param[out] Resulting CSGTree
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 */
inline void intersection(CSGTree& result, const CSGTree& c1, const CSGTree& c2) {
    result = intersection(c1, c2);
}

/**
 * @brief Intersection of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 */
inline void intersection(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    result = intersection(m1, m2);
}

/**
 * @brief Intersection of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 */
inline void intersection(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    result = intersection(m1, m2);
}


/* ----- DIFFERENCE ----- */

/**
 * @brief Difference of two CSGTrees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Resulting CSGTree
 */
inline CSGTree difference(const CSGTree& c1, const CSGTree& c2) {
    return internal::BooleansAlgorithms::difference(c1, c2);
}

/**
 * @brief Difference of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
inline SimpleEigenMesh difference(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

/**
 * @brief Difference of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
inline EigenMesh difference(const EigenMesh& m1, const EigenMesh& m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

/**
 * @brief Difference of two CSGTrees
 * @param[out] Resulting CSGTree
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 */
inline void difference(CSGTree& result, const CSGTree& c1, const CSGTree& c2) {
    result = difference(c1, c2);
}

/**
 * @brief Difference of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 */
inline void difference(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    result = difference(m1, m2);
}

/**
 * @brief Difference of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 */
inline void difference(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    result = difference(m1, m2);
}


/* ----- UNION ----- */

/**
 * @brief Union of two CSGTrees
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 * @return Resulting CSGTree
 */
inline CSGTree union_(const CSGTree& c1, const CSGTree& c2) {
    return internal::BooleansAlgorithms::union_(c1, c2);
}

/**
 * @brief Union of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
inline SimpleEigenMesh union_(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

/**
 * @brief Union of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
inline EigenMesh union_(const EigenMesh& m1, const EigenMesh& m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

/**
 * @brief Union of two CSGTrees
 * @param[out] Resulting CSGTree
 * @param[in] c1 First CSGTree
 * @param[in] c2 Second CSGTree
 */
inline void union_(CSGTree& result, const CSGTree& c1, const CSGTree& c2) {
    result = union_(c1, c2);
}

/**
 * @brief Union of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 */
inline void union_(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    result = union_(m1, m2);
}

/**
 * @brief Union of two meshes
 * @param[out] Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 */
inline void union_(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    result = union_(m1, m2);
}


}

}
#endif
