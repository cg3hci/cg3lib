/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_LAPLACIAN_SMOOTHING_H
#define CG3_LAPLACIAN_SMOOTHING_H

namespace cg3 {

class Dcel;

void laplacianSmoothing(cg3::Dcel& mesh, unsigned int nIt = 1);
cg3::Dcel laplacianSmoothing(const cg3::Dcel& mesh, unsigned int nIt = 1);

} //namespace cg3

#ifndef CG3_STATIC
#define  CG3_LAPLACIAN_SMOOTHING_CPP "laplacian_smoothing.cpp"
#include  CG3_LAPLACIAN_SMOOTHING_CPP
#undef  CG3_LAPLACIAN_SMOOTHING_CPP
#endif //CG3_STATIC

#endif // CG3_LAPLACIAN_SMOOTHING_H
