/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_VCGLIB_TRIANGLEEDGEMESHTYPE_H
#define CG3_VCGLIB_TRIANGLEEDGEMESHTYPE_H

#include <vcg/complex/complex.h>

namespace cg3 {
namespace vcglib {


/* ----- Triangle edge mesh ----- */

class TriangleEdgeVertex;
class TriangleEdgeFace;
class TriangleEdgeEdge;

struct MyTriangleEdgeTypes : public vcg::UsedTypes<
        vcg::Use<TriangleEdgeVertex>::AsVertexType,
        vcg::Use<TriangleEdgeEdge>::AsEdgeType,
        vcg::Use<TriangleEdgeFace>::AsFaceType>{};

class TriangleEdgeVertex : public vcg::Vertex<
        MyTriangleEdgeTypes,
        vcg::vertex::Coord3d,
        vcg::vertex::Normal3d,
        vcg::vertex::VFAdj,
        vcg::vertex::VEAdj,
        vcg::vertex::Color4b,
        vcg::vertex::Qualityd,
        vcg::vertex::BitFlags,
        vcg::vertex::CurvatureDird>{};

class TriangleEdgeEdge : public vcg::Edge<
        MyTriangleEdgeTypes,
        vcg::edge::VertexRef,
        vcg::edge::VEAdj,
        vcg::edge::EEAdj,
        vcg::edge::BitFlags> {};

class TriangleEdgeFace : public vcg::Face<
        MyTriangleEdgeTypes,
        vcg::face::VertexRef,
        vcg::face::Normal3d,
        vcg::face::Color4b,
        vcg::face::Qualityd,
        vcg::face::BitFlags,
        vcg::face::FFAdj,
        vcg::face::VFAdj,
        vcg::face::CurvatureDird,
        vcg::face::Mark,
        vcg::face::WedgeTexCoord2f> {};

class TriangleEdgeMesh : public vcg::tri::TriMesh<
        std::vector<TriangleEdgeVertex>,
        std::vector<TriangleEdgeEdge>,
        std::vector<TriangleEdgeFace> > {};

}
}

#endif // CG3_VCGLIB_TRIANGLEEDGEMESHTYPE_H
