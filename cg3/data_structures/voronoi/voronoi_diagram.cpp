/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "voronoi_diagram.h"

#include "internal/voro_parser.h"

namespace cg3 {

uint VoronoiDiagram::numSites() const
{
    return cells.size();
}

const VoronoiCell& VoronoiDiagram::cell(uint i)
{
    return cells[i];
}

const VoronoiCell &VoronoiDiagram::cell(const Pointd &site)
{
    assert(mapCells.find(site) != mapCells.end());
    return cells[mapCells[site]];
}

void VoronoiDiagram::addSite(const Pointd &p)
{
    addSite(cells.size(), p);
    finalize();
}

std::vector<VoronoiCell>::const_iterator VoronoiDiagram::begin() const
{
    return cells.begin();
}

std::vector<VoronoiCell>::const_iterator VoronoiDiagram::end() const
{
    return cells.end();
}

void VoronoiDiagram::addSite(uint i, const Pointd &site)
{
    if (bb.isInside(site) && mapCells.find(site) == mapCells.end()) {
        container.put(i, site.x(), site.y(), site.z());
        cells.push_back(VoronoiCell(i, site));
        mapCells[site] = i;
    }
}

void VoronoiDiagram::finalize()
{
    std::vector<std::vector<cg3::Pointd>> vertices = internal::parseAllVertices(container);
    std::vector<std::vector<std::vector<uint>>> faces = internal::parseAllFaces(container);
    std::vector<std::vector<int>> adjs = internal::parseAdjacences(container);

    assert(faces.size() == cells.size());
    assert(adjs.size() == cells.size());

    for (uint i = 0; i < cells.size(); i++) {
        cells[i].setGeometry(vertices[i], faces[i]);
        cells[i].setAdjacents(adjs[i]);
    }
}

}
