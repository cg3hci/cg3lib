/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VORONOI_CELL3_H
#define CG3_VORONOI_CELL3_H

#include <cg3/geometry/bounding_box3.h>

namespace cg3 {

#ifdef CG3_DCEL_DEFINED
class Dcel;
#endif

namespace voro {

class VoronoiCell3 : public SerializableObject
{
	friend class VoronoiDiagram3;

public:
	VoronoiCell3();
    uint id() const;
    const cg3::Point3d& site() const;

	bool operator<(const VoronoiCell3& o) const;

    #ifdef CG3_DCEL_DEFINED
	cg3::Dcel geometry() const;
    #endif

    std::vector<int>::const_iterator begin() const;
    std::vector<int>::const_iterator end() const;

    const std::vector<cg3::Point3d>& coords() const;
    int adjacentCell(uint i) const;
    const std::vector<uint>& face(uint i) const;

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
	VoronoiCell3(int id, const cg3::Point3d& site);
	VoronoiCell3(int id, const cg3::Point3d& site,
                const std::vector<cg3::Point3d>& _coords,
                const std::vector<std::vector<uint>>& faces);

    void clearAdjacences();
    void addAdjacent(int adj);
    void setAdjacents(const std::vector<int>& adjacences);
    void setGeometry(const std::vector<cg3::Point3d>& _coords,
                     const std::vector<std::vector<uint>>& faces);

    uint _id;
    cg3::Point3d _site;
    cg3::BoundingBox3 bb;
    std::vector<int> adjacences;
    std::vector<cg3::Point3d> _coords;
    std::vector<std::vector<uint>> faces;
};

} //namespace cg3::voro
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_VORONOI_CELL3_CPP "voronoi_cell3.cpp"
#include CG3_VORONOI_CELL3_CPP
#undef CG3_VORONOI_CELL3_CPP
#endif //CG3_STATIC

#endif // CG3_VORONOI_CELL3_H
