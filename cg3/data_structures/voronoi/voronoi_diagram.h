/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VORONOI_DIAGRAM_H
#define CG3_VORONOI_DIAGRAM_H

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

class VoronoiDiagram
{
public:
    //ids for the external walls of the voronoi diagram
    static const int MIN_X = -1, MAX_X = -2;
    static const int MIN_Y = -3, MAX_Y = -4;
    static const int MIN_Z = -5, MAX_Z = -6;


    VoronoiDiagram(const BoundingBox& bb, uint nPoints = 100);
    template<class Container>
    VoronoiDiagram(const Container& c);
    template<class Iterator>
    VoronoiDiagram(Iterator begin, Iterator end);

    uint numSites() const;
    const VoronoiCell& cell(uint i);
    const VoronoiCell& cell(const cg3::Pointd& site);

    std::vector<VoronoiCell>::const_iterator begin() const;
    std::vector<VoronoiCell>::const_iterator end() const;


protected:

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
};

inline VoronoiDiagram::VoronoiDiagram(const BoundingBox& bb, uint nPoints) :
    bb(bbInitializer(bb)),
    container(this->bb.minX(), this->bb.maxX(),
              this->bb.minY(), this->bb.maxY(),
              this->bb.minZ(), this->bb.maxZ(),
              6, 6, 6, false, false, false,
              nPoints + 2)
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

}

#endif // CG3_VORONOI_DIAGRAM_H
