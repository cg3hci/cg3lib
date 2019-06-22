/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_ROBUSTNESS_H
#define CG3_DCEL_ROBUSTNESS_H

#include <cg3/meshes/dcel/dcel.h>

namespace cg3 {
namespace dcelAlgorithms {

bool isWaterTight(const cg3::Dcel& mesh);

bool hasDegenerateFaces(const cg3::Dcel& mesh);

}
}

#ifndef CG3_STATIC
#define CG3_DCEL_ROBUSTNESS_CPP "dcel_robustness.cpp"
#include CG3_DCEL_ROBUSTNESS_CPP
#undef CG3_DCEL_ROBUSTNESS_CPP
#endif

#endif // CG3_DCEL_ROBUSTNESS_H
