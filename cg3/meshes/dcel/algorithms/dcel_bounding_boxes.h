/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_BOUNDING_BOXES_H
#define CG3_DCEL_BOUNDING_BOXES_H

#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {
namespace dcelAlgorithms {

/**
 * @param first: iterator to the first face of the container
 * @param last: iterator to the last face of the container
 * @return the Bounding Box that bounds the faces contained in the input range.
 */
template <typename InputIterator>
BoundingBox3 boundingBoxOfFaces(InputIterator first, InputIterator last);

} //namespace cg3::dcelAlgorithms
} //namespace cg3

#include "dcel_bounding_boxes.cpp"

#endif // CG3_DCEL_BOUNDING_BOXES_H
