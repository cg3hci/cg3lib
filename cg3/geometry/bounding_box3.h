/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#ifndef CG3_BOUNDING_BOX3_H
#define CG3_BOUNDING_BOX3_H

#include <float.h>
#include "point3.h"
#include "../utilities/color.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @class BoundingBox
 * @brief The BoundingBox class models a Bounding Box which contains a 3D mesh.
 *
 * It is composed of two 3D points representing the minimum and maximum coordinates that generates the bounding box.
 * The class provides methods like for obtaining the center or the diagonal of the bounding box.
 */
class BoundingBox3 : public SerializableObject
{
public:

	BoundingBox3();
	BoundingBox3(const Point3d& min, const Point3d& max);
    template<class Iterator>
	BoundingBox3(Iterator begin, Iterator end);

    const Point3d& min()        const;
    const Point3d& max()        const;
    const double& minX()       const;
    const double& minY()       const;
    const double& minZ()       const;
    const double& maxX()       const;
    const double& maxY()       const;
    const double& maxZ()       const;
    double lengthX()        const;
    double lengthY()        const;
    double lengthZ()        const;

    Point3d  center()    const;
    double diag()       const;
    bool isValid() const;
    bool isStrictlyIntern(const Point3d& p)     const;
    bool isStrictlyInside(const Point3d& p)     const;
    bool isStrictlyIntern(double px, double py, double pz)     const;
    bool isStrictlyInside(double px, double py, double pz)     const;
    bool isIntern(const Point3d& p)     const;
    bool isInside(const Point3d& p)     const;
    bool isIntern(double px, double py, double pz)     const;
    bool isInside(double px, double py, double pz)     const;
    bool isEpsilonIntern(const Point3d& p, double epsilon = 1e-6)     const;
    bool isEpsilonInside(const Point3d& p, double epsilon = 1e-6)     const;
    bool isEpsilonIntern(double px, double py, double pz, double epsilon = 1e-6)     const;
    bool isEpsilonInside(double px, double py, double pz, double epsilon = 1e-6)     const;
	bool intersect(const BoundingBox3& otherBox);
	bool overlap(const BoundingBox3& otherBox);
    void extremes(std::vector<Point3d> &extremes) const;
    std::vector<Point3d> extremes() const;

    //Operators
    const double &operator ()(unsigned int i) const;
    Point3d operator[](unsigned int i)                 const;

    void saveOnObj(const std::string &filename, const Color& c = Color(128, 128, 128)) const;

    void setMin(const Point3d& min);
    Point3d& min();
    void setMax(const Point3d& max);
    Point3d& max();
    void setMin(double x, double y, double z);
    void setMax(double x, double y, double z);
    void setMinX(double x);
    double& minX();
    void setMinY(double y);
    double& minY();
    void setMinZ(double z);
    double& minZ();
    void setMaxX(double x);
    double& maxX();
    void setMaxY(double y);
    double& maxY();
    void setMaxZ(double z);
    double& maxZ();
    void reset();

    //Operators
    double& operator()(unsigned int i);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:
    Point3d _min;
    Point3d _max;
};

typedef BoundingBox3 Box;

/**
 * @brief Constructor, creates a bounding box that contains all the Pointd iterated
 * from begin to end.
 * @param begin: start iterator on a container of Pointd
 * @param end: end iterator on a container of Pointd
 */
template<class Iterator>
CG3_INLINE BoundingBox3::BoundingBox3(Iterator begin, Iterator end)
{
	_min = *begin;
	_max = *begin;
	for (Iterator i = begin; i != end; ++i){
		_min = _min.min(*i);
		_max = _max.max(*i);
	}
}

} //namespace cg3

//hash specialization
namespace std {

template <>
struct hash<cg3::BoundingBox3> {
	size_t operator()(const cg3::BoundingBox3& k) const;
};

} //namespace std

#ifndef CG3_STATIC
#define CG3_BOUNDINGBOX3_CPP "bounding_box3.cpp"
#include CG3_BOUNDINGBOX3_CPP
#undef CG3_BOUNDINGBOX3_CPP
#endif

#endif // CG3_BOUNDING_BOX3_H
