#ifndef CG3_LINE_H
#define CG3_LINE_H

#include "point.h"
namespace cg3 {

class Line {
    public:
        Line();
        Line(const Pointd& p0, const Vec3& dir);
        const Vec3& getDir() const;
        const Pointd& getStartingPoint() const;

        bool pointBelonging(const Pointd &p) const;

    protected:
        Pointd p0;
        Vec3 dir;

};

}

#endif // LINE_H
