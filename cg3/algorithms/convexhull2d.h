#ifndef CG3_CONVEXHULL2D_H
#define CG3_CONVEXHULL2D_H


namespace cg3 {


template <class T, class InputContainer, class OutputContainer>
void convexHull2D(const InputContainer& container, OutputContainer& convexHull);


}

#include "convexhull2d.tpp"


#endif // CG3_CONVEXHULL2D_H
