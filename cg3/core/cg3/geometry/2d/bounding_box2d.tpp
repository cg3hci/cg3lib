/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bounding_box2d.h"

namespace cg3 {

/**
 * @brief BoundingBox2D::BoundingBox2D
 * Default constructor. Creates a bounding box with the maximum double value as min point,
 * and the minimum double value as max point.
 */
inline BoundingBox2D::BoundingBox2D(): minCoord( std::numeric_limits<double>::max(),  std::numeric_limits<double>::max()), maxCoord(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

/**
 * @brief BoundingBox2D::BoundingBox2D
 * Constructor. Creates a BoundingBox2D with the given min and max coordinates
 * @param min
 * @param max
 */
inline BoundingBox2D::BoundingBox2D(const Point2Dd& min, const Point2Dd& max) : minCoord(min), maxCoord(max) {
}

/**
 * @brief BoundingBox2D::getMin
 * @return the min coordinate
 */
inline const Point2Dd& BoundingBox2D::getMin() const {
    return minCoord;
}

/**
 * @brief BoundingBox2D::min
 * @return the min coordinate
 */
inline const Point2Dd& BoundingBox2D::min() const {
    return minCoord;
}

/**
 * @brief BoundingBox2D::min
 * @return a reference to the min coordinate
 */
inline Point2Dd&BoundingBox2D::min() {
    return minCoord;
}

/**
 * @brief BoundingBox2D::setMin
 * Setter for the min coordinate
 * @param value
 */
inline void BoundingBox2D::setMin(const Point2Dd& value) {
    minCoord = value;
}

/**
 * @brief BoundingBox2D::getMax
 * @return the max coordinate
 */
inline const Point2Dd& BoundingBox2D::getMax() const {
    return maxCoord;
}

/**
 * @brief BoundingBox2D::max
 * @return the max coordinate
 */
inline const Point2Dd&BoundingBox2D::max() const {
    return maxCoord;
}

/**
 * @brief BoundingBox2D::max
 * @return a reference to the max coordinate
 */
inline Point2Dd& BoundingBox2D::max() {
    return maxCoord;
}

/**
 * @brief BoundingBox2D::setMax
 * Setter for the max coordinate
 * @param value
 */
inline void BoundingBox2D::setMax(const Point2Dd& value) {
    maxCoord = value;
}

/**
 * @brief BoundingBox2D::set
 * Setter for the Bounding Box
 * @param min
 * @param max
 */
inline void BoundingBox2D::set(const Point2Dd& min, const Point2Dd& max) {
    minCoord = min;
    maxCoord = max;
}

/**
 * @brief BoundingBox2D::center
 * @return the center point of the bounding box
 */
inline Point2Dd BoundingBox2D::center() const {
    return (minCoord+maxCoord)/2;
}

/**
 * @brief BoundingBox2D::diag
 * @return the length of the diagonal of the bounding box
 */
inline double BoundingBox2D::diag() const {
    return minCoord.dist(maxCoord);
}

/**
 * @brief BoundingBox2D::lengthX
 * @return the length of the x edge of the bounding box
 */
inline double BoundingBox2D::lengthX() const {
    return maxCoord.x() - minCoord.x();
}

/**
 * @brief BoundingBox2D::lengthY
 * @return the length of the y edge of the bounding box
 */
inline double BoundingBox2D::lengthY() const {
    return maxCoord.y() - minCoord.y();
}

/**
 * @brief BoundingBox2D::isInside
 * @param p
 * @return true if the point p is inside the bounding box (borders included)
 */
inline bool BoundingBox2D::isInside(const Point2Dd& p) const {
    return (p.x() >= minCoord.x() && p.y() >= minCoord.y() &&
            p.x() <= maxCoord.x() && p.y() <= maxCoord.y());
}

/**
 * @brief BoundingBox2D::serialize
 * Serializes a Bounding Box 2D in a binary file
 * @param binaryFile
 * @see the SerializableObject Class
 */
inline void BoundingBox2D::serialize(std::ofstream& binaryFile) const {
    serializeObjectAttributes("cg3BoundingBox2D", binaryFile, minCoord, maxCoord);
}

/**
 * @brief BoundingBox2D::deserialize
 * Deserializes a Bounding Box 2D from a binary file
 * @param binaryFile
 * @see the SerializableObject Class
 */
inline void BoundingBox2D::deserialize(std::ifstream& binaryFile) {
    deserializeObjectAttributes("cg3BoundingBox2D", binaryFile, minCoord, maxCoord);
}

/**
 * @brief getBoundingBox
 * Calculates the Bounding Box of the given sets of points
 * @param container A container (with begin() and end() member functions) of cg3::Point2Dd
 * @return the bounding box of the points
 */
template<class InputContainer>
BoundingBox2D getBoundingBox(const InputContainer& container) {
    BoundingBox2D bb;
    if (container.begin() == container.end())
        return BoundingBox2D();
    bb.min() = *container.begin();
    bb.max() = *container.begin();
    for (const cg3::Point2Dd& p : container){
        bb.min() = bb.min().min(p);
        bb.max() = bb.max().max(p);
    }
    return bb;
}

}

//hash specialization
inline std::size_t std::hash<cg3::BoundingBox2D>::operator()(const cg3::BoundingBox2D &k) const {
    std::size_t h=0;
    cg3::hashCombine(h, k.min(), k.max());
    return h;
}
