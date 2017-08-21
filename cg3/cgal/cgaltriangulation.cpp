#include "cgaltriangulation.h"

#include <cg3/geometry/transformations.h>

namespace cg3 {

void CGALInterface::Triangulation::markDomains(
        CDT& ct, CDT::Face_handle start, int index, std::list<CDT::Edge>& border) {
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

void CGALInterface::Triangulation::markDomains(CDT& cdt) {
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

std::vector<std::array<Point2Dd, 3> > CGALInterface::Triangulation::triangulate(
        const std::vector<Point2Dd >& polygon,
        const std::vector<std::vector<Point2Dd > >& holes) {

    std::vector<std::array<Point2Dd, 3> > triangles;
    Polygon_2 polygon1;
    std::vector<Polygon_2> innerPolygons;
    for (unsigned int i = 0; i < polygon.size(); ++i){
        CGALPoint p(polygon[i].x(), polygon[i].y());
        polygon1.push_back(p);
    }
    if (holes.size() > 0){
        for (unsigned int i = 0; i < holes.size(); ++i) {
            Polygon_2 innerPolygon;
            for (unsigned int j = 0; j < holes[i].size(); ++j) {
                CGALPoint p(holes[i][j].x(), holes[i][j].y());
                innerPolygon.push_back(p);
            }
            innerPolygons.push_back(innerPolygon);
        }
    }

    ///TRIANGULATION

    CDT cdt;
    cdt.insert_constraint(polygon1.vertices_begin(), polygon1.vertices_end(), true);
    for (unsigned int i = 0; i < innerPolygons.size(); ++i)
        cdt.insert_constraint(innerPolygons[i].vertices_begin(), innerPolygons[i].vertices_end(), true);
    markDomains(cdt);

    for (CDT::Finite_faces_iterator fit=cdt.finite_faces_begin(); fit!=cdt.finite_faces_end();++fit) {
        if ( fit->info().in_domain() ) {
            Triangle triangle = *fit;
            CDT::Vertex_handle v = triangle.vertex(0);
            const CGALPoint p1 = v->point();
            v = triangle.vertex(1);
            const CGALPoint p2 = v->point();
            v = triangle.vertex(2);
            const CGALPoint p3 = v->point();

            std::array<Point2Dd, 3> t;
            t[0] = Point2Dd(p1.x(), p1.y());
            t[1] = Point2Dd(p2.x(), p2.y());
            t[2] = Point2Dd(p3.x(), p3.y());
            triangles.push_back(t);
        }
    }
    return triangles;
}

std::vector<std::array<Pointd, 3> > CGALInterface::Triangulation::triangulate(
        const Vec3 &normal,
        const std::vector<Pointd>& polygon,
        const std::vector<std::vector<Pointd> >& holes,
        bool& nonRegularPolygon) {

    std::vector<std::array<Pointd, 3> > triangles;
    std::map<Point2Dd, Pointd> pointsVerticesMap;

    //Rotation of the coordinates
    Vec3 zAxis(0,0,1);
    Vec3 axis = -(normal.cross(zAxis));
    axis.normalize();
    double dot = normal.dot(zAxis);
    double angle = acos(dot);

    double r[3][3] = {{0}};
    if (normal != zAxis){
        if (normal == -zAxis){
            axis = Vec3(1,0,0);
        }
        getRotationMatrix(axis, angle, r);
    }
    else {
        r[0][0] = r[1][1] = r[2][2] = 1;
    }

    //rotate points and make 2D polygon
    std::vector<Point2Dd> polygon2D;
    std::vector<std::vector<Point2Dd> > innerPolygons2D;
    for (unsigned int i = 0; i < polygon.size(); ++i){
        Pointd a = polygon[i];
        Pointd p1(a.x() * r[0][0] + a.y() * r[1][0] +a.z() * r[2][0], a.x() * r[0][1] + a.y() * r[1][1] +a.z() * r[2][1], a.x() * r[0][2] + a.y() * r[1][2] +a.z() * r[2][2]);
        Point2Dd p(p1.x(), p1.y());
        polygon2D.push_back(p);
        pointsVerticesMap[p] = a;
    }
    if (holes.size() > 0){
        for (unsigned int i = 0; i < holes.size(); ++i) {
            std::vector<Point2Dd> innerPolygon;
            for (unsigned j = 0; j < holes[i].size(); ++j) {
                Pointd a = holes[i][j];
                Pointd p1(a.x() * r[0][0] + a.y() * r[1][0] + a.z() * r[2][0],
                        a.x() * r[0][1] + a.y() * r[1][1] + a.z() * r[2][1],
                        a.x() * r[0][2] + a.y() * r[1][2] + a.z() * r[2][2]);
                Point2Dd p(p1.x(), p1.y());
                innerPolygon.push_back(p);
                pointsVerticesMap[p] = a;
            }
            innerPolygons2D.push_back(innerPolygon);
        }
    }
    std::vector<std::array<Point2Dd, 3> > triangles2D;
    triangles2D = triangulate(polygon2D, innerPolygons2D);
    triangles.clear();
    triangles.reserve(triangles2D.size());

    nonRegularPolygon = false;

    for (unsigned int i = 0; i < triangles2D.size(); i++){
        std::array<Point2Dd, 3> triangle2D = triangles2D[i];
        std::array<Pointd, 3> triangle3D;

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

