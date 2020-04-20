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
#include <cg3/algorithms/normalization.h>

namespace cg3 {

#ifdef CG3_EIGENMESH_DEFINED

/**
 * @brief Compute saliency
 * @param mesh Input mesh
 * @param sigma Maximum distance of a vertex to be counted as neighbor in the saliency calculation
 * @param meanCurvature Mean curvature values
 * @return Saliency
*/
CG3_INLINE std::vector<double> computeSaliency(
        const EigenMesh& mesh,
        const std::vector<double>& meanCurvature,
        const double sigma)
{
    std::vector<double> gaussianWeighted1 = cg3::vertexFunctionGaussianSmoothing(mesh, meanCurvature, 1, sigma, sigma * 2);
    std::vector<double> gaussianWeighted2 = cg3::vertexFunctionGaussianSmoothing(mesh, meanCurvature, 1, sigma * 2, sigma * 2 * 2);

    std::vector<double> saliency(gaussianWeighted1.size());

    for (size_t i = 0; i < gaussianWeighted1.size(); i++) {
        saliency[i] = std::abs(gaussianWeighted2[i] - gaussianWeighted1[i]);
    }

    return saliency;
}

/**
 * @brief Compute saliency
 * @param mesh Input mesh
 * @param sigma Maximum distance of a vertex to be counted as neighbor in the saliency calculation
 * @param nRing Ring for computing the curvature
 * @return Saliency
*/
CG3_INLINE std::vector<double> computeSaliency(
        const EigenMesh& mesh,
        const double sigma,
        const unsigned int nRing)
{
    std::vector<double> meanCurvature = cg3::libigl::meanVertexCurvature(mesh, nRing);

    return cg3::computeSaliency(mesh, meanCurvature, sigma);
}


/**
 * @brief Compute multi-scale saliency
 * @param mesh Input mesh
 * @param sigma Maximum distance of a vertex to be counted as neighbor in the saliency calculation
 * @param nRing Ring for computing the curvature
 * @return Saliency
*/
CG3_INLINE std::vector<double> computeSaliencyMultiScale(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& meanCurvature,
        const std::vector<std::vector<int>>& vvAdj,
        const unsigned int nScales)
{
    double epsilon = (mesh.boundingBox().diag() * 0.003);

    //Calculate sigmas
    std::vector<double> sigma(nScales);
    for(size_t i = 0; i < nScales; i++){
        sigma[i] = epsilon * (i + 2);
    }

    //Calculate saliencies for each scale
    std::vector<std::vector<double>> saliencies(nScales);
    for(size_t i = 0; i < nScales; i++){
        saliencies[i] = cg3::computeSaliency(mesh, meanCurvature, sigma[i]);
    }

    //Find min and max saliencies
    std::vector<std::vector<double>> normalizedSaliencies(nScales);
    for (size_t i = 0; i < saliencies.size(); i++) {
        normalizedSaliencies[i] = cg3::linearNormalization(saliencies[i]);
    }

    //Find average local maximas
    std::vector<std::vector<double>> localMaximas(nScales, std::vector<double>(mesh.numberVertices(), -std::numeric_limits<double>::max()));
    for(size_t i = 0; i < nScales; i++) {
        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++) {
            //Current point being evaluated
            cg3::Point3d p = mesh.vertex(vId);

            //Stack
            std::vector<int> stack;
            std::vector<bool> visited(mesh.numberVertices(), false);

            //Initializing with the current vertex
            stack.push_back(vId);
            visited[vId] = true;

            while (!stack.empty()){
                int currentVertex = stack.back();
                stack.pop_back();

                cg3::Point3d currentPoint = mesh.vertex(currentVertex);

                for(size_t j = 0; j < vvAdj[currentVertex].size(); j++){
                    int adjVId = vvAdj[currentVertex][j];

                    if(!visited[adjVId]) {
                        double distance = mesh.vertex(vId).dist(mesh.vertex(adjVId));

                        if (distance <= sigma[i]) {
                            stack.push_back(vvAdj[currentVertex][j]);
                            visited[vvAdj[currentVertex][j]] = true;
                        }
                    }
                }

                localMaximas[i][vId] = std::max(localMaximas[i][vId], normalizedSaliencies[i][currentVertex]);
            }
        }
    }

    //Multiply for non-linear normalization factor
    for (size_t i = 0; i < nScales; i++) {
        double avgLocalMaxima = 0; //Local maxima average
        unsigned int nLocalMaxima = 0;
        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++) {
            if (localMaximas[i][vId] < 1) {
                avgLocalMaxima += localMaximas[i][vId];
                nLocalMaxima++;
            }
        }
        avgLocalMaxima /= nLocalMaxima;

        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++) {
            normalizedSaliencies[i][vId] *= (1 - avgLocalMaxima) * (1 - avgLocalMaxima);
        }
    }

    //Compute final result
    std::vector<double> saliencyMultiScale(mesh.numberVertices(), 0.0);
    for (size_t i = 0; i < nScales; i++) {
        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++) {
            saliencyMultiScale[vId] += normalizedSaliencies[i][vId];
        }
    }

    return saliencyMultiScale;
}

/**
 * @brief Compute multi-scale saliency
 * @param mesh Input mesh
 * @param sigma Maximum distance of a vertex to be counted as neighbor in the saliency calculation
 * @param nRing Ring for computing the curvature
 * @return Saliency
*/
CG3_INLINE std::vector<double> computeSaliencyMultiScale(
        const cg3::EigenMesh& mesh,
        const std::vector<std::vector<int>>& vvAdj,
        const unsigned int nRing,
        const unsigned int nScales)
{
    std::vector<double> meanCurvature = cg3::libigl::meanVertexCurvature(mesh, nRing);
    return computeSaliencyMultiScale(mesh, meanCurvature, vvAdj, nScales);
}

/**
 * @brief Compute multi-scale saliency
 * @param mesh Input mesh
 * @param sigma Maximum distance of a vertex to be counted as neighbor in the saliency calculation
 * @param nRing Ring for computing the curvature
 * @return Saliency
*/
CG3_INLINE std::vector<double> computeSaliencyMultiScale(
        const cg3::EigenMesh& mesh,
        const unsigned int nRing,
        const unsigned int nScales)
{
    std::vector<std::vector<int>> vvAdj = cg3::libigl::vertexToVertexAdjacencies(mesh);
    return computeSaliencyMultiScale(mesh, vvAdj, nRing, nScales);
}


#endif

}
