/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#include "line3.h"

namespace cg3 {

CG3_INLINE Line3::Line3()
{
}

CG3_INLINE Line3::Line3(const Point3d &p0, const Vec3d &dir) :
    p0(p0),
    _dir(dir)
{
    this->_dir.normalize();
}

CG3_INLINE const Vec3d&Line3::dir() const
{
    return _dir;
}

CG3_INLINE const Point3d&Line3::startingPoint() const
{
    return p0;
}

CG3_INLINE bool Line3::pointLiesOnLine(const Point3d& p) const
{
    if (p.x() != 0 && p.y() != 0 && p.z() != 0){
        Vec3d t = (_dir - p0) / p;
        return (t.x() == t.y() && t.x() == t.z());
    }
    else {
        return false; /** \todo */
    }
}

CG3_INLINE void Line3::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3Line", binaryFile, p0, _dir);
}

CG3_INLINE void Line3::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3Line", binaryFile, p0, _dir);
}

} //namespace cg3

//hash specialization
CG3_INLINE std::size_t std::hash<cg3::Line3>::operator()(const cg3::Line3 &k) const
{
    std::size_t h = 0;
    cg3::hashCombine(h, k.startingPoint(), k.dir());
    return h;
}
