/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#ifndef CG3_BOUNDING_BOX_H
#define CG3_BOUNDING_BOX_H

#include <float.h>
#include "point.h"
#include "../utilities/color.h"

namespace cg3 {

/**
 * @ingroup cg3core
 * @class BoundingBox
 * @brief The BoundingBox class models a Bounding Box which contains a 3D mesh.
 *
 * It is composed of two 3D points representing the minimum and maximum coordinates that generates the bounding box.
 * The class provides methods like for obtaining the center or the diagonal of the bounding box.
 */
class BoundingBox : public SerializableObject
{
public:

    BoundingBox();
    BoundingBox(const Pointd& min, const Pointd& max);

    const Pointd& min()        const;
    const Pointd& max()        const;
    const double& minX()       const;
    const double& minY()       const;
    const double& minZ()       const;
    const double& maxX()       const;
    const double& maxY()       const;
    const double& maxZ()       const;
    double lengthX()        const;
    double lengthY()        const;
    double lengthZ()        const;

    Pointd  center()    const;
    double diag()       const;
    bool isValid() const;
    bool isStrictlyIntern(const Pointd& p)     const;
    bool isStrictlyInside(const Pointd& p)     const;
    bool isStrictlyIntern(double px, double py, double pz)     const;
    bool isStrictlyInside(double px, double py, double pz)     const;
    bool isIntern(const Pointd& p)     const;
    bool isInside(const Pointd& p)     const;
    bool isIntern(double px, double py, double pz)     const;
    bool isInside(double px, double py, double pz)     const;
    bool isEpsilonIntern(const Pointd& p, double epsilon = 1e-6)     const;
    bool isEpsilonInside(const Pointd& p, double epsilon = 1e-6)     const;
    bool isEpsilonIntern(double px, double py, double pz, double epsilon = 1e-6)     const;
    bool isEpsilonInside(double px, double py, double pz, double epsilon = 1e-6)     const;
    bool intersect(const BoundingBox& otherBox);
    void extremes(std::vector<Pointd> &extremes) const;
    std::vector<Pointd> extremes() const;

    //Operators
    const double &operator ()(unsigned int i) const;
    Pointd operator[](unsigned int i)                 const;

    void saveOnObj(const std::string &filename, const Color& c = Color(128, 128, 128)) const;

    void setMin(const Pointd& min);
    Pointd& min();
    void setMax(const Pointd& max);
    Pointd& max();
    void setMin(double x, double y, double z);
    void setMax(double x, double y, double z);
    void setMinX(double x);
    double& minX();
    void setMinY(double y);
    double& minY();
    void setMinZ(double z);
    double& minZ();
    void setMaxX(double x);
    double& maxX();
    void setMaxY(double y);
    double& maxY();
    void setMaxZ(double z);
    double& maxZ();
    void reset();

    //Operators
    double& operator()(unsigned int i);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    #ifdef CG3_OLD_NAMES_COMPATIBILITY
    inline const Pointd& getMin() const {return min();}
    inline const Pointd& getMax() const {return max();}
    inline const double& getMinX() const {return minX();}
    inline const double& getMinY() const {return minY();}
    inline const double& getMinZ() const {return minZ();}
    inline const double& getMaxX() const {return maxX();}
    inline const double& getMaxY() const {return maxY();}
    inline const double& getMaxZ() const {return maxZ();}
    inline double getLengthX() const {return lengthX();}
    inline double getLengthY() const {return lengthY();}
    inline double getLengthZ() const {return lengthZ();}
    inline void getExtremes(std::vector<Pointd> &v) const {extremes(v);}
    inline std::vector<Pointd> getExtremes() const {return extremes();}
    #endif

protected:
    Pointd _min;
    Pointd _max;
};

typedef BoundingBox Box;

} //namespace cg3

//hash specialization
namespace std {

template <>
struct hash<cg3::BoundingBox> {
    size_t operator()(const cg3::BoundingBox& k) const;
};

} //namespace std

#include "bounding_box.tpp"

#endif // CG3_BOUNDING_BOX_H
