/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_REGULAR_LATTICE_H
#define CG3_REGULAR_LATTICE_H

#include <cg3/geometry/bounding_box3.h>
#include <cg3/data_structures/arrays/array3d.h>

namespace cg3 {

template <class VT>
class RegularLattice3D : public cg3::SerializableObject
{
public:

    //iterators
    class VertexIterator;
    class PropertyIterator;
    class ConstPropertyIterator;
    class Iterator;
    class ConstIterator;

    RegularLattice3D();
    RegularLattice3D(const cg3::BoundingBox3& bb, double unit, bool outsideBB = true);

    unsigned int resX() const;
    unsigned int resY() const;
    unsigned int resZ() const;

    const cg3::BoundingBox3& boundingBox() const;
	double unit() const;

	cg3::Point3d vertex(unsigned int i, unsigned int j, unsigned int k) const;
    cg3::Point3d nearestVertex(const cg3::Point3d& p) const;
	VT vertexProperty(unsigned int i, unsigned int j, unsigned int k) const;
	VT& vertexProperty(unsigned int i, unsigned int j, unsigned int k);
	VT vertexProperty(const cg3::Point3d& p) const;
    VT& vertexProperty(const cg3::Point3d& p);
    void setVertexProperty(const cg3::Point3d& p, const VT& property);
	void setVertexProperty(unsigned int i, unsigned int j, unsigned int k, const VT& property);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    VertexIterator vertexBegin() const;
    VertexIterator vertexEnd() const;
    PropertyIterator propertyBegin();
    PropertyIterator propertyEnd();
    ConstPropertyIterator propertyBegin() const;
    ConstPropertyIterator propertyEnd() const;
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

protected:


    cg3::Point3d vertex(unsigned int id) const;
    VT& property(unsigned int id);
	VT property(unsigned int id) const;
    uint indexOfCoordinateX(double x) const;
    uint indexOfCoordinateY(double y) const;
    uint indexOfCoordinateZ(double z) const;
    cg3::Point3i reverseIndex(unsigned int id) const;

    cg3::BoundingBox3 bb;
	double _unit;
    cg3::Array3D<VT> vertexProperties;
};

} //namespace cg3

#include "regular_lattice_iterators.h"
#include "regular_lattice.cpp"

#endif // CG3_REGULAR_LATTICE_H
