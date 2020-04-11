/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (alessandro85.tola@gmail.com)
 */
#include "saliency.h"

#include <cg3/libigl/mesh_adjacencies.h>
#include <cg3/libigl/curvature.h>
#include <cg3/algorithms/gaussian_weighted_smoothing.h>

namespace cg3 {

#ifdef CG3_EIGENMESH_DEFINED

/**
 * @brief Smooth of a function over a mesh (defined on vertices), using a gaussian weighted
 * function
 * @param mesh Input mesh
 * @param sigma Maximum distance of a vertex to be counted as neighbor in the saliency calculation
 * @param nRing Ring for computing the curvature
 * @return Saliency
*/
std::vector<double> computeSaliency(const EigenMesh& mesh, const double sigma, const unsigned int nRing)
{
    std::vector<double> meanCurvature = cg3::libigl::meanVertexCurvature(mesh, nRing);
    std::vector<double> gaussianWeighted1 = cg3::vertexGaussianWeightedSmoothing(mesh, meanCurvature, sigma, sigma * 2);
    std::vector<double> gaussianWeighted2 = cg3::vertexGaussianWeightedSmoothing(mesh, meanCurvature, sigma * 2, sigma * 2 * 2);

    std::vector<double> saliency(gaussianWeighted1.size());

    for (size_t i = 0; i < gaussianWeighted1.size(); i++) {
        saliency[i] = std::abs(gaussianWeighted2[i] - gaussianWeighted1[i]);
    }

    return saliency;
}

#endif

}
