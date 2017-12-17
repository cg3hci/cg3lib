/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  * @author Andreas Scalas (andreasscalas@gmail.com)
  */

#include "pickable_dcel.h"

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace cg3 {

PickableDcel::PickableDcel(){
    selection_color = Color(244,196,48);
    selection_width = 3;
}

PickableDcel::PickableDcel(const Dcel& d) : DrawableDcel(d) {
    selection_color = Color(244,196,48);
    selection_width = 3;
}

/**
 * \~Italian
 * @brief PickableDcel::drawWithNames Metodo che si occupa di disegnare le facce assegnando a esse un identificativo
 * riconoscibile nella postSelection (classe glCanvas) in modo da poterne effettuare il picking.
 */
void PickableDcel::drawWithNames() const{

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertexCoordinates.data());

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, vertexNormals.data());

    //Per ogni faccia si effettua il push dell'id associato e quindi la si disegna
    for (ConstFaceIterator fit = faceBegin(); fit != faceEnd(); ++fit) {
        glPushName((*fit)->getId());
        drawFace((*fit));
        glPopName();
    }

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * \~Italian
 * @brief PickableDcel::draw Metodo che si occupa di disegnare il contorno delle facce selezionate durante il picking (selezione multipla).
 */
void PickableDcel::draw() const{

    DrawableDcel::draw();
    foreach(Dcel::HalfEdge* he, selected_faces_contour){
        glDisable(GL_LIGHTING);
        glLineWidth(selection_width);
        glColor3ub(selection_color.red(),selection_color.green(),selection_color.blue());
        glBegin(GL_LINES);
        Pointd p1 = he->getFromVertex()->getCoordinate();
        Pointd p2 = he->getToVertex()->getCoordinate();
        glVertex3d(p1.x(), p1.y(), p1.z());
        glVertex3d(p2.x(), p2.y(), p2.z());
        glEnd();
    }
}

void PickableDcel::setSelectionColor(Color color){
    selection_color = color;
}

void PickableDcel::setSelectionWidth(int value){
    selection_width = 2*value;
}

/**
 * \~Italian
 * @brief DrawableDcel::drawFace Metodo che si occupa di effettuare il rendering di una faccia
 * @param f La faccia da renderizzare
 */
void PickableDcel::drawFace(const Face* f) const{

    std::vector<int> face_triangles = obtainFaceTriangles(f);

    glDrawElements(GL_TRIANGLES, (GLsizei)face_triangles.size(), GL_UNSIGNED_INT, face_triangles.data());

}

/**
 * \~Italian
 * @brief DrawableDcel::obtainFaceTriangles Metodo che si occupa della ricerca dei triangoli
 * appartenenti a una data faccia all'interno della lista tris
 * @param f la faccia a cui apparterranno i triangoli
 * @return una lista di triangoli (da interpretare nello stesso modo di tris)
 */
std::vector<int> PickableDcel::obtainFaceTriangles(const Face* f) const{
    std::vector<int> face_triangles;

    //Ricerca dei triangoli appartenenti alla faccia
    for(unsigned int i=0; i<triangles_face.size(); i++)
        if(triangles_face.at(i)==f->getId()){
            face_triangles.push_back(triangles.at(i*3));
            face_triangles.push_back(triangles.at(i*3+1));
            face_triangles.push_back(triangles.at(i*3+2));
        }

    return face_triangles;
}

void PickableDcel::setSelectedFacesContour(std::vector<Dcel::HalfEdge*> selected_faces_contour){
    this->selected_faces_contour = selected_faces_contour;
}

}
