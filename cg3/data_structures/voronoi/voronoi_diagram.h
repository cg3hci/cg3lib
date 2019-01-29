/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VORONOI_DIAGRAM_H
#define CG3_VORONOI_DIAGRAM_H

#include <limits>

#include "voronoi_cell.h"
#include <cg3/geometry/bounding_box.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <voro++.hh>
#pragma GCC diagnostic pop
#else
#include <voro++.hh>
#endif

namespace cg3 {

class VoronoiDiagram : virtual public SerializableObject
{
public:
    //ids for the external walls of the voronoi diagram
    static const int MIN_X = -1, MAX_X = -2;
    static const int MIN_Y = -3, MAX_Y = -4;
    static const int MIN_Z = -5, MAX_Z = -6;

    VoronoiDiagram();
    VoronoiDiagram(const BoundingBox& bb, uint nPoints = 500);
    template<class Container>
    VoronoiDiagram(const Container& c);
    template<class Iterator>
    VoronoiDiagram(Iterator begin, Iterator end);
    VoronoiDiagram(const VoronoiDiagram& vd);

    uint numSites() const;
    const VoronoiCell& cell(uint i);
    const VoronoiCell& cell(const cg3::Pointd& site);

    void addSite(const cg3::Pointd& p);
    template<class Container>
    void addSites(const Container& c);
    template<class Iterator>
    void addSites(Iterator begin, Iterator end);

    void clear();

    VoronoiDiagram& operator=(const VoronoiDiagram& vd);

    std::vector<VoronoiCell>::const_iterator begin() const;
    std::vector<VoronoiCell>::const_iterator end() const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    const int DEFAULT_N_POINTS = 1000;
    static BoundingBox bbInitializer(BoundingBox bb){
        bb.min() -= cg3::Pointd(1,1,1);
        bb.max() += cg3::Pointd(1,1,1);
        return bb;
    }

    void addSite(uint i, const cg3::Pointd& site);
    virtual void finalize();
    cg3::BoundingBox bb;
    voro::container container;
    std::vector<VoronoiCell> cells;
    std::map<cg3::Pointd, uint> mapCells;
    uint nPoints;
};

/**
 * @brief Default constructor Voronoi Diagram
 * Creates a Voronoi Diagram having as bounding box the double numeric limits,
 * zero sites and a maximum numer of sites od 1000.
 */
inline VoronoiDiagram::VoronoiDiagram() :
    bb(cg3::Pointd(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(),std::numeric_limits<double>::lowest()),
       cg3::Pointd(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max())),
    container(this->bb.minX(), this->bb.maxX(),
              this->bb.minY(), this->bb.maxY(),
              this->bb.minZ(), this->bb.maxZ(),
              6, 6, 6, false, false, false,
              DEFAULT_N_POINTS),
    nPoints(DEFAULT_N_POINTS)
{
}

/**
 * @brief Constructor of a Voronoi Diagram. Creates a Voronoi Diagram with the given
 * Bounding Box and the given maximum number of sites.
 * @param bb
 * @param nPoints
 */
inline VoronoiDiagram::VoronoiDiagram(const BoundingBox& bb, uint nPoints) :
    bb(bbInitializer(bb)),
    container(this->bb.minX(), this->bb.maxX(),
              this->bb.minY(), this->bb.maxY(),
              this->bb.minZ(), this->bb.maxZ(),
              6, 6, 6, false, false, false,
              nPoints + 2),
    nPoints(nPoints+2)
{
}

template<class Container>
VoronoiDiagram::VoronoiDiagram(const Container& c) :
    VoronoiDiagram(c.begin(), c.end())
{
}

template<class Iterator>
VoronoiDiagram::VoronoiDiagram(Iterator begin, Iterator end) :
    VoronoiDiagram(BoundingBox(begin, end), std::distance(begin, end))
{
    uint i = 0;
    for (Iterator it = begin; it != end; ++it, ++i){
        addSite(i, *it);
    }
    finalize();
}

template<class Container>
void VoronoiDiagram::addSites(const Container &c)
{
    addSites(c.begin(), c.end());
}

template<class Iterator>
void VoronoiDiagram::addSites(Iterator begin, Iterator end)
{
    uint i = cells.size();
    for (Iterator it = begin; it != end; ++it, ++i){
        addSite(i, *it);
    }
    finalize();
}

}

#endif // CG3_VORONOI_DIAGRAM_H
