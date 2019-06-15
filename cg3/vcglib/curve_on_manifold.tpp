/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#include "curve_on_manifold.h"

#include "meshes/triangleedgemeshtype.h"

#include "convert.h"

#include <vcg/complex/algorithms/curve_on_manifold.h>

namespace cg3 {
namespace vcglib {

#ifdef CG3_EIGENMESH_DEFINED

inline cg3::EigenMesh curveOnManifold(
        const cg3::EigenMesh& mesh,
		const std::vector<std::pair<cg3::Point3d, cg3::Point3d>>& edges,
		std::set<std::pair<cg3::Point3d, cg3::Point3d>>& newEdgesCoordinates,
        const int firstStepIterations,
        const int secondStepIterations,
        const double baryCentricThreshold,
        const bool fixBorders,
        const bool fixCorners)
{
    typedef cg3::vcglib::TriangleEdgeMesh TriangleEdgeMesh;
    typedef typename TriangleEdgeMesh::CoordType CoordType;
    cg3::vcglib::TriangleEdgeMesh vcgMesh, resultMesh, edgeMesh;

    cg3::vcglib::eigenMeshToVCG(mesh, vcgMesh);
    cg3::vcglib::edgesToVCG(edges, edgeMesh);

    curveOnManifold(vcgMesh, edgeMesh, resultMesh, firstStepIterations, secondStepIterations, baryCentricThreshold, fixBorders, fixCorners);

    vcg::tri::Allocator<TriangleEdgeMesh>::CompactEveryVector(resultMesh);
    for (size_t i = 0; i < resultMesh.face.size(); i++) {
        for (int k = 0; k < resultMesh.face[i].VN(); k++) {
            if (resultMesh.face[i].IsFaceEdgeS(k)) {
                const CoordType& p1 = resultMesh.face[i].V0(k)->cP();
                const CoordType& p2 = resultMesh.face[i].V1(k)->cP();

				std::pair<cg3::Point3d, cg3::Point3d> newEdge;
				newEdge.first = cg3::Point3d(p1.X(), p1.Y(), p1.Z());
				newEdge.second = cg3::Point3d(p2.X(), p2.Y(), p2.Z());
                if (newEdge.first < newEdge.second)
                    std::swap(newEdge.first, newEdge.second);

                newEdgesCoordinates.insert(newEdge);
            }
        }
    }

    return cg3::vcglib::VCGToEigenMesh(resultMesh);
}

#endif

template <class TriangleEdgeMeshType>
void curveOnManifold(
        TriangleEdgeMeshType& polyMesh,
        TriangleEdgeMeshType& edgeMesh,
        TriangleEdgeMeshType& resultMesh,
        const int firstStepIterations,
        const int secondStepIterations,
        const double baryCentricThreshold,
        const bool fixBorders,
        const bool fixCorners)
{
    vcg::tri::Append<TriangleEdgeMeshType,TriangleEdgeMeshType>::MeshCopy(resultMesh, polyMesh);
    vcg::tri::UpdateTopology<TriangleEdgeMeshType>::FaceFace(resultMesh);
    vcg::tri::UpdateBounding<TriangleEdgeMeshType>::Box(resultMesh);

    vcg::tri::CoM<TriangleEdgeMeshType> cc(resultMesh);

    cc.Init();


    if (fixBorders) {
        cc.SelectBoundaryVertex(edgeMesh);
    }
    else {
        vcg::tri::UpdateSelection<TriangleEdgeMeshType>::VertexClear(edgeMesh);
        vcg::tri::UpdateTopology<TriangleEdgeMeshType>::VertexEdge(edgeMesh);
    }

    if (fixCorners) {

        vcg::tri::ForEachVertex(edgeMesh, [&](typename TriangleEdgeMeshType::VertexType &v){
          if(vcg::edge::VEDegree<typename TriangleEdgeMeshType::EdgeType>(&v)!=2) v.SetS();
        });
    }

    // Two smoothing runs,
    // the first that allows fast movement over the surface (long edges that can skim surface details)
    cc.par.surfDistThr = resultMesh.bbox.Diag()/100.0f;
    cc.par.maxSimpEdgeLen = resultMesh.bbox.Diag()/50.0f;
    cc.par.minRefEdgeLen = resultMesh.bbox.Diag()/100.0f;
    cc.par.barycentricSnapThr = baryCentricThreshold;
    cc.SmoothProject(edgeMesh,firstStepIterations,0.7f,.3f);

    // The second smooting run more accurate to adapt to the surface
    cc.par.surfDistThr = resultMesh.bbox.Diag()/1000.0f;
    cc.par.maxSimpEdgeLen = resultMesh.bbox.Diag()/1000.0f;
    cc.par.minRefEdgeLen = resultMesh.bbox.Diag()/2000.0f;
    cc.par.barycentricSnapThr = baryCentricThreshold;
    cc.SmoothProject(edgeMesh,secondStepIterations,0.01f,.99f);

    // Adapt the polyline to the mesh (in the end it will have vertices only on edges and vertices of the base mesh)
    cc.RefineCurveByBaseMesh(edgeMesh);

    // Safely split the mesh with this refined polyline
    cc.SplitMeshWithPolyline(edgeMesh);

    // Now the two meshes should have coincident edges
    cc.TagFaceEdgeSelWithPolyLine(edgeMesh);
}

}
}
