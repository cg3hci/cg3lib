/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bounding_box2.h"

namespace cg3 {

/**
 * @brief Default constructor. Creates a bounding box with the maximum double value as min point,
 * and the minimum double value as max point.
 */
CG3_INLINE BoundingBox2::BoundingBox2() :
    minCoord(std::numeric_limits<double>::max(),  std::numeric_limits<double>::max()),
    maxCoord(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

/**
 * @brief Constructor. Creates a BoundingBox2D with the given min and max coordinates.
 * @param[in] min: coordinates of the min extreme
 * @param[in] max: coordinates of the max extreme
 */
CG3_INLINE BoundingBox2::BoundingBox2(const Point2d& min, const Point2d& max) :
    minCoord(min),
    maxCoord(max)
{
}

/**
 * @brief Returns the minimum extreme of the bounding box.
 * @return the min coordinate
 */
CG3_INLINE const Point2d& BoundingBox2::min() const
{
    return minCoord;
}

/**
 * @brief BoundingBox2D::min
 * @return a reference to the min coordinate
 */
CG3_INLINE Point2d&BoundingBox2::min()
{
    return minCoord;
}

/**
 * @brief BoundingBox2D::setMin
 * Setter for the min coordinate
 * @param value
 */
CG3_INLINE void BoundingBox2::setMin(const Point2d& value)
{
    minCoord = value;
}

/**
 * @brief BoundingBox2D::max
 * @return the max coordinate
 */
CG3_INLINE const Point2d& BoundingBox2::max() const
{
    return maxCoord;
}

/**
 * @brief BoundingBox2D::max
 * @return a reference to the max coordinate
 */
CG3_INLINE Point2d& BoundingBox2::max()
{
    return maxCoord;
}

/**
 * @brief BoundingBox2D::setMax
 * Setter for the max coordinate
 * @param value
 */
CG3_INLINE void BoundingBox2::setMax(const Point2d& value)
{
    maxCoord = value;
}

/**
 * @brief BoundingBox2D::set
 * Setter for the Bounding Box
 * @param min
 * @param max
 */
CG3_INLINE void BoundingBox2::set(const Point2d& min, const Point2d& max)
{
    minCoord = min;
    maxCoord = max;
}

/**
 * @brief BoundingBox2D::center
 * @return the center point of the bounding box
 */
CG3_INLINE Point2d BoundingBox2::center() const
{
    return (minCoord+maxCoord)/2;
}

/**
 * @brief BoundingBox2D::diag
 * @return the length of the diagonal of the bounding box
 */
CG3_INLINE double BoundingBox2::diag() const
{
    return minCoord.dist(maxCoord);
}

/**
 * @brief BoundingBox2D::lengthX
 * @return the length of the x edge of the bounding box
 */
CG3_INLINE double BoundingBox2::lengthX() const
{
    return maxCoord.x() - minCoord.x();
}

/**
 * @brief BoundingBox2D::lengthY
 * @return the length of the y edge of the bounding box
 */
CG3_INLINE double BoundingBox2::lengthY() const
{
    return maxCoord.y() - minCoord.y();
}

/**
 * @brief BoundingBox2D::isInside
 * @param[in] p:
 * @return true if the point p is inside the bounding box (borders included)
 */
CG3_INLINE bool BoundingBox2::isInside(const Point2d& p) const
{
    return (p.x() >= minCoord.x() && p.y() >= minCoord.y() &&
            p.x() <= maxCoord.x() && p.y() <= maxCoord.y());
}

CG3_INLINE bool BoundingBox2::isStrictlyInside(const Point2d& p) const
{
    return (p.x() > minCoord.x() && p.y() > minCoord.y() &&
            p.x() < maxCoord.x() && p.y() < maxCoord.y());
}

/**
 * @brief Serializes a Bounding Box 2D in a binary file
 * @param binaryFile
 * @see the SerializableObject Class
 */
CG3_INLINE void BoundingBox2::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3BoundingBox2D", binaryFile, minCoord, maxCoord);
}

/**
 * @brief Deserializes a Bounding Box 2D from a binary file
 * @param binaryFile
 * @see the SerializableObject Class
 */
CG3_INLINE void BoundingBox2::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3BoundingBox2D", binaryFile, minCoord, maxCoord);
}

} //namespace cg3

//hash specialization
CG3_INLINE std::size_t std::hash<cg3::BoundingBox2>::operator()(const cg3::BoundingBox2 &k) const
{
    std::size_t h=0;
    cg3::hashCombine(h, k.min(), k.max());
    return h;
}
