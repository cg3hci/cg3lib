/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_REGULAR_LATTICE_ITERATORS_H
#define CG3_REGULAR_LATTICE_ITERATORS_H

#include "regular_lattice.h"

namespace cg3 {

template <class VT>
class RegularLattice<VT>::VertexIterator{
        friend class RegularLattice;
    public:
        VertexIterator();

        const Pointd& operator *() const;
        bool operator == (const VertexIterator& otherIterator) const;
        bool operator != (const VertexIterator& otherIterator) const;

        VertexIterator operator ++ ();
        VertexIterator operator ++ (int);
        VertexIterator operator -- ();
        VertexIterator operator -- (int);

    protected:
        const RegularLattice* l;
        unsigned int pos;
        VertexIterator(unsigned int pos, const RegularLattice &g);


};

}

#endif // CG3_REGULAR_LATTICE_ITERATORS_H
