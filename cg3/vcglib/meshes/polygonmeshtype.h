/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_VCGLIB_POLYGONMESHTYPE_H
#define CG3_VCGLIB_POLYGONMESHTYPE_H

#include <vcg/complex/complex.h>

namespace cg3 {
namespace vcglib {

/* ----- Polygon mesh ----- */

class PolyVertex;
class PolyFace;
class PolyEdge;

struct MyPolyTypes : public vcg::UsedTypes<
        vcg::Use<PolyVertex>::AsVertexType,
        vcg::Use<PolyEdge>::AsEdgeType,
        vcg::Use<PolyFace>::AsFaceType>{};

class PolyVertex : public vcg::Vertex<MyPolyTypes,
        vcg::vertex::Coord3d,
        vcg::vertex::Normal3d,
        vcg::vertex::Color4b,
        vcg::vertex::Qualityd,
        vcg::vertex::BitFlags,
        vcg::vertex::VFAdj,
        vcg::vertex::CurvatureDird>{};

class PolyFace : public vcg::Face<
        MyPolyTypes,
        vcg::face::PolyInfo,
        vcg::face::VertexRef,
        vcg::face::Normal3d,
        vcg::face::Color4b,
        vcg::face::Qualityd,
        vcg::face::BitFlags,
        vcg::face::PFVAdj,
        vcg::face::PFFAdj,
        vcg::face::PVFAdj,
        vcg::face::CurvatureDird,
        vcg::face::Mark,
        vcg::face::WedgeTexCoord2d> {};

class PolyEdge : public vcg::Edge<
        MyPolyTypes,
        vcg::edge::VertexRef,
        vcg::edge::VEAdj,
        vcg::edge::EEAdj,
        vcg::edge::BitFlags> {};

class PolyMesh : public vcg::tri::TriMesh<
        std::vector<PolyVertex>,
        std::vector<PolyEdge>,
        std::vector<PolyFace>> {};

}
}

#endif // CG3_VCGLIB_POLYGONMESHTYPE_H
