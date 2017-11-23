#include "bounding_box2d.h"

namespace cg3 {

inline BoundingBox2D::BoundingBox2D(): minCoord( std::numeric_limits<double>::max(),  std::numeric_limits<double>::max()), maxCoord(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max())
{
}

inline BoundingBox2D::BoundingBox2D(const Point2Dd& min, const Point2Dd& max) : minCoord(min), maxCoord(max) {
}

inline const Point2Dd& BoundingBox2D::getMin() const {
    return minCoord;
}

inline const Point2Dd& BoundingBox2D::min() const {
    return minCoord;
}

inline Point2Dd&BoundingBox2D::min() {
    return minCoord;
}

inline void BoundingBox2D::setMin(const Point2Dd& value) {
    minCoord = value;
}

inline const Point2Dd& BoundingBox2D::getMax() const {
    return maxCoord;
}

inline const Point2Dd&BoundingBox2D::max() const {
    return maxCoord;
}

inline Point2Dd& BoundingBox2D::max() {
    return maxCoord;
}

inline void BoundingBox2D::setMax(const Point2Dd& value) {
    maxCoord = value;
}

inline void BoundingBox2D::set(const Point2Dd& min, const Point2Dd& max) {
    minCoord = min;
    maxCoord = max;
}

inline Point2Dd BoundingBox2D::center() const {
    return (minCoord+maxCoord)/2;
}

inline double BoundingBox2D::diag() const {
    return minCoord.dist(maxCoord);
}

inline double BoundingBox2D::lengthX() const {
    return maxCoord.x() - minCoord.x();
}

inline double BoundingBox2D::lengthY() const {
    return maxCoord.y() - minCoord.y();
}

inline bool BoundingBox2D::isInside(const Point2Dd& p) const {
    return (p.x() >= minCoord.x() && p.y() >= minCoord.y() &&
            p.x() <= maxCoord.x() && p.y() <= maxCoord.y());
}

inline void BoundingBox2D::serialize(std::ofstream& binaryFile) const {
    Serializer::serializeObjectAttributes("cg3BoundingBox2D", binaryFile, minCoord, maxCoord);
}

inline void BoundingBox2D::deserialize(std::ifstream& binaryFile) {
    Serializer::deserializeObjectAttributes("cg3BoundingBox2D", binaryFile, minCoord, maxCoord);
}

}
