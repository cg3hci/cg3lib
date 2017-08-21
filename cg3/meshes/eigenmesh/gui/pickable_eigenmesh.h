#ifndef PICKABLEEIGENMESH_H
#define PICKABLEEIGENMESH_H

#include "drawableeigenmesh.h"
#include <cg3/viewer/interfaces/pickable_object.h>

namespace cg3 {

/**
 * \~Italian
 * @class PickableEigenmesh
 */
class PickableEigenmesh : public DrawableEigenMesh, public PickableObject
{
public:
    PickableEigenmesh();
    PickableEigenmesh(const EigenMesh &e);
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

#endif // PICKABLEEIGENMESH_H
