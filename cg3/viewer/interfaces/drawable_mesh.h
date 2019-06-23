/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DRAWABLE_MESH_H
#define CG3_DRAWABLE_MESH_H

#ifdef WIN32
#include "windows.h"
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

#include <cg3/meshes/mesh.h>

#include "../opengl_objects/opengl_objects3.h"
#include "drawable_object.h"

namespace cg3 {

// From: https://blog.nobel-joergensen.com/2013/01/29/debugging-opengl-using-glgeterror/
void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

/**
 * @ingroup cg3viewer
 * @brief The DrawableMesh class
 * This is a non-instantiable class.
 * You can only inherit this class (protected constructors).
 */
class DrawableMesh : public virtual DrawableObject, public virtual Mesh
{
public:

    void init();

    //rendering options getters
    //
    bool isWireframeEnabled() const;
    bool isPointShadingEnabled() const;
    bool isFlatShadingEnabled() const;
    bool isSmoothShadingEnabled() const;
    bool isBboxEnabled() const;
    bool isTriangleColorEnabled() const;
    bool isVertexColorEnabled() const;

    // rendering options setters
    //
    void setWireframe(bool b) const;
    void setFlatShading() const;
    void setSmoothShading() const;
    void setPointsShading() const;
    void setWireframeColor(float r, float g, float b) const;
    void setWireframeWidth(int width) const;
    void setPointWidth(int width) const;
    void setEnableVertexColor() const;
    void setEnableTriangleColor() const;
    void setVisibleBoundingBox(bool b) const;

protected:
    DrawableMesh();
    virtual void draw() const = 0;
    virtual void draw(unsigned int nv, unsigned int nt, const double* pCoords, const int* pTriangles, const double* pVertexNormals, const float* pVertexColors, const double* pTriangleNormals, const float* pTriangleColors, const Point3d &min, const Point3d &max) const;
    virtual void renderPass(unsigned int nv, unsigned int nt, const double* coords, const int* triangles, const double* vertexNormals, const float* vertexColors, const double* triangleNormals, const float* triangleColors) const;

    enum {
        DRAW_MESH        = 0b00000001,
        DRAW_POINTS      = 0b00000010,
        DRAW_FLAT        = 0b00000100,
        DRAW_SMOOTH      = 0b00001000,
        DRAW_WIREFRAME   = 0b00010000,
        DRAW_FACECOLOR   = 0b00100000,
        DRAW_VERTEXCOLOR = 0b01000000,
        DRAW_BOUNDINGBOX = 0b10000000
    };

    mutable int   drawMode;
    mutable int   wireframeWidth;
    mutable float wireframeColor[3];
    mutable int   pointWidth;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DRAWABLE_MESH_CPP "drawable_mesh.cpp"
#include CG3_DRAWABLE_MESH_CPP
#undef CG3_DRAWABLE_MESH_CPP
#endif //CG3_STATIC

#endif // CG3_DRAWABLE_MESH_H
