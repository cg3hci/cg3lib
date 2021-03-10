/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */
#ifndef CG3_GLOBAL_OPTIMAL_ROTATION_MATRIX_H
#define CG3_GLOBAL_OPTIMAL_ROTATION_MATRIX_H

#include <cg3/geometry/point3.h>

#include <Eigen/Core>

namespace cg3 {


class Dcel;
Eigen::Matrix3d globalOptimalRotationMatrix(const Dcel& inputMesh, unsigned int nDirs = 1000);
Eigen::Matrix3d globalOptimalRotationMatrix(const Dcel& inputMesh, const std::vector<cg3::Vec3d>& dirPool);

class SimpleEigenMesh;
Eigen::Matrix3d globalOptimalRotationMatrix(const SimpleEigenMesh& inputMesh, unsigned int nDirs = 1000);
Eigen::Matrix3d globalOptimalRotationMatrix(const SimpleEigenMesh& inputMesh, const std::vector<cg3::Vec3d>& dirPool);

} //namespace cg3

#ifndef CG3_STATIC
#define  CG3_GLOBAL_OPTIMAL_ROTATION_MATRIX_CPP "global_optimal_rotation_matrix.cpp"
#include  CG3_GLOBAL_OPTIMAL_ROTATION_MATRIX_CPP
#undef  CG3_GLOBAL_OPTIMAL_ROTATION_MATRIX_CPP
#endif

#endif // CG3_GLOBAL_OPTIMAL_ROTATION_MATRIX_H
