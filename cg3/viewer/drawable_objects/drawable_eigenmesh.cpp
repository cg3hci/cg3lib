#include "drawable_eigenmesh.h"

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace cg3 {

DrawableEigenMesh::DrawableEigenMesh() {
}

DrawableEigenMesh::DrawableEigenMesh(const SimpleEigenMesh& m) : EigenMesh(m) {
}

DrawableEigenMesh::DrawableEigenMesh(const EigenMesh& m) : EigenMesh(m){
}

void DrawableEigenMesh::draw() const {
    DrawableMesh::draw(V.rows(), F.rows(), V.data(), F.data(), NV.data(), CV.data(), NF.data(), CF.data(), bb.min(), bb.max());
}

Pointd DrawableEigenMesh::sceneCenter() const {
    if (bb.isValid())
        return bb.center();
    else
        return Pointd();
}

double DrawableEigenMesh::sceneRadius() const {
    if (bb.isValid())
        return bb.diag() / 2;
    else
        return -1;
}

}
