/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "drawable_mesh.h"

namespace cg3 {

void DrawableMesh::init() {
    drawMode          = DRAW_MESH | DRAW_SMOOTH | DRAW_FACECOLOR;
    wireframeWidth    = 1;
    wireframeColor[0] = (float)0.1;
    wireframeColor[1] = (float)0.1;
    wireframeColor[2] = (float)0.1;
}

bool DrawableMesh::isVisible() const {
    return (drawMode & DRAW_MESH);
}

void DrawableMesh::setWireframe(bool b) {
    if (b) drawMode |=  DRAW_WIREFRAME;
    else   drawMode &= ~DRAW_WIREFRAME;
}

void DrawableMesh::setFlatShading() {
    drawMode |=  DRAW_FLAT;
    drawMode &= ~DRAW_SMOOTH;
    drawMode &= ~DRAW_POINTS;
}

void DrawableMesh::setSmoothShading() {
    drawMode |=  DRAW_SMOOTH;
    drawMode &= ~DRAW_FLAT;
    drawMode &= ~DRAW_POINTS;
}

void DrawableMesh::setPointsShading() {
    drawMode |=  DRAW_POINTS;
    drawMode &= ~DRAW_FLAT;
    drawMode &= ~DRAW_SMOOTH;
}

void DrawableMesh::setWireframeColor(float r, float g, float b) {
    wireframeColor[0] = r;
    wireframeColor[1] = g;
    wireframeColor[2] = b;
}

void DrawableMesh::setWireframeWidth(float width) {
    wireframeWidth = width;
}

void DrawableMesh::setEnableVertexColor() {
    drawMode |=  DRAW_VERTEXCOLOR;
    drawMode &= ~DRAW_FACECOLOR;
}

void DrawableMesh::setEnableTriangleColor() {
    drawMode |=  DRAW_FACECOLOR;
    drawMode &= ~DRAW_VERTEXCOLOR;
}

void DrawableMesh::setVisibleBoundingBox(bool b) {
    if (b) drawMode |=  DRAW_BOUNDINGBOX;
    else   drawMode &= ~DRAW_BOUNDINGBOX;
}

void DrawableMesh::setVisible(bool b) {
    if (b) drawMode |=  DRAW_MESH;
    else   drawMode &= ~DRAW_MESH;
}

DrawableMesh::DrawableMesh() {
    init();
}

void DrawableMesh::draw(unsigned int nv, unsigned int nt, const double* pCoords, const int* pTriangles, const double* pVertexNormals, const float* pVertexColors, const double* pTriangleNormals, const float* pTriangleColors, const Pointd &min, const Pointd &max) const {
    if (drawMode & DRAW_MESH) {
        if (drawMode & DRAW_WIREFRAME) {
            if (drawMode & DRAW_POINTS) {
                glDisable(GL_LIGHTING);
                glShadeModel(GL_FLAT);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDepthRange(0.0, 1.0);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            else if (drawMode & DRAW_FLAT) {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_FLAT);
                glDepthRange(0.01, 1.0);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);

                glDisable(GL_LIGHTING);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDepthRange(0.0, 1.0);
                glDepthFunc(GL_LEQUAL);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);
                glDepthFunc(GL_LESS);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            else if (drawMode & DRAW_SMOOTH) {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_SMOOTH);
                glDepthRange(0.01, 1.0);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);

                glDisable(GL_LIGHTING);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDepthRange(0.0, 1.0);
                glDepthFunc(GL_LEQUAL);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);
                glDepthFunc(GL_LESS);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
        else {
            if (drawMode & DRAW_POINTS) {
                glDisable(GL_LIGHTING);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);
            }
            else if (drawMode & DRAW_FLAT) {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_FLAT);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);
            }
            else if (drawMode & DRAW_SMOOTH) {
                glEnable(GL_LIGHTING);
                glShadeModel(GL_SMOOTH);
                renderPass(nv, nt, pCoords, pTriangles, pVertexNormals, pVertexColors, pTriangleNormals, pTriangleColors);
            }
        }
        if (drawMode & DRAW_BOUNDINGBOX) {
            viewer::drawBox(min, max, QColor(0,0,0));
        }
    }
}

void DrawableMesh::renderPass(unsigned int nv, unsigned int nt, const double* coords, const int* triangles, const double* vertexNormals, const float* vertexColors, const double* triangleNormals, const float* triangleColors) const {
    if (drawMode & DRAW_POINTS) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, coords);

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer (3, GL_FLOAT, 0, vertexColors);

        glDrawArrays(GL_POINTS, 0, nv);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    else if (drawMode & DRAW_SMOOTH || drawMode & DRAW_FLAT) {
        // Old fashioned, verbose and slow rendering.
        //
        if (drawMode & DRAW_FACECOLOR) {
            int n_tris = nt;
            for(int tid=0; tid<n_tris; ++tid) {
                int tid_ptr  = 3 * tid;
                int vid0     = triangles[tid_ptr + 0];
                int vid1     = triangles[tid_ptr + 1];
                int vid2     = triangles[tid_ptr + 2];
                int vid0_ptr = 3 * vid0;
                int vid1_ptr = 3 * vid1;
                int vid2_ptr = 3 * vid2;

                if (drawMode & DRAW_SMOOTH){
                    glBegin(GL_TRIANGLES);
                    glColor3fv(&(triangleColors[tid_ptr]));
                    glNormal3dv(&(vertexNormals[vid0_ptr]));
                    glVertex3dv(&(coords[vid0_ptr]));
                    glNormal3dv(&(vertexNormals[vid1_ptr]));
                    glVertex3dv(&(coords[vid1_ptr]));
                    glNormal3dv(&(vertexNormals[vid2_ptr]));
                    glVertex3dv(&(coords[vid2_ptr]));
                    glEnd();
                }
                else {
                    glBegin(GL_TRIANGLES);
                    glColor3fv(&(triangleColors[tid_ptr]));
                    glNormal3dv(&(triangleNormals[tid_ptr]));
                    glVertex3dv(&(coords[vid0_ptr]));
                    glNormal3dv(&(triangleNormals[tid_ptr]));
                    glVertex3dv(&(coords[vid1_ptr]));
                    glNormal3dv(&(triangleNormals[tid_ptr]));
                    glVertex3dv(&(coords[vid2_ptr]));
                    glEnd();
                }
            }
        }
        else if (drawMode & DRAW_VERTEXCOLOR){
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, coords);

            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_DOUBLE, 0, vertexNormals);

            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, vertexColors);

            glDrawElements(GL_TRIANGLES, nt*3, GL_UNSIGNED_INT, triangles);

            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }

    if (drawMode & DRAW_WIREFRAME) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, coords);

        glLineWidth(wireframeWidth);
        glColor4fv(wireframeColor);

        glDrawElements(GL_TRIANGLES, nt*3, GL_UNSIGNED_INT, triangles);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void _check_gl_error(const char *file, int line)
{
  GLenum err (glGetError());

  while(err!=GL_NO_ERROR)
  {
    std::string error;

    switch(err)
    {
      case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
      case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
      case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
      case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
      #ifdef unix
      case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
      #endif
    }

    std::cerr << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
    err = glGetError();
  }
}

}
