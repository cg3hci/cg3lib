/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (gul4ssss@gmail.com )
 */

#ifndef CG3_PICKABLE_EIGENMESH_H
#define CG3_PICKABLE_EIGENMESH_H

#include "../drawable_objects/drawable_eigenmesh.h"
#include <cg3/viewer/interfaces/pickable_object.h>

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @brief The PickableEigenmesh class
 */
class PickableEigenMesh : public DrawableEigenMesh, public PickableObject
{
public:
    PickableEigenMesh();
    PickableEigenMesh(const EigenMesh &e);
    void drawWithNames() const;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_PICKABLE_EIGENMESH_CPP "pickable_eigenmesh.cpp"
#include CG3_PICKABLE_EIGENMESH_CPP
#undef CG3_PICKABLE_EIGENMESH_CPP
#endif //CG3_STATIC

#endif // CG3_PICKABLE_EIGENMESH_H
