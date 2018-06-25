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

DrawableEigenMesh::DrawableEigenMesh()
{
}

DrawableEigenMesh::DrawableEigenMesh(const SimpleEigenMesh& m) : EigenMesh(m) {
}


DrawableEigenMesh::DrawableEigenMesh(const EigenMesh& m) : EigenMesh(m)
{
}

DrawableEigenMesh::DrawableEigenMesh(const std::string& filename)  : EigenMesh(filename)
{
}

void DrawableEigenMesh::draw() const
{
    DrawableMesh::draw(V.rows(), F.rows(), V.data(), F.data(), NV.data(), CV.data(), NF.data(), CF.data(), bb.min(), bb.max());
}

Pointd DrawableEigenMesh::sceneCenter() const
{
    if (bb.isValid())
        return bb.center();
    else
        return Pointd();
}

double DrawableEigenMesh::sceneRadius() const
{
    if (bb.isValid())
        return bb.diag() / 2;
    else
        return -1;
}

bool DrawableEigenMesh::loadFromFile(const std::string& filename)
{
    return EigenMesh::loadFromFile(filename);
}

bool DrawableEigenMesh::loadFromObj(const std::string& filename)
{
    return EigenMesh::loadFromObj(filename);
}

bool DrawableEigenMesh::loadFromPly(const std::string& filename)
{
    return EigenMesh::loadFromPly(filename);
}

bool DrawableEigenMesh::saveOnObj(const std::string& filename) const
{
    return EigenMesh::saveOnObj(filename);
}

bool DrawableEigenMesh::saveOnPly(const std::string& filename) const
{
    return EigenMesh::saveOnPly(filename);
}

} //namespace cg3
