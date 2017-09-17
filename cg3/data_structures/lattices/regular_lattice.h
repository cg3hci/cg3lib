#ifndef CG3_REGULAR_LATTICE_H
#define CG3_REGULAR_LATTICE_H

#include <cg3/geometry/bounding_box.h>

namespace cg3 {

template <class VT>
class RegularLattice : public cg3::SerializableObject
{
public:
    RegularLattice();
    RegularLattice(const cg3::BoundingBox& bb, double unit, bool outsideBB = true);

    unsigned int resX() const;
    unsigned int resY() const;
    unsigned int resZ() const;

    const cg3::BoundingBox& boundingBox() const;

    cg3::Pointd nearestVertex(const cg3::Pointd& p) const;
    const VT& vertexProperty(const cg3::Pointd& p) const;
    void setVertexProperty(const cg3::Pointd& p, const VT& property);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    bool deserialize(std::ifstream& binaryFile);

    class VertexIterator;


protected:

    cg3::Pointd getPoint(unsigned int i, unsigned int j, unsigned int k) const;
    unsigned int getIndex(unsigned int i, unsigned int j, unsigned int k) const;
    int getIndexOfCoordinateX(double x) const;
    int getIndexOfCoordinateY(double y) const;
    int getIndexOfCoordinateZ(double z) const;

    cg3::BoundingBox bb;
    double unit;
    unsigned int mresX, mresY, mresZ;
    std::vector<VT> vertexProperties;
};

}

#endif // CG3_REGULAR_LATTICE_H
