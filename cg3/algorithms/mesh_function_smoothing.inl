/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (alessandro85.tola@gmail.com)
 */
#include "mesh_function_smoothing.h"

#ifdef CG3_LIBIGL_DEFINED
#include <cg3/libigl/mesh_adjacencies.h>
#endif

namespace cg3 {

/**
 * @brief Smooth of a function over a mesh (defined on vertices), using a gaussian weighted
 * function
 * @param mesh Input mesh
 * @param function Input function defined on vertices
 * @param iterations Iterations
 * @param sigma Standard deviation of the gaussian function
 * @param neighborDistance Maximum distance of a vertex to be counted as neighbor
 * @param vvAdj Vertex-vertex adjacencies of the mesh
 * @return Gaussian weighted value of the function for each vertex. If it was impossible
 * to find a value (denomination equals 0 while computing) the original value is returned.
 */
inline std::vector<double> vertexFunctionGaussianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double sigma,
        const double neighborDistance,
        const std::vector<std::vector<int>>& vvAdj)
{
    std::vector<double> gaussianWeighted = function;

    for (unsigned int it = 0; it < iterations; it++) {
        std::vector<double> lastValues = gaussianWeighted;

        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++){
            double numerator = 0;
            double denominator = 0;

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

                double distance = p.dist(currentPoint);
                double expression = std::exp(-(distance * distance) / (2.0 * sigma * sigma));

                numerator += lastValues[currentVertex] * expression;
                denominator += expression;

                for(size_t j = 0; j < vvAdj[currentVertex].size(); j++){
                    int adjVId = vvAdj[currentVertex][j];

                    if(!visited[adjVId]) {
                        double distance = mesh.vertex(vId).dist(mesh.vertex(adjVId));

                        if (distance <= neighborDistance) {
                            stack.push_back(vvAdj[currentVertex][j]);
                            visited[vvAdj[currentVertex][j]] = true;
                        }
                    }
                }
            }

            if (denominator != 0) {
                gaussianWeighted[vId] = numerator / denominator;
            }
            else {
                gaussianWeighted[vId] = lastValues[vId];
            }
        }
    }

    return gaussianWeighted;
}

#ifdef CG3_LIBIGL_DEFINED

/**
 * @brief Smooth of a function over a mesh, using a gaussian weighted function
 * @param mesh Input mesh
 * @param function Input function defined on vertices
 * @param iterations Iterations
 * @param sigma Standard deviation of the gaussian function
 * @param neighborDistance Maximum distance of a vertex to be counted as neighbor
 * @param vvAdj Vertex-vertex adjacencies of the mesh
 * @return Gaussian weighted value of the function for each vertex.
 */
inline std::vector<double> vertexFunctionGaussianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double sigma,
        const double neighborDistance)
{
    std::vector<std::vector<int>> vvAdj = cg3::libigl::vertexToVertexAdjacencies(mesh);
    return vertexFunctionGaussianSmoothing(mesh, function, iterations, sigma, neighborDistance, vvAdj);
}

#endif

/**
 * @brief Smooth of a function over a mesh (defined on vertices), using a laplacian smoothing
 * @param mesh Input mesh
 * @param function Input function defined on vertices
 * @param iterations Iterations
 * @param weight Weight for each vertex for its value
 * @param vvAdj Vertex-vertex adjacencies of the mesh
 * @return Laplacian smoothed value of the function for each vertex.
 */
template<class T>
std::vector<T> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<T>& function,
        const unsigned int iterations,
        const double weight,
        const std::vector<std::vector<int>>& vvAdj)
{
    std::vector<T> laplacianValue = function;

    for (unsigned int it = 0; it < iterations; it++) {
        std::vector<T> lastValues = laplacianValue;

        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++) {
            T adjValue = 0;

            for(size_t j = 0; j < vvAdj[vId].size(); j++) {
                unsigned int adjId = vvAdj[vId][j];

                adjValue += lastValues[adjId];
            }

            adjValue /= vvAdj[vId].size();

            laplacianValue[vId] = (weight * lastValues[vId]) + ((1 - weight) * adjValue);
        }
    }

    return laplacianValue;
}

#ifdef CG3_LIBIGL_DEFINED
/**
 * @brief Smooth of a function over a mesh, using a gaussian weighted function
 * @param mesh Input mesh
 * @param function Input function defined on vertices
 * @param iterations Iterations
 * @param weight Weight for each vertex for its value
 * @param vvAdj Vertex-vertex adjacencies of the mesh
 * @return Laplacian smoothed value of the function for each vertex.
 */
template<class T>
std::vector<T> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<T>& function,
        const double weight,
        const unsigned int iterations)
{
    std::vector<std::vector<int>> vvAdj = cg3::libigl::vertexToVertexAdjacencies(mesh);
    return vertexFunctionLaplacianSmoothing(mesh, function, iterations, weight, vvAdj);
}

#endif

}
