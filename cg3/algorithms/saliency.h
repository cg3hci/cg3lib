/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (alessandro85.tola@gmail.com)
 */
#ifndef CG3_SALIENCY_H
#define CG3_SALIENCY_H

#ifdef CG3_EIGENMESH_DEFINED

#include <cg3/meshes/eigenmesh/eigenmesh.h>

namespace cg3 {

std::vector<double> computeSaliency(
        const EigenMesh& mesh,
        const std::vector<double>& meanCurvature,
        const double sigma);

std::vector<double> computeSaliency(
        const EigenMesh& mesh,
        const double sigma,
        const unsigned int nRing = 5);


std::vector<double> computeSaliencyMultiScale(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& meanCurvature,
        const std::vector<std::vector<int>>& vvAdj,
        const unsigned int nScales = 5);

std::vector<double> computeSaliencyMultiScale(
        const cg3::EigenMesh& mesh,
        const std::vector<std::vector<int>>& vvAdj,
        const unsigned int nRing = 5,
        const unsigned int nScales = 5);

std::vector<double> computeSaliencyMultiScale(
        const cg3::EigenMesh& mesh,
        const unsigned int nRing = 5,
        const unsigned int nScales = 5);


} //namespace cg3

#endif

#ifndef CG3_STATIC
#define  CG3_SALIENCY_CPP "saliency.cpp"
#include  CG3_SALIENCY_CPP
#undef  CG3_SALIENCY_CPP
#endif //CG3_STATIC

#endif // CG3_SALIENCY_H
