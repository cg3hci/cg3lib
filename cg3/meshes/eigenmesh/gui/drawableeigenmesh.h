#ifndef DRAWABLEEIGENMESH_H
#define DRAWABLEEIGENMESH_H

#include <cg3/viewer/interfaces/drawable_mesh.h>
#include "../eigenmesh.h"

namespace cg3 {

class DrawableEigenMesh : public EigenMesh, public DrawableMesh {
    public:
        DrawableEigenMesh();
        DrawableEigenMesh(const SimpleEigenMesh &m);
        DrawableEigenMesh(const EigenMesh &m);
        virtual ~DrawableEigenMesh();

        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;
};

}

#endif // DRAWABLEEIGENMESH_H
