#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3-adding_manager-example)

add_executable(adding_manager example_manager.h example_manager.cpp main.cpp example_manager.ui)

target_link_libraries(adding_manager PUBLIC cg3lib)
