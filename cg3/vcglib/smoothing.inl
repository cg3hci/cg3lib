/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "smoothing.h"

#include "meshes/trianglemeshtype.h"

#include "convert.h"

#include <vcg/complex/algorithms/smooth.h>

namespace cg3 {
namespace vcglib {

#ifdef CG3_EIGENMESH_DEFINED
inline cg3::EigenMesh taubinSmoothing(
        const cg3::EigenMesh& mesh,
        const int iterations,
        const float lambda,
        const float mu,
        const std::vector<size_t>& selectedVertices)
{
    typedef cg3::vcglib::TriangleMesh TriangleMesh;
    TriangleMesh vcgMesh;

    cg3::vcglib::eigenMeshToVCG(mesh, vcgMesh);

    if (!selectedVertices.empty()) {
        vcg::tri::Allocator<TriangleMesh>::CompactEveryVector(vcgMesh);
        vcg::tri::UpdateSelection<TriangleMesh>::FaceClear(vcgMesh);
        for (size_t selectedVertex : selectedVertices) {
            vcgMesh.face[selectedVertex].SetS();
        }
    }

    taubinSmoothing(vcgMesh, iterations, lambda, mu, !selectedVertices.empty());

	EigenMesh tmp = cg3::vcglib::VCGToEigenMesh(vcgMesh);
	tmp.setVerticesColorMatrix(mesh.verticesColorMatrix());
	tmp.setFacesColorMatrix(mesh.facesColorMatrix());
	return tmp;
}
#endif

template <class TriangleEdgeMeshType>
void taubinSmoothing(
        TriangleEdgeMeshType& mesh,
        const int iterations,
        const float lambda,
        const float mu,
        bool selectedVertices)
{
    vcg::tri::Smooth<TriangleMesh>::VertexCoordTaubin(mesh, iterations, lambda, mu, selectedVertices);
}

#ifdef CG3_EIGENMESH_DEFINED
inline cg3::EigenMesh laplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const int iterations,
        const std::vector<size_t>& selectedVertices)
{
    typedef cg3::vcglib::TriangleMesh TriangleMesh;
    TriangleMesh vcgMesh;

    cg3::vcglib::eigenMeshToVCG(mesh, vcgMesh);

    if (!selectedVertices.empty()) {
        vcg::tri::Allocator<TriangleMesh>::CompactEveryVector(vcgMesh);
        vcg::tri::UpdateSelection<TriangleMesh>::FaceClear(vcgMesh);
        for (size_t selectedVertex : selectedVertices) {
            vcgMesh.face[selectedVertex].SetS();
        }
    }

    laplacianSmoothing(vcgMesh, iterations, !selectedVertices.empty());

    EigenMesh tmp = cg3::vcglib::VCGToEigenMesh(vcgMesh);
    tmp.setVerticesColorMatrix(mesh.verticesColorMatrix());
    tmp.setFacesColorMatrix(mesh.facesColorMatrix());
    return tmp;
}
#endif

template <class TriangleEdgeMeshType>
void laplacianSmoothing(
        TriangleEdgeMeshType& mesh,
        const int iterations,
        bool selectedVertices)
{
    vcg::tri::Smooth<TriangleMesh>::VertexCoordLaplacian(mesh, iterations);
}

}
}
