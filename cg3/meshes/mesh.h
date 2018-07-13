/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_MESH_H
#define CG3_MESH_H

#include <cg3/geometry/bounding_box.h>
#include <string>

namespace cg3 {

class Mesh {
public:
    Mesh(){}
    virtual ~Mesh(){}

    virtual unsigned int numberVertices() const = 0;
    virtual unsigned int numberFaces() const = 0;
    virtual BoundingBox boundingBox() const = 0;

    virtual void scale(double scaleFactor) = 0;
    virtual void translate(const Vec3& dir) = 0;
    virtual void rotate(const Vec3& axis, double angle, const Pointd& centroid = Pointd()) = 0;

    virtual Pointd barycenter() const = 0;

    virtual bool loadFromFile(const std::string& filename) = 0;
    virtual bool loadFromObj(const std::string& filename) = 0;
    virtual bool loadFromPly(const std::string& filename) = 0;

    virtual bool saveOnObj(const std::string& filename) const = 0;
    virtual bool saveOnPly(const std::string& filename) const = 0;
};

} //namespace cg3
#endif // CG3_MESH_H
