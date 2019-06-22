/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "voronoi2.h"

// standard includes
#include <iostream>
#include <fstream>
#include <cassert>
// includes for defining the Voronoi diagram adaptor
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>

namespace cg3 {
namespace cgal {
namespace internal {

typedef CGAL::Exact_predicates_inexact_constructions_kernel                  K;
typedef CGAL::Delaunay_triangulation_2<K>                                    DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                 AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT,AT,AP>                                    VD;
// typedef for the result type of the point location
typedef AT::Site_2                    Site_2;
typedef AT::Point_2                   Point_2;
typedef VD::Locate_result             Locate_result;
typedef VD::Vertex_handle             Vertex_handle;
typedef VD::Face_handle               Face_handle;
typedef VD::Halfedge_handle           Halfedge_handle;
typedef VD::Ccb_halfedge_circulator   Ccb_halfedge_circulator;

} //namespace cg3::cgal::internal

/**
 * @ingroup cg3cgal
 * @brief computeVoronoiDiagram
 * @param sites
 * @return
 */
CG3_INLINE std::vector<std::vector<cg3::Point2d> > voronoiDiagram2(
        const std::vector<cg3::Point2d>& sites)
{
    std::vector<std::vector<cg3::Point2d> > voronoi;

    internal::VD vd;
    for (const Point2d& p : sites) {
        internal::Site_2 t(p.x(), p.y());
        vd.insert(t);
    }
    assert( vd.is_valid() );

    for (internal::VD::Face_iterator fit = vd.faces_begin(); fit != vd.faces_end(); ++fit){
        internal::VD::Face f = *fit;

        if (!f.is_unbounded()) {
            std::vector<cg3::Point2d> face;
            internal::VD::Face::Ccb_halfedge_circulator start = f.ccb();
            internal::VD::Face::Ccb_halfedge_circulator curr = start;
            do {
                internal::VD::Halfedge he = *curr;
                if (he.has_source()){
                    Point2d p;
                    p.x() = (*he.source()).point().x();
                    p.y() = (*he.source()).point().y();
                    face.push_back(p);
                }
            } while (++curr != start);
            voronoi.push_back(face);
        }
    }
    return voronoi;
}

/**
 * @ingroup cg3cgal
 * @brief computeVoronoiDiagram
 * @param sites
 * @param vl
 * @param fl
 */
CG3_INLINE void voronoiDiagram2(
        const std::vector<Point2d>& sites,
        std::vector<Point2d>& vl,
        std::vector<std::vector<unsigned int> >& fl)
{
    std::vector<std::vector<cg3::Point2d> > vd = voronoiDiagram2(sites);
    vl.clear();
    fl.clear();
    std::map<cg3::Point2d, unsigned int> vertMap;
    unsigned int nv = 0;
    fl.reserve(vd.size());
    for (const std::vector<cg3::Point2d>& vf : vd){
        std::vector<unsigned int> face;
        face.reserve(vf.size());
        for (const cg3::Point2d& p : vf){
            std::map<cg3::Point2d, unsigned int>::iterator vit = vertMap.find(p);
            if (vit == vertMap.end()){ // vertex doesn't exist in the list
                vertMap[p] = nv;
                vl.push_back(p);
                face.push_back(nv);
                nv++;
            }
            else {
                face.push_back(vit->second);
            }
        }
        fl.push_back(face);
    }
}

} //namespace cg3::cgal
} //namespace cg3
