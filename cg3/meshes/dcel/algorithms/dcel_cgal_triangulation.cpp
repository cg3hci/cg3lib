/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_cgal_triangulation.h"

#ifdef CG3_CGAL_DEFINED

#include <map>

#include <cg3/geometry/point2.h>
#include <cg3/geometry/transformations3.h>
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

CG3_INLINE std::vector<std::array<cg3::Point3d, 3> > triangulate3(
        const cg3::Vec3d &normal, 
        const std::vector<cg3::Point3d> &polygon, 
        const std::vector<std::vector<cg3::Point3d> > &holes, 
        bool &nonRegularPolygon)
{
	std::vector<std::array<Point3d, 3> > triangles;
    std::map<Point2d, Point3d> pointsVerticesMap;

    //Rotation of the coordinates
    Vec3d zAxis(0,0,1);
    Vec3d axis = -(normal.cross(zAxis));
    axis.normalize();
    double dot = normal.dot(zAxis);
    double angle = acos(dot);

    double r[3][3] = {{0}};
    if (normal != zAxis){
        if (normal == -zAxis){
            axis = Vec3d(1,0,0);
        }
        rotationMatrix(axis, angle, r);
    }
    else {
        r[0][0] = r[1][1] = r[2][2] = 1;
    }

    //rotate points and make 2D polygon
    std::vector<Point2d> polygon2D;
    std::vector<std::vector<Point2d> > innerPolygons2D;
    for (unsigned int i = 0; i < polygon.size(); ++i){
        Point3d a = polygon[i];
        Point3d p1(a.x() * r[0][0] + a.y() * r[1][0] +a.z() * r[2][0], a.x() * r[0][1] + a.y() * r[1][1] +a.z() * r[2][1], a.x() * r[0][2] + a.y() * r[1][2] +a.z() * r[2][2]);
        Point2d p(p1.x(), p1.y());
        polygon2D.push_back(p);
        pointsVerticesMap[p] = a;
    }
    if (holes.size() > 0){
        for (unsigned int i = 0; i < holes.size(); ++i) {
            std::vector<Point2d> innerPolygon;
            for (unsigned j = 0; j < holes[i].size(); ++j) {
                Point3d a = holes[i][j];
                Point3d p1(a.x() * r[0][0] + a.y() * r[1][0] + a.z() * r[2][0],
                        a.x() * r[0][1] + a.y() * r[1][1] + a.z() * r[2][1],
                        a.x() * r[0][2] + a.y() * r[1][2] + a.z() * r[2][2]);
                Point2d p(p1.x(), p1.y());
                innerPolygon.push_back(p);
                pointsVerticesMap[p] = a;
            }
            innerPolygons2D.push_back(innerPolygon);
        }
    }
    std::vector<std::array<Point2d, 3> > triangles2D;
	triangles2D = triangulate2(polygon2D, innerPolygons2D);
    triangles.clear();
    triangles.reserve(triangles2D.size());

    nonRegularPolygon = false;

    for (unsigned int i = 0; i < triangles2D.size(); i++){
        std::array<Point2d, 3> triangle2D = triangles2D[i];
        std::array<Point3d, 3> triangle3D;

        if (pointsVerticesMap.find(triangle2D[0]) != pointsVerticesMap.end() &&
                pointsVerticesMap.find(triangle2D[1]) != pointsVerticesMap.end() &&
                pointsVerticesMap.find(triangle2D[2]) != pointsVerticesMap.end()) {

            triangle3D[0] = pointsVerticesMap[triangle2D[0]];
            triangle3D[1] = pointsVerticesMap[triangle2D[1]];
            triangle3D[2] = pointsVerticesMap[triangle2D[2]];
            triangles.push_back(triangle3D);
        }
        else {
            nonRegularPolygon = true;
        }
    }

    return triangles;
}

}
}

#endif // CG3_CGAL_DEFINED
