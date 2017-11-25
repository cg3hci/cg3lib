/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CONVEXHULL_H
#define CG3_CONVEXHULL_H

#include "cg3/meshes/dcel/dcel.h"
#include "cg3/data_structures/graphs/bipartite_graph.h"


namespace cg3 {

Dcel convexHull(const Dcel& inputDcel);

Dcel convexHull(std::vector<Pointd> points);

namespace internal {

double complanar(const Pointd &p0, const Pointd &p1, const Pointd &p2, const Pointd &p3);

bool see(const Dcel::Face* f, const Pointd &p);

void insertTet(Dcel &dcel, const Pointd &p0, const Pointd &p1, const Pointd &p2, const Pointd &p3);

void horizonEdgeList(std::vector<Dcel::HalfEdge*> &horizon, const std::set<Dcel::Face*>& visibleFaces, std::set<Dcel::Vertex*>& horizonVertex, const Pointd &next_point);

void calculateP(std::vector<std::set<Pointd> >& P, const BipartiteGraph<Pointd, Dcel::Face*>& cg, std::vector<Dcel::HalfEdge*> &horizonEdges);

void deleteVisibleFaces(Dcel & ch, std::set<Dcel::Vertex*>& horizonVertices, const std::set<Dcel::Face*>& visibleFaces, BipartiteGraph<Pointd, Dcel::Face*>& cg);

void insertNewFaces (Dcel & ch, std::vector<Dcel::HalfEdge*> & horizonEdges, const Pointd & p, BipartiteGraph<Pointd, Dcel::Face*>& cg, std::vector<std::set<Pointd> > & P);

}

}

#endif // ENGINE_H
