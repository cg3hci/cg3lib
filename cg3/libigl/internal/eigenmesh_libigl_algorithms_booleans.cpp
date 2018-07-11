/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#ifdef CG3_CGAL_DEFINED

namespace cg3 {
namespace libigl {
namespace internal {

/* Data reassociation declaration */

void reassociateDataAfterOperation(
        EigenMesh& resultingMesh,
        const EigenMesh& m1,
        const EigenMesh& m2,
        const CSGTree::VectorJ& birthFaces);


/* ----- CSG CONVERSIONS ----- */

/**
 * @brief Get CSGTree from an EigenMesh
 * @param m Input mesh
 * @return CSG tree of the mesh
 */
CSGTree EigenMeshLibIglAlgorithms::eigenMeshToCSGTree(const SimpleEigenMesh& m)
{
    return CSGTree(m.V, m.F);
}


/**
 * @brief Get an Eigen mesh from an CSGTree
 * @param c Input CSG tree
 * @return Mesh
 */
SimpleEigenMesh EigenMeshLibIglAlgorithms::CSGTreeToEigenMesh(const CSGTree& c)
{
    SimpleEigenMesh result(
        c.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >(),
        c.F());

    return result;
}


/* ----- MESH INTERSECTIONS ----- */

/**
 * @brief Intersection of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
SimpleEigenMesh EigenMeshLibIglAlgorithms::intersection(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2)
{
    CSGTree csgResult =
            internal::intersection(
                eigenMeshToCSGTree(m1),
                eigenMeshToCSGTree(m2));

    return (SimpleEigenMesh) CSGTreeToEigenMesh(csgResult);
}

/**
 * @brief Intersection of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
EigenMesh EigenMeshLibIglAlgorithms::intersection(const EigenMesh& m1, const EigenMesh& m2)
{
    CSGTree csgResult =
            internal::intersection(
                eigenMeshToCSGTree(m1),
                eigenMeshToCSGTree(m2));

    EigenMesh eigenMesh(CSGTreeToEigenMesh(csgResult));

    reassociateDataAfterOperation(eigenMesh, m1, m2, csgResult.J());

    return eigenMesh;
}


/* ----- MESH DIFFERENCES ----- */

/**
 * @brief Difference of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
SimpleEigenMesh EigenMeshLibIglAlgorithms::difference(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2)
{
    CSGTree csgResult =
            internal::difference(
                eigenMeshToCSGTree(m1),
                eigenMeshToCSGTree(m2));

    return (SimpleEigenMesh) CSGTreeToEigenMesh(csgResult);
}

/**
 * @brief Difference of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
EigenMesh EigenMeshLibIglAlgorithms::difference(
        const EigenMesh& m1,
        const EigenMesh& m2)
{
    CSGTree csgResult =
            internal::difference(
                eigenMeshToCSGTree(m1),
                eigenMeshToCSGTree(m2));

    EigenMesh eigenMesh(CSGTreeToEigenMesh(csgResult));

    reassociateDataAfterOperation(eigenMesh, m1, m2, csgResult.J());    

    return eigenMesh;
}


/* ----- MESH UNIONS ----- */

/**
 * @brief Union of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
SimpleEigenMesh EigenMeshLibIglAlgorithms::union_(
        const SimpleEigenMesh& m1,
        const SimpleEigenMesh& m2)
{
    CSGTree csgResult =
            internal::union_(
                eigenMeshToCSGTree(m1),
                eigenMeshToCSGTree(m2));

    return (SimpleEigenMesh) CSGTreeToEigenMesh(csgResult);
}

/**
 * @brief Union of two meshes
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @return Resulting mesh
 */
EigenMesh EigenMeshLibIglAlgorithms::union_(
        const EigenMesh& m1,
        const EigenMesh& m2)
{
    CSGTree csgResult =
            internal::union_(
                eigenMeshToCSGTree(m1),
                eigenMeshToCSGTree(m2));

    EigenMesh eigenMesh(CSGTreeToEigenMesh(csgResult));

    reassociateDataAfterOperation(eigenMesh, m1, m2, csgResult.J());

    return eigenMesh;
}


/* ----- DATA REASSOCIATION ----- */

/**
 * @brief Reassociate data of the eigen mesh after an operation
 * @param[out] resultingMesh Resulting mesh
 * @param[in] m1 First mesh
 * @param[in] m2 Second mesh
 * @param[in] birthFaces Vector of birth faces (use CSG Tree J() method)
 */
void reassociateDataAfterOperation(
        EigenMesh& resultingMesh,
        const EigenMesh& m1,
        const EigenMesh& m2,
        const CSGTree::VectorJ& birthFaces)
{
    unsigned int nFaces = resultingMesh.numberFaces();
    unsigned int nA = m1.numberFaces();

    for (unsigned int i = 0; i < nFaces; i++) {
        unsigned int birthFace = birthFaces[i];

        //If the birth face is in the first mesh
        if (birthFace < nA) {
            resultingMesh.setFaceColor(m1.faceColor(birthFace), i);
        }
        //If the birth face is in the second mesh
        else {
            resultingMesh.setFaceColor(m2.faceColor(birthFace - nA), i);
        }
    }
}

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
} //namespace cg3


#endif // CG3_CGAL_DEFINED
