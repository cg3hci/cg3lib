/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_tetmesh.h"

namespace cg3 {
namespace cino {

CG3_INLINE DrawableTetMesh::DrawableTetMesh()
{
}

CG3_INLINE DrawableTetMesh::DrawableTetMesh(const std::string& s)
{
    this->load(s.c_str());
    this->updateGL();
}

CG3_INLINE void DrawableTetMesh::draw() const
{
    DrawableTetmesh::draw();
}

CG3_INLINE void DrawableTetMesh::draw(const float f) const
{
    DrawableTetmesh::draw(f);
}

CG3_INLINE Point3d DrawableTetMesh::sceneCenter() const
{
    return DrawableTetmesh::scene_center();
}

CG3_INLINE double DrawableTetMesh::sceneRadius() const
{
    return (double) DrawableTetmesh::scene_radius();
}

} //namespace cg3::cino
} //namespace cg3
