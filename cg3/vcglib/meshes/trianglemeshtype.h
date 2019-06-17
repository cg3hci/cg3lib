/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_VCGLIB_TRIANGLEMESHTYPE_H
#define CG3_VCGLIB_TRIANGLEMESHTYPE_H

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#include <vcg/complex/complex.h>
#pragma GCC diagnostic pop
#else
#include <vcg/complex/complex.h>
#endif

namespace cg3 {
namespace vcglib {


/* ----- Triangle mesh ----- */

class TriangleVertex;
class TriangleFace;
struct MyTriangleTypes : public vcg::UsedTypes<
        vcg::Use<TriangleVertex>::AsVertexType,
        vcg::Use<TriangleFace>::AsFaceType>{};

class TriangleVertex : public vcg::Vertex<
        MyTriangleTypes,
        vcg::vertex::Coord3d,
        vcg::vertex::Normal3d,
        vcg::vertex::VFAdj,
        vcg::vertex::Color4b,
        vcg::vertex::Qualityd,
        vcg::vertex::BitFlags,
        vcg::vertex::CurvatureDird>{};

class TriangleFace : public vcg::Face<
        MyTriangleTypes,
        vcg::face::VertexRef,
        vcg::face::Normal3d,
        vcg::face::Color4b,
        vcg::face::Qualityd,
        vcg::face::BitFlags,
        vcg::face::FFAdj,
        vcg::face::VFAdj,
        vcg::face::CurvatureDird,
        vcg::face::Mark,
        vcg::face::WedgeTexCoord2d> {};

class TriangleMesh : public vcg::tri::TriMesh<
        std::vector<TriangleVertex>,
        std::vector<TriangleFace> > {};

}
}

#endif // CG3_VCGLIB_TRIANGLEMESHTYPE_H
