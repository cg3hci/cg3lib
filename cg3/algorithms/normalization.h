/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_NORMALIZATION_H
#define CG3_NORMALIZATION_H

#include <cg3/cg3lib.h>

#include <vector>

namespace cg3 {

std::vector<double> linearNormalization(
        const std::vector<double>& function,
        const double minFunction,
        const double maxFunction);

std::vector<double> linearNormalization(
        const std::vector<double>& function);

std::vector<double> varianceNormalization(
        const std::vector<double>& function,
        const double stdMultiplier = 1.0);

} //namespace cg3

#ifndef CG3_STATIC
#define  CG3_NORMALIZATION_CPP "normalization.cpp"
#include  CG3_NORMALIZATION_CPP
#undef  CG3_NORMALIZATION_CPP
#endif //CG3_STATIC

#endif // CG3_NORMALIZATION_H
