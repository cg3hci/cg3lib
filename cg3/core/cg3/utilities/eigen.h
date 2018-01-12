/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_EIGEN_H
#define CG3_EIGEN_H

#include <vector>
#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

namespace cg3 {

#ifdef CG3_WITH_EIGEN
template <typename T, int ...A>
std::vector<T> eigenVectorToStdVector(const Eigen::Matrix<T, A...>& v);

template <typename T, int ...A>
void removeRowFromEigenMatrix(Eigen::Matrix<T, A...> &m, unsigned int row);

template <typename T, int ...A>
void removeColumnFromEigenMatrix(Eigen::Matrix<T, A...> &m, unsigned int column);
#endif

}

#include "eigen.tpp"

#endif // CG3_EIGEN_H
