/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_CONVEXHULL_H
#define CG3_CONVEXHULL_H

#include "cg3/meshes/dcel/dcel.h"
#include "cg3/data_structures/graphs/bipartite_graph.h"


namespace cg3 {

Dcel convexHull(const Dcel& inputDcel);

template <class InputContainer>
Dcel convexHull(const InputContainer& points);

template <class InputIterator>
Dcel convexHull(InputIterator first, InputIterator end);

}

#include "convexhull.tpp"

#endif // CG3_CONVEXHULL_H
