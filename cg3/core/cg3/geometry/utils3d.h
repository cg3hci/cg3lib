#ifndef CG3_UTILS3D_H
#define CG3_UTILS3D_H

#include "cg3/geometry/point.h"

namespace cg3 {
    template <class Vector>
    inline double getAngle(const Vector& v1, const Vector& v2);
    inline double getInternalAngle(const Vec3& v1, const Vec3& v2, const Vec3& direction);


}

#include "utils3d.tpp"

#endif // CG3_UTILS3D_H
