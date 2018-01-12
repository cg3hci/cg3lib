/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Alessandro Tola (gul4ssss@gmail.com )
 */

#include "pickable_eigenmesh.h"

namespace cg3 {

PickableEigenMesh::PickableEigenMesh()
{
    selection_color = Color(244,196,48);
    selection_width = 3;
}

PickableEigenMesh::PickableEigenMesh(const EigenMesh &e) :DrawableEigenMesh(e)
{
    selection_color = Color(244,196,48);
    selection_width = 3;
}

/**
 * \~Italian
 * @brief PickableEigenmesh::drawWithNames Metodo che si occupa di disegnare le facce assegnando a esse un identificativo
 * riconoscibile nella postSelection (classe glCanvas) in modo da poterne effettuare il picking.
 */
void PickableEigenMesh::drawWithNames() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, V.data());

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, NV.data());
    std::array<double,3> vertex;
    for(unsigned int i = 0; i<F.rows();i++){
        glPushMatrix();
        glPushName(i);

        glBegin(GL_TRIANGLES);
        vertex[0]=V(F(i,0),0);
        vertex[1]=V(F(i,0),1);
        vertex[2]=V(F(i,0),2);
        glVertex3dv(vertex.data());

        vertex[0]=V(F(i,1),0);
        vertex[1]=V(F(i,1),1);
        vertex[2]=V(F(i,1),2);
        glVertex3dv(vertex.data());

        vertex[0]=V(F(i,2),0);
        vertex[1]=V(F(i,2),1);
        vertex[2]=V(F(i,2),2);
        glVertex3dv(vertex.data());

        glEnd();
        glPopName();
        glPopMatrix();
    }

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}

/**
 * \~Italian
 * @brief PickableEigenmesh::drawFace Metodo che si occupa di effettuare il rendering di una faccia
 * @param f La faccia da renderizzare
 */
void PickableEigenMesh::drawFace(int f) const{

    std::vector<unsigned int> face_vertex;
    face_vertex.push_back(F(f,0));
    face_vertex.push_back(F(f,1));
    face_vertex.push_back(F(f,2));

    glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, face_vertex.data());

}

void PickableEigenMesh::setSelectedFaces(std::vector<int> selected_faces){
    this->selected_faces = selected_faces;
}

void PickableEigenMesh::setSelectionColor(Color color){
    selection_color = color;
}

}
