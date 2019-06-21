/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_SEGMENT_H
#define CG3_SEGMENT_H

#include "point3.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief Class representing a directed segment. It is composed
 * by two end-points
 */
template <class T>
class Segment : public SerializableObject
{
public:
    /* Constructors/destructor */
    Segment();
    Segment(const T& p1, const T& p2);

    /* Getters */
    inline const T& p1() const;
    inline const T& p2() const;

    /* Setters */
    inline void setP1(const T& p1);
    inline void setP2(const T& p2);
    inline void set(const T& p1, const T& p2);

    /* Operators */
    inline double length() const;

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
    T _p1;
    T _p2;
};

template<class T>
std::ostream& operator<<(std::ostream& o, const Segment<T>& b);

/* ----- Common typedefs (1D) ----- */

template <class T>
using Segment1 = Segment<T>;

typedef Segment1<double> Segment1d;

typedef Segment1<float> Segment1f;

typedef Segment1<int> Segment1i;

} //namespace cg3

//hash specialization
namespace std {

template <typename T>
struct hash<cg3::Segment<T>> {
    size_t operator()(const cg3::Segment<T>& k) const;
};

} //namespace std

#include "segment.cpp"


#endif // CG3_SEGMENT_H
