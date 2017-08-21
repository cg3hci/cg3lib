#ifndef MESHCONVERSIONS_H
#define MESHCONVERSIONS_H

#include <cinolib/meshes/trimesh/trimesh.h>

#ifdef EIGENMESH_DEFINED
#include <eigenmesh/eigenmesh.h>
#endif //EIGENMESH_DEFINED

#ifdef DCEL_DEFINED
#include <dcel/dcel.h>
#endif //DCEL_DEFINED

namespace MeshConversions {
    #ifdef EIGENMESH_DEFINED
    void eigenMeshToTrimesh(cinolib::Trimesh& m, const SimpleEigenMesh& simpleEigenMesh);
    #endif //EIGENMESH_DEFINED

    #ifdef DCEL_DEFINED
    void dcelToTrimesh(cinolib::Trimesh& m, const Dcel &d);
    #endif //DCEL_DEFINED
}

#endif // MESHCONVERSIONS_H
