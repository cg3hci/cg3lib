/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_POLYGON2_H
#define CG3_POLYGON2_H

#include "bounding_box2.h"
#include <cg3/io/serializable_object.h>

namespace cg3 {

class Polygon2 : public cg3::SerializableObject
{
public:
	Polygon2();

    unsigned int size() const;
    cg3::Point2d& operator [](unsigned int i);
    const cg3::Point2d& operator [](unsigned int i) const;
    void updateBoundingBox();
    void pushBack(const cg3::Point2d& p);
    bool isCounterClockWise() const;
    double area() const;
    const std::vector<cg3::Point2d>& vectorPoints() const;
    void clear();

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    typedef std::vector<cg3::Point2d>::iterator iterator;
    typedef std::vector<cg3::Point2d>::const_iterator const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

protected:
    std::vector<cg3::Point2d> pol;
    cg3::BoundingBox2 bb;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_POLYGON2_CPP "polygon2.cpp"
#include CG3_POLYGON2_CPP
#undef CG3_POLYGON2_CPP
#endif

#endif // CG3_POLYGON2_H
