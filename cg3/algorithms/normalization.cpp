/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 */
#include "normalization.h"

#include <limits>

#include <cmath>

#include "assert.h"

namespace cg3 {

CG3_INLINE std::vector<double> linearNormalization(
        const std::vector<double>& function,
        const double minFunction,
        const double maxFunction)
{
    std::vector<double> normalizedFunction(function.size());

    if (maxFunction - minFunction == 0) {
        std::fill(normalizedFunction.begin(), normalizedFunction.end(), 0);
    }
    else {
        for(size_t i = 0; i < function.size(); i++) {
            assert(function[i] >= minFunction && function[i] <= maxFunction);
            normalizedFunction[i] = (function[i] - minFunction) / (maxFunction - minFunction);
        }
    }

    return normalizedFunction;
}

CG3_INLINE std::vector<double> linearNormalization(const std::vector<double>& function)
{
    double minFunction = std::numeric_limits<double>::max();
    double maxFunction = -std::numeric_limits<double>::max();

    for (size_t i = 0; i < function.size(); i++) {
        minFunction = std::min(minFunction, function[i]);
        maxFunction = std::max(maxFunction, function[i]);
    }

    return linearNormalization(function, minFunction, maxFunction);
}

CG3_INLINE std::vector<double> varianceNormalization(
        const std::vector<double>& function,
        const double stdMultiplier)
{
    std::vector<double> normalizedFunction(function.size());

    double avg = 0;
    for(size_t i = 0; i < function.size(); i++) {
        avg += function[i];
    }
    avg /= function.size();

    double standardDeviation = 0;
    for(size_t i = 0; i < function.size(); i++) {
        standardDeviation += (function[i] - avg) * (function[i] - avg);
    }
    standardDeviation /= function.size();

    standardDeviation = std::sqrt(standardDeviation);

    const double stdMultiplied = standardDeviation * stdMultiplier;
    const double minValue = avg - stdMultiplied;
    const double maxValue = avg + stdMultiplied;

    for(size_t i = 0; i < function.size(); i++) {
        if (function[i] >= maxValue)
            normalizedFunction[i] = 1.0;
        else if (function[i] <= minValue)
            normalizedFunction[i] = 0.0;
        else
            normalizedFunction[i] = (function[i] - minValue) / (maxValue - minValue);
    }

    return normalizedFunction;
}

}
