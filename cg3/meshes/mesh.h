/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_MESH_H
#define CG3_MESH_H

#include <cg3/geometry/bounding_box3.h>
#include <string>

namespace cg3 {

class Mesh {
public:
    Mesh(){}
    virtual ~Mesh(){}

    virtual unsigned int numberVertices() const = 0;
    virtual unsigned int numberFaces() const = 0;
    virtual BoundingBox3 boundingBox() const = 0;

    virtual void scale(double scaleFactor) = 0;
    virtual void translate(const Vec3d& dir) = 0;
    virtual void rotate(const Vec3d& axis, double angle, const Point3d& centroid = Point3d()) = 0;

    virtual Point3d barycenter() const = 0;

    virtual bool loadFromFile(const std::string& filename) = 0;
    virtual bool loadFromObj(const std::string& filename) = 0;
	virtual bool loadFromPly(const std::string& filename) = 0;

    virtual bool saveOnObj(const std::string& filename) const = 0;
	virtual bool saveOnPly(const std::string& filename, bool binary = true) const = 0;
};

} //namespace cg3
#endif // CG3_MESH_H
