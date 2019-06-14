/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_BOUNDINGBOX2_H
#define CG3_BOUNDINGBOX2_H

#include "point2.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief The BoundingBox2D class
 * This class models an axis aligned 2D box.
 * It is composed of two points, min and max, which represent the minimum and
 * maximum coordinates of the box.
 */
class BoundingBox2 : public SerializableObject
{
public:
	BoundingBox2();
	BoundingBox2(const Point2d& minCoord, const Point2d& maxCoord);


    const Point2d& min() const;
    Point2d& min();
    void setMin(const Point2d& value);

    const Point2d& max() const;
    Point2d& max();
    void setMax(const Point2d& value);
    void set(const Point2d& min, const Point2d& max);

    Point2d center() const;
    double diag() const;

    double lengthX() const;
    double lengthY() const;

    bool isInside(const Point2d& p) const;
    bool isStrictlyInside(const Point2d& p) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    Point2d minCoord, maxCoord;
};

template <class InputContainer>
BoundingBox2 boundingBox(const InputContainer& container);

} //namespace cg3

//hash specialization
namespace std {

template<>
struct hash<cg3::BoundingBox2> {
	size_t operator()(const cg3::BoundingBox2& k) const;
};

} //namespace std

#include "bounding_box2.tpp"

#endif // CG3_BOUNDINGBOX2_H
