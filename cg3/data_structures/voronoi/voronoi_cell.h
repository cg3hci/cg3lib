/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VORONOI_CELL_H
#define CG3_VORONOI_CELL_H

#include <cg3/geometry/bounding_box.h>

namespace cg3 {
#ifdef CG3_DCEL_DEFINED
class Dcel;
#endif

class VoronoiCell : public SerializableObject
{
    friend class VoronoiDiagram;

public:
    VoronoiCell();
    uint id() const;
    const cg3::Pointd& site() const;

    bool operator<(const VoronoiCell& o) const;

    #ifdef CG3_DCEL_DEFINED
    Dcel geometry() const;
    #endif

    std::vector<int>::const_iterator begin() const;
    std::vector<int>::const_iterator end() const;

    const std::vector<cg3::Pointd>& coords() const;
    int adjacentCell(uint i) const;
    const std::vector<uint>& face(uint i) const;

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
    VoronoiCell(int id, const cg3::Pointd& site);
    VoronoiCell(int id, const cg3::Pointd& site,
                const std::vector<cg3::Pointd>& _coords,
                const std::vector<std::vector<uint>>& faces);

    void clearAdjacences();
    void addAdjacent(int adj);
    void setAdjacents(const std::vector<int>& adjacences);
    void setGeometry(const std::vector<cg3::Pointd>& _coords,
                     const std::vector<std::vector<uint>>& faces);

    uint _id;
    cg3::Pointd _site;
    cg3::BoundingBox bb;
    std::vector<int> adjacences;
    std::vector<cg3::Pointd> _coords;
    std::vector<std::vector<uint>> faces;
};

}

#endif // CG3_VORONOI_CELL_H
