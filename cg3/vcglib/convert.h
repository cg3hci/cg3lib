/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_VCGLIB_CONVERT_H
#define CG3_VCGLIB_CONVERT_H

#include <Eigen/Core>
#include <vector>

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

namespace cg3 {
namespace vcglib {

static std::vector<int> dummyVMap;
static std::vector<int> dummyFMap;

template<class EdgeMesh>
void edgesToVCG(
		const std::vector<std::pair<cg3::Point3d, cg3::Point3d>>& edges,
        EdgeMesh& edgeMesh);

#ifdef CG3_WITH_EIGEN

template<class PolyMeshType>
void VCGToEigen(
        PolyMeshType& vcgMesh,
        Eigen::MatrixXd& V,
        Eigen::MatrixXi& F,
        std::vector<int>& vMap = dummyVMap,
        std::vector<int>& fMap = dummyFMap,
        bool selectedOnly = false,
        int numVerticesPerFace = 3,
        int dim = 3);

template<class PolyMeshType>
void eigenToVCG(
        const Eigen::MatrixXd& V,
        const Eigen::MatrixXi& F,
        PolyMeshType& vcgMesh);

#endif


#ifdef CG3_EIGENMESH_DEFINED

template<class PolyMeshType>
cg3::EigenMesh VCGToEigenMesh(
        PolyMeshType& vcgMesh,
        std::vector<int>& vMap = dummyVMap,
        std::vector<int>& fMap = dummyFMap,
        bool selectedOnly = false,
        int numVerticesPerFace = 3,
        int dim = 3);

template<class PolyMeshType>
void eigenMeshToVCG(
        const cg3::EigenMesh& eigenMesh,
        PolyMeshType& vcgMesh);

#endif

}
}

#include "convert.cpp"

#endif // CG3_VCGLIB_CONVERT_H
