#ifndef CG3_SEGMENT_H
#define CG3_SEGMENT_H

#include "point.h"
#include "2d/point2d.h"

#include <ostream>

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
    Segment(const T& getP1, const T& getP2);

    /* Getters */
    inline const T& getP1() const;
    inline const T& getP2() const;

    /* Setters */
    inline void setP1(const T& getP1);
    inline void setP2(const T& getP2);
    inline void set(const T& getP1, const T& getP2);

    /* Operator overrides */
    inline bool operator == (const Segment& otherSegment) const;
    inline bool operator != (const Segment& otherSegment) const;
    inline bool operator < (const Segment& otherSegment) const;
    inline bool operator > (const Segment& otherSegment) const;
    inline bool operator <= (const Segment& otherSegment) const;
    inline bool operator >= (const Segment& otherSegment) const;

    /* Serialization */
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    /* Utilities */
    std::string toString() const;

private:

    /* Fields */
    T p1;
    T p2;
};

template<class T>
std::ostream& operator<<(std::ostream& o, const Segment<T>& b);

/* ----- Common typedefs (1D, 2D, 3D double) ----- */

template <class T>
using Segment1D = Segment<T>;
template <class T>
using Segment2D = Segment<Point2D<T>>;
template <class T>
using Segment3D = Segment<Point<T>>;

typedef Segment1D<double> Segment1Dd;
typedef Segment2D<double> Segment2Dd;
typedef Segment3D<double> Segment3Dd;

typedef Segment1D<double> Segment1Di;
typedef Segment2D<double> Segment2Di;
typedef Segment3D<double> Segment3Di;

}

#include "segment.tpp"


#endif // CG3_SEGMENT_H
