#include "serialize_eigen.h"

#ifdef CG3_WITH_EIGEN
namespace cg3 {

template <typename T>
inline void Serializer::internal::serializeEigen(const Eigen::PlainObjectBase<T> &m, std::ofstream& binaryFile){
    unsigned long long int row = m.rows(), col = m.cols();
    Serializer::serialize("EigenMatrix", binaryFile);
    Serializer::serialize(row, binaryFile);
    Serializer::serialize(col, binaryFile);
    for (unsigned int i = 0; i < row; i++){
        for (unsigned int j = 0; j < col; ++j){
            Serializer::serialize(m(i,j), binaryFile);
        }
    }
}

template <typename T>
inline void Serializer::internal::deserializeEigen(Eigen::PlainObjectBase<T> &m, std::ifstream& binaryFile){
    unsigned long long int row, col;
    std::string s;
    T tmp;
    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "EigenMatrix")
            throw std::ios_base::failure("Mismatching String: " + s + " != EigenMatrix");
        Serializer::deserialize(row, binaryFile);
        Serializer::deserialize(col, binaryFile);
        tmp.resize(row, col);

        for (unsigned int i = 0; i < row; i++){
            for (unsigned int j = 0; j < col; ++j){
                Serializer::deserialize(tmp(i,j), binaryFile);
            }
        }
        #ifndef _WIN32
        m = std::move(tmp);
        #else
        m = tmp;
        #endif
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

inline void Serializer::serialize(const Eigen::MatrixXd& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::MatrixXd& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void Serializer::serialize(const Eigen::MatrixXf& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::MatrixXf& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void Serializer::serialize(const Eigen::MatrixXi& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::MatrixXi& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void Serializer::serialize(const Eigen::Matrix<double, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::Matrix<double, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void Serializer::serialize(const Eigen::Matrix<double, 3, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::Matrix<double, 3, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void Serializer::serialize(const Eigen::Matrix<float, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::Matrix<float, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

inline void Serializer::serialize(const Eigen::Matrix<int, -1, 3, 1, -1, 3>& m, std::ofstream& binaryFile) {
    internal::serializeEigen(m, binaryFile);
}

inline void Serializer::deserialize(Eigen::Matrix<int, -1, 3, 1, -1, 3>& m, std::ifstream& binaryFile) {
    internal::deserializeEigen(m, binaryFile);
}

}
#endif //CG3_WITH_EIGEN*/
