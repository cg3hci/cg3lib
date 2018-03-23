/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_REGULAR_LATTICE_H
#define CG3_REGULAR_LATTICE_H

#include <cg3/geometry/bounding_box.h>
#include <cg3/data_structures/arrays/array3d.h>

namespace cg3 {

template <class VT>
class RegularLattice : public cg3::SerializableObject {

public:
    RegularLattice();
    RegularLattice(const cg3::BoundingBox& bb, double unit, bool outsideBB = true);

    unsigned int resX() const;
    unsigned int resY() const;
    unsigned int resZ() const;

    const cg3::BoundingBox& boundingBox() const;

    cg3::Pointd nearestVertex(const cg3::Pointd& p) const;
    const VT& vertexProperty(const cg3::Pointd& p) const;
    void setVertexProperty(const cg3::Pointd& p, const VT& property);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    class VertexIterator;


protected:

    cg3::Pointd getPoint(unsigned int i, unsigned int j, unsigned int k) const;
    int getIndexOfCoordinateX(double x) const;
    int getIndexOfCoordinateY(double y) const;
    int getIndexOfCoordinateZ(double z) const;

    cg3::BoundingBox bb;
    double unit;
    cg3::Array3D<VT> vertexProperties;
    unsigned int mresX, mresY, mresZ;
};

}

#include "regular_lattice.tpp"

#endif // CG3_REGULAR_LATTICE_H
