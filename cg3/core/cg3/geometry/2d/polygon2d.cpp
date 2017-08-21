#include "polygon2d.h"

namespace cg3 {

bool isCounterClockwise(const std::vector<Point2Dd>& polygon) {
    double sum = 0;
    for (unsigned int i = 0; i < polygon.size(); i++){
        Point2Dd p1 = polygon[i];
        Point2Dd p2 = polygon[(i+1)%polygon.size()];
        sum += (p2.x() - p1.x()) * (p2.y()+p1.y());
    }
    if (sum > 0)
        return false;
    else
        return true;
}

}
