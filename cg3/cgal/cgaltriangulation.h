#ifndef CG3_TRIANGULATION_H
#define CG3_TRIANGULATION_H

#include <cg3/utilities/utils.h>
#include <cg3/geometry/point.h>
#include <cg3/geometry/2d/point2d.h>

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

namespace CGALInterface {
    namespace Triangulation {
        struct FaceInfo2 {
                FaceInfo2(){}
                int nesting_level;
                bool in_domain(){
                    return nesting_level%2 == 1;
                }
        };

        static bool dummy;

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

        static std::vector< std::vector<Point2Dd > > dummy_holes2D;
        static std::vector< std::vector<Pointd> > dummy_holes;

        void markDomains(CDT& ct, CDT::Face_handle start, int index, std::list<CDT::Edge>& border);
        void markDomains(CDT& cdt);
        std::vector<std::array<Point2Dd , 3> > triangulate(const std::vector<Point2Dd >& polygon, const std::vector<std::vector<Point2Dd > >& holes = dummy_holes2D);
        std::vector<std::array<Pointd, 3> > triangulate(const Vec3 &normal, const std::vector<Pointd>& polygon, const std::vector<std::vector<Pointd> >& holes = dummy_holes, bool& nonRegularPolygon = dummy);
    }
}

}

#endif // CG3_TRIANGULATION_H
