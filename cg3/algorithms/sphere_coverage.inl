/*
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
inline std::vector<Point3d> sphereCoverage(
        unsigned int nSamples,
        bool deterministic)
{
    std::vector<Point3d> points;

    if (nSamples > 0) {
        points.reserve(nSamples);

        static std::random_device r;
        static std::mt19937 mt(r());
        std::uniform_real_distribution<> dist(0, 1);

        double rnd = 1;
        if (!deterministic)
            rnd = dist(mt) * nSamples;
        double offset   = 2.0/nSamples;
        double increment = M_PI * (3.0 - sqrt(5.0));

        for(unsigned int i=0; i<nSamples; ++i) {
            double y   = ((i * offset) - 1) + (offset / 2);
            double r   = sqrt(1 - pow(y,2));
            double phi = ((i + int(rnd)) % nSamples) * increment;
            double x   = cos(phi) * r;
            double z   = sin(phi) * r;

            points.push_back(Point3d(x,y,z));
        }
    }
    return points;
}

/**
 * @brief sphereCoverageFibonacci
 *
 * Implementation of the Spherical Fibonacci Point Sets
 * according to the description of
 * Spherical Fibonacci Mapping
 * Benjamin Keinert, Matthias Innmann, Michael Sanger, Marc Stamminger
 * TOG 2015
 *
 * Implementation of VCGLib:
 * (https://github.com/cnr-isti-vclab/vcglib/blob/master/vcg/math/gen_normal.h)
 */
inline std::vector<cg3::Point3d> sphereCoverageFibonacci(unsigned int nSamples)
{
	std::vector<cg3::Point3d> points;
	points.reserve(nSamples);
	const double Phi =  std::sqrt(3);

    for (uint i = 0; i < nSamples; i++){
		double phi = 2*M_PI * (i/Phi - std::floor(i/Phi));
		double cosTheta = 1 - (2*i + 1.0)/nSamples;
        double sinTheta = 1 - cosTheta*cosTheta;
		sinTheta = std::sqrt(std::min(1.0, std::max(0.0, sinTheta)));
		points.push_back(cg3::Point3d(cos(phi)*sinTheta, sin(phi)*sinTheta, cosTheta));
    }

    return points;
}

} //namespace cg3
