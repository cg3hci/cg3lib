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

bool Line::pointBelonging(const Pointd& p) const{
    if (p.x() != 0 && p.y() != 0 && p.z() != 0){
        Vec3 t = (dir - p0) / p;
        return (t.x() == t.y() && t.x() == t.z());
    }
    else {
        return false; /** \todo */
    }
}

}
