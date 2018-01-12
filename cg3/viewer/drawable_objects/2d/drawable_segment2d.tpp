/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_segment2d.h"

template<typename T>
inline cg3::DrawableSegment2D<T>::DrawableSegment2D() : Segment2D<T>(), color(), width(2) {
}

template<typename T>
cg3::DrawableSegment2D<T>::DrawableSegment2D(const Segment2D<T>& s) : Segment2D<T>(s), color(), width(2) {
}

template<typename T>
inline cg3::DrawableSegment2D<T>::DrawableSegment2D(const Point2D<T>& p1, const Point2D<T>& p2) : Segment2D<T>(p1, p2), color(), width(2)  {
}

template<typename T>
inline void cg3::DrawableSegment2D<T>::draw() const {
    cg3::viewer::drawLine2D(Segment2D<T>::p1, Segment2D<T>::p2, color, width);
}

template<typename T>
inline cg3::Pointd cg3::DrawableSegment2D<T>::sceneCenter() const {
    cg3::Point2D<T> p = (Segment2D<T>::p1 + Segment2D<T>::p2)/2;
    return cg3::Pointd(p.x(), p.y(), 0);
}

template<typename T>
inline double cg3::DrawableSegment2D<T>::sceneRadius() const {
    return Segment2D<T>::p1.dist(Segment2D<T>::p2) / 2;
}

template<typename T>
inline void cg3::DrawableSegment2D<T>::setColor(const QColor& c) {
    color = c;
}

template<typename T>
inline void cg3::DrawableSegment2D::setWidth(int w) {
    width = w;
}
