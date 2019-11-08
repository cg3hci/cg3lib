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

CG3_INLINE DrawableDcel::DrawableDcel() : Dcel()
{
	init();
}

CG3_INLINE DrawableDcel::DrawableDcel(const char* filename) : Dcel(filename)
{
	init();
}

CG3_INLINE DrawableDcel::DrawableDcel(const std::string& filename) : Dcel(filename)
{
	init();
}

/**
 * \~Italian
 * @brief Crea una DrawableDcel a partire dalla Dcel passata come parametro (di cui ne verrà fatta una copia)
 * @param[in] d: Dcel che verrà copiata e resa visualizzabile
 */
CG3_INLINE DrawableDcel::DrawableDcel(const Dcel &d) : Dcel(d)
{
    init();
}

/**
 * \~Italian
 * @brief Setta impostazioni di visualizzazione di default.
 */
CG3_INLINE void DrawableDcel::init()
{
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
CG3_INLINE void DrawableDcel::clear()
{
    Dcel::clear();
    init();
    vertexCoordinates.clear();
    vertexNormals.clear();
    vertexColors.clear();
    triangleNormals.clear();
    triangles.clear();
    triangleColors.clear();
}

CG3_INLINE void DrawableDcel::draw() const
{
    DrawableMesh::draw((unsigned int)vertexCoordinates.size()/3, (unsigned int)triangles.size()/3, vertexCoordinates.data(), triangles.data(), vertexNormals.data(), vertexColors.data(), triangleNormals.data(), triangleColors.data(), bBox.min(), bBox.max());
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
    if (drawMode & DRAW_FLAGGED_EDGES){
        for (uint i = 0; i < flaggedEdges.size(); i+=2){
            cg3::opengl::drawLine3(flaggedEdges[i], flaggedEdges[i+1], flaggedEdgesColor, flaggedEdgesWireframeWidth);
        }
    }
}

/**
 * \~Italian
 * @brief Calcola e restituisce il centro della Dcel.
 * @return il punto rappresentante il centro della mesh.
 */
CG3_INLINE Point3d DrawableDcel::sceneCenter() const
{
    if (bBox.isValid())
        return bBox.center();
    else
        return Point3d();
}

/**
 * \~Italian
 * @brief Calcola il raggio della Dcel.
 * @return Restituisce un valore rappresentante il raggio della mesh
 */
CG3_INLINE double DrawableDcel::sceneRadius() const
{
    if (bBox.isValid())
        return bBox.diag() / 2;
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
CG3_INLINE void DrawableDcel::update()
{
    vertexCoordinates.clear();
    vertexNormals.clear();
    triangles.clear();
    triangleColors.clear();
    vertexColors.clear();
    triangleNormals.clear();
    facesWireframe.clear();
    trianglesFacesMap.clear();
    facesTrianglesMap.clear();
    flaggedEdges.clear();
    vertexCoordinates.reserve(numberVertices()*3);
    vertexNormals.reserve(numberVertices()*3);
    triangles.reserve(numberFaces()*3);
    triangleColors.reserve(numberFaces()*3);
    triangleNormals.reserve(numberFaces()*3);
    vertexColors.resize(numberVertices()*3,0.5);
    facesWireframe.reserve(numberHalfEdges());
    trianglesFacesMap.reserve(numberFaces());
    std::map<int, int> v_ids;
    int vi = 0;

    for (const Dcel::Vertex* v : vertexIterator()) {
        Point3d p = v->coordinate();
        Vec3d n = v->normal();
        vertexCoordinates.push_back(p.x());
        vertexCoordinates.push_back(p.y());
        vertexCoordinates.push_back(p.z());
        n.normalize();
        vertexNormals.push_back(n.x());
        vertexNormals.push_back(n.y());
        vertexNormals.push_back(n.z());

        v_ids[v->id()] = vi;
        vi++;
    }

    unsigned int actualTriangle = 0;
    #ifdef CG3_CGAL_DEFINED
    for (const Dcel::Face* f : faceIterator()) {
        for (const Dcel::HalfEdge* he : f->incidentHalfEdgeIterator()) {
            unsigned int p1, p2;
                p1 = v_ids[he->fromVertex()->id()];
                p2 = v_ids[he->toVertex()->id()];
                std::pair<unsigned int, unsigned int> edge(p1,p2);
                facesWireframe.push_back(edge);
            }


        if (f->isTriangle()){
            for (const Dcel::Vertex* v : f->incidentVertexIterator())
                triangles.push_back(v_ids[v->id()]);
            triangleColors.push_back(f->color().redF());
            triangleColors.push_back(f->color().greenF());
            triangleColors.push_back(f->color().blueF());
            triangleNormals.push_back(f->normal().x());
            triangleNormals.push_back(f->normal().y());
            triangleNormals.push_back(f->normal().z());
            trianglesFacesMap.push_back(f->id());
            facesTrianglesMap[f->id()] = actualTriangle++;
        }
        else {
            facesTrianglesMap[f->id()] = actualTriangle;
            //Si ottiene la triangolazione della faccia e si inseriscono i triangoli
            //prodotti nell'array tris.
            std::vector<std::array<const Dcel::Vertex*, 3> > face_triangles;
            f->triangulation(face_triangles);
            std::array<const Dcel::Vertex*, 3> t;
            for(unsigned int i = 0; i<face_triangles.size(); ++i){
                t = face_triangles[i];
                const Dcel::Vertex* v1 = t[0];
                const Dcel::Vertex* v2 = t[1];
                const Dcel::Vertex* v3 = t[2];
                triangles.push_back(v_ids[v1->id()]);
                triangles.push_back(v_ids[v3->id()]);
                triangles.push_back(v_ids[v2->id()]);
                trianglesFacesMap.push_back(f->id());
                triangleColors.push_back(f->color().redF());
                triangleColors.push_back(f->color().greenF());
                triangleColors.push_back(f->color().blueF());
                triangleNormals.push_back(f->normal().x());
                triangleNormals.push_back(f->normal().y());
                triangleNormals.push_back(f->normal().z());
                actualTriangle++;
            }
            /***********************************************************************/
        }
    }
    #else
    for (const Dcel::Face* f : faceIterator()) {
        Dcel::Face::ConstIncidentVertexIterator vit = f->incidentVertexBegin();
        triangles.push_back(v_ids[(*vit)->id()]);
        ++vit;
        triangles.push_back(v_ids[(*vit)->id()]);
        ++vit;
        triangles.push_back(v_ids[(*vit)->id()]);
        triangleColors.push_back(f->color().redF());
        triangleColors.push_back(f->color().greenF());
        triangleColors.push_back(f->color().blueF());
        triangleNormals.push_back(f->normal().x());
        triangleNormals.push_back(f->normal().y());
        triangleNormals.push_back(f->normal().z());
        trianglesFacesMap.push_back(f->id());
        facesTrianglesMap[f->id()] = actualTriangle++;
    }
    #endif
    for (cg3::Dcel::HalfEdge* he : halfEdgeIterator()){
        if (he->twin() != nullptr) {
            if (he->id() < he->twin()->id()){
                if (he->flag() == flag || he->twin()->flag() == flag){
                    Vec3d ff = (he->face()->normal() + he->twin()->face()->normal())/2;
                    flaggedEdges.push_back(he->fromVertex()->coordinate() + ff*cg3::CG3_EPSILON);
                    flaggedEdges.push_back(he->toVertex()->coordinate() + ff*cg3::CG3_EPSILON);
                }
            }
        } else {
            if (he->flag() == flag){
                Vec3d ff = he->face()->normal();
                flaggedEdges.push_back(he->fromVertex()->coordinate() + ff*cg3::CG3_EPSILON);
                flaggedEdges.push_back(he->toVertex()->coordinate() + ff*cg3::CG3_EPSILON);
            }
        }
    }
}

/**
 * \~Italian
 * @brief Rendering della mesh
 */
CG3_INLINE void DrawableDcel::renderPass(unsigned int nv, unsigned int nt, const double* coords, const int* triangles, const double* vertexNormals, const float* vertexColors, const double* triangleNormals, const float* triangleColors) const
{
    DrawableMesh::renderPass(nv, nt, coords, triangles, vertexNormals, vertexColors, triangleNormals, triangleColors);
}

/**
 * \~Italian
 * @brief Setta la visibilità del wireframe del contorno delle facce della mesh
 */
CG3_INLINE void DrawableDcel::setFacesWireframe(bool b)
{
    if (b) drawMode |=  DRAW_FACES_WIREFRAME;
    else   drawMode &= ~DRAW_FACES_WIREFRAME;
}

/**
 * \~Italian
 * @brief Setta la larghezza del wireframe del contorno delle facce della mesh
 */
CG3_INLINE void DrawableDcel::setFacesWireframeWidth(const int w)
{
    facesWireframeWidth = w;
}

/**
 * \~Italian
 * @brief Setta il colore del wireframe del contorno delle facce della mesh
 */
CG3_INLINE void DrawableDcel::setFacesWireframeColor(float r, float g, float b)
{
    wireframeColor[0] = r;
    wireframeColor[1] = g;
    wireframeColor[2] = b;
}

/**
 * @brief DrawableDcel::setFlaggedEdgesWireframe
 * @param b
 * @param flag
 * @param w
 * @param color
 */
CG3_INLINE void DrawableDcel::setFlaggedEdgesWireframe(
        bool b,
        int flag,
        int w,
        Color color)
{
    if (b) drawMode |=  DRAW_FLAGGED_EDGES;
    else   drawMode &= ~DRAW_FLAGGED_EDGES;
    this->flag = flag;
    flaggedEdgesWireframeWidth = w;
    flaggedEdgesColor = color;
}

CG3_INLINE void DrawableDcel::deserialize(std::ifstream& binaryFile)
{
    Dcel::deserialize(binaryFile);
    update();
}

CG3_INLINE bool DrawableDcel::loadFromDcelFile(const std::string& filename)
{
    if (Dcel::loadFromDcelFile(filename)){
        update();
        return true;
    }
    return false;
}

CG3_INLINE bool DrawableDcel::loadFromObj(const std::string& filename)
{
    if (Dcel::loadFromObj(filename)){
        update();
        return true;
    }
    return false;
}

CG3_INLINE bool DrawableDcel::loadFromPly(const std::string& filename)
{
    if (Dcel::loadFromPly(filename)) {
        update();
        return true;
    }
    return false;
}

CG3_INLINE bool DrawableDcel::loadFromFile(const std::string& filename)
{
    if (Dcel::loadFromFile(filename)){
        update();
        return true;
    }
    return false;
}

} //namespace cg3
