/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SERIALIZE_EIGEN_H
#define CG3_SERIALIZE_EIGEN_H

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>

namespace cg3 {
namespace serializer {

namespace internal {
    template <typename T>
    void serializeEigen(const Eigen::PlainObjectBase<T> &m, std::ofstream& binaryFile);

    template <typename T>
    void deserializeEigen(Eigen::PlainObjectBase<T> &m, std::ifstream& binaryFile);
}

//specializations for eigen matrices
void serialize(const Eigen::MatrixXd& m, std::ofstream& binaryFile);
void deserialize(Eigen::MatrixXd& m, std::ifstream& binaryFile);

void serialize(const Eigen::MatrixXf& m, std::ofstream& binaryFile);
void deserialize(Eigen::MatrixXf& m, std::ifstream& binaryFile);

void serialize(const Eigen::MatrixXi& m, std::ofstream& binaryFile);
void deserialize(Eigen::MatrixXi& m, std::ifstream& binaryFile);

void serialize(const Eigen::Matrix<double, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile);
void deserialize(Eigen::Matrix<double, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile);

void serialize(const Eigen::Matrix<double, 3, 3>& m, std::ofstream& binaryFile);
void deserialize(Eigen::Matrix<double, 3, 3>& m, std::ifstream& binaryFile);

void serialize(const Eigen::Matrix<float, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile);
void deserialize(Eigen::Matrix<float, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile);

void serialize(const Eigen::Matrix<int, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile);
void deserialize(Eigen::Matrix<int, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile);

}
}
#endif //CG3_WITH_EIGEN

#include "serialize_eigen.tpp"

#endif // CG3_SERIALIZE_EIGEN_H
