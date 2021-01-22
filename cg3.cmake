#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

set(CMAKE_CXX_STANDARD 14)

option(CG3_STATIC "" ON)

include(${CMAKE_CURRENT_LIST_DIR}/external/external.cmake)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cg3)

