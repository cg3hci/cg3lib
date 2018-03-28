/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_CGAL_SDF_H
#define CG3_CGAL_SDF_H

#include "polyhedron.h"

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

namespace cg3 {
namespace cgal {

std::vector<double> getSDFMap(const cgal::Polyhedron& mesh);

#ifdef  CG3_DCEL_DEFINED
std::map<const Dcel::Face*, double> getSDFMap(const Dcel& dcel);
#endif

#ifdef  CG3_EIGENMESH_DEFINED
std::vector<double> getSDFMap(const SimpleEigenMesh& m);
#endif

} //namespace cg3::cgal
} //namespace cg3

#endif // CG3_CGAL_SDF_H
