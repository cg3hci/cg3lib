/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "voronoi_cell3.h"

#include <cg3/utilities/const.h>

#ifdef CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel_builder.h>
#endif

namespace cg3 {
namespace voro {

CG3_INLINE VoronoiCell3::VoronoiCell3() :
    _id(0)
{
}

CG3_INLINE uint VoronoiCell3::id() const
{
    return _id;
}

CG3_INLINE const Point3d& VoronoiCell3::site() const
{
    return _site;
}

CG3_INLINE bool VoronoiCell3::operator<(const VoronoiCell3& o) const
{
    return _id < o._id;
}

#ifdef CG3_DCEL_DEFINED
CG3_INLINE cg3::Dcel VoronoiCell3::geometry() const
{
    DcelBuilder builder;
    for (const cg3::Point3d& p : _coords){
        builder.addVertex(p);
    }
    uint i = 0;
    for (const std::vector<uint>& face : faces)
        builder.addFace(face, cg3::GREY, adjacences[i++]);
    builder.finalize();
    return builder.dcel();
}
#endif

CG3_INLINE std::vector<int>::const_iterator VoronoiCell3::begin() const
{
    return adjacences.begin();
}

CG3_INLINE std::vector<int>::const_iterator VoronoiCell3::end() const
{
    return adjacences.end();
}

CG3_INLINE const std::vector<Point3d>&VoronoiCell3::coords() const
{
    return _coords;
}

CG3_INLINE int VoronoiCell3::adjacentCell(uint i) const
{
    return adjacences[i];
}

CG3_INLINE const std::vector<uint>&VoronoiCell3::face(uint i) const
{
    return faces[i];
}

CG3_INLINE void VoronoiCell3::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3VoronoiCell", binaryFile, _id, _site, bb, adjacences, _coords, faces);
}

CG3_INLINE void VoronoiCell3::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3VoronoiCell", binaryFile, _id, _site, bb, adjacences, _coords, faces);
}

CG3_INLINE VoronoiCell3::VoronoiCell3(int id, const Point3d& site) :
    _id(id), _site(site)
{
}

CG3_INLINE void VoronoiCell3::clearAdjacences()
{
    adjacences.clear();
}

CG3_INLINE void VoronoiCell3::addAdjacent(int adj)
{
    adjacences.push_back(adj);
}

CG3_INLINE void VoronoiCell3::setAdjacents(const std::vector<int>& adjacences)
{
    this->adjacences = adjacences;
}

CG3_INLINE void VoronoiCell3::setGeometry(
        const std::vector<Point3d>& coords,
        const std::vector<std::vector<uint> >& faces)
{
    this->_coords = coords;
    this->faces = faces;
    bb = BoundingBox3(_coords);
}

} //namespace cg3::voro
} //namespace cg3
