/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "laplacian_smoothing.h"
#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {

/**
 * @brief Computes nIt iterations of laplacian smoothing on the mesh
 * @param [in/out] mesh: mesh on which the smoothing will be applied
 * @param [in] nIt: number of iterations
 */
void laplacianSmoothing(cg3::Dcel& mesh, unsigned int nIt)
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
Dcel laplacianSmoothing(const Dcel& mesh, unsigned int nIt)
{
	cg3::Dcel output = mesh;
	laplacianSmoothing(output, nIt);
	return output;
}

}
