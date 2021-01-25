#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

cmake_minimum_required(VERSION 3.9)
project(cg3-bipartite_graph-example)

add_executable(bipartite_graph main.cpp)

target_link_libraries(bipartite_graph PUBLIC cg3lib)
