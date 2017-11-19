#ifndef CG3_BOUNDINGBOX2D_H
#define CG3_BOUNDINGBOX2D_H

#include "point2d.h"

namespace cg3 {

/**
 * @brief The BoundingBox2D class
 * This class models an axis aligned 2D box.
 * It is composed of two points, min and max, which represent the minimum and
 * maximum coordinates of the box.
 */
class BoundingBox2D : public SerializableObjectOld, SerializableObject{
    public:
        BoundingBox2D();
        BoundingBox2D(const Point2Dd& minCoord, const Point2Dd& maxCoord);

        const Point2Dd& getMin() const;
        const Point2Dd& min() const;
        Point2Dd& min();
        void setMin(const Point2Dd& value);

        const Point2Dd& getMax() const;
        const Point2Dd& max() const;
        Point2Dd& max();
        void setMax(const Point2Dd& value);
        void set(const Point2Dd& min, const Point2Dd& max);

        Point2Dd center() const;
        double diag() const;

        double lengthX() const;
        double lengthY() const;

        bool isInside(const Point2Dd& p) const;

        // SerializableObject interface
        void serializeOld(std::ofstream& binaryFile) const;
        bool deserializeOld(std::ifstream& binaryFile);


        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    private:
        Point2Dd minCoord, maxCoord;
};

}

#include "bounding_box2d.tpp"

#endif // CG3_BOUNDINGBOX2D_H
