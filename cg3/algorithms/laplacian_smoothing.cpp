/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "laplacian_smoothing.h"

#ifdef CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#include <cg3/libigl/mesh_adjacencies.h>
#endif

namespace cg3 {

#ifdef CG3_DCEL_DEFINED

/**
 * @brief Computes nIt iterations of laplacian smoothing on the mesh
 * @param [in/out] mesh: mesh on which the smoothing will be applied
 * @param [in] nIt: number of iterations
 */
CG3_INLINE void laplacianSmoothing(cg3::Dcel& mesh, unsigned int nIt)
{
	std::map<uint, cg3::Point3d> mapCoords;

	for (uint i = 0; i < nIt; ++i){
		for (const cg3::Dcel::Vertex* v : mesh.vertexIterator()){
			cg3::Point3d avg;
			uint n = 0;
			for (const cg3::Dcel::Vertex* adj : v->adjacentVertexIterator()){
				avg += adj->coordinate();
				n++;
			}
			if (n > 0){
				avg /= n;
				mapCoords[v->id()] = avg;
			}
		}
		for (const std::pair<uint, cg3::Point3d>& p : mapCoords){
			mesh.vertex(p.first)->setCoordinate(p.second);
		}
	}
	mesh.updateFaceNormals();
	mesh.updateFaceAreas();
	mesh.updateVertexNormals();
	mesh.updateBoundingBox();
}

/**
 * @brief Computes nIt iterations of laplacian smoothing on the mesh and returns the result
 * @param [in] mesh: mesh on which the smoothing will be applied
 * @param [in] nIt: number of iterations
 * @return a mesh with the smoothing applied
 */
CG3_INLINE Dcel laplacianSmoothing(const Dcel& mesh, unsigned int nIt)
{
	cg3::Dcel output = mesh;
	laplacianSmoothing(output, nIt);
	return output;
}

#endif


#ifdef CG3_EIGENMESH_DEFINED

/**
 * @brief Smooth of a function over a mesh (defined on vertices), using a laplacian smoothing
 * @param mesh Input mesh
 * @param function Input function defined on vertices
 * @param iterations Iterations
 * @param weight Weight for each vertex for its value
 * @param vvAdj Vertex-vertex adjacencies of the mesh
 * @return Laplacian smoothed value of the function for each vertex.
 */
CG3_INLINE std::vector<double> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const unsigned int iterations,
        const double weight,
        const std::vector<std::vector<int>>& vvAdj)
{
    std::vector<double> laplacianValue = function;

    for (unsigned int it = 0; it < iterations; it++) {
        std::vector<double> lastValues = laplacianValue;

        for(unsigned int vId = 0; vId < mesh.numberVertices(); vId++) {
            double adjValue = 0;

            for(size_t j = 0; j < vvAdj[vId].size(); j++) {
                double adjId = vvAdj[vId][j];

                adjValue += lastValues[adjId];
            }

            adjValue /= vvAdj[vId].size();

            laplacianValue[vId] = (weight * lastValues[vId]) + ((1 - weight) * adjValue);
        }
    }

    return laplacianValue;
}

/**
 * @brief Smooth of a function over a mesh, using a gaussian weighted function
 * @param mesh Input mesh
 * @param function Input function defined on vertices
 * @param iterations Iterations
 * @param weight Weight for each vertex for its value
 * @param vvAdj Vertex-vertex adjacencies of the mesh
 * @return Laplacian smoothed value of the function for each vertex.
 */
CG3_INLINE std::vector<double> vertexFunctionLaplacianSmoothing(
        const cg3::EigenMesh& mesh,
        const std::vector<double>& function,
        const double weight,
        const unsigned int iterations)
{
    std::vector<std::vector<int>> vvAdj = cg3::libigl::vertexToVertexAdjacencies(mesh);
    return vertexFunctionLaplacianSmoothing(mesh, function, iterations, weight, vvAdj);
}

#endif


}
