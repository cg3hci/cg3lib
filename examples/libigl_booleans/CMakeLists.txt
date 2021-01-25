#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3-libigl_booleans-example)

add_executable(libigl_booleans main.cpp)

target_link_libraries(libigl_booleans PUBLIC cg3lib)
target_compile_definitions(libigl_booleans PUBLIC SOURCE_PATH=${CMAKE_CURRENT_SOURCE_DIR})

