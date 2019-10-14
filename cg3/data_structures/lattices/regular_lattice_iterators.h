/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_REGULAR_LATTICE_ITERATORS_H
#define CG3_REGULAR_LATTICE_ITERATORS_H

namespace cg3 {

template <class VT>
class RegularLattice3D;

template <class VT>
class RegularLattice3D<VT>::VertexIterator
{
    friend class RegularLattice3D;
public:
    VertexIterator();

	Point3d operator *() const;
	const Point3d* operator ->() const;
    bool operator == (const VertexIterator& otherIterator) const;
    bool operator != (const VertexIterator& otherIterator) const;

    VertexIterator operator ++ ();
    VertexIterator operator ++ (int);
    VertexIterator operator -- ();
    VertexIterator operator -- (int);

protected:
	mutable Point3d tmp;
    const RegularLattice3D<VT>* l;
    unsigned int pos;
    VertexIterator(unsigned int pos, const RegularLattice3D<VT> &g);
};

template <class VT>
class RegularLattice3D<VT>::PropertyIterator
{
    friend class RegularLattice3D;
public:
    PropertyIterator();

    VT& operator *() const;
    VT* operator ->() const;
    bool operator == (const PropertyIterator& otherIterator) const;
    bool operator != (const PropertyIterator& otherIterator) const;

    PropertyIterator operator ++ ();
    PropertyIterator operator ++ (int);
    PropertyIterator operator -- ();
    PropertyIterator operator -- (int);

protected:
    RegularLattice3D<VT>* l;
    unsigned int pos;
    PropertyIterator(unsigned int pos, RegularLattice3D<VT> &g);
};

template <class VT>
class RegularLattice3D<VT>::ConstPropertyIterator
{
    friend class RegularLattice3D;
public:
    ConstPropertyIterator();

    const VT& operator *() const;
    const VT* operator ->() const;
    bool operator == (const ConstPropertyIterator& otherIterator) const;
    bool operator != (const ConstPropertyIterator& otherIterator) const;

    ConstPropertyIterator operator ++ ();
    ConstPropertyIterator operator ++ (int);
    ConstPropertyIterator operator -- ();
    ConstPropertyIterator operator -- (int);

protected:
    const RegularLattice3D<VT>* l;
    unsigned int pos;
    ConstPropertyIterator(unsigned int pos, const RegularLattice3D<VT> &g);
};

template <class VT>
class RegularLattice3D<VT>::Iterator
{
    friend class RegularLattice3D;
public:
    Iterator();

	std::pair<Point3d, VT&> operator *() const;
	std::pair<Point3d, VT&>* operator ->() const;
    bool operator == (const Iterator& otherIterator) const;
    bool operator != (const Iterator& otherIterator) const;

    Iterator operator ++ ();
    Iterator operator ++ (int);
    Iterator operator -- ();
    Iterator operator -- (int);

protected:
    mutable VT tmpvt;
	mutable std::pair<Point3d, VT&> tmpp;
    RegularLattice3D<VT>* l;
    unsigned int pos;
    Iterator(unsigned int pos, RegularLattice3D<VT> &g);
};

template <class VT>
class RegularLattice3D<VT>::ConstIterator
{
    friend class RegularLattice3D;
public:
    ConstIterator();

	std::pair<Point3d, const VT&> operator *() const;
	const std::pair<Point3d, const VT&>* operator ->() const;
    bool operator == (const ConstIterator& otherIterator) const;
    bool operator != (const ConstIterator& otherIterator) const;

    ConstIterator operator ++ ();
    ConstIterator operator ++ (int);
    ConstIterator operator -- ();
    ConstIterator operator -- (int);

protected:
    mutable VT tmpvt;
	mutable std::pair<Point3d, const VT&> tmpp;
    const RegularLattice3D<VT>* l;
    unsigned int pos;
    ConstIterator(unsigned int pos, const RegularLattice3D<VT> &g);
};

} //namespace cg3

#include "regular_lattice_iterators.cpp"

#endif // CG3_REGULAR_LATTICE_ITERATORS_H
