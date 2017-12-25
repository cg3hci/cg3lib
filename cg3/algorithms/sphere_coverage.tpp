/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  * @author Marco Livesu (marco.livesu@gmail.com)
  */

#include "sphere_coverage.h"
#include <random>

namespace cg3 {

/**
 * @brief sphereCoverage
 * Compute an approximate (though good) approximation of the even
 * coverage of a sphere. Reference:
 *
 * @link http://stackoverflow.com/questions/9600801/evenly-distributing-n-points-on-a-sphere
 */
inline std::vector<Pointd> sphereCoverage(unsigned int nSamples, bool deterministic) {
    std::vector<Pointd> points;
    points.reserve(nSamples);

    static std::random_device r;
    static std::mt19937 mt(r());
    std::uniform_real_distribution<> dist(0, 1);

    double rnd;
    if (deterministic)
        rnd = 0;
    else {
        rnd = dist(mt);
    }
    rnd*=nSamples;
    double offset   = 2.0/double(nSamples);
    double increment = M_PI * (3.0 - sqrt(5.0));

    for(unsigned int i=0; i<nSamples; ++i) {
        double y   = ((i * offset) - 1) + (offset / 2);
        double r   = sqrt(1 - pow(y,2));
        double phi = ((i + int(rnd)) % nSamples) * increment;
        double x   = cos(phi) * r;
        double z   = sin(phi) * r;

        points.push_back(Pointd(x,y,z));
    }
    return points;
}

}
