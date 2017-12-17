/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  * @author Andreas Scalas (andreasscalas@gmail.com)
  */

#include "line.h"

namespace cg3 {

Line::Line(){
}

Line::Line(const Pointd &p0, const Vec3 &dir) : p0(p0), dir(dir){
    this->dir.normalize();
}

const Vec3&Line::getDir() const {
    return dir;
}

const Pointd&Line::getStartingPoint() const{
    return p0;
}

bool Line::pointLiesOnLine(const Pointd& p) const{
    if (p.x() != 0 && p.y() != 0 && p.z() != 0){
        Vec3 t = (dir - p0) / p;
        return (t.x() == t.y() && t.x() == t.z());
    }
    else {
        return false; /** \todo */
    }
}

void Line::serialize(std::ofstream& binaryFile) const {
    Serializer::serializeObjectAttributes("cg3Line", binaryFile, p0, dir);
}

void Line::deserialize(std::ifstream& binaryFile) {
    Serializer::deserializeObjectAttributes("cg3Line", binaryFile, p0, dir);
}

}
