/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "polygon2d.h"
#include <cg3/io/serialize.h>
#include <cg3/io/serialize_std.h>
#include "utils2d.h"

namespace cg3 {

Polygon2D::Polygon2D()
{

}

unsigned int Polygon2D::size() const
{
    return (unsigned int)pol.size();
}

Point2Dd&Polygon2D::operator [](unsigned int i)
{
    return pol[i];
}

const Point2Dd&Polygon2D::operator [](unsigned int i) const
{
    return pol[i];
}

void Polygon2D::updateBoundingBox()
{
    bb = BoundingBox2D();
    if (size() > 0){
        bb.min() = pol[0];
        bb.max() = pol[0];
        for (cg3::Point2Dd& p : pol){
            bb.min() = bb.min().min(p);
            bb.max() = bb.max().max(p);
        }
    }
}

void Polygon2D::pushBack(const Point2Dd& p)
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

bool Polygon2D::isCounterClockWise() const
{
    return cg3::isPolygonCounterClockwise(pol);
}

double Polygon2D::area() const
{
    return cg3::polygonArea(pol);
}

const std::vector<Point2Dd>& Polygon2D::vectorPoints() const
{
    return pol;
}

void Polygon2D::clear()
{
    pol.clear();
    bb = BoundingBox2D();
}

void Polygon2D::serialize(std::ofstream& binaryFile) const
{
    cg3::serializeObjectAttributes("cg3Polygon2D", binaryFile, pol, bb);
}

void Polygon2D::deserialize(std::ifstream& binaryFile)
{
    cg3::deserializeObjectAttributes("cg3Polygon2D", binaryFile, pol, bb);
}

Polygon2D::iterator Polygon2D::begin()
{
    return pol.begin();
}

Polygon2D::iterator Polygon2D::end()
{
    return pol.end();
}

Polygon2D::const_iterator Polygon2D::begin() const
{
    return pol.begin();
}

Polygon2D::const_iterator Polygon2D::end() const
{
    return pol.end();
}

} //namespace cg3
