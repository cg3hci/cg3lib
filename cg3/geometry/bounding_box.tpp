/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bounding_box.h"
#include "../io/load_save_file.h"

namespace cg3 {

/**
 * @brief Constructor, creates a bounding box and calls BoundingBox::reset() method
 */
inline BoundingBox::BoundingBox()
{
    reset();
}

/**
 * @brief Constructor, creates a bounding box whith with minimum equal to the parameter \c min and maximum equal to the parameter \c max
 * @param[in] min: point setted as minimum point of the bounding box
 * @param[in] max: point setted as maximum point of the bounding box
 */
inline BoundingBox::BoundingBox(const Pointd& min, const Pointd& max) :
    _min(min),
    _max(max)
{
}


/**
 * @brief Constructor, creates a bounding box that contains all the Pointd iterated
 * from begin to end.
 * @param begin: start iterator on a container of Pointd
 * @param end: end iterator on a container of Pointd
 */
template<class Iterator>
inline BoundingBox::BoundingBox(Iterator begin, Iterator end)
{
    _min = *begin;
    _max = *begin;
    for (Iterator i = begin; i != end; ++i){
        _min = _min.min(*i);
        _max = _max.max(*i);
    }
}

/**
 * @brief Constructor, creates a bounding box that contains all the Pointd contained
 * in the input container.
 * @param c: a container of Pointd
 */
template<class Container>
inline BoundingBox::BoundingBox(const Container& c) :
    BoundingBox(c.begin(), c.end())
{
}

/*************************
* Public Inline Methods *
*************************/

/**
 * @brief Returns the minimum point of the bounding box
 * @return The minimum point
 */
inline const Pointd& BoundingBox::min() const
{
    return _min;
}

/**
 * @brief Returns the maximum point of the bounding box
 * @return The maximum point
 */
inline const Pointd& BoundingBox::max() const
{
    return _max;
}

/**
 * @brief Returns the x component of the minimum point of the bounding box
 * @return X component of the minimum point
 */
inline const double& BoundingBox::minX() const
{
    return _min.x();
}

/**
 * @brief Returns the y component of the minimum point of the bounding box
 * @return Y component of the minimum point
 */
inline const double& BoundingBox::minY() const
{
    return _min.y();
}

/**
 * @brief Returns the z component of the minimum point of the bounding box
 * @return Z component of the minimum point
 */
inline const double& BoundingBox::minZ() const
{
    return _min.z();
}

/**
 * @brief Returns the x component of the maximum point of the bounding box
 * @return X component of the maximum point
 */
inline const double& BoundingBox::maxX() const
{
    return _max.x();
}

/**
 * @brief Returns the y component of the maximum point of the bounding box
 * @return Y component of the maximum point
 */
inline const double& BoundingBox::maxY() const
{
    return _max.y();
}

/**
 * @brief Returns the Z component of the maximum point of the bounding box
 * @return Z component of the maximum point
 */
inline const double& BoundingBox::maxZ() const
{
    return _max.z();
}

inline double BoundingBox::lengthX() const
{
    return _max.x() - _min.x();
}

inline double BoundingBox::lengthY() const
{
    return _max.y() - _min.y();
}

inline double BoundingBox::lengthZ() const
{
    return _max.z() - _min.z();
}

/**
 * @brief Calculates the center of the bounding box
 * @return The point centered in the bounding box
 */
inline Pointd BoundingBox::center() const
{
    return (_min + _max) * 0.5;
}

/**
 * @brief Calculates the length of the diagonal of the bounding box
 * @return The length of the diagonal of the bounding box
 */
inline double BoundingBox::diag() const
{
    return (_min - _max).length();
}

inline bool BoundingBox::isValid() const
{
    return _min.x() <= _max.x() && _min.y() <= _max.y() && _min.z() <= _max.z();
}

inline bool BoundingBox::isStrictlyIntern(const Pointd &p) const
{
    return (p.x() > _min.x() && p.y() > _min.y() && p.z() > _min.z() &&
            p.x() < _max.x() && p.y() < _max.y() && p.z() < _max.z());
}

inline bool BoundingBox::isStrictlyInside(const Pointd& p) const
{
    return isStrictlyIntern(p);
}

inline bool BoundingBox::isStrictlyIntern(double px, double py, double pz) const
{
    return (px > _min.x() && py > _min.y() && pz > _min.z() &&
            px < _max.x() && py < _max.y() && pz < _max.z());
}

inline bool BoundingBox::isStrictlyInside(double px, double py, double pz) const
{
    return isStrictlyIntern(px, py, pz);
}

inline bool BoundingBox::isIntern(const Pointd &p) const
{
    return (p.x() >= _min.x() && p.y() >= _min.y() && p.z() >= _min.z() &&
            p.x() <= _max.x() && p.y() <= _max.y() && p.z() <= _max.z());
}

inline bool BoundingBox::isInside(const Pointd& p) const
{
    return isIntern(p);
}

inline bool BoundingBox::isIntern(double px, double py, double pz) const
{
    return (px >= _min.x() && py >= _min.y() && pz >= _min.z() &&
            px <= _max.x() && py <= _max.y() && pz <= _max.z());
}

inline bool BoundingBox::isInside(double px, double py, double pz) const
{
    return isIntern(px, py, pz);
}

inline bool BoundingBox::isEpsilonIntern(const Pointd& p, double epsilon) const
{
    return (p.x() >= _min.x()-epsilon && p.y() >= _min.y()-epsilon && p.z() >= _min.z()-epsilon &&
            p.x() <= _max.x()+epsilon && p.y() <= _max.y()+epsilon && p.z() <= _max.z()+epsilon);
}

inline bool BoundingBox::isEpsilonInside(const Pointd& p, double epsilon) const
{
    return isEpsilonIntern(p, epsilon);
}

inline bool BoundingBox::isEpsilonIntern(double px, double py, double pz, double epsilon) const
{
    return (px >= _min.x()-epsilon && py >= _min.y()-epsilon && pz >= _min.z()-epsilon &&
            px <= _max.x()+epsilon && py <= _max.y()+epsilon && pz <= _max.z()+epsilon);
}

inline bool BoundingBox::isEpsilonInside(double px, double py, double pz, double epsilon) const
{
    return isEpsilonIntern(px, py, pz, epsilon);
}

/**
 * @brief BoundingBox::intersect
 * @param[in] otherBox
 * @return true if otherBox overlaps this box
 * @link http://gamemath.com/2011/09/detecting-whether-two-boxes-overlap/
 */
inline bool BoundingBox::intersect(const BoundingBox& otherBox)
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
inline bool BoundingBox::overlap(const BoundingBox& otherBox)
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
inline void BoundingBox::extremes(std::vector<Pointd>& extremes) const
{
    extremes.resize(8);
    extremes[0] = _min;
    extremes[1].set(_max.x(), _min.y(), _min.z());
    extremes[2].set(_max.x(), _min.y(), _max.z());
    extremes[3].set(_min.x(), _min.y(), _max.z());
    extremes[4].set(_min.x(), _max.y(), _min.z());
    extremes[5].set(_max.x(), _max.y(), _min.z());
    extremes[6] = _max;
    extremes[7].set(_min.x(), _max.y(), _max.z());
}

/**
 * @brief BoundingBox::getExtremes
 * @return a vector of 8 Pointd which are the extremes of the bounding box
 */
inline std::vector<Pointd> BoundingBox::extremes() const
{
    std::vector<Pointd> ext;
    extremes(ext);
    return ext;
}

/**
 * @brief BoundingBox::operator ()
 * @param i
 * @return a double which is a coordinate of minCoord [0-2] or a coordinate of maxCoord[3-5]
 */
inline const double& BoundingBox::operator ()(unsigned int i) const
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
inline Pointd BoundingBox::operator[](unsigned int i) const
{
    assert(i < 8);
    switch (i%8){
        case 0: return _min;
        case 1: return Pointd(_max.x(), _min.y(), _min.z());
        case 2: return Pointd(_max.x(), _min.y(), _max.z());
        case 3: return Pointd(_min.x(), _min.y(), _max.z());
        case 4: return Pointd(_min.x(), _max.y(), _min.z());
        case 5: return Pointd(_max.x(), _max.y(), _min.z());
        case 6: return _max;
        case 7: return Pointd(_min.x(), _max.y(), _max.z());
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
inline void BoundingBox::saveOnObj(const std::string& filename, const Color &c) const
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
inline void BoundingBox::setMin(const Pointd& min)
{
    this->_min = min;
}

/**
 * @brief BoundingBox::min
 * @see setMin()
 */
inline Pointd& BoundingBox::min()
{
    return _min;
}

/**
 * @brief Modifies the maximum point of the bounding box
 * @param[in] max: point setted as maximum point
 */
inline void BoundingBox::setMax(const Pointd& max)
{
    this->_max = max;
}

/**
 * @brief BoundingBox::max
 * @see setMax()
 */
inline Pointd& BoundingBox::max()
{
    return _max;
}

/**
 * @brief Modifies the minimum point of the bounding box
 * @param[in] x: value setted as \c x component of the minimum point
 * @param[in] y: value setted as \c y component of the minimum point
 * @param[in] z: value setted as \c z component of the minimum point
 */
inline void BoundingBox::setMin(double x, double y, double z)
{
    _min.set(x, y, z);
}

/**
 * @brief Modifies the maximum point of the bounding box
 * @param[in] x: value setted as \c x component of the maximum point
 * @param[in] y: value setted as \c y component of the maximum point
 * @param[in] z: value setted as \c z component of the maximum point
 */
inline void BoundingBox::setMax(double x, double y, double z)
{
    _max.set(x, y, z);
}

/**
 * @brief Modifies the \c x component of the minimum point of the bounding box
 * @param[in] x: value that will be setted as \c x component of the minimum point
 */
inline void BoundingBox::setMinX(double x)
{
    _min.setX(x);
}

inline double& BoundingBox::minX()
{
    return _min.x();
}

/**
 * @brief Modifies the \c y component of the minimum point of the bounding box
 * @param[in] y: value that will be setted as \c y component of the minimum point
 */
inline void BoundingBox::setMinY(double y)
{
    _min.setY(y);
}

inline double& BoundingBox::minY()
{
    return _min.y();
}

/**
 * @brief Modifies the \c z component of the minimum point of the bounding box
 * @param[in] z: value that will be setted as \c z component of the minimum point
 */
inline void BoundingBox::setMinZ(double z)
{
    _min.setZ(z);
}

inline double& BoundingBox::minZ()
{
    return _min.z();
}

/**
 * @brief Modifies the \c x component of the maximum point of the bounding box
 * @param[in] x: value that will be setted as \c x component of the maximum point
 */
inline void BoundingBox::setMaxX(double x)
{
    _max.setX(x);
}

inline double&BoundingBox::maxX()
{
    return _max.x();
}

/**
 * @brief Modifies the \c y component of the maximum point of the bounding box
 * @param[in] y: value that will be setted as \c y component of the maximum point
 */
inline void BoundingBox::setMaxY(double y)
{
    _max.setY(y);
}

inline double&BoundingBox::maxY()
{
    return _max.y();
}

/**
 * @brief Modifies the \c z component of the maximum point of the bounding box
 * @param[in] z: value that will be setted as \c z component of the maximum point
 */
inline void BoundingBox::setMaxZ(double z)
{
    _max.setZ(z);
}

inline double& BoundingBox::maxZ()
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
inline void BoundingBox::reset()
{
    _min = Pointd( std::numeric_limits<double>::max(),  std::numeric_limits<double>::max(),  std::numeric_limits<double>::max());
    _max = Pointd(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
}

inline double& BoundingBox::operator()(unsigned int i)
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

inline void BoundingBox::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3BoundingBox", binaryFile, _min, _max);
}

inline void BoundingBox::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3BoundingBox", binaryFile, _min, _max);
}

} //namespace cg3

//hash specialization
inline std::size_t std::hash<cg3::BoundingBox>::operator()(const cg3::BoundingBox& k) const
{
    std::size_t h = 0;
    cg3::hashCombine(h, k.min(), k.max());
    return h;
}
