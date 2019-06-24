/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "triangulation3.h"

#include <map>

#include "triangulation2.h"
#include <cg3/geometry/transformations3.h>

namespace cg3 {
namespace cgal {

/**
 * @ingroup cg3cgal
 * @brief cgal::triangulation::triangulate
 * @param normal
 * @param polygon
 * @param holes
 * @param nonRegularPolygon
 * @return
 */
CG3_INLINE std::vector<std::array<Point3d, 3> > triangulate3(
        const Vec3d &normal,
        const std::vector<Point3d>& polygon,
        const std::vector<std::vector<Point3d> >& holes,
        bool& nonRegularPolygon)
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
	triangles2D = cgal::triangulate2(polygon2D, innerPolygons2D);
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

} //namespace cg3::cgal
} //namespace cg3

