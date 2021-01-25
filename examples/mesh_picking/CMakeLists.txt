#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3-mesh_picking-example)

add_executable(mesh_picking picker.h picker.cpp main.cpp)

target_link_libraries(mesh_picking PUBLIC cg3lib)
target_compile_definitions(mesh_picking PUBLIC SOURCE_PATH=${CMAKE_CURRENT_SOURCE_DIR})
