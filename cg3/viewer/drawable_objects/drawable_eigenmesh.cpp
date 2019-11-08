/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "drawable_eigenmesh.h"

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace cg3 {

CG3_INLINE DrawableEigenMesh::DrawableEigenMesh()
{
}

CG3_INLINE DrawableEigenMesh::DrawableEigenMesh(const SimpleEigenMesh& m) : EigenMesh(m) {
}


CG3_INLINE DrawableEigenMesh::DrawableEigenMesh(const EigenMesh& m) : EigenMesh(m)
{
}

CG3_INLINE DrawableEigenMesh::DrawableEigenMesh(const char* filename) : EigenMesh(filename)
{
}

CG3_INLINE DrawableEigenMesh::DrawableEigenMesh(const std::string& filename)  : EigenMesh(filename)
{
}

CG3_INLINE void DrawableEigenMesh::draw() const
{
    DrawableMesh::draw(V.rows(), F.rows(), V.data(), F.data(), NV.data(), CV.data(), NF.data(), CF.data(), bb.min(), bb.max());
}

CG3_INLINE Point3d DrawableEigenMesh::sceneCenter() const
{
    if (bb.isValid())
        return bb.center();
    else
        return Point3d();
}

CG3_INLINE double DrawableEigenMesh::sceneRadius() const
{
    if (bb.isValid())
        return bb.diag() / 2;
    else
        return -1;
}

} //namespace cg3
