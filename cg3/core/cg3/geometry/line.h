#ifndef CG3_LINE_H
#define CG3_LINE_H

#include "point.h"
namespace cg3 {

class Line : SerializableObject{
    public:
        Line();
        Line(const Pointd& p0, const Vec3& dir);
        const Vec3& getDir() const;
        const Pointd& getStartingPoint() const;

        bool pointLiesOnLine(const Pointd &p) const;

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:
        Pointd p0;
        Vec3 dir;
};

}

#endif // LINE_H
