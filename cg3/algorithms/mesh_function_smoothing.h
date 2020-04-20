/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (alessandro85.tola@gmail.com)
 */
#ifndef CG3_MESH_FUNCTION_SMOOTHING_H
#define CG3_MESH_FUNCTION_SMOOTHING_H

#ifdef CG3_EIGENMESH_DEFINED

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

std::vector<double> vertexFunctionGaussianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double sigma,
        const double neighborDistance,
        const std::vector<std::vector<int>>& vvAdj);

#ifdef CG3_LIBIGL_DEFINED
std::vector<double> vertexFunctionGaussianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double sigma,
        const double neighborDistance);
#endif


template<class T>
std::vector<T> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<T>& function,
        const unsigned int iterations,
        const double weight,
        const std::vector<std::vector<int>>& vvAdj);

#ifdef CG3_LIBIGL_DEFINED

template<class T>
std::vector<double> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<T>& function,
        const unsigned int iterations,
        const double weight);

#endif

} //namespace cg3

#endif

#include "mesh_function_smoothing.cpp"

#endif // CG3_MESH_FUNCTION_SMOOTHING_H
