/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "voronoi_cell.h"

#include <cg3/utilities/const.h>

#ifdef CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel_builder.h>
#endif

namespace cg3 {

VoronoiCell::VoronoiCell() :
    _id(0)
{
}

uint VoronoiCell::id() const
{
    return _id;
}

const Pointd& VoronoiCell::site() const
{
    return _site;
}

bool VoronoiCell::operator<(const VoronoiCell& o) const
{
    return _id < o._id;
}

#ifdef CG3_DCEL_DEFINED
Dcel VoronoiCell::geometry() const
{
    DcelBuilder builder;
    for (const cg3::Pointd& p : _coords){
        builder.addVertex(p);
    }
    uint i = 0;
    for (const std::vector<uint>& face : faces)
        builder.addFace(face, cg3::GREY, adjacences[i++]);
    builder.finalize();
    return builder.dcel();
}
#endif

std::vector<int>::const_iterator VoronoiCell::begin() const
{
    return adjacences.begin();
}

std::vector<int>::const_iterator VoronoiCell::end() const
{
    return adjacences.end();
}

const std::vector<Pointd>&VoronoiCell::coords() const
{
    return _coords;
}

int VoronoiCell::adjacentCell(uint i) const
{
    return adjacences[i];
}

const std::vector<uint>&VoronoiCell::face(uint i) const
{
    return faces[i];
}

void VoronoiCell::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3VoronoiCell", binaryFile, _id, _site, bb, adjacences, _coords, faces);
}

void VoronoiCell::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3VoronoiCell", binaryFile, _id, _site, bb, adjacences, _coords, faces);
}

VoronoiCell::VoronoiCell(int id, const Pointd& site) :
    _id(id), _site(site)
{
}

void VoronoiCell::clearAdjacences()
{
    adjacences.clear();
}

void VoronoiCell::addAdjacent(int adj)
{
    adjacences.push_back(adj);
}

void VoronoiCell::setAdjacents(const std::vector<int>& adjacences)
{
    this->adjacences = adjacences;
}

void VoronoiCell::setGeometry(
        const std::vector<Pointd>& coords,
        const std::vector<std::vector<uint> >& faces)
{
    this->_coords = coords;
    this->faces = faces;
    bb = BoundingBox(_coords);
}

}
