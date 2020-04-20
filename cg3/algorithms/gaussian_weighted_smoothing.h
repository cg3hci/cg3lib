/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (alessandro85.tola@gmail.com)
 */
#ifndef CG3_GAUSSIAN_WEIGHTED_SMOOTHING_H
#define CG3_GAUSSIAN_WEIGHTED_SMOOTHING_H

#ifdef CG3_EIGENMESH_DEFINED

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

CG3_INLINE std::vector<double> vertexFunctionGaussianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double sigma,
        const double neighborDistance,
        const std::vector<std::vector<int>>& vvAdj);

CG3_INLINE std::vector<double> vertexFunctionGaussianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double sigma,
        const double neighborDistance);

} //namespace cg3

#endif

#ifndef CG3_STATIC
#define  CG3_GAUSSIAN_WEIGHTED_SMOOTHING_CPP "gaussian_weighted_smoothing.cpp"
#include  CG3_GAUSSIAN_WEIGHTED_SMOOTHING_CPP
#undef  CG3_GAUSSIAN_WEIGHTED_SMOOTHING_CPP
#endif //CG3_STATIC

#endif // CG3_GAUSSIAN_WEIGHTED_SMOOTHING_H
