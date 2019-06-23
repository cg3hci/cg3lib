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

CG3_INLINE PickableDcel::PickableDcel()
{
    selectionColor = Color(244,196,48);
    selectionWidth = 3;
}

CG3_INLINE PickableDcel::PickableDcel(const Dcel& d) : DrawableDcel(d)
{
    selectionColor = Color(244,196,48);
    selectionWidth = 3;
}

/**
 * \~Italian
 * @brief PickableDcel::drawWithNames Metodo che si occupa di disegnare le facce assegnando a esse un identificativo
 * riconoscibile nella postSelection (classe glCanvas) in modo da poterne effettuare il picking.
 */
CG3_INLINE void PickableDcel::drawWithNames() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertexCoordinates.data());

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, vertexNormals.data());

    //Per ogni faccia si effettua il push dell'id associato e quindi la si disegna
    for (ConstFaceIterator fit = faceBegin(); fit != faceEnd(); ++fit) {
        glPushName((*fit)->id());
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
CG3_INLINE void PickableDcel::draw() const
{
    DrawableDcel::draw();
    for(Dcel::HalfEdge* he : selectedFacesContour){
        glDisable(GL_LIGHTING);
        glLineWidth(selectionWidth);
        glColor3ub(selectionColor.red(),selectionColor.green(),selectionColor.blue());
        glBegin(GL_LINES);
        Point3d p1 = he->fromVertex()->coordinate();
        Point3d p2 = he->toVertex()->coordinate();
        glVertex3d(p1.x(), p1.y(), p1.z());
        glVertex3d(p2.x(), p2.y(), p2.z());
        glEnd();
    }
}

CG3_INLINE void PickableDcel::setSelectionColor(Color color)
{
    selectionColor = color;
}

CG3_INLINE void PickableDcel::setSelectionWidth(int value)
{
    selectionWidth = 2*value;
}

/**
 * \~Italian
 * @brief DrawableDcel::drawFace Metodo che si occupa di effettuare il rendering di una faccia
 * @param f La faccia da renderizzare
 */
CG3_INLINE void PickableDcel::drawFace(const Face* f) const
{
    unsigned int firstIndex = facesTrianglesMap.at(f->id());
    std::map<unsigned int, unsigned int>::const_iterator it = facesTrianglesMap.find(f->id());
    ++it;
    unsigned int lastIndex;
    if (it == facesTrianglesMap.end())
        lastIndex = (unsigned int)triangles.size()/3;
    else
        lastIndex = it->second;

    std::vector<int> face_triangles;
    face_triangles.reserve((lastIndex-firstIndex)*3);

    for (unsigned int i = firstIndex; i < lastIndex; i++) {
        face_triangles.push_back(triangles.at(i*3));
        face_triangles.push_back(triangles.at(i*3+1));
        face_triangles.push_back(triangles.at(i*3+2));
    }

    glDrawElements(GL_TRIANGLES, (GLsizei)face_triangles.size(), GL_UNSIGNED_INT, face_triangles.data());
}

CG3_INLINE void PickableDcel::setSelectedFacesContour(std::vector<Dcel::HalfEdge*> selected_faces_contour)
{
    this->selectedFacesContour = selected_faces_contour;
}

} //namespace cg3
