/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_VCGLIB_SMOOTHING_H
#define CG3_VCGLIB_SMOOTHING_H

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

namespace cg3 {
namespace vcglib {

namespace internal {
static std::vector<size_t> dummySelectedVertices;
}

#ifdef CG3_EIGENMESH_DEFINED
cg3::EigenMesh taubinSmoothing(
        const cg3::EigenMesh& mesh,
        const int iterations,
        const float lambda,
        const float mu,
        const std::vector<size_t>& selectedVertices = internal::dummySelectedVertices);
#endif

template <class TriangleEdgeMeshType>
void taubinSmoothing(
        TriangleEdgeMeshType& smoothedMesh,
        const int iterations,
        const float lambda,
        const float mu,
        bool selectedVertices);


#ifdef CG3_EIGENMESH_DEFINED
inline cg3::EigenMesh laplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const int iterations,
        const std::vector<size_t>& selectedVertices = internal::dummySelectedVertices);

#endif

template <class TriangleEdgeMeshType>
void laplacianSmoothing(
        TriangleEdgeMeshType& mesh,
        const int iterations,
        bool selectedVertices);

}
}

#include "smoothing.cpp"

#endif // CG3_VCGLIB_SMOOTHING_H
