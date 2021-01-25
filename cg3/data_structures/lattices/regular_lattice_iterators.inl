/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "regular_lattice_iterators.h"

namespace cg3 {

template<class VT>
cg3::RegularLattice3D<VT>::VertexIterator::VertexIterator() : l(nullptr), pos(0)
{
}

template<class VT>
Point3d cg3::RegularLattice3D<VT>::VertexIterator::operator *() const
{
    return l->vertex(pos);
}

template<class VT>
const Point3d* cg3::RegularLattice3D<VT>::VertexIterator::operator ->() const
{
    tmp = l->vertex(pos);
    return &tmp;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::VertexIterator::operator ==(const cg3::RegularLattice3D<VT>::VertexIterator& otherIterator) const
{
    return l == otherIterator.l && pos == otherIterator.pos;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::VertexIterator::operator !=(const cg3::RegularLattice3D<VT>::VertexIterator& otherIterator) const
{
    return l != otherIterator.l || pos != otherIterator.pos;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::VertexIterator cg3::RegularLattice3D<VT>::VertexIterator::operator ++()
{
    ++pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::VertexIterator cg3::RegularLattice3D<VT>::VertexIterator::operator ++(int)
{
    VertexIterator old = *this;
    ++pos;
    return old;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::VertexIterator cg3::RegularLattice3D<VT>::VertexIterator::operator --()
{
    --pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::VertexIterator cg3::RegularLattice3D<VT>::VertexIterator::operator --(int)
{
    VertexIterator old = *this;
    --pos;
    return *this;
}

template<class VT>
cg3::RegularLattice3D<VT>::VertexIterator::VertexIterator(unsigned int pos, const RegularLattice3D<VT>& g) :
    l(&g), pos(pos)
{
}

template<class VT>
cg3::RegularLattice3D<VT>::PropertyIterator::PropertyIterator() : l(nullptr), pos(0)
{
}

template<class VT>
VT& cg3::RegularLattice3D<VT>::PropertyIterator::operator *() const
{
    return l->property(pos);
}

template<class VT>
VT* cg3::RegularLattice3D<VT>::PropertyIterator::operator ->() const
{
    return &(l->property(pos));
}

template<class VT>
bool cg3::RegularLattice3D<VT>::PropertyIterator::operator ==(const cg3::RegularLattice3D<VT>::PropertyIterator& otherIterator) const
{
    return l == otherIterator.l && pos == otherIterator.pos;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::PropertyIterator::operator !=(const cg3::RegularLattice3D<VT>::PropertyIterator& otherIterator) const
{
    return l != otherIterator.l || pos != otherIterator.pos;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::PropertyIterator cg3::RegularLattice3D<VT>::PropertyIterator::operator ++()
{
    ++pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::PropertyIterator cg3::RegularLattice3D<VT>::PropertyIterator::operator ++(int)
{
    PropertyIterator old = *this;
    ++pos;
    return old;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::PropertyIterator cg3::RegularLattice3D<VT>::PropertyIterator::operator --()
{
    --pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::PropertyIterator cg3::RegularLattice3D<VT>::PropertyIterator::operator --(int)
{
    PropertyIterator old = *this;
    --pos;
    return *this;
}

template<class VT>
cg3::RegularLattice3D<VT>::PropertyIterator::PropertyIterator(unsigned int pos, RegularLattice3D<VT>& g) :
    l(&g), pos(pos)
{
}

template<class VT>
cg3::RegularLattice3D<VT>::ConstPropertyIterator::ConstPropertyIterator() : l(nullptr), pos(0)
{
}

template<class VT>
const VT& cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator *() const
{
    return l->property(pos);
}

template<class VT>
const VT* cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator ->() const
{
    return &(l->property(pos));
}

template<class VT>
bool cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator ==(const cg3::RegularLattice3D<VT>::ConstPropertyIterator& otherIterator) const
{
    return l == otherIterator.l && pos == otherIterator.pos;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator !=(const cg3::RegularLattice3D<VT>::ConstPropertyIterator& otherIterator) const
{
    return l != otherIterator.l || pos != otherIterator.pos;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstPropertyIterator cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator ++()
{
    ++pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstPropertyIterator cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator ++(int)
{
    ConstPropertyIterator old = *this;
    ++pos;
    return old;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstPropertyIterator cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator --()
{
    --pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstPropertyIterator cg3::RegularLattice3D<VT>::ConstPropertyIterator::operator --(int)
{
    ConstPropertyIterator old = *this;
    --pos;
    return *this;
}

template<class VT>
cg3::RegularLattice3D<VT>::ConstPropertyIterator::ConstPropertyIterator(unsigned int pos, const RegularLattice3D<VT>& g) :
    l(&g), pos(pos)
{
}

template<class VT>
cg3::RegularLattice3D<VT>::Iterator::Iterator() : tmpvt(), tmpp(Point3d(), tmpvt), l(nullptr), pos(0)
{
}

template<class VT>
std::pair<Point3d, VT&> cg3::RegularLattice3D<VT>::Iterator::operator *() const
{
	return std::pair<Point3d, VT&>(l->vertex(pos), l->property(pos));
}

template<class VT>
std::pair<Point3d, VT&>* cg3::RegularLattice3D<VT>::Iterator::operator ->() const
{
    if (pos < l->resX()*l->resY()*l->resZ()){
		tmpp = std::pair<Point3d, VT&>(l->vertex(pos), l->property(pos));
    }
    return &tmpp;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::Iterator::operator ==(const cg3::RegularLattice3D<VT>::Iterator& otherIterator) const
{
    return l == otherIterator.l && pos == otherIterator.pos;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::Iterator::operator !=(const cg3::RegularLattice3D<VT>::Iterator& otherIterator) const
{
    return l != otherIterator.l || pos != otherIterator.pos;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::Iterator cg3::RegularLattice3D<VT>::Iterator::operator ++()
{
    ++pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::Iterator cg3::RegularLattice3D<VT>::Iterator::operator ++(int)
{
    Iterator old = *this;
    ++pos;
    return old;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::Iterator cg3::RegularLattice3D<VT>::Iterator::operator --()
{
    --pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::Iterator cg3::RegularLattice3D<VT>::Iterator::operator --(int)
{
    Iterator old = *this;
    --pos;
    return *this;
}

template<class VT>
cg3::RegularLattice3D<VT>::Iterator::Iterator(unsigned int pos, RegularLattice3D<VT>& g) :
	tmpvt(), tmpp(Point3d(), tmpvt), l(&g), pos(pos)
{
    if (pos < l->resX()*l->resY()*l->resZ()){
		tmpp = std::pair<Point3d, VT&>(l->vertex(pos), l->property(pos));
    }
}

template<class VT>
cg3::RegularLattice3D<VT>::ConstIterator::ConstIterator() : tmpvt(), tmpp(Point3d(), tmpvt), l(nullptr), pos(0)
{
}

template<class VT>
std::pair<Point3d, const VT&> cg3::RegularLattice3D<VT>::ConstIterator::operator *() const
{
	return std::pair<Point3d, const VT&>(l->vertex(pos), l->property(pos));
}

template<class VT>
const std::pair<Point3d, const VT&>* cg3::RegularLattice3D<VT>::ConstIterator::operator ->() const
{
	tmpp = std::pair<Point3d, const VT&>(l->vertex(pos), l->property(pos));
    return &tmpp;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::ConstIterator::operator ==(const cg3::RegularLattice3D<VT>::ConstIterator& otherIterator) const
{
    return l == otherIterator.l && pos == otherIterator.pos;
}

template<class VT>
bool cg3::RegularLattice3D<VT>::ConstIterator::operator !=(const cg3::RegularLattice3D<VT>::ConstIterator& otherIterator) const
{
    return l != otherIterator.l || pos != otherIterator.pos;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstIterator cg3::RegularLattice3D<VT>::ConstIterator::operator ++()
{
    ++pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstIterator cg3::RegularLattice3D<VT>::ConstIterator::operator ++(int)
{
    ConstIterator old = *this;
    ++pos;
    return old;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstIterator cg3::RegularLattice3D<VT>::ConstIterator::operator --()
{
    --pos;
    return *this;
}

template<class VT>
typename cg3::RegularLattice3D<VT>::ConstIterator cg3::RegularLattice3D<VT>::ConstIterator::operator --(int)
{
    ConstIterator old = *this;
    --pos;
    return *this;
}

template<class VT>
cg3::RegularLattice3D<VT>::ConstIterator::ConstIterator(unsigned int pos, const RegularLattice3D<VT>& g) :
	tmpvt(), tmpp(Point3d(), tmpvt), l(&g), pos(pos)
{
    if (pos < l->resX()*l->resY()*l->resZ()){
		tmpp = std::pair<Point3d, const VT&>(l->vertex(pos), l->property(pos));
    }
}

} //namespace cg3
