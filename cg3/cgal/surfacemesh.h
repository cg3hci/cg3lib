/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_SURFACEMESH_H
#define CG3_CGAL_SURFACEMESH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

namespace cg3 {

namespace cgal {

    typedef CGAL::Surface_mesh<CGAL::Exact_predicates_inexact_constructions_kernel::Point_3> SurfaceMesh;

    #ifdef  CG3_DCEL_DEFINED
    Dcel getDcelFromSurfaceMesh(const SurfaceMesh& poly);
    SurfaceMesh getSurfaceMeshFromDcel(const Dcel& d);
    #endif

    #ifdef  CG3_EIGENMESH_DEFINED

    #endif
}

}

#endif // CG3_CGAL_SURFACEMESH_H
