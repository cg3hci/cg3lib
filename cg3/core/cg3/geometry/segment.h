#ifndef CG3_SEGMENT_H
#define CG3_SEGMENT_H

#include "point.h"
#include "2d/point2d.h"

namespace cg3 {

/**
 * Class representing a directed segment. It is composed
 * by two end-points
 */
template <class T>
class Segment : SerializableObject {

public:

    /* Constructors/destructor */
    Segment();
    Segment(const T& p1, const T& p2);

    /* Getters/setters */
    const T& getP1() const;
    const T& getP2() const;

    /* Getters/setters */
    void setP1(const T& p1);
    void setP2(const T& p2);

    void set(const T& p1, const T& p2);

    /* Operator overrides */
    bool operator == (const Segment& otherSegment) const;
    bool operator != (const Segment& otherSegment) const;
    bool operator < (const Segment& otherSegment) const;
    bool operator > (const Segment& otherSegment) const;
    bool operator <= (const Segment& otherSegment) const;
    bool operator >= (const Segment& otherSegment) const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    /* Utilities */
    std::string toString() const;

private:

    /* Fields */
    T p1;
    T p2;
};

/* ----- Common typedefs (1D, 2D, 3D double) ----- */

typedef Segment<double> Segment1Dd;
typedef Segment<Point2Dd> Segment2Dd;
typedef Segment<Pointd> Segment3Dd;

}

#include "segment.tpp"


#endif // CG3_SEGMENT_H
