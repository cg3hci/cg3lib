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
 * \~Italian
 * @class PickableEigenmesh
 */
class PickableEigenMesh : public DrawableEigenMesh, public PickableObject
{
public:
    PickableEigenMesh();
    PickableEigenMesh(const EigenMesh &e);
    void drawWithNames() const;
    void setSelectedFaces(std::vector<int> selected_faces);
    void setSelectionColor(Color color);
protected:
    void drawFace(int f) const;

    std::vector<int> selected_faces;
    Color selection_color;
    int selection_width;
};

}

#endif // CG3_PICKABLE_EIGENMESH_H
