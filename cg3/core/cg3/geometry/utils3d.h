/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

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
