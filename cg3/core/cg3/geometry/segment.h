/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_SEGMENT_H
#define CG3_SEGMENT_H

#include "point.h"
#include <ostream>

namespace cg3 {

/**
 * Class representing a directed segment. It is composed
 * by two end-points
 */
template <class T>
class Segment : public SerializableObject {

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

protected:

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
using Segment3D = Segment<Point<T>>;

typedef Segment1D<double> Segment1Dd;
typedef Segment3D<double> Segment3Dd;

typedef Segment1D<float> Segment1Df;
typedef Segment3D<float> Segment3Df;

typedef Segment1D<int> Segment1Di;
typedef Segment3D<int> Segment3Di;

}

//hash specialization
namespace std {

template <typename T>
struct hash<cg3::Segment<T>> {
    size_t operator()(const cg3::Segment<T>& k) const;
};

}

#include "segment.tpp"


#endif // CG3_SEGMENT_H
