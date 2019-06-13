/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */
#include "global_optimal_rotation_matrix.h"

#include "sphere_coverage.h"

#include <cg3/geometry/transformations.h>

#ifdef CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/simpleeigenmesh.h>
#endif

namespace cg3 {

void defineRotation(const cg3::Vec3& zAxis,
                    cg3::Vec3& rotationAxis,
                    double& angle)
{
    const cg3::Vec3 Z(0,0,1);
    rotationAxis = zAxis.cross(Z);
    rotationAxis.normalize();
    angle = acos(zAxis.dot(Z));
    assert(!std::isnan(angle));
}

#ifdef CG3_WITH_EIGEN
#ifdef CG3_DCEL_DEFINED
/**
 * @ingroup cg3Algorithms
 * @brief Computes the rotation matrix that, if applied to the mesh,
 * minimizes the angle between the face normals and the global axis
 * @param inputMesh
 * @param nDirs
 * @return A rotation matrix for the input mesh
 */
Eigen::Matrix3d globalOptimalRotationMatrix(
		const cg3::Dcel& inputMesh,
		unsigned int nDirs)
{

	std::vector<Vec3> dirPool = cg3::sphereCoverageFibonacci(nDirs);

	return globalOptimalRotationMatrix(inputMesh, dirPool);
}

Eigen::Matrix3d globalOptimalRotationMatrix(const Dcel &inputMesh, const std::vector<Vec3> &dirPool)
{
	std::set<std::pair<double,Vec3>> priorizitedOrientations;
	for(Vec3 zAxis : dirPool) {
		Vec3 axis;
		double angle;
		zAxis.normalize();
		defineRotation(zAxis, axis, angle);
		Eigen::Matrix3d mr = rotationMatrix(axis, angle);

		double L1_extent = 0.0;
		for(const Dcel::Face* f : inputMesh.faceIterator()) {
			Vec3 n = f->normal();
			n.rotate(mr);
			L1_extent += std::fabs(n.x()) + std::fabs(n.y()) + std::fabs(n.z());
		}

		priorizitedOrientations.insert(std::make_pair(L1_extent,zAxis));
	}

	Vec3  bestZ  = priorizitedOrientations.begin()->second;

	Vec3  axis;
	double angle;
	bestZ.normalize();
	defineRotation(bestZ, axis, angle);

	return cg3::rotationMatrix(axis, angle);
}
#endif

#ifdef CG3_EIGENMESH_DEFINED
/**
 * @ingroup cg3Algorithms
 * @brief Computes the rotation matrix that, if applied to the mesh,
 * minimizes the angle between the face normals and the global axis
 * @param inputMesh
 * @param nDirs
 * @return
 */
Eigen::Matrix3d globalOptimalRotationMatrix(
        const SimpleEigenMesh& inputMesh,
		unsigned int nDirs)
{
	std::vector<Vec3> dirPool = cg3::sphereCoverageFibonacci(nDirs);

	return globalOptimalRotationMatrix(inputMesh, dirPool);
}

Eigen::Matrix3d globalOptimalRotationMatrix(
		const SimpleEigenMesh &inputMesh,
		const std::vector<Vec3> &dirPool)
{
	std::set<std::pair<double,Vec3>> priorizitedOrientations;
	for(Vec3 zAxis : dirPool) {
		Vec3 axis;
		double angle;
		zAxis.normalize();
		defineRotation(zAxis, axis, angle);
		Eigen::Matrix3d mr = rotationMatrix(axis, angle);

		double L1_extent = 0.0;
		for(unsigned int f = 0; f < inputMesh.numberFaces(); f++) {
			Vec3 n = inputMesh.faceNormal(f);
			n.rotate(mr);
			L1_extent += std::fabs(n.x()) + std::fabs(n.y()) + std::fabs(n.z());
		}

		priorizitedOrientations.insert(std::make_pair(L1_extent,zAxis));
	}

	Vec3  bestZ  = priorizitedOrientations.begin()->second;

	Vec3  axis;
	double angle;
	bestZ.normalize();
	defineRotation(bestZ, axis, angle);

	return cg3::rotationMatrix(axis, angle);
}

#endif
#endif

} //namespace cg3
