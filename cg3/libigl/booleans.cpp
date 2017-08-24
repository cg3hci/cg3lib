#include "booleans.h"

#ifdef CG3_CGAL_DEFINED
#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

CSGTree eigenMeshToCSGTree(const SimpleEigenMesh &m) {
    return internal::EigenMeshLibIglAlgorithms::eigenMeshToCSGTree(m);
}

SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree &tree) {
    return internal::EigenMeshLibIglAlgorithms::CSGTreeToEigenMesh(tree);
}

void intersection(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

void intersection(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

SimpleEigenMesh intersection(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

EigenMesh intersection(const EigenMesh &m1, const EigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

void intersection(CSGTree &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

CSGTree intersection(const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

void intersection(SimpleEigenMesh &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

void difference(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::difference(result, m1, m2);
}

void difference(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::difference(result, m1, m2);
}

SimpleEigenMesh difference(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

EigenMesh difference(const EigenMesh &m1, const EigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

void difference(CSGTree &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::difference(result, m1, m2);
}

CSGTree difference(const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

void union_(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::union_(result, m1, m2);
}

void union_(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::union_(result, m1, m2);
}

SimpleEigenMesh union_(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

EigenMesh union_(const EigenMesh &m1, const EigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

void union_(CSGTree &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::union_(result, m1, m2);
}

CSGTree union_(const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

}

}
#endif
