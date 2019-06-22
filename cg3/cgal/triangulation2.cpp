/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "triangulation2.h"

#include <cg3/utilities/utils.h>

#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshift-negative-value"
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

#ifdef __APPLE__
#pragma clang diagnostic pop
#endif

#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Polygon_2.h>

namespace cg3 {
namespace cgal {
namespace internal {

struct FaceInfo2 {
        FaceInfo2(){}
        int nesting_level;
        bool in_domain(){
            return nesting_level%2 == 1;
        }
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel             K;
typedef CGAL::Triangulation_vertex_base_2<K>                            Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2,K>          Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>              Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>                     TDS;
typedef CGAL::Exact_predicates_tag                                      Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>        CDT;
typedef CDT::Point                                                      CGALPoint;
typedef CGAL::Polygon_2<K>                                              Polygon_2;

typedef CGAL::Epick                                                     E;
typedef CGAL::Triangulation_ds_face_base_2<TDS>                         TDFB2;
typedef CGAL::Triangulation_face_base_2<E, TDFB2>                       TFB2;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2, E, TFB2>   TFBI;
typedef CGAL::Constrained_triangulation_face_base_2<E, TFBI >           Triangle;

CG3_INLINE void markDomains(CDT& ct, CDT::Face_handle start, int index, std::list<CDT::Edge>& border)
{
    if(start->info().nesting_level != -1){
        return;
    }
    std::list<CDT::Face_handle> queue;
    queue.push_back(start);
    while(! queue.empty()){
        CDT::Face_handle fh = queue.front();
        queue.pop_front();
        if(fh->info().nesting_level == -1){
            fh->info().nesting_level = index;
            for(int i = 0; i < 3; i++){
                CDT::Edge e(fh,i);
                CDT::Face_handle n = fh->neighbor(i);
                if(n->info().nesting_level == -1){
                    if(ct.is_constrained(e)) border.push_back(e);
                    else queue.push_back(n);
                }
            }
        }
    }
}

CG3_INLINE void markDomains(CDT& cdt)
{
    for(CDT::All_faces_iterator it = cdt.all_faces_begin(); it != cdt.all_faces_end(); ++it){
        it->info().nesting_level = -1;
    }
    std::list<CDT::Edge> border;
    markDomains(cdt, cdt.infinite_face(), 0, border);
    while(! border.empty()){
        CDT::Edge e = border.front();
        border.pop_front();
        CDT::Face_handle n = e.first->neighbor(e.second);
        if(n->info().nesting_level == -1){
            markDomains(cdt, n, e.first->info().nesting_level+1, border);
        }
    }
}

} //namespace cg3::cgal::internal

/**
 * @ingroup cg3cgal
 * @brief triangulate
 * @param polygon
 * @param holes
 * @return
 */
CG3_INLINE std::vector<std::array<Point2d, 3> > triangulate2(
        const std::vector<Point2d >& polygon,
        const std::vector<std::vector<Point2d > >& holes)
{

    std::vector<std::array<Point2d, 3> > triangles;
    internal::Polygon_2 polygon1;
    std::vector<internal::Polygon_2> innerPolygons;
    for (unsigned int i = 0; i < polygon.size(); ++i){
        internal::CGALPoint p(polygon[i].x(), polygon[i].y());
        polygon1.push_back(p);
    }
    if (holes.size() > 0){
        for (unsigned int i = 0; i < holes.size(); ++i) {
            internal::Polygon_2 innerPolygon;
            for (unsigned int j = 0; j < holes[i].size(); ++j) {
                internal::CGALPoint p(holes[i][j].x(), holes[i][j].y());
                innerPolygon.push_back(p);
            }
            innerPolygons.push_back(innerPolygon);
        }
    }

    ///TRIANGULATION

    internal::CDT cdt;
    cdt.insert_constraint(polygon1.vertices_begin(), polygon1.vertices_end(), true);
    for (unsigned int i = 0; i < innerPolygons.size(); ++i)
        cdt.insert_constraint(innerPolygons[i].vertices_begin(), innerPolygons[i].vertices_end(), true);
    internal::markDomains(cdt);

    for (internal::CDT::Finite_faces_iterator fit=cdt.finite_faces_begin(); fit!=cdt.finite_faces_end();++fit) {
        if ( fit->info().in_domain() ) {
            internal::Triangle triangle = *fit;
            internal::CDT::Vertex_handle v = triangle.vertex(0);
            const internal::CGALPoint p1 = v->point();
            v = triangle.vertex(1);
            const internal::CGALPoint p2 = v->point();
            v = triangle.vertex(2);
            const internal::CGALPoint p3 = v->point();

            std::array<Point2d, 3> t;
            t[0] = Point2d(p1.x(), p1.y());
            t[1] = Point2d(p2.x(), p2.y());
            t[2] = Point2d(p3.x(), p3.y());
            triangles.push_back(t);
        }
    }
    return triangles;
}

} //namespace cg3::cgal
} //namespace cg3
