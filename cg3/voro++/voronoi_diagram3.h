/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VORONOI_DIAGRAM3_H
#define CG3_VORONOI_DIAGRAM3_H

#include <limits>

#include "voronoi_cell3.h"
#include <cg3/geometry/bounding_box3.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <voro++.hh>
#pragma GCC diagnostic pop
#else
#include <voro++.hh>
#endif

namespace cg3 {
namespace voro {

class VoronoiDiagram3 : virtual public SerializableObject
{
public:
    //ids for the external walls of the voronoi diagram
    static const int MIN_X = -1, MAX_X = -2;
    static const int MIN_Y = -3, MAX_Y = -4;
    static const int MIN_Z = -5, MAX_Z = -6;

	VoronoiDiagram3();
	VoronoiDiagram3(const BoundingBox3& bb, uint nPoints = 500);
    template<class Container>
	VoronoiDiagram3(const Container& c);
    template<class Iterator>
	VoronoiDiagram3(Iterator begin, Iterator end);
	VoronoiDiagram3(const VoronoiDiagram3& vd);

    uint numSites() const;
	const VoronoiCell3& cell(uint i);
	const VoronoiCell3& cell(const cg3::Point3d& site);

    void addSite(const cg3::Point3d& p);
    template<class Container>
    void addSites(const Container& c);
    template<class Iterator>
    void addSites(Iterator begin, Iterator end);

    void clear();

	VoronoiDiagram3& operator=(const VoronoiDiagram3& vd);

	std::vector<VoronoiCell3>::const_iterator begin() const;
	std::vector<VoronoiCell3>::const_iterator end() const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    const int DEFAULT_N_POINTS = 1000;
    static BoundingBox3 bbInitializer(BoundingBox3 bb){
        bb.min() -= cg3::Point3d(1,1,1);
        bb.max() += cg3::Point3d(1,1,1);
        return bb;
    }

    void addSite(uint i, const cg3::Point3d& site);
    virtual void finalize();
    cg3::BoundingBox3 bb;
	::voro::container container;
	std::vector<VoronoiCell3> cells;
    std::map<cg3::Point3d, uint> mapCells;
    uint nPoints;
};

/**
 * @brief Default constructor Voronoi Diagram
 * Creates a Voronoi Diagram having as bounding box the double numeric limits,
 * zero sites and a maximum numer of sites od 1000.
 */
inline VoronoiDiagram3::VoronoiDiagram3() :
    bb(cg3::Point3d(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(),std::numeric_limits<double>::lowest()),
       cg3::Point3d(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max())),
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
inline VoronoiDiagram3::VoronoiDiagram3(const BoundingBox3& bb, uint nPoints) :
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
VoronoiDiagram3::VoronoiDiagram3(const Container& c) :
	VoronoiDiagram3(c.begin(), c.end())
{
}

template<class Iterator>
VoronoiDiagram3::VoronoiDiagram3(Iterator begin, Iterator end) :
	VoronoiDiagram3(BoundingBox3(begin, end), std::distance(begin, end))
{
    uint i = 0;
    for (Iterator it = begin; it != end; ++it, ++i){
        addSite(i, *it);
    }
    finalize();
}

template<class Container>
void VoronoiDiagram3::addSites(const Container &c)
{
    addSites(c.begin(), c.end());
}

template<class Iterator>
void VoronoiDiagram3::addSites(Iterator begin, Iterator end)
{
    uint i = cells.size();
    for (Iterator it = begin; it != end; ++it, ++i){
        addSite(i, *it);
    }
    finalize();
}

} //namespace cg3::voro
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_VORONOI_DIAGRAM3_CPP "voronoi_diagram3.cpp"
#include CG3_VORONOI_DIAGRAM3_CPP
#undef CG3_VORONOI_DIAGRAM3_CPP
#endif //CG3_STATIC

#endif // CG3_VORONOI_DIAGRAM3_H
