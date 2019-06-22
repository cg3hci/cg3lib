/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "voronoi_diagram3.h"

#include "internal/voro_parser.h"

namespace cg3 {
namespace voro {

CG3_INLINE VoronoiDiagram3::VoronoiDiagram3(const VoronoiDiagram3& vd) :
    bb(vd.bb),
    container(this->bb.minX(), this->bb.maxX(),
              this->bb.minY(), this->bb.maxY(),
              this->bb.minZ(), this->bb.maxZ(),
              6, 6, 6, false, false, false,
              vd.nPoints),
    cells(vd.cells),
    mapCells(vd.mapCells),
    nPoints(vd.nPoints)
{

    for (uint i = 0; i < cells.size(); ++i){
        container.put(i, cells[i].site().x(), cells[i].site().y(), cells[i].site().z());
    }
    finalize();
}

CG3_INLINE uint VoronoiDiagram3::numSites() const
{
    return cells.size();
}

CG3_INLINE const VoronoiCell3& VoronoiDiagram3::cell(uint i)
{
    assert(i < cells.size());
    return cells[i];
}

CG3_INLINE const VoronoiCell3 &VoronoiDiagram3::cell(const Point3d &site)
{
    assert(mapCells.find(site) != mapCells.end());
    return cells[mapCells[site]];
}

CG3_INLINE void VoronoiDiagram3::addSite(const Point3d &p)
{
    addSite(cells.size(), p);
    finalize();
}

CG3_INLINE void VoronoiDiagram3::clear()
{
    container.clear();
    cells.clear();
    mapCells.clear();
}

CG3_INLINE VoronoiDiagram3& VoronoiDiagram3::operator=(const VoronoiDiagram3& vd)
{
    if (this != &vd){
        bb = vd.bb;
        cells = vd.cells;
        mapCells = vd.mapCells;
        nPoints = vd.nPoints;
        (&container)->~container();
		new (&container) ::voro::container(this->bb.minX(), this->bb.maxX(),
                                         this->bb.minY(), this->bb.maxY(),
                                         this->bb.minZ(), this->bb.maxZ(),
                                         6, 6, 6, false, false, false,
                                         nPoints);
        for (uint i = 0; i < cells.size(); ++i){
            container.put(i, cells[i].site().x(), cells[i].site().y(), cells[i].site().z());
        }
        finalize();
    }
    return *this;
}

CG3_INLINE std::vector<VoronoiCell3>::const_iterator VoronoiDiagram3::begin() const
{
    return cells.begin();
}

CG3_INLINE std::vector<VoronoiCell3>::const_iterator VoronoiDiagram3::end() const
{
    return cells.end();
}

CG3_INLINE void VoronoiDiagram3::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3VoronoiDiagram", binaryFile, bb, cells, mapCells, nPoints);
}

CG3_INLINE void VoronoiDiagram3::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3VoronoiDiagram", binaryFile, bb, cells, mapCells, nPoints);
    (&container)->~container();
	new (&container) ::voro::container(this->bb.minX(), this->bb.maxX(),
                                     this->bb.minY(), this->bb.maxY(),
                                     this->bb.minZ(), this->bb.maxZ(),
                                     6, 6, 6, false, false, false,
                                     nPoints);
    for (uint i = 0; i < cells.size(); ++i){
        container.put(i, cells[i].site().x(), cells[i].site().y(), cells[i].site().z());
    }
    finalize();
}

CG3_INLINE void VoronoiDiagram3::addSite(uint i, const Point3d &site)
{
    if (bb.isInside(site) && mapCells.find(site) == mapCells.end()) {
        container.put(i, site.x(), site.y(), site.z());
        cells.push_back(VoronoiCell3(i, site));
        mapCells[site] = i;
    }
}

CG3_INLINE void VoronoiDiagram3::finalize()
{
    std::vector<std::vector<cg3::Point3d>> vertices = internal::parseAllVertices(container);
    std::vector<std::vector<std::vector<uint>>> faces = internal::parseAllFaces(container);
    std::vector<std::vector<int>> adjs = internal::parseAdjacences(container);

    assert(faces.size() == cells.size());
    assert(adjs.size() == cells.size());

    for (uint i = 0; i < cells.size(); i++) {
        cells[i].setGeometry(vertices[i], faces[i]);
        cells[i].setAdjacents(adjs[i]);
    }
}

} //namespace cg3::voro
} //namespace cg3
