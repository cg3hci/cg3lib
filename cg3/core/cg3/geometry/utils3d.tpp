/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#include "utils3d.h"

namespace cg3 {

    /* ----- UTILS IMPLEMENTATION ----- */

    /**
     * @brief Calculate angle between 2 vectors
     * @param v1 First vector
     * @param v2 Second vector
     * @return Angle in radians
     */
    template <class Vector>
    inline double getAngle(const Vector& v1, const Vector& v2) {
        double dot = v1.dot(v2);
        return acos(dot);
    }

    /**
     * @brief Get internal (clockwise) angle between two 3D vector
     * @param v1 First vector
     * @param v2 Second vector
     * @param direction Axis
     * @return Angle in radians
     */
    inline double getInternalAngle(
            const Vec3& v1, const Vec3& v2,
            const Vec3& direction)
    {
        if (cg3::epsilonEqual(v1,v2))
            return 0;
        if (cg3::epsilonEqual(v1,-v2))
            return M_PI;

        double angle = getAngle(v1,v2);

        Vec3 cross = v1.cross(v2);
        cross.normalize();

        int sign = cross.dot(direction) >= 0 ? 1 : -1;

        return sign*angle;
    }

}
