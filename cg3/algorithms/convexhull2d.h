#ifndef CG3_CONVEXHULL2D_H
#define CG3_CONVEXHULL2D_H


namespace cg3 {


template <class T = double, class InputContainer, class OutputContainer>
void getConvexHull2D(const InputContainer& container, OutputContainer& convexHull);

template <class T = double, class InputIterator, class OutputIterator>
void getConvexHull2D(const InputIterator first, const InputIterator end, OutputIterator outIt);


}

#include "convexhull2d.tpp"


#endif // CG3_CONVEXHULL2D_H
