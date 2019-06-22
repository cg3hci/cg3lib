/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_VORO_PARSER_H
#define CG3_VORO_PARSER_H

#include <cg3/geometry/point3.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <voro++.hh>
#pragma GCC diagnostic pop
#else
#include <voro++.hh>
#endif

namespace cg3 {
namespace voro {
namespace internal {
	std::vector<std::vector<Point3d>> parseAllVertices(::voro::container& container);
	std::vector<std::vector<std::vector<uint> > > parseAllFaces(::voro::container& container);
	std::vector<std::vector<int>> parseAdjacences(::voro::container& container);
} //namespace cg3::voro::internal
} //namespace cg3::voro
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_VORO_PARSER_CPP "voro_parser.cpp"
#include CG3_VORO_PARSER_CPP
#undef CG3_VORO_PARSER_CPP
#endif //CG3_STATIC

#endif // CG3_VORO_PARSER_H
