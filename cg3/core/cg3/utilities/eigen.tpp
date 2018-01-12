/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigen.h"

namespace cg3 {

#ifdef CG3_WITH_EIGEN
/**
 * @brief eigenVectorToStdVector
 * @param v
 * @return
 * @link https://stackoverflow.com/questions/26094379/typecasting-eigenvectorxd-to-stdvector
 */
template<typename T, int ...A>
inline std::vector<T> eigenVectorToStdVector(const Eigen::Matrix<T, A...>& ev) {
    std::vector<T> stdv;
    stdv.resize(ev.size());
    Eigen::Matrix<T, A...>::Map(&stdv[0], ev.size()) = ev;
    return stdv;
}

/**
 * @brief removeRowFromEigenMatrix
 * @param m
 * @param row
 * @link https://stackoverflow.com/questions/13290395/how-to-remove-a-certain-row-or-column-while-using-eigen-library-c
 */
template<typename T, int ...A>
inline void removeRowFromEigenMatrix(Eigen::Matrix<T, A...>& m, unsigned int row) {
    unsigned int numRows = m.rows()-1;
    unsigned int numCols = m.cols();

    if( row < numRows )
        m.block(row,0,numRows-row,numCols) = m.block(row+1,0,numRows-row,numCols);

    m.conservativeResize(numRows,numCols);
}

/**
 * @brief removeColumnFromEigenMatrix
 * @param m
 * @param column
 * @link https://stackoverflow.com/questions/13290395/how-to-remove-a-certain-row-or-column-while-using-eigen-library-c
 */
template<typename T, int ...A>
inline void removeColumnFromEigenMatrix(Eigen::Matrix<T, A...>& m, unsigned int column) {
    unsigned int numRows = m.rows();
    unsigned int numCols = m.cols()-1;

    if(column < numCols )
        m.block(0,column,numRows,numCols-column) = m.block(0,column+1,numRows,numCols-column);

    m.conservativeResize(numRows,numCols);
}
#endif

}
