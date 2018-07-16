/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_POLYGON2D_H
#define CG3_POLYGON2D_H

#include "bounding_box2d.h"
#include <cg3/io/serializable_object.h>

namespace cg3 {

class Polygon2D : public cg3::SerializableObject
{
public:
    Polygon2D();

    unsigned int size() const;
    cg3::Point2Dd& operator [](unsigned int i);
    const cg3::Point2Dd& operator [](unsigned int i) const;
    void updateBoundingBox();
    void pushBack(const cg3::Point2Dd& p);
    bool isCounterClockWise() const;
    const std::vector<cg3::Point2Dd>& vectorPoints() const;
    void clear();

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    typedef std::vector<cg3::Point2Dd>::iterator iterator;
    typedef std::vector<cg3::Point2Dd>::const_iterator const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

protected:
    std::vector<cg3::Point2Dd> pol;
    cg3::BoundingBox2D bb;
};

} //namespace cg3

#endif // CG3_POLYGON2D_H
