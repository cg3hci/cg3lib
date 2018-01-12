/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#include "drawable_dcel.h"

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace cg3 {

DrawableDcel::DrawableDcel() : Dcel(){
    init();
}

/**
 * \~Italian
 * @brief Crea una DrawableDcel a partire dalla Dcel passata come parametro (di cui ne verrà fatta una copia)
 * @param[in] d: Dcel che verrà copiata e resa visualizzabile
 */
DrawableDcel::DrawableDcel(const Dcel &d) : Dcel(d) {
    init();
}

/**
 * \~Italian
 * @brief Setta impostazioni di visualizzazione di default.
 */
void DrawableDcel::init() {
    DrawableMesh::init();
    update();

    facesWireframeWidth    = 1;
    facesWireframeColor[0] = 0;
    facesWireframeColor[1] = 0;
    facesWireframeColor[2] = 0;
}

/**
 * \~Italian
 * @brief esegue una clear della Dcel e della DrawableDcel
 */
void DrawableDcel::clear() {
    Dcel::clear();
    init();
    vertexCoordinates.clear();
    vertexNormals.clear();
    vertexColors.clear();
    triangleNormals.clear();
    triangles.clear();
    triangleColors.clear();
}

void DrawableDcel::draw() const {
    DrawableMesh::draw((unsigned int)vertexCoordinates.size()/3, (unsigned int)triangles.size()/3, vertexCoordinates.data(), triangles.data(), vertexNormals.data(), vertexColors.data(), triangleNormals.data(), triangleColors.data(), boundingBox.min(), boundingBox.max());
}

/**
 * \~Italian
 * @brief Calcola e restituisce il centro della Dcel.
 * @return il punto rappresentante il centro della mesh.
 */
Pointd DrawableDcel::sceneCenter() const {
    if (boundingBox.isValid())
        return boundingBox.center();
    else
        return Pointd();
}

/**
 * \~Italian
 * @brief Calcola il raggio della Dcel.
 * @return Restituisce un valore rappresentante il raggio della mesh
 */
double DrawableDcel::sceneRadius() const {
    if (boundingBox.isValid())
        return boundingBox.diag() / 2;
    else
        return -1;
}

/**
 * \~Italian
 * @brief DrawableDcel::update()
 * Aggiorna i vettori visualuizzati dalla draw() con le informazioni contenute nella Dcel.
 * Fa in modo che la mesh visualizzata sia effettivamente quella contenuta all'interno della struttura dati
 * Dcel. Deve essere chiamata ogni volta che è stata fatta una modifica nella Dcel e si vuole visualizzare tale
 * modifica.
 */
void DrawableDcel::update() {
    vertexCoordinates.clear();
    vertexNormals.clear();
    triangles.clear();
    triangleColors.clear();
    vertexColors.clear();
    triangleNormals.clear();
    facesWireframe.clear();
    vertexCoordinates.reserve(getNumberVertices()*3);
    vertexNormals.reserve(getNumberVertices()*3);
    triangles.reserve(getNumberFaces()*3);
    triangleColors.reserve(getNumberFaces()*3);
    triangleNormals.reserve(getNumberFaces()*3);
    vertexColors.resize(getNumberVertices()*3,0.5);
    facesWireframe.reserve(getNumberHalfEdges());
    std::map<int, int> v_ids;
    int vi = 0;

    for (const Dcel::Vertex* v : vertexIterator()) {
        Pointd p = v->getCoordinate();
        Vec3 n = v->getNormal();
        vertexCoordinates.push_back(p.x());
        vertexCoordinates.push_back(p.y());
        vertexCoordinates.push_back(p.z());
        vertexNormals.push_back(n.x());
        vertexNormals.push_back(n.y());
        vertexNormals.push_back(n.z());

        v_ids[v->getId()] = vi;
        vi++;
    }
    #ifdef CG3_CGAL_DEFINED
    triangles_face.clear();
    for (const Dcel::Face* f : faceIterator()) {
        for (const Dcel::HalfEdge* he : f->incidentHalfEdgeIterator()) {
            unsigned int p1, p2;
                p1 = v_ids[he->getFromVertex()->getId()];
                p2 = v_ids[he->getToVertex()->getId()];
                std::pair<unsigned int, unsigned int> edge(p1,p2);
                facesWireframe.push_back(edge);
            }


        if (f->isTriangle()){
            for (const Dcel::Vertex* v : f->incidentVertexIterator())
                triangles.push_back(v_ids[v->getId()]);
            triangleColors.push_back(f->getColor().redF());
            triangleColors.push_back(f->getColor().greenF());
            triangleColors.push_back(f->getColor().blueF());
            triangleNormals.push_back(f->getNormal().x());
            triangleNormals.push_back(f->getNormal().y());
            triangleNormals.push_back(f->getNormal().z());
            triangles_face.push_back(f->getId());
        }
        else {
            //Si ottiene la triangolazione della faccia e si inseriscono i triangoli
            //prodotti nell'array tris.
            std::vector<std::array<const Dcel::Vertex*, 3> > face_triangles;
            f->getTriangulation(face_triangles);
            std::array<const Dcel::Vertex*, 3> t;
            for(unsigned int i = 0; i<face_triangles.size(); ++i){
                t = face_triangles[i];
                const Dcel::Vertex* v1 = t[0];
                const Dcel::Vertex* v2 = t[1];
                const Dcel::Vertex* v3 = t[2];
                triangles.push_back(v_ids[v1->getId()]);
                triangles.push_back(v_ids[v3->getId()]);
                triangles.push_back(v_ids[v2->getId()]);
            }
            //Si crea una mappatura triangolo->faccia di appartenenza
            //Per ogni triangolo prodotto dalla triangolazione della faccia si aggiunge
            //un colore (composto da una tripla di valori)
            for(unsigned int ti = 0; ti < face_triangles.size(); ti++){
                triangles_face.push_back(f->getId());
                triangleColors.push_back(f->getColor().redF());
                triangleColors.push_back(f->getColor().greenF());
                triangleColors.push_back(f->getColor().blueF());
                triangleNormals.push_back(f->getNormal().x());
                triangleNormals.push_back(f->getNormal().y());
                triangleNormals.push_back(f->getNormal().z());
            }
            /***********************************************************************/
        }
    }
    #else
    for (ConstFaceIterator fit = faceBegin(); fit != faceEnd(); ++fit) {
        Dcel::Face::ConstIncidentVertexIterator vit = (*fit)->incidentVertexBegin();
        triangles.push_back(v_ids[(*vit)->getId()]);
        ++vit;
        triangles.push_back(v_ids[(*vit)->getId()]);
        ++vit;
        triangles.push_back(v_ids[(*vit)->getId()]);
        triangleColors.push_back((*fit)->getColor().redF());
        triangleColors.push_back((*fit)->getColor().greenF());
        triangleColors.push_back((*fit)->getColor().blueF());
        triangleNormals.push_back((*fit)->getNormal().x());
        triangleNormals.push_back((*fit)->getNormal().y());
        triangleNormals.push_back((*fit)->getNormal().z());
    }
    #endif
}

/**
 * \~Italian
 * @brief Rendering della mesh
 */
void DrawableDcel::renderPass(unsigned int nv, unsigned int nt, const double* coords, const int* triangles, const double* vertexNormals, const float* vertexColors, const double* triangleNormals, const float* triangleColors) const {
    DrawableMesh::renderPass(nv, nt, coords, triangles, vertexNormals, vertexColors, triangleNormals, triangleColors);
    if(drawMode & DRAW_FACES_WIREFRAME){
        for(unsigned int i=0; i<facesWireframe.size(); i++){
            glLineWidth(facesWireframeWidth);
            glColor3f(facesWireframeColor[0], facesWireframeColor[1], facesWireframeColor[2]);
            glBegin(GL_LINES);
            glVertex3dv(&(vertexCoordinates[3*(facesWireframe[i].first)]));
            glVertex3dv(&(vertexCoordinates[3*(facesWireframe[i].second)]));
            glEnd();
        }
    }
}

/**
 * \~Italian
 * @brief Setta la visibilità del wireframe del contorno delle facce della mesh
 */
void DrawableDcel::setFacesWireframe(bool b) {
    if (b) drawMode |=  DRAW_FACES_WIREFRAME;
    else   drawMode &= ~DRAW_FACES_WIREFRAME;
}

/**
 * \~Italian
 * @brief Setta la larghezza del wireframe del contorno delle facce della mesh
 */
void DrawableDcel::setFacesWireframeWidth(const int w) {
    facesWireframeWidth = w;
}

/**
 * \~Italian
 * @brief Setta il colore del wireframe del contorno delle facce della mesh
 */
void DrawableDcel::setFacesWireframeColor(float r, float g, float b) {
    wireframeColor[0] = r;
    wireframeColor[1] = g;
    wireframeColor[2] = b;
}

void DrawableDcel::deserialize(std::ifstream& binaryFile) {
    Dcel::deserialize(binaryFile);
    update();
}

}
