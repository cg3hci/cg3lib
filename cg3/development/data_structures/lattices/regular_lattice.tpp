/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "regular_lattice.h"

namespace cg3 {

template <class VT>
RegularLattice3D<VT>::RegularLattice3D()
{
}

template<class VT>
RegularLattice3D<VT>::RegularLattice3D(const cg3::BoundingBox &bb, double unit, bool outsideBB) :
    bb(bb),
    unit(unit)
{
    unsigned int mresX, mresY, mresZ;
    mresX = bb.lengthX() / unit;
    if (outsideBB || std::fmod(bb.lengthX(), unit) == 0)
        mresX++;
    mresY = bb.lengthY() / unit;
    if (outsideBB || std::fmod(bb.lengthY(), unit) == 0)
        mresY++;
    mresZ = bb.lengthZ() / unit;
    if (outsideBB || std::fmod(bb.lengthZ(), unit) == 0)
        mresZ++;
    this->bb.max() = Pointd(bb.minX() + unit * (mresX-1), bb.minY() + unit * (mresY-1), bb.minZ() + unit * (mresZ-1));
    vertexProperties.resize(mresX,mresY,mresZ);
}

template<class VT>
unsigned int RegularLattice3D<VT>::resX() const
{
    return vertexProperties.sizeX();
}

template<class VT>
unsigned int RegularLattice3D<VT>::resY() const
{
    return vertexProperties.sizeY();
}

template<class VT>
unsigned int RegularLattice3D<VT>::resZ() const
{
    return vertexProperties.sizeZ();
}

template<class VT>
const BoundingBox &RegularLattice3D<VT>::boundingBox() const
{
    return bb;
}

template<class VT>
Pointd RegularLattice3D<VT>::nearestVertex(const Pointd &p) const
{
    return cg3::Pointd(bb.getMinX() + indexOfCoordinateX(p.x())*unit,
                       bb.getMinY() + indexOfCoordinateY(p.y())*unit,
                       bb.getMinZ() + indexOfCoordinateZ(p.z())*unit);
}

template<class VT>
const VT &RegularLattice3D<VT>::vertexProperty(const Pointd &p) const
{
    assert(indexOfCoordinateX(p.x()) < vertexProperties.sizeX());
    assert(indexOfCoordinateY(p.y()) < vertexProperties.sizeY());
    assert(indexOfCoordinateZ(p.z()) < vertexProperties.sizeZ());
    return vertexProperties(
            indexOfCoordinateX(p.x()),
            indexOfCoordinateY(p.y()),
            indexOfCoordinateZ(p.z()));
}

template<class VT>
VT& RegularLattice3D<VT>::vertexProperty(const Pointd& p)
{
    assert(indexOfCoordinateX(p.x()) < vertexProperties.sizeX());
    assert(indexOfCoordinateY(p.y()) < vertexProperties.sizeY());
    assert(indexOfCoordinateZ(p.z()) < vertexProperties.sizeZ());
    return vertexProperties(
            indexOfCoordinateX(p.x()),
            indexOfCoordinateY(p.y()),
            indexOfCoordinateZ(p.z()));
}

template<class VT>
void RegularLattice3D<VT>::setVertexProperty(const Pointd &p, const VT &property)
{
    assert(indexOfCoordinateX(p.x()) < vertexProperties.sizeX());
    assert(indexOfCoordinateY(p.y()) < vertexProperties.sizeY());
    assert(indexOfCoordinateZ(p.z()) < vertexProperties.sizeZ());
    vertexProperties(
            indexOfCoordinateX(p.x()),
            indexOfCoordinateY(p.y()),
            indexOfCoordinateZ(p.z())) = property;
}

template<class VT>
void RegularLattice3D<VT>::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes(
                "cg3RegularLattice3D",
                binaryFile,
                bb,
                unit,
                vertexProperties);
}

template<class VT>
void RegularLattice3D<VT>::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes(
                "cg3RegularLattice3D",
                binaryFile,
                bb,
                unit,
                vertexProperties);
}

template<class VT>
typename RegularLattice3D<VT>::VertexIterator RegularLattice3D<VT>::vertexBegin() const
{
    return VertexIterator(0, *this);
}

template<class VT>
typename RegularLattice3D<VT>::VertexIterator RegularLattice3D<VT>::vertexEnd() const
{
    return VertexIterator(vertexProperties.sizeX()*vertexProperties.sizeY()*vertexProperties.sizeZ(), *this);
}

template<class VT>
typename RegularLattice3D<VT>::PropertyIterator RegularLattice3D<VT>::propertyBegin()
{
    return PropertyIterator(0, *this);
}

template<class VT>
typename RegularLattice3D<VT>::PropertyIterator RegularLattice3D<VT>::propertyEnd()
{
    return PropertyIterator(vertexProperties.sizeX()*vertexProperties.sizeY()*vertexProperties.sizeZ(), *this);
}

template<class VT>
typename RegularLattice3D<VT>::ConstPropertyIterator RegularLattice3D<VT>::propertyBegin() const
{
    return ConstPropertyIterator(0, *this);
}

template<class VT>
typename RegularLattice3D<VT>::ConstPropertyIterator RegularLattice3D<VT>::propertyEnd() const
{
    return ConstPropertyIterator(vertexProperties.sizeX()*vertexProperties.sizeY()*vertexProperties.sizeZ(), *this);
}

template<class VT>
typename RegularLattice3D<VT>::Iterator RegularLattice3D<VT>::begin()
{
    return Iterator(0, *this);
}

template<class VT>
typename RegularLattice3D<VT>::Iterator RegularLattice3D<VT>::end()
{
    return Iterator(vertexProperties.sizeX()*vertexProperties.sizeY()*vertexProperties.sizeZ(), *this);
}

template<class VT>
typename RegularLattice3D<VT>::ConstIterator RegularLattice3D<VT>::begin() const
{
    return ConstIterator(0, *this);
}

template<class VT>
typename RegularLattice3D<VT>::ConstIterator RegularLattice3D<VT>::end() const
{
    return ConstIterator(vertexProperties.sizeX()*vertexProperties.sizeY()*vertexProperties.sizeZ(), *this);
}

template<class VT>
Pointd RegularLattice3D<VT>::vertex(
        unsigned int i,
        unsigned int j,
        unsigned int k) const
{
    return cg3::Pointd(bb.minX() + i*unit,
                       bb.minY() + j*unit,
                       bb.minZ() + k*unit);
}

template<class VT>
Pointd RegularLattice3D<VT>::vertex(unsigned int id) const
{
    Pointi ids = reverseIndex(id);
    return vertex(ids.x(),ids.y(),ids.z());
}

template<class VT>
VT& RegularLattice3D<VT>::property(unsigned int id)
{
    Pointi ids = reverseIndex(id);
    return vertexProperties(ids.x(), ids.y(), ids.z());
}

template<class VT>
const VT& RegularLattice3D<VT>::property(unsigned int id) const
{
    Pointi ids = reverseIndex(id);
    return vertexProperties(ids.x(), ids.y(), ids.z());
}

template<class VT>
uint RegularLattice3D<VT>::indexOfCoordinateX(double x) const
{
    double deltax = x - bb.minX();
    return (deltax * (vertexProperties.sizeX()-1)) / bb.lengthX();
}

template<class VT>
uint RegularLattice3D<VT>::indexOfCoordinateY(double y) const
{
    double deltay = y - bb.minY();
    return (deltay * (vertexProperties.sizeY()-1)) / bb.lengthY();
}

template<class VT>
uint RegularLattice3D<VT>::indexOfCoordinateZ(double z) const
{
    double deltaz = z - bb.minZ();
    return (deltaz * (vertexProperties.sizeZ()-1)) / bb.lengthZ();
}

template<class VT>
Pointi RegularLattice3D<VT>::reverseIndex(unsigned int id) const
{
    Pointi ids;
    assert(id < vertexProperties.sizeX()*vertexProperties.sizeY()*vertexProperties.sizeZ());
    ids.z() = id % vertexProperties.sizeZ();
    id/= vertexProperties.sizeZ();
    ids.y() = id % vertexProperties.sizeY();
    id/= vertexProperties.sizeY();
    ids.x() = id % vertexProperties.sizeX();
    return ids;
}

}
