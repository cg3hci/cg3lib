/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_DATA_H
#define CG3_DCEL_DATA_H

#include <vector>
#include <cg3/meshes/mesh.h>

namespace cg3 {

class HalfEdge;
class Vertex;
class Face;

namespace internal {
class DcelData : public virtual cg3::Mesh
{
	friend class cg3::Vertex;
	friend class cg3::HalfEdge;
	friend class cg3::Face;
protected:
	//Data
	#ifdef NDEBUG
	std::vector<Point3d> vertexCoordinates;
	std::vector<Vec3d> vertexNormals;
	std::vector<Color> vertexColors;
	std::vector<Vec3d> faceNormals;
	std::vector<Color> faceColors;
	#endif
};

} //namespace cg3::internal
} //namespace cg3

#endif // CG3_DCEL_DATA_H
