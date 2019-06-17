/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "convert.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/clean.h>
#pragma GCC diagnostic pop
#else
#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/clean.h>
#endif


namespace cg3 {
namespace vcglib {

template<class EdgeMesh>
void edgesToVCG(
		const std::vector<std::pair<cg3::Point3d, cg3::Point3d>>& edges,
        EdgeMesh& edgeMesh)
{
	for (const std::pair<cg3::Point3d, cg3::Point3d>& edge : edges) {
        typename EdgeMesh::CoordType coord1(edge.first.x(), edge.first.y(), edge.first.z());
        typename EdgeMesh::CoordType coord2(edge.second.x(), edge.second.y(), edge.second.z());
        vcg::tri::Allocator<EdgeMesh>::AddEdge(edgeMesh, coord1, coord2);
    }
    vcg::tri::Clean<EdgeMesh>::RemoveDuplicateVertex(edgeMesh);
    vcg::tri::Allocator<EdgeMesh>::CompactEveryVector(edgeMesh);
}

#ifdef CG3_WITH_EIGEN

template<class PolyMeshType>
void VCGToEigen(
        PolyMeshType& vcgMesh,
        Eigen::MatrixXd& V,
        Eigen::MatrixXi& F,
        std::vector<int>& vMap,
        std::vector<int>& fMap,
        bool selectedOnly,
        int numVerticesPerFace,
        int dim)
{
    assert(dim >= 2);
    assert(numVerticesPerFace > 2);

    int nSelectedVertices = 0;
    for (size_t i = 0; i < vcgMesh.vert.size(); i++){
        if ((!selectedOnly || vcgMesh.vert[i].IsS()) && !vcgMesh.vert[i].IsD()) {
            nSelectedVertices++;
        }
    }
    int nSelectedFaces = 0;
    for (size_t i = 0; i < vcgMesh.face.size(); i++){
        if ((!selectedOnly || vcgMesh.face[i].IsS()) && !vcgMesh.face[i].IsD()) {
            nSelectedFaces++;
        }
    }

    V.resize(nSelectedVertices, dim);
    F.resize(nSelectedFaces, numVerticesPerFace);

    vMap.resize(vcgMesh.vert.size(), -1);
    int vId = 0;
    for (size_t i = 0; i < vcgMesh.vert.size(); i++){
        if ((!selectedOnly || vcgMesh.vert[i].IsS()) && !vcgMesh.vert[i].IsD()) {
            vMap[i] = vId;
            for (int j = 0; j < dim; j++) {
                V(vId, j) = vcgMesh.vert[i].P()[j];
            }
            vId++;
        }
    }

    fMap.resize(vcgMesh.face.size(), -1);
    int fId = 0;
    for (size_t i = 0; i < vcgMesh.face.size(); i++){
        if ((!selectedOnly || vcgMesh.face[i].IsS()) && !vcgMesh.face[i].IsD()) {
            fMap[i] = fId;
            for (int j = 0; j < vcgMesh.face[i].VN(); j++) {
                F(fId, j) = vMap[vcg::tri::Index(vcgMesh, vcgMesh.face[i].V(j))];
            }
            fId++;
        }
    }
}

template<class PolyMeshType>
void eigenToVCG(
        const Eigen::MatrixXd& V,
        const Eigen::MatrixXi& F,
        PolyMeshType& vcgMesh)
{
    vcgMesh.Clear();

    vcg::tri::Allocator<PolyMeshType>::AddVertices(vcgMesh, V.rows());
    for (int i = 0; i < V.rows(); i++) {
        typename PolyMeshType::CoordType vv(V(i,0), V(i,1), V(i,2));
        vcgMesh.vert[static_cast<size_t>(i)].P() = vv;
    }

    vcg::tri::Allocator<PolyMeshType>::AddFaces(vcgMesh, static_cast<size_t>(F.rows()));
    for (int i = 0; i < F.rows(); i++) {
        const Eigen::VectorXi& row = F.row(i);
        Eigen::Index numVertices = row.size();
        vcgMesh.face[static_cast<size_t>(i)].Alloc(numVertices);
        for (Eigen::Index j = 0; j < numVertices; j++) {
            vcgMesh.face[static_cast<size_t>(i)].V(j) = &(vcgMesh.vert[static_cast<size_t>(F(i,j))]);
        }
    }
}

#endif

#ifdef CG3_EIGENMESH_DEFINED

template<class PolyMeshType>
cg3::EigenMesh VCGToEigenMesh(
        PolyMeshType& vcgMesh,
        std::vector<int>& vMap,
        std::vector<int>& fMap,
        bool selectedOnly,
        int numVerticesPerFace,
        int dim)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    VCGToEigen(vcgMesh, V, F, vMap, fMap, selectedOnly, numVerticesPerFace, dim);

    return cg3::EigenMesh(V,F);
}

template<class PolyMeshType>
void eigenMeshToVCG(
        const cg3::EigenMesh& eigenMesh,
        PolyMeshType& vcgMesh)
{
    const Eigen::MatrixXd& V = eigenMesh.getVerticesMatrix();
    const Eigen::MatrixXi& F = eigenMesh.getFacesMatrix();

    eigenToVCG(V, F, vcgMesh);
}

#endif

}
}
