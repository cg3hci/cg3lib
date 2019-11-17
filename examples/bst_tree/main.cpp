/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

///Test cg3 core module
#ifdef CG3_CORE_DEFINED
#include <cg3/data_structures/arrays/arrays.h>
#include <cg3/geometry/bounding_box3.h>
#include <cg3/utilities/comparators.h>
#include <cg3/utilities/timer.h>
#endif

#include <cg3/cg3lib.h>
#include "bstsample.h"

#include <iostream>

int main(int argc, char *argv[]) {
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

    std::cout << "------ Binary search tree sample ------" << std::endl << std::endl;
    BSTSample::execute();
    std::cout <<  std::endl << std::endl;
}
