/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LAPLACIAN_SMOOTHING_H
#define CG3_LAPLACIAN_SMOOTHING_H

#include <cg3/cg3lib.h>

#include <vector>

namespace cg3 {

#ifdef CG3_DCEL_DEFINED

class Dcel;

void laplacianSmoothing(cg3::Dcel& mesh, unsigned int nIt = 1);
cg3::Dcel laplacianSmoothing(const cg3::Dcel& mesh, unsigned int nIt = 1);

#endif


#ifdef CG3_EIGENMESH_DEFINED

class EigenMesh;
std::vector<double> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double weight,
        const std::vector<std::vector<int>>& vvAdj);

std::vector<double> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double weight);

#endif

} //namespace cg3

#ifndef CG3_STATIC
#define  CG3_LAPLACIAN_SMOOTHING_CPP "laplacian_smoothing.cpp"
#include  CG3_LAPLACIAN_SMOOTHING_CPP
#undef  CG3_LAPLACIAN_SMOOTHING_CPP
#endif //CG3_STATIC

#endif // CG3_LAPLACIAN_SMOOTHING_H
