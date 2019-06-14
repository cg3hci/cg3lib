/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "polygon2.h"
#include <cg3/io/serialize.h>
#include <cg3/io/serialize_std.h>
#include "utils2.h"

namespace cg3 {

Polygon2::Polygon2()
{

}

unsigned int Polygon2::size() const
{
    return (unsigned int)pol.size();
}

Point2d&Polygon2::operator [](unsigned int i)
{
    return pol[i];
}

const Point2d&Polygon2::operator [](unsigned int i) const
{
    return pol[i];
}

void Polygon2::updateBoundingBox()
{
    bb = BoundingBox2();
    if (size() > 0){
        bb.min() = pol[0];
        bb.max() = pol[0];
        for (cg3::Point2d& p : pol){
            bb.min() = bb.min().min(p);
            bb.max() = bb.max().max(p);
        }
    }
}

void Polygon2::pushBack(const Point2d& p)
{
    pol.push_back(p);
    if (pol.size() > 1){
        bb.min() = bb.min().min(p);
        bb.max() = bb.max().max(p);
    }
    else {
        bb.min() = p;
        bb.max() = p;
    }
}

bool Polygon2::isCounterClockWise() const
{
    return cg3::isPolygonCounterClockwise(pol);
}

double Polygon2::area() const
{
    return cg3::polygonArea(pol);
}

const std::vector<Point2d>& Polygon2::vectorPoints() const
{
    return pol;
}

void Polygon2::clear()
{
    pol.clear();
    bb = BoundingBox2();
}

void Polygon2::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Polygon2D", binaryFile, pol, bb);
}

void Polygon2::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Polygon2D", binaryFile, pol, bb);
}

Polygon2::iterator Polygon2::begin()
{
    return pol.begin();
}

Polygon2::iterator Polygon2::end()
{
    return pol.end();
}

Polygon2::const_iterator Polygon2::begin() const
{
    return pol.begin();
}

Polygon2::const_iterator Polygon2::end() const
{
    return pol.end();
}

} //namespace cg3
