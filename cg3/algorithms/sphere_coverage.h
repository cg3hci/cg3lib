/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  * @author Marco Livesu (marco.livesu@gmail.com)
  */

#ifndef SPHERE_COVERAGE_H
#define SPHERE_COVERAGE_H

#include <cg3/geometry/point.h>

namespace cg3 {

std::vector<Pointd> sphereCoverage(unsigned int nSamples = 1000, bool deterministic = false);

}

#include "sphere_coverage.tpp"

#endif // SPHERE_COVERAGE_H
