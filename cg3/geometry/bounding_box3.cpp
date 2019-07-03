/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bounding_box3.h"
#include "../io/load_save_file.h"

namespace cg3 {

/**
 * @brief Constructor, creates a bounding box and calls BoundingBox::reset() method
 */
CG3_INLINE BoundingBox3::BoundingBox3()
{
    reset();
}

/**
 * @brief Constructor, creates a bounding box whith with minimum equal to the parameter \c min and maximum equal to the parameter \c max
 * @param[in] min: point setted as minimum point of the bounding box
 * @param[in] max: point setted as maximum point of the bounding box
 */
CG3_INLINE BoundingBox3::BoundingBox3(const Point3d& min, const Point3d& max) :
    _min(min),
    _max(max)
{
}

/*************************
* Public Inline Methods *
*************************/

/**
 * @brief Returns the minimum point of the bounding box
 * @return The minimum point
 */
CG3_INLINE const Point3d& BoundingBox3::min() const
{
    return _min;
}

/**
 * @brief Returns the maximum point of the bounding box
 * @return The maximum point
 */
CG3_INLINE const Point3d& BoundingBox3::max() const
{
    return _max;
}

/**
 * @brief Returns the x component of the minimum point of the bounding box
 * @return X component of the minimum point
 */
CG3_INLINE const double& BoundingBox3::minX() const
{
    return _min.x();
}

/**
 * @brief Returns the y component of the minimum point of the bounding box
 * @return Y component of the minimum point
 */
CG3_INLINE const double& BoundingBox3::minY() const
{
    return _min.y();
}

/**
 * @brief Returns the z component of the minimum point of the bounding box
 * @return Z component of the minimum point
 */
CG3_INLINE const double& BoundingBox3::minZ() const
{
    return _min.z();
}

/**
 * @brief Returns the x component of the maximum point of the bounding box
 * @return X component of the maximum point
 */
CG3_INLINE const double& BoundingBox3::maxX() const
{
    return _max.x();
}

/**
 * @brief Returns the y component of the maximum point of the bounding box
 * @return Y component of the maximum point
 */
CG3_INLINE const double& BoundingBox3::maxY() const
{
    return _max.y();
}

/**
 * @brief Returns the Z component of the maximum point of the bounding box
 * @return Z component of the maximum point
 */
CG3_INLINE const double& BoundingBox3::maxZ() const
{
    return _max.z();
}

CG3_INLINE double BoundingBox3::lengthX() const
{
    return _max.x() - _min.x();
}

CG3_INLINE double BoundingBox3::lengthY() const
{
    return _max.y() - _min.y();
}

CG3_INLINE double BoundingBox3::lengthZ() const
{
    return _max.z() - _min.z();
}

/**
 * @brief Calculates the center of the bounding box
 * @return The point centered in the bounding box
 */
CG3_INLINE Point3d BoundingBox3::center() const
{
    return (_min + _max) * 0.5;
}

/**
 * @brief Calculates the length of the diagonal of the bounding box
 * @return The length of the diagonal of the bounding box
 */
CG3_INLINE double BoundingBox3::diag() const
{
    return (_min - _max).length();
}

CG3_INLINE bool BoundingBox3::isValid() const
{
    return _min.x() <= _max.x() && _min.y() <= _max.y() && _min.z() <= _max.z();
}

CG3_INLINE bool BoundingBox3::isStrictlyIntern(const Point3d &p) const
{
    return (p.x() > _min.x() && p.y() > _min.y() && p.z() > _min.z() &&
            p.x() < _max.x() && p.y() < _max.y() && p.z() < _max.z());
}

CG3_INLINE bool BoundingBox3::isStrictlyInside(const Point3d& p) const
{
    return isStrictlyIntern(p);
}

CG3_INLINE bool BoundingBox3::isStrictlyIntern(double px, double py, double pz) const
{
    return (px > _min.x() && py > _min.y() && pz > _min.z() &&
            px < _max.x() && py < _max.y() && pz < _max.z());
}

CG3_INLINE bool BoundingBox3::isStrictlyInside(double px, double py, double pz) const
{
    return isStrictlyIntern(px, py, pz);
}

CG3_INLINE bool BoundingBox3::isIntern(const Point3d &p) const
{
    return (p.x() >= _min.x() && p.y() >= _min.y() && p.z() >= _min.z() &&
            p.x() <= _max.x() && p.y() <= _max.y() && p.z() <= _max.z());
}

CG3_INLINE bool BoundingBox3::isInside(const Point3d& p) const
{
    return isIntern(p);
}

CG3_INLINE bool BoundingBox3::isIntern(double px, double py, double pz) const
{
    return (px >= _min.x() && py >= _min.y() && pz >= _min.z() &&
            px <= _max.x() && py <= _max.y() && pz <= _max.z());
}

CG3_INLINE bool BoundingBox3::isInside(double px, double py, double pz) const
{
    return isIntern(px, py, pz);
}

CG3_INLINE bool BoundingBox3::isEpsilonIntern(const Point3d& p, double epsilon) const
{
    return (p.x() >= _min.x()-epsilon && p.y() >= _min.y()-epsilon && p.z() >= _min.z()-epsilon &&
            p.x() <= _max.x()+epsilon && p.y() <= _max.y()+epsilon && p.z() <= _max.z()+epsilon);
}

CG3_INLINE bool BoundingBox3::isEpsilonInside(const Point3d& p, double epsilon) const
{
    return isEpsilonIntern(p, epsilon);
}

CG3_INLINE bool BoundingBox3::isEpsilonIntern(double px, double py, double pz, double epsilon) const
{
    return (px >= _min.x()-epsilon && py >= _min.y()-epsilon && pz >= _min.z()-epsilon &&
            px <= _max.x()+epsilon && py <= _max.y()+epsilon && pz <= _max.z()+epsilon);
}

CG3_INLINE bool BoundingBox3::isEpsilonInside(double px, double py, double pz, double epsilon) const
{
    return isEpsilonIntern(px, py, pz, epsilon);
}

/**
 * @brief BoundingBox::intersect
 * @param[in] otherBox
 * @return true if otherBox overlaps this box
 * @link http://gamemath.com/2011/09/detecting-whether-two-boxes-overlap/
 */
CG3_INLINE bool BoundingBox3::intersect(const BoundingBox3& otherBox)
{
    if (maxX() <= otherBox.minX()) return false; // a is left of b
    if (minX() >= otherBox.maxX()) return false; // a is right of b
    if (maxY() <= otherBox.minY()) return false; // a is above b
    if (minY() >= otherBox.maxY()) return false; // a is below b
    if (maxZ() <= otherBox.minZ()) return false; // a is behind b
    if (minZ() >= otherBox.maxZ()) return false; // a is in front b
    return true; //boxes overlap
}

/**
 * @brief BoundingBox::intersect
 * @param[in] otherBox
 * @return true if otherBox overlaps this box
 * @link http://gamemath.com/2011/09/detecting-whether-two-boxes-overlap/
 */
CG3_INLINE bool BoundingBox3::overlap(const BoundingBox3& otherBox)
{
	if (maxX() <= otherBox.minX()) return false; // a is left of b
	if (minX() >= otherBox.maxX()) return false; // a is right of b
	if (maxY() <= otherBox.minY()) return false; // a is above b
	if (minY() >= otherBox.maxY()) return false; // a is below b
	if (maxZ() <= otherBox.minZ()) return false; // a is behind b
	if (minZ() >= otherBox.maxZ()) return false; // a is in front b
	return true; //boxes overlap
}

/**
 * @brief BoundingBox::getExtremes
 * @param[out] extremes: a vector of 8 Pointd which are the extremes of the bounding box
 */
CG3_INLINE void BoundingBox3::extremes(std::vector<Point3d>& extremes) const
{
    extremes.resize(8);
	for (uint i = 0; i < 8; ++i) {
		extremes[i] = this->operator[](i);
	}
}

/**
 * @brief BoundingBox::getExtremes
 * @return a vector of 8 Pointd which are the extremes of the bounding box
 */
CG3_INLINE std::vector<Point3d> BoundingBox3::extremes() const
{
    std::vector<Point3d> ext;
    extremes(ext);
    return ext;
}

/**
 * @brief BoundingBox::operator ()
 * @param i
 * @return a double which is a coordinate of minCoord [0-2] or a coordinate of maxCoord[3-5]
 */
CG3_INLINE const double& BoundingBox3::operator ()(unsigned int i) const
{
    assert(i < 6);
    switch (i%6){
        case 0: return _min.x();
        case 1: return _min.y();
        case 2: return _min.z();
        case 3: return _max.x();
        case 4: return _max.y();
        case 5: return _max.z();
    }
    return _min.x();
}

/**
 * @brief BoundingBox::operator []
 * @param i
 * @return a Pointd which is an extreme of the bounding box [0-7]
 */
CG3_INLINE Point3d BoundingBox3::operator[](unsigned int i) const
{
    assert(i < 8);
    switch (i%8){
        case 0: return _min;
        case 1: return Point3d(_max.x(), _min.y(), _min.z());
        case 2: return Point3d(_max.x(), _min.y(), _max.z());
        case 3: return Point3d(_min.x(), _min.y(), _max.z());
        case 4: return Point3d(_min.x(), _max.y(), _min.z());
        case 5: return Point3d(_max.x(), _max.y(), _min.z());
        case 6: return _max;
        case 7: return Point3d(_min.x(), _max.y(), _max.z());
    }
    return _min.x();
}

/**
 * @brief BoundingBox::saveOnObj
 *
 * It saves the bounding box as a quad mesh in the obj file saved on parameters.
 *
 * @param filename
 * @param c
 */
CG3_INLINE void BoundingBox3::saveOnObj(const std::string& filename, const Color &c) const
{
    std::vector<double> v {
        _min.x(), _min.y(), _min.z(),
        _max.x(), _min.y(), _min.z(),
        _max.x(), _min.y(), _max.z(),
        _min.x(), _min.y(), _max.z(),
        _min.x(), _max.y(), _min.z(),
        _max.x(), _max.y(), _min.z(),
        _max.x(), _max.y(), _max.z(),
        _min.x(), _max.y(), _max.z()
    };
    std::vector<int> f {
        0, 1, 2, 3,
        7, 6, 5, 4,
        2, 1, 5, 6,
        0, 3, 7, 4,
        3, 2, 6, 7,
        1, 0, 4, 5
    };
    int r = c.red(), g = c.green(), b = c.blue();
    std::vector<int> cl {
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b
    };
	io::FileMeshMode fm;
	fm.setQuadMesh();
	fm.setFaceColors();
	cg3::saveMeshOnObj(filename, 8, 6, v.data(), f.data(), fm,
                       internal::dummyVectorDouble.data(), io::RGB,
                       internal::dummyVectorFloat.data(), cl.data());
}

/**
 * @brief Modifies the minimum point of the bounding box
 * @param[in] min: point setted as minimum point
 */
CG3_INLINE void BoundingBox3::setMin(const Point3d& min)
{
    this->_min = min;
}

/**
 * @brief BoundingBox::min
 * @see setMin()
 */
CG3_INLINE Point3d& BoundingBox3::min()
{
    return _min;
}

/**
 * @brief Modifies the maximum point of the bounding box
 * @param[in] max: point setted as maximum point
 */
CG3_INLINE void BoundingBox3::setMax(const Point3d& max)
{
    this->_max = max;
}

/**
 * @brief BoundingBox::max
 * @see setMax()
 */
CG3_INLINE Point3d& BoundingBox3::max()
{
    return _max;
}

/**
 * @brief Modifies the minimum point of the bounding box
 * @param[in] x: value setted as \c x component of the minimum point
 * @param[in] y: value setted as \c y component of the minimum point
 * @param[in] z: value setted as \c z component of the minimum point
 */
CG3_INLINE void BoundingBox3::setMin(double x, double y, double z)
{
    _min.set(x, y, z);
}

/**
 * @brief Modifies the maximum point of the bounding box
 * @param[in] x: value setted as \c x component of the maximum point
 * @param[in] y: value setted as \c y component of the maximum point
 * @param[in] z: value setted as \c z component of the maximum point
 */
CG3_INLINE void BoundingBox3::setMax(double x, double y, double z)
{
    _max.set(x, y, z);
}

/**
 * @brief Modifies the \c x component of the minimum point of the bounding box
 * @param[in] x: value that will be setted as \c x component of the minimum point
 */
CG3_INLINE void BoundingBox3::setMinX(double x)
{
    _min.setX(x);
}

CG3_INLINE double& BoundingBox3::minX()
{
    return _min.x();
}

/**
 * @brief Modifies the \c y component of the minimum point of the bounding box
 * @param[in] y: value that will be setted as \c y component of the minimum point
 */
CG3_INLINE void BoundingBox3::setMinY(double y)
{
    _min.setY(y);
}

CG3_INLINE double& BoundingBox3::minY()
{
    return _min.y();
}

/**
 * @brief Modifies the \c z component of the minimum point of the bounding box
 * @param[in] z: value that will be setted as \c z component of the minimum point
 */
CG3_INLINE void BoundingBox3::setMinZ(double z)
{
    _min.setZ(z);
}

CG3_INLINE double& BoundingBox3::minZ()
{
    return _min.z();
}

/**
 * @brief Modifies the \c x component of the maximum point of the bounding box
 * @param[in] x: value that will be setted as \c x component of the maximum point
 */
CG3_INLINE void BoundingBox3::setMaxX(double x)
{
    _max.setX(x);
}

CG3_INLINE double&BoundingBox3::maxX()
{
    return _max.x();
}

/**
 * @brief Modifies the \c y component of the maximum point of the bounding box
 * @param[in] y: value that will be setted as \c y component of the maximum point
 */
CG3_INLINE void BoundingBox3::setMaxY(double y)
{
    _max.setY(y);
}

CG3_INLINE double&BoundingBox3::maxY()
{
    return _max.y();
}

/**
 * @brief Modifies the \c z component of the maximum point of the bounding box
 * @param[in] z: value that will be setted as \c z component of the maximum point
 */
CG3_INLINE void BoundingBox3::setMaxZ(double z)
{
    _max.setZ(z);
}

CG3_INLINE double& BoundingBox3::maxZ()
{
    return _max.z();
}

/**
 * @brief Resets the bounding box.
 *
 * Sets the three components of minimum to +std::numeric_limits<double>::max() and the three components of maximum to -std::numeric_limits<double>::max().
 * In this way, it is faster to create a new bounding box (every number is greater than -std::numeric_limits<double>::max() and every number is lower
 * than std::numeric_limits<double>::max()).
 */
CG3_INLINE void BoundingBox3::reset()
{
    _min = Point3d( std::numeric_limits<double>::max(),  std::numeric_limits<double>::max(),  std::numeric_limits<double>::max());
    _max = Point3d(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
}

CG3_INLINE double& BoundingBox3::operator()(unsigned int i)
{
    assert(i < 6);
    switch (i%6){
        case 0: return _min.x();
        case 1: return _min.y();
        case 2: return _min.z();
        case 3: return _max.x();
        case 4: return _max.y();
        case 5: return _max.z();
    }
    return _min.x();
}

CG3_INLINE void BoundingBox3::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3BoundingBox", binaryFile, _min, _max);
}

CG3_INLINE void BoundingBox3::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3BoundingBox", binaryFile, _min, _max);
}

} //namespace cg3

//hash specialization
CG3_INLINE std::size_t std::hash<cg3::BoundingBox3>::operator()(const cg3::BoundingBox3& k) const
{
    std::size_t h = 0;
    cg3::hashCombine(h, k.min(), k.max());
    return h;
}
