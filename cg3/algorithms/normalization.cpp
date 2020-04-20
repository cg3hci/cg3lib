/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (muntoni.alessandro@gmail.com)
 */
#include "normalization.h"

#include <limits>

#include <cmath>

namespace cg3 {

CG3_INLINE std::vector<double> linearNormalization(
        const std::vector<double>& function,
        const double minFunction,
        const double maxFunction)
{
    std::vector<double> normalizedFunction(function.size());

    for(size_t i = 0; i < function.size(); i++){
        normalizedFunction[i] = (function[i] - minFunction) / (maxFunction - minFunction);
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

    //We find the variance from 0
    double positiveSTD = 0;
    double negativeSTD = 0;

    size_t numPositive = 0;
    size_t numNegative = 0;
    for(size_t i = 0; i < function.size(); i++) {
        if (function[i] >= 0) {
            positiveSTD += (function[i] * function[i]);
            numPositive++;
        }
        else {
            negativeSTD += (function[i] * function[i]);
            numNegative++;
        }
    }
    positiveSTD /= numPositive;
    negativeSTD /= numNegative;

    positiveSTD = std::sqrt(positiveSTD) * stdMultiplier;
    negativeSTD = std::sqrt(negativeSTD) * stdMultiplier;

    for(size_t i = 0; i < function.size(); i++) {
        if (function[i] >= 0) {
            if (function[i] > positiveSTD)
                normalizedFunction[i] = 1;
            else
                normalizedFunction[i] = 0.5 + ((function[i] / positiveSTD) / 2.0);
        }
        else {
            if (-function[i] > negativeSTD)
                normalizedFunction[i] = 0;
            else
                normalizedFunction[i] = 0.5 - ((-function[i] / negativeSTD) / 2.0);
        }
    }

    return normalizedFunction;
}

}
