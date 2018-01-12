/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "serialize_eigen.h"

#ifdef CG3_WITH_EIGEN
namespace cg3 {

template <typename T>
inline void serializer::internal::serializeEigen(const Eigen::PlainObjectBase<T> &m, std::ofstream& binaryFile){
    unsigned long long int row = m.rows(), col = m.cols();
    serializer::serialize("EigenMatrix", binaryFile);
    serializer::serialize(row, binaryFile);
    serializer::serialize(col, binaryFile);
    for (unsigned int i = 0; i < row; i++){
        for (unsigned int j = 0; j < col; ++j){
            serializer::serialize(m(i,j), binaryFile);
        }
    }
}

template <typename T>
inline void serializer::internal::deserializeEigen(Eigen::PlainObjectBase<T> &m, std::ifstream& binaryFile){
    unsigned long long int row, col;
    std::string s;
    T tmp;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(s, binaryFile);
        if (s != "EigenMatrix")
            throw std::ios_base::failure("Mismatching String: " + s + " != EigenMatrix");
        serializer::deserialize(row, binaryFile);
        serializer::deserialize(col, binaryFile);
        tmp.resize(row, col);

        for (unsigned int i = 0; i < row; i++){
            for (unsigned int j = 0; j < col; ++j){
                serializer::deserialize(tmp(i,j), binaryFile);
            }
        }
        m = tmp;
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom Eigen::Matrix"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of Eigen::Matrix");
    }
}

inline void serializer::serialize(const Eigen::MatrixXd& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::MatrixXd& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void serializer::serialize(const Eigen::MatrixXf& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::MatrixXf& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void serializer::serialize(const Eigen::MatrixXi& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::MatrixXi& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void serializer::serialize(const Eigen::Matrix<double, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::Matrix<double, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void serializer::serialize(const Eigen::Matrix<double, 3, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::Matrix<double, 3, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void serializer::serialize(const Eigen::Matrix<float, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::Matrix<float, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void serializer::serialize(const Eigen::Matrix<int, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void serializer::deserialize(Eigen::Matrix<int, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

}
#endif //CG3_WITH_EIGEN*/
