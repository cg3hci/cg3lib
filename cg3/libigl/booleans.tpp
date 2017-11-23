#include "booleans.h"

#ifdef CG3_CGAL_DEFINED
#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

inline CSGTree eigenMeshToCSGTree(const SimpleEigenMesh &m) {
    return internal::EigenMeshLibIglAlgorithms::eigenMeshToCSGTree(m);
}

inline SimpleEigenMesh CSGTreeToEigenMesh(const CSGTree &tree) {
    return internal::EigenMeshLibIglAlgorithms::CSGTreeToEigenMesh(tree);
}

inline void intersection(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

inline void intersection(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

inline SimpleEigenMesh intersection(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

inline EigenMesh intersection(const EigenMesh &m1, const EigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

inline void intersection(CSGTree &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

inline CSGTree intersection(const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(m1, m2);
}

inline void intersection(SimpleEigenMesh &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::intersection(result, m1, m2);
}

inline void difference(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::difference(result, m1, m2);
}

inline void difference(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::difference(result, m1, m2);
}

inline SimpleEigenMesh difference(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

inline EigenMesh difference(const EigenMesh &m1, const EigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

inline void difference(CSGTree &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::difference(result, m1, m2);
}

inline CSGTree difference(const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::difference(m1, m2);
}

inline void union_(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::union_(result, m1, m2);
}

inline void union_(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::union_(result, m1, m2);
}

inline SimpleEigenMesh union_(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

inline EigenMesh union_(const EigenMesh &m1, const EigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

inline void union_(CSGTree &result, const CSGTree &m1, const SimpleEigenMesh &m2) {
    internal::EigenMeshLibIglAlgorithms::union_(result, m1, m2);
}

inline CSGTree union_(const CSGTree &m1, const SimpleEigenMesh &m2) {
    return internal::EigenMeshLibIglAlgorithms::union_(m1, m2);
}

}

}
#endif
