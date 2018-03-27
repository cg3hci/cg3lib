/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "triangulation.h"

#include <cg3/geometry/transformations.h>

namespace cg3 {

/**
 * @ingroup cg3cgal
 * @brief cgal::triangulation::triangulate
 * @param normal
 * @param polygon
 * @param holes
 * @param nonRegularPolygon
 * @return
 */
std::vector<std::array<Pointd, 3> > cgal::triangulate(
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
    triangles2D = cgal::triangulate(polygon2D, innerPolygons2D);
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

