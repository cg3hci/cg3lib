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

#include "eigen.cpp"

#endif // CG3_EIGEN_H
