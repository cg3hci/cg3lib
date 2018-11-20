/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "dcel_face_iterators.h"
#include "dcel_vertex_iterators.h"
#include "dcel_iterators.h"
#include <cg3/utilities/comparators.h>
#include <cg3/utilities/utils.h>
#include <cg3/utilities/const.h>
#include <cg3/io/serialize.h>
#include <cg3/io/load_save_file.h>
#include <cg3/geometry/transformations.h>

#ifdef  CG3_CGAL_DEFINED
#include <cg3/cgal/triangulation.h>
#endif //CGAL_DEFINED

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif //EIGENMESH_DEFINED

#ifdef CG3_CINOLIB_DEFINED
#include <cinolib/meshes/trimesh.h>
#endif //CG3_CINOLIB_DEFINED

namespace cg3 {

/****************
 * Constructors *
 ****************/

/**
 * @brief Empty constructor
 *
 * Creates an empty Dcel: 0 vertices, 0 half edges and 0 faces.
 */
Dcel::Dcel() :
    nVertices(0),
    nHalfEdges(0),
    nFaces(0)
{
}

/**
 * \~Italian
 * @brief Costruttore di copia di una Dcel.
 *
 * Crea una nuova Dcel a partire dalla Dcel passata in input, creando nuove istanze
 * di tutti i vertici, gli half edge e le facce contenute in dcel, e settando di conseguenza
 * tutte le relazioni tra essi.
 * @param[in] dcel: dcel da cui verrà creata la Dcel this.
 */
Dcel::Dcel(const Dcel& dcel)
{
    this->unusedVids = dcel.unusedVids;
    this->unusedHeids = dcel.unusedHeids;
    this->unusedFids = dcel.unusedFids;
    this->nVertices = dcel.nVertices;
    this->nHalfEdges = dcel.nHalfEdges;
    this->nFaces = dcel.nFaces;
    this->bBox = dcel.bBox;
    std::map<const Dcel::Vertex*, Dcel::Vertex*> mapVertices;
    std::map<const Dcel::HalfEdge*, Dcel::HalfEdge*> mapHalfEdges;
    std::map<const Dcel::Face*, Dcel::Face*> mapFaces;
    this->vertices.resize(dcel.vertices.size(), nullptr);
    #ifdef NDEBUG
    this->vertexCoordinates.resize(dcel.vertexCoordinates.size(), Pointd());
    this->vertexNormals.resize(dcel.vertexNormals.size(), Vec3());
    this->vertexColors.resize(dcel.vertexColors.size(), Color());
    #endif
    for (const Dcel::Vertex* ov : dcel.vertexIterator()) {
        Dcel::Vertex* v = this->addVertex(ov->id());
        v->setId(ov->id());
        v->setCoordinate(ov->coordinate());
        v->setFlag(ov->flag());
        v->setCardinality(ov->cardinality());
        v->setNormal(ov->normal());
        v->setColor(ov->color());
        mapVertices[ov] = v;
    }

    this->halfEdges.resize(dcel.halfEdges.size(), nullptr);
    for (const Dcel::HalfEdge* ohe : dcel.halfEdgeIterator()) {
        Dcel::HalfEdge* he = this->addHalfEdge(ohe->id());
        he->setId(ohe->id());
        he->setFlag(ohe->flag());
        he->setFromVertex(mapVertices[ohe->fromVertex()]);
        he->setToVertex(mapVertices[ohe->toVertex()]);
        mapHalfEdges[ohe] = he;
    }

    this->faces.resize(dcel.faces.size(), nullptr);
    #ifdef NDEBUG
    this->faceNormals.resize(dcel.faceNormals.size(), Vec3());
    this->faceColors.resize(dcel.faceColors.size(), Color());
    #endif
    for (const Face* of : dcel.faceIterator()){
        Dcel::Face* f = this->addFace(of->id());
        f->setId(of->id());
        f->setColor(of->color());
        f->setFlag(of->flag());
        f->setNormal(of->normal());
        f->setArea(of->area());
        f->setOuterHalfEdge(mapHalfEdges[of->outerHalfEdge()]);
        for (Dcel::Face::ConstInnerHalfEdgeIterator heit = of->innerHalfEdgeBegin(); heit != of->innerHalfEdgeEnd(); ++heit){
            f->addInnerHalfEdge(mapHalfEdges[*heit]);
        }
        mapFaces[of] = f;
    }

    for (const Dcel::HalfEdge* ohe : dcel.halfEdgeIterator()) {
        Dcel::HalfEdge* he = mapHalfEdges[ohe];
        he->setNext(mapHalfEdges[ohe->next()]);
        he->setPrev(mapHalfEdges[ohe->prev()]);
        he->setTwin(mapHalfEdges[ohe->twin()]);
        he->setFace(mapFaces[ohe->face()]);
    }

    for (const Dcel::Vertex* ov : dcel.vertexIterator()) {
        Dcel::Vertex * v = mapVertices[ov];
        v->setIncidentHalfEdge(mapHalfEdges[ov->incidentHalfEdge()]);
    }
}

Dcel::Dcel(Dcel&& dcel)
{
    vertices = std::move(dcel.vertices);
    faces = std::move(dcel.faces);
    halfEdges = std::move(dcel.halfEdges);
    unusedVids = std::move(dcel.unusedVids);
    unusedHeids = std::move(dcel.unusedHeids);
    unusedFids = std::move(dcel.unusedFids);
    nVertices = std::move(dcel.nVertices);
    nHalfEdges = std::move(dcel.nHalfEdges);
    nFaces = std::move(dcel.nFaces);
    bBox = std::move(dcel.bBox);
    #ifdef NDEBUG
    vertexCoordinates = std::move(dcel.vertexCoordinates);
    vertexNormals = std::move(dcel.vertexNormals);
    vertexColors = std::move(dcel.vertexColors);
    faceNormals = std::move(dcel.faceNormals);
    faceColors = std::move(dcel.faceColors);
    for (Dcel::Vertex* v : vertexIterator()){
        v->parent = this;
    }
    for (Dcel::HalfEdge* he : halfEdgeIterator()){
        he->parent = this;
    }
    for (Dcel::Face* f : faceIterator()){
        f->parent = this;
    }
    #endif

}

#ifdef  CG3_EIGENMESH_DEFINED
Dcel::Dcel(const cg3::SimpleEigenMesh& eigenMesh)
{
    copyFrom(eigenMesh);
    updateVertexNormals();
}

Dcel::Dcel(const cg3::EigenMesh& eigenMesh)
{
    copyFrom(eigenMesh);
}
#endif // CG3_EIGNEMESH_DEFINED

#ifdef CG3_CINOLIB_DEFINED
Dcel::Dcel(const cinolib::Trimesh<> &trimesh)
{
    copyFrom(trimesh);
}
#endif //CG3_CINOLIB_DEFINED



/**
 * \~Italian
 * @brief Distruttore della Dcel.
 *
 * Elimina tutti gli elementi contenuti nelle liste dei vertici, degli half edge e delle facce della Dcel.
 */
Dcel::~Dcel()
{
    for (unsigned int i=0; i<vertices.size(); i++)
        if (vertices[i]!= nullptr)
            delete vertices[i];
    for (unsigned int i=0; i<halfEdges.size(); i++)
        if (halfEdges[i] != nullptr)
            delete halfEdges[i];
    for (unsigned int i=0; i<faces.size(); i++)
        if (faces[i] != nullptr)
            delete faces[i];
}

/******************
* Public Methods *
******************/

/**
 * \~Italian
 * @brief Funzione che verifica se la mesh contenuta nella Dcel è una mesh di triangoli
 * @warning utilizza Dcel::Face::constIncidentVertexIterator
 * @return True se la mesh è composta da soli triangoli, false altrimenti
 * @par Complessità:
 *      \e O(numFaces)
 */
bool Dcel::isTriangleMesh() const
{
    if (numberFaces() == 0) return false;
    for (const Face* f : faceIterator())
        if (! f->isTriangle()) return false;
    return true;
}

/**
 * \~Italian
 * @brief Funzione che restituisce la somma delle aree di tutta le facce presenti nella Dcel.
 * @return L'area dell'intra superficie della mesh
 * @par Complessità:
 *      \e O(numFaces)
 */
double Dcel::surfaceArea() const
{
    double area = 0;
    for (const Face* f : faceIterator()){
        area += f->area();
    }
    return area;
}

Pointd Dcel::barycenter() const
{
    Pointd bc;
    for (const Dcel::Vertex* v : vertexIterator()){
        bc += v->coordinate();
    }
    bc /= numberVertices();
    return bc;
}

double Dcel::averageHalfEdgesLength() const
{
    double average = 0;
    for (const HalfEdge* he : halfEdgeIterator()){
        average += he->length();
    }
    average /= nHalfEdges;
    return average;
}

/**
 * \~Italian
 * @brief Salva un file nel formato obj rappresentante la mesh contenuta nella Dcel.
 *
 * @todo Il formato OBJ non gestisce buchi all'interno delle facce, per cui, ogni volta che ci sono
 * buchi, viene creato un singolo bordo che unsice il bordo interno a tutti i bordi interni utilizzando
 * dummy edges. \n
 * Per la gestione dei colori, viene creato un file separato con lo stesso nome e con estensione mtl.
 *
 * @warning Utilizza Dcel::Face::ConstIncidentHalfEdgeIterator
 *
 * @param[in] fileNameObj: il nome del file su cui verrà salvata la mesh, \b con \b l'estensione \b obj.
 *
 * @par Complessità:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
bool Dcel::saveOnObj(const std::string& fileNameObj) const
{
    std::vector<double> vertices;
    std::vector<double> verticesNormals;
    std::vector<int> faces;
    std::vector<unsigned int> faceSizes;
    std::vector<float> faceColors;

    toStdVectors(vertices, verticesNormals, faces, faceSizes, faceColors);

    io::MeshType meshType = io::POLYGON_MESH;
    int mode = io::NORMAL_VERTICES | io::COLOR_FACES;
    return saveMeshOnObj(fileNameObj, numberVertices(), numberFaces(), vertices.data(),
                         faces.data(), meshType, mode, verticesNormals.data(), io::RGB,
                         internal::dummyVectorFloat.data(), faceColors.data(), faceSizes.data());
}

/**
 * \~Italian
 * @brief Salva un file nel formato ply rappresentante la mesh contenuta nella Dcel.
 *
 * @todo Il formato PLY non gestisce buchi all'interno delle facce, per cui, ogni volta che ci sono
 * buchi, viene creato un singolo bordo che unsice il bordo interno a tutti i bordi interni utilizzando
 * dummy edges. \n
 *
 * @warning Utilizza Dcel::Face::ConstIncidentHalfEdgeIterator
 *
 * @param[in] fileNamePly: il nome del file su cui verrà salvata la mesh, \b con \b l'estensione \b ply.
 *
 * @par Complessità:
 *      \e O(numVertices) + \e O(numFaces) + \e O(numHalfEdges)
 */
bool Dcel::saveOnPly(const std::string& fileNamePly) const
{
    std::vector<double> vertices;
    std::vector<double> verticesNormals;
    std::vector<int> faces;
    std::vector<unsigned int> faceSizes;
    std::vector<float> faceColors;

    toStdVectors(vertices, verticesNormals, faces, faceSizes, faceColors);

    io::MeshType meshType = io::POLYGON_MESH;
    int mode = io::NORMAL_VERTICES | io::COLOR_FACES;
    return saveMeshOnPly(fileNamePly, numberVertices(), numberFaces(), vertices.data(),
                         faces.data(), meshType, mode, verticesNormals.data(),
                         io::RGB, internal::dummyVectorFloat.data(), faceColors.data(), faceSizes.data());
}

void Dcel::saveOnDcelFile(const std::string& fileNameDcel) const
{
    std::ofstream myfile;
    myfile.open (fileNameDcel, std::ios::out | std::ios::binary);
    if (myfile.is_open()) {
        serialize(myfile);
    }
    myfile.close();
}

/**
 * \~Italian
 * @brief Aggiunge un vertice alla Dcel con le coordinate passate in input, e ne restituisce il puntatore
 *
 * Il Dcel::Vertex è inizializzato col costruttore Vertex(Pointd), e successivamente viene settato un id
 * univoco..
 *
 * @param[in] p: le coordinate del vertice da aggiungere alla Dcel
 * @return Il puntatore al vertice appena inserito nella Dcel
 * @par Complessità:
 *      \e O(1)
 */
Dcel::Vertex *Dcel::addVertex(const Pointd& p, const Vec3& n, const Color& c)
{
    #ifdef NDEBUG
    Vertex* last= new Vertex(*this);
    #else
    Vertex* last= new Vertex();
    #endif
    if (unusedVids.size() == 0) {
        last->setId(nVertices);
        vertices.push_back(last);
        #ifdef NDEBUG
        vertexCoordinates.push_back(p);
        vertexNormals.push_back(n);
        vertexColors.push_back(c);
        #else
        last->setCoordinate(p);
        last->setNormal(n);
        last->setColor(c);
        #endif
    }
    else {
        int vid = *(unusedVids.begin());
        last->setId(vid);
        vertices[vid] = last;
        unusedVids.erase(vid);
        #ifdef NDEBUG
        vertexCoordinates[vid] = p;
        vertexNormals[vid] = n;
        vertexColors[vid] = c;
        #else
        last->setCoordinate(p);
        last->setNormal(n);
        last->setColor(c);
        #endif

    }
    nVertices++;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge un half edge alla Dcel e ne restituisce il puntatore.
 *
 * Il Dcel::HalfEdge è inizializzato col costruttore vuoto, e successivamente viene settato un id
 * univoco.
 *
 * @return Il puntatore all'half edge appena inserito nella Dcel
 * @par Complessità:
 *      \e O(1)
 */
Dcel::HalfEdge* Dcel::addHalfEdge()
{
    #ifdef NDEBUG
    HalfEdge* last = new HalfEdge(*this);
    #else
    HalfEdge* last = new HalfEdge();
    #endif
    if (unusedHeids.size() == 0){
        last->setId(nHalfEdges);
        halfEdges.push_back(last);
        //halfEdgeLinks.push_back({-1, -1, -1, -1, -1, -1});
    }
    else {
        int heid = *(unusedHeids.begin());
        last->setId(heid);
        halfEdges[heid] = last;
        //halfEdgeLinks[heid] = {-1, -1, -1, -1, -1, -1};
        unusedHeids.erase(heid);
    }
    nHalfEdges++;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge una faccia alla Dcel e ne restituisce il puntatore.
 *
 * La Dcel::Face è inizializzata col costruttore vuoto, e successivamente viene settato un id
 * univoco.
 *
 * @return Il puntatore alla faccia appena inserita nella Dcel
 * @par Complessità:
 *      \e O(1)
 */
Dcel::Face* Dcel::addFace(const Vec3& n, const Color& c)
{
    #ifdef NDEBUG
    Face* last = new Face(*this);
    #else
    Face* last = new Face();
    #endif
    if (unusedFids.size() == 0){
        last->setId(nFaces);
        faces.push_back(last);
        #ifdef NDEBUG
        faceNormals.push_back(n);
        faceColors.push_back(c);
        #else
        last->setNormal(n);
        last->setColor(c);
        #endif
    }
    else {
        int fid = *(unusedFids.begin());
        last->setId(fid);
        faces[fid] = last;
        unusedFids.erase(fid);
        #ifdef NDEBUG
        faceNormals[fid] = n;
        faceColors[fid] = c;
        #else
        last->setNormal(n);
        last->setColor(c);
        #endif
    }
    nFaces++;
    return last;
}

/**
 * \~Italian
 * @brief Funzione che elimina il vertice passato in input.
 *
 * Una volta eliminato, il vertice passato in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento al vertice eliminato v:
 * per ogni half edge uscente he:
 * - he->fromVertex
 * - he->twin->toVertex
 *
 * @param[in] v: vertice da eliminare
 * @return True se il vertice è stato eliminato correttamente (ossia è stato trovato un vertice con
 * lo stesso id all'interno della lista di vertici), false altrimenti
 * @par Complessità:
 *      \e O(nIncidentHalfEdges) ->  \e ~O(1)
 */
bool Dcel::deleteVertex(Dcel::Vertex* v)
{
    if (v->_incidentHalfEdge != nullptr){
        Dcel::HalfEdge* he = v->_incidentHalfEdge;
        do {
            if (he != nullptr){
                if (he->_fromVertex == v) he->_fromVertex = nullptr;
                if (he->_twin != nullptr) {
                    he = he->_twin;
                    if (he->_toVertex == v) he->_toVertex = nullptr;
                    he = he->_next;
                }
                else he = v->_incidentHalfEdge;
            }
            else he = v->_incidentHalfEdge;
        } while (he != v->_incidentHalfEdge);
    }
    vertices[v->_id]=nullptr;
    unusedVids.insert(v->_id);
    nVertices--;

    delete v;
    return true;
}

bool Dcel::vertexBelongsToThis(const Dcel::Vertex* v) const
{
    if (!v) return false;
#ifdef NDEBUG
    return v->parent == this;
#else
    return v->id() < vertices.size() && vertices[v->id()] == v;
#endif
}

bool Dcel::halfEdgeBelongsToThis(const Dcel::HalfEdge* he) const
{
    if (!he) return false;
#ifdef NDEBUG
    return he->parent == this;
#else
    return he->id() < halfEdges.size() && halfEdges[he->id()] == he;
#endif
}

bool Dcel::faceBelongsToThis(const Dcel::Face* f) const
{
    if (!f) return false;
#ifdef NDEBUG
    return f->parent == this;
#else
    return f->id() < faces.size() && faces[f->id()] == f;
#endif
}

/**
 * \~Italian
 * @brief Funzione che elimina l'half edge passato in input.
 *
 * Una volta eliminato, il'half edge passato in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento all'half edge eliminato he:
 * - he->twin->twin
 * - he->next->prev
 * - he->prev->next
 * - he->fromVertex->incidentHalfEdge
 * - he->face->outerHalfEdge
 * eventuali inner half edge di he->face
 *
 * @param[in] he: half edge da eliminare
 * @return True se l'half edge è stato eliminato correttamente (ossia è stato trovato un half edge con
 * lo stesso id all'interno della lista degli half edge), false altrimenti
 * @par Complessità:
 *      \e O(1)
 */
bool Dcel::deleteHalfEdge(HalfEdge* he)
{
    if (he->_twin != nullptr)
        if (he->_twin->_twin == he) he->_twin->_twin = nullptr;
    if (he->_next != nullptr)
        if (he->_next->_prev == he) he->_next->_prev = nullptr;
    if (he->_prev != nullptr)
        if(he->_prev->_next == he) he->_prev->_next = nullptr;
    if (he->_face != nullptr){
        if (he->_face->_outerHalfEdge == he) he->_face->_outerHalfEdge = nullptr;
        else if (he->_face->hasHoles()) {
            for (unsigned int i = 0; i < he->_face->_innerHalfEdges.size(); i++){
                if (he->_face->_innerHalfEdges[i] == he)
                    he->_face->_innerHalfEdges.erase(he->_face->_innerHalfEdges.begin() + i--);
            }
        }
    }
    if (he->_fromVertex != nullptr)
        if (he->_fromVertex->_incidentHalfEdge == he) he->_fromVertex->_incidentHalfEdge = nullptr;
    halfEdges[he->_id] = nullptr;
    unusedHeids.insert(he->_id);
    nHalfEdges--;

    delete he;
    return true;
}

/**
 * \~Italian
 * @brief Funzione che elimina la faccia passata in input.
 *
 * Una volta eliminata, la faccia passata in input non è più utilizzabile.
 *
 * Setta a nullptr tutti i seguenti campi se contengono un riferimento alla faccia eliminata f:
 * per ogni half edge incidente he:
 * - he->face
 *
 * @param[in] f: faccia da eliminare
 * @return True se la faccia è stata eliminata correttamente (ossia è stato trovata una faccia con
 * lo stesso id all'interno della lista delle facce), false altrimenti
 * @par Complessità:
 *      \e O(nIncidentHalfEdges) -> \e ~O(1)
 */
bool Dcel::deleteFace(Face* f)
{
    if (f->_outerHalfEdge != nullptr){
        Dcel::HalfEdge* he = f->_outerHalfEdge;
        do {
            if (he->_face == f) he->_face = nullptr;
            he = he->_next;
        } while (he != f->_outerHalfEdge);
    }
    for (unsigned int i = 0; i < f->_innerHalfEdges.size(); i++){
        Dcel::HalfEdge* he = f->_innerHalfEdges[i];
        do {
            if (he->_face == f) he->_face = nullptr;
            he = he->_next;
        } while (he != f->_innerHalfEdges[i]);
    }
    faces[f->id()]=nullptr;
    unusedFids.insert(f->id());
    nFaces--;
    delete f;
    return true;
}

/**
 * \~Italian
 * @brief Funzione che ricalcola e aggiorna le normali delle facce presenti nella Dcel.
 *
 * Richiama il metodo \c updateNormal() della classe Dcel::Face, per cui non aggiorna
 * le normali delle facce che non sono triangoli.
 *
 * @warning Funziona solo sulle facce che sono triangoli
 * @warning Utilizza Dcel::Face::constIncidentVertexIterator
 * @par Complessità:
 *      \e O(numFaces)
 */
void Dcel::updateFaceNormals()
{
    for (Dcel::Face* f : faceIterator()){
        f->updateArea();
    }
}

/**
 * \~Italian
 * @brief Funzione che ricalcola e aggiorna le normali e le cardinalità dei vertici presenti nella Dcel.
 *
 * Richiama il metodo \c updateNormal() della classe Dcel::Vertex.
 *
 * @warning Utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @par Complessità:
 *      \e O(numVertices)
 */
void Dcel::updateVertexNormals()
{
    for (Dcel::Vertex* v : vertexIterator())
        v->updateNormal();
}

/**
 * \~Italian
 * @brief Funzione che ricalcola il bounding box più piccolo contenete la mesh
 * @return Il bounding box appena calcolato
 * @par Complessità:
 *      \e O(numVertices)
 */
BoundingBox Dcel::updateBoundingBox()
{
    bBox.reset();
    for (const Dcel::Vertex* v : vertexIterator()){
        const Pointd& coord = v->coordinate();

        bBox.setMinX(std::min(bBox.minX(), coord.x()));
        bBox.setMinY(std::min(bBox.minY(), coord.y()));
        bBox.setMinZ(std::min(bBox.minZ(), coord.z()));

        bBox.setMaxX(std::max(bBox.maxX(), coord.x()));
        bBox.setMaxY(std::max(bBox.maxY(), coord.y()));
        bBox.setMaxZ(std::max(bBox.maxZ(), coord.z()));
    }
    return bBox;
}

void Dcel::setColor(const Color& c)
{
    for (Dcel::Face* f : faceIterator())
        f->setColor(c);
}

void Dcel::scale(double scaleFactor)
{
    scale(cg3::Vec3(scaleFactor, scaleFactor, scaleFactor));
}

void Dcel::scale(const Vec3& scaleVector)
{
    for (Dcel::Vertex* v : vertexIterator()){
        cg3::Pointd p = v->coordinate();
        p *= scaleVector;
        v->setCoordinate(p);
    }
    updateBoundingBox();
}

void Dcel::scale(const BoundingBox& newBoundingBox)
{
    Pointd oldCenter = bBox.center();
    Pointd newCenter = newBoundingBox.center();
    Pointd deltaOld = bBox.max() - bBox.min();
    Pointd deltaNew = newBoundingBox.max() - newBoundingBox.min();
    for (Dcel::Vertex* v : vertexIterator()) {
        v->setCoordinate(v->coordinate() - oldCenter);
        v->setCoordinate(v->coordinate() * (deltaNew / deltaOld));
        v->setCoordinate(v->coordinate() + newCenter);
    }
    bBox = newBoundingBox;
}

#ifdef CG3_WITH_EIGEN
void Dcel::rotate(const Eigen::Matrix3d& matrix)
{
    Pointd c;
    rotate(matrix, c);
}

void Dcel::rotate(const Eigen::Matrix3d &matrix, const Pointd& centroid)
{
    for (Dcel::Vertex* v : vertexIterator()){
        Pointd r = v->coordinate();
        r.rotate(matrix, centroid);
        v->setCoordinate(r);
    }
    updateFaceNormals();
    updateVertexNormals();
    updateBoundingBox();
}
#endif

void Dcel::rotate(const Vec3& axis, double angle, const Pointd& centroid)
{
    double matrix[3][3];
    cg3::rotationMatrix(axis, angle, matrix);
    rotate(matrix, centroid);
}

void Dcel::rotate(double matrix[3][3], const Pointd& centroid)
{
    for (Dcel::Vertex* v : vertexIterator()){
        Pointd r = v->coordinate();
        r.rotate(matrix, centroid);
        v->setCoordinate(r);
        Vec3 n = v->normal();
        n.rotate(matrix, centroid);
        v->setNormal(n);
    }
    updateFaceNormals();
    updateBoundingBox();
}

void Dcel::translate(const cg3::Vec3& c)
{
    for (Dcel::Vertex* v : vertexIterator()){
        v->setCoordinate(v->coordinate() + c);
    }
    updateBoundingBox();
}

/**
 * \~Italian
 * @brief Funzione che ricalcola gli id di vertici, half edge e facce della Dcel.
 *
 * Ricompatta gli id all'interno delle liste contenute della Dcel.
 * Può essere utile richiamare questa funzione se sono state effettuate diverse cancellazioni
 * di componenti, e soprattutto se non si sono memorizzati riferimenti alle componenti mediante
 * vecchi id.
 *
 * @par Complessità:
 *      \e O(numVertices \e + \e NumHalfEdges \e + \e NumFaces)
 */
void Dcel::recalculateIds()
{
    nVertices = 0;
    for (unsigned int i = 0; i < vertices.size(); i++){
        vertices[nVertices] = vertices[i];
        if (vertices[i] != nullptr) {
            vertices[i]->setId(nVertices);
            nVertices++;
        }
    }
    unusedVids.clear();
    vertices.resize(nVertices);

    nHalfEdges = 0;
    for (unsigned int i = 0; i < halfEdges.size(); i++){
        halfEdges[nHalfEdges] = halfEdges[i];
        if (halfEdges[i] != nullptr) {
            halfEdges[i]->setId(nHalfEdges);
            nHalfEdges++;
        }
    }
    unusedHeids.clear();
    halfEdges.resize(nHalfEdges);

    nFaces = 0;
    for (unsigned int i = 0; i < faces.size(); i++){
        faces[nFaces] = faces[i];
        if (faces[i] != nullptr) {
            faces[i]->setId(nFaces);
            nFaces++;
        }
    }
    unusedFids.clear();
    faces.resize(nFaces);
}

/**
 * \~Italian
 * @brief Funzione che resetta i colori delle facce della Dcel.
 *
 * Setta ad ogni faccia un Color(128,128,128), ossia il colore grigio.
 *
 * @par Complessità:
 *      \e O(NumFaces)
 */
void Dcel::resetFaceColors()
{
    for (Face* f: faceIterator())
        f->setColor(Color(128,128,128));
}

/**
 * \~Italian
 * @brief Funzione che cancella tutti i dati contenuti nella Dcel.
 *
 * Per cancellazione si intende la rimozione di tutti i vertici,
 * gli half-edge e le facce precedentemente create, con relativa
 * perdita di tutte le informazioni in esse contenute.
 *
 * @par Complessità:
 *      \e O(numVertices \e + \e NumHalfEdges \e + \e NumFaces)
 */
void Dcel::clear()
{
    for (unsigned int i=0; i<vertices.size(); i++)
        if (vertices[i] != nullptr)
            delete vertices[i];
    for (unsigned int i=0; i<halfEdges.size(); i++)
        if (halfEdges[i] != nullptr)
            delete halfEdges[i];
    for (unsigned int i=0; i<faces.size(); i++)
        if (faces[i] != nullptr)
            delete faces[i];
    vertices.clear();
    halfEdges.clear();
    faces.clear();
    unusedVids.clear();
    unusedHeids.clear();
    unusedFids.clear();
    nVertices = 0;
    nFaces = 0;
    nHalfEdges = 0;
    #ifdef NDEBUG
    vertexCoordinates.clear();
    vertexNormals.clear();
    vertexColors.clear();
    faceNormals.clear();
    faceColors.clear();
    #endif
}

#ifdef  CG3_CGAL_DEFINED
/**
 * \~Italian
 * @brief Funzione che, presa in ingresso una faccia, ne crea una triangolazione.
 *
 * La faccia in ingresso diventa un triangolo (se se lo era già rimarrà un triangolo),
 * e inserisce nella Dcel tanti altri triangoli che comporranno la faccia triangolata.
 *
 * Utilizza CGAL.
 * Utilizzabile SOLAMENTE se è definita la costante letterale CGAL_DEFINED
 * @param[in] f: la faccia che verrà triangolata
 * @return Il numero di triangoli che compone la faccia appena triangolata.
 */
unsigned int Dcel::triangulateFace(Dcel::Face* f)
{
    int count=0;
    if (f->isTriangle())
        return 1;
    else {
        // Taking all the coordinates on vectors
        Dcel::HalfEdge* firstHalfEdge = *(f->incidentHalfEdgeBegin());
        std::vector<Pointd> borderCoordinates;
        std::vector< std::vector<Pointd> > innerBorderCoordinates;
        std::map<std::pair<Dcel::Vertex*, Dcel::Vertex*> , Dcel::HalfEdge*> verticesEdgeMap;
        std::map<std::pair<Dcel::Vertex*, Dcel::Vertex*> , Dcel::HalfEdge*> twinsEdgeMap;
        std::map<Pointd, Dcel::Vertex*> pointsVerticesMap;
        for (Dcel::Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
            borderCoordinates.push_back((*heit)->fromVertex()->coordinate());
            std::pair<Dcel::Vertex*, Dcel::Vertex*> pp;
            pp.first = (*heit)->fromVertex();
            pp.second = (*heit)->toVertex();
            verticesEdgeMap[pp] = *heit;
            pointsVerticesMap[(*heit)->fromVertex()->coordinate()] = (*heit)->fromVertex();
        }

        if (f->hasHoles()){
            innerBorderCoordinates.reserve(f->numberInnerHalfEdges());
            int i = 0;
            for (Dcel::Face::InnerHalfEdgeIterator ihe = f->innerHalfEdgeBegin(); ihe != f->innerHalfEdgeEnd(); ++ihe, ++i){
                Dcel::HalfEdge* he = *ihe;
                std::vector<Pointd> inner;
                for (Dcel::Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(he); heit != f->incidentHalfEdgeEnd(); ++heit){
                    inner.push_back((*heit)->fromVertex()->coordinate());
                    std::pair<Dcel::Vertex*, Dcel::Vertex*> pp;
                    pp.first = (*heit)->fromVertex();
                    pp.second = (*heit)->toVertex();
                    verticesEdgeMap[pp] = *heit;
                }
                innerBorderCoordinates.push_back(inner);
            }
        }

        ///TRIANGULATION

        std::vector<std::array<Pointd, 3> > triangulation = cgal::triangulate(f->normal(), borderCoordinates, innerBorderCoordinates);
        ///


        ///RECONSTRUCTION
        for (unsigned int i = 0; i < triangulation.size(); i++) {
            std::array<Pointd, 3> triangle = triangulation[i];

                Pointd p1 = triangle[0];
                Pointd p2 = triangle[1];
                Pointd p3 = triangle[2];

                Dcel::HalfEdge* e1, *e2, *e3;
                std::pair<Dcel::Vertex*, Dcel::Vertex*> pp;
                bool b = false;
                pp.first = pointsVerticesMap[p1];
                pp.second = pointsVerticesMap[p2];
                if (verticesEdgeMap.find(pp) != verticesEdgeMap.end()){
                    e1 = verticesEdgeMap[pp];
                    if (e1 == firstHalfEdge) b = true;
                }
                else {
                    e1 = addHalfEdge();
                    e1->setFromVertex(pp.first);
                    e1->setToVertex(pp.second);
                    if (twinsEdgeMap.find(pp) == twinsEdgeMap.end()){
                        Dcel::Vertex* tmp = pp.first;
                        pp.first = pp.second;
                        pp.second = tmp;
                        twinsEdgeMap[pp] = e1;
                    }
                    else {
                        Dcel::HalfEdge* twin = twinsEdgeMap[pp];
                        twin->setTwin(e1);
                        e1->setTwin(twin);
                        twinsEdgeMap.erase(pp);
                    }
                }
                pp.first = pointsVerticesMap[p2];
                pp.second = pointsVerticesMap[p3];
                if (verticesEdgeMap.find(pp) != verticesEdgeMap.end()){
                    e2 = verticesEdgeMap[pp];
                    if (e2 == firstHalfEdge) b = true;
                }
                else {
                    e2 = addHalfEdge();
                    e2->setFromVertex(pp.first);
                    e2->setToVertex(pp.second);
                    if (twinsEdgeMap.find(pp) == twinsEdgeMap.end()){
                        Dcel::Vertex* tmp = pp.first;
                        pp.first = pp.second;
                        pp.second = tmp;
                        twinsEdgeMap[pp] = e2;
                    }
                    else {
                        Dcel::HalfEdge* twin = twinsEdgeMap[pp];
                        twin->setTwin(e2);
                        e2->setTwin(twin);
                        twinsEdgeMap.erase(pp);
                    }
                }
                pp.first = pointsVerticesMap[p3];
                pp.second = pointsVerticesMap[p1];
                if (verticesEdgeMap.find(pp) != verticesEdgeMap.end()){
                    e3 = verticesEdgeMap[pp];
                    if (e3 == firstHalfEdge) b = true;
                }
                else {
                    e3 = addHalfEdge();
                    e3->setFromVertex(pp.first);
                    e3->setToVertex(pp.second);
                    if (twinsEdgeMap.find(pp) == twinsEdgeMap.end()){
                        Dcel::Vertex* tmp = pp.first;
                        pp.first = pp.second;
                        pp.second = tmp;
                        twinsEdgeMap[pp] = e3;
                    }
                    else {
                        Dcel::HalfEdge* twin = twinsEdgeMap[pp];
                        twin->setTwin(e3);
                        e3->setTwin(twin);
                        twinsEdgeMap.erase(pp);
                    }
                }

                Dcel::Face* f;
                if (!b)
                    f = addFace();
                else
                    f = firstHalfEdge->face();

                e1->setNext(e2);
                e2->setNext(e3);
                e3->setNext(e1);
                e1->setPrev(e3);
                e2->setPrev(e1);
                e3->setPrev(e2);
                e1->setFace(f);
                e2->setFace(f);
                e3->setFace(f);
                f->setOuterHalfEdge(e1);
                f->setNormal(firstHalfEdge->face()->normal());
                f->setColor(firstHalfEdge->face()->color());

                ++count;
        }

    }
    return count;
}


/**
 * \~Italian
 * @brief Funzione che trasforma una Dcel composta da poligoni generici in una Dcel di triangoli.
 *
 * Per ogni faccia, ne viene creata una triangolazione. I triangoli presenti non vengono modificati.
 * Vengono tuttavia aggiornate le normali ai vertici.
 *
 * Utilizza CGAL.
 * Utilizzabile SOLAMENTE se è definita la costante letterale CGAL_DEFINED
 */
void Dcel::triangulate()
{
    for (Dcel::Face* f : faceIterator()) {
        triangulateFace(f);
    }
    updateVertexNormals();
}
#endif

bool Dcel::loadFromFile(const std::string& filename)
{
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    if(ext == "obj" || ext == "OBJ") { //obj file
        loadFromObj(filename);
        return true;
    }
    else if(ext == "ply" || ext == "PLY") { //ply file
        loadFromPly(filename);
        return true;
    }
    else if (ext == "dcel" || ext == "DCEL") {
        loadFromDcelFile(filename);
        return true;
    }
    else
        return false;
}


/**
 * \~Italian
 * @brief Funzione che carica una mesh salvta su file OBJ nella Dcel.
 *
 * Prima di caricare la mesh, viene chiamata la Dcel::reset().
 * Se, mediante il parametro regular, viene indicato che la mesh è chiusa e senza buchi (ossia
 * ogni vertice ha una \e star completa), una volta caricata la mesh, vengono anche calcolate
 * le normali ai vertici e le cardinalità.
 *
 * @param[in] filename: nome del file su cui è salvata la mesh, comprensivo di estensione
 * @param[in] regular: se true (default), indica che la mesh è chiusa e priva di buchi
 * @warning Se regular, utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @return Una stringa indicante da quanti vertici, half edge e facce è composta la mesh caricata
 */
bool Dcel::loadFromObj(const std::string& filename)
{
    std::list<double> coords, vnorm;
    std::list<unsigned int> faces, fsizes;
    io::MeshType meshType;
    int mode;
    std::list<Color> vcolor, fcolor;

    if (loadMeshFromObj(filename, coords, faces, meshType, mode, vnorm, vcolor, fcolor, fsizes)){
        clear();
        afterLoadFile(coords, faces, mode, vnorm, vcolor, fcolor, fsizes);
        return true;
    }
    else
        return false;
}

/**
 * \~Italian
 * @brief Funzione che carica una mesh salvta su file PLY nella Dcel.
 *
 * Prima di caricare la mesh, viene chiamata la Dcel::reset().
 * Se, mediante il parametro regular, viene indicato che la mesh è chiusa e senza buchi (ossia
 * ogni vertice ha una \e star completa), una volta caricata la mesh, vengono anche calcolate
 * le normali ai vertici e le cardinalità.
 *
 * @param[in] filename: nome del file su cui è salvata la mesh, comprensivo di estensione
 * @param[in] regular: se true (default), indica che la mesh è chiusa e priva di buchi
 * @warning Se regular, utilizza Dcel::Vertex::ConstIncidentFaceIterator
 * @todo Gestione colori vertici
 * @return Una stringa indicante da quanti vertici, half edge e facce è composta la mesh caricata
 */
bool Dcel::loadFromPly(const std::string& filename)
{
    std::list<double> coords, vnorm;
    std::list<unsigned int> faces, fsizes;
    io::MeshType meshType;
    int mode;
    std::list<Color> vcolor, fcolor;

    if (loadMeshFromPly(filename, coords, faces, meshType, mode, vnorm, vcolor, fcolor, fsizes)){
        clear();
        afterLoadFile(coords, faces, mode, vnorm,vcolor, fcolor, fsizes);
        return true;
    }
    else
        return false;
}

bool Dcel::loadFromDcelFile(const std::string& filename)
{
    std::ifstream myfile;
    myfile.open (filename, std::ios::in | std::ios::binary);
    if (myfile.is_open()) {
        try {
            deserialize(myfile);
        }
        catch(...){
            myfile.close();
            return false;
        }
    }
    myfile.close();
    return true;
}

void Dcel::swap(Dcel& d)
{
    std::swap(vertices, d.vertices);
    std::swap(halfEdges, d.halfEdges);
    std::swap(faces, d.faces);
    std::swap(unusedVids, d.unusedVids);
    std::swap(unusedHeids, d.unusedHeids);
    std::swap(unusedFids, d.unusedFids);
    std::swap(nVertices, d.nVertices);
    std::swap(nHalfEdges, d.nHalfEdges);
    std::swap(nFaces, d.nFaces);
    std::swap(bBox, d.bBox);

    #ifdef NDEBUG
    std::swap(vertexCoordinates, d.vertexCoordinates);
    std::swap(vertexNormals, d.vertexNormals);
    std::swap(vertexColors, d.vertexColors);
    std::swap(faceNormals, d.faceNormals);
    std::swap(faceColors, d.faceColors);
    for (Dcel::Vertex* v: vertexIterator())
        v->parent = this;
    for (Dcel::HalfEdge* he: halfEdgeIterator())
        he->parent = this;
    for (Dcel::Face* f: faceIterator())
        f->parent = this;
    for (Dcel::Vertex* v: d.vertexIterator())
        v->parent = &d;
    for (Dcel::HalfEdge* he: d.halfEdgeIterator())
        he->parent = &d;
    for (Dcel::Face* f: d.faceIterator())
        f->parent = &d;
    #endif
}

void Dcel::serialize(std::ofstream& binaryFile) const
{
    cg3::serialize("cg3Dcel", binaryFile);
    //BB
    bBox.serialize(binaryFile);
    //N
    cg3::serialize(nVertices, binaryFile);
    cg3::serialize(nHalfEdges, binaryFile);
    cg3::serialize(nFaces, binaryFile);
    //Sets
    cg3::serialize(unusedVids, binaryFile);
    cg3::serialize(unusedHeids, binaryFile);
    cg3::serialize(unusedFids, binaryFile);
    //Vertices
    for (const Dcel::Vertex* v : vertexIterator()){
        int heid = -1;
        if (v->incidentHalfEdge() != nullptr) heid = v->incidentHalfEdge()->id();

        cg3::serialize(v->id(), binaryFile);
        v->coordinate().serialize(binaryFile);
        v->normal().serialize(binaryFile);
        cg3::serialize(v->color(), binaryFile);
        cg3::serialize(heid, binaryFile);
        cg3::serialize(v->cardinality(), binaryFile);
        cg3::serialize(v->flag(), binaryFile);
    }
    //HalfEdges
    for (const Dcel::HalfEdge* he : halfEdgeIterator()){
        int fv = -1; if (he->fromVertex() != nullptr) fv = he->fromVertex()->id();
        int tv = -1; if (he->toVertex() != nullptr) tv = he->toVertex()->id();
        int tw = -1; if (he->twin() != nullptr) tw = he->twin()->id();
        int prev = -1; if (he->prev() != nullptr) prev = he->prev()->id();
        int next = -1; if (he->next() != nullptr) next = he->next()->id();
        int face = -1; if (he->face() != nullptr) face = he->face()->id();

        cg3::serialize(he->id(), binaryFile);
        cg3::serialize(fv, binaryFile);
        cg3::serialize(tv, binaryFile);
        cg3::serialize(tw, binaryFile);
        cg3::serialize(prev, binaryFile);
        cg3::serialize(next, binaryFile);
        cg3::serialize(face, binaryFile);
        cg3::serialize(he->flag(), binaryFile);
    }
    //Faces
    for (const Dcel::Face* f : faceIterator()){
        int ohe = -1; if (f->outerHalfEdge() != nullptr) ohe = f->outerHalfEdge()->id();
        cg3::serialize(f->id(), binaryFile);
        cg3::serialize(ohe, binaryFile);
        f->normal().serialize(binaryFile);
        cg3::serialize(f->color(), binaryFile);
        cg3::serialize(f->area(), binaryFile);
        cg3::serialize(f->flag(), binaryFile);
        cg3::serialize(f->numberInnerHalfEdges(), binaryFile);

        for (Dcel::Face::ConstInnerHalfEdgeIterator heit = f->innerHalfEdgeBegin(); heit != f->innerHalfEdgeEnd(); ++heit){
            const Dcel::HalfEdge* he = *heit;
            int idhe = -1; if (he != nullptr) idhe = he->id();
            cg3::serialize(idhe, binaryFile);
        }

    }
}

void Dcel::deserialize(std::ifstream& binaryFile)
{
    int begin = binaryFile.tellg();
    Dcel tmp;
    try {
        std::string s;
        cg3::deserialize(s, binaryFile);

        if (s != "cg3Dcel")
            throw std::ios_base::failure("Mismatching String: " + s + " != cg3Dcel");
        //BB

        tmp.bBox.deserialize(binaryFile);
        cg3::deserialize(tmp.nVertices, binaryFile);
        cg3::deserialize(tmp.nHalfEdges, binaryFile);
        cg3::deserialize(tmp.nFaces, binaryFile);
        cg3::deserialize(tmp.unusedVids, binaryFile);
        cg3::deserialize(tmp.unusedHeids, binaryFile);
        cg3::deserialize(tmp.unusedFids, binaryFile);

        //Vertices
        tmp.vertices.resize(tmp.nVertices+tmp.unusedVids.size(), nullptr);
        #ifdef NDEBUG
        tmp.vertexCoordinates.resize(tmp.nVertices+tmp.unusedVids.size(), Pointd());
        tmp.vertexNormals.resize(tmp.nVertices+tmp.unusedVids.size(), Vec3());
        tmp.vertexColors.resize(tmp.nVertices+tmp.unusedVids.size(), Color());
        #endif
        std::map<int, int> vert;

        for (unsigned int i = 0; i < tmp.nVertices; i++){
            int id, heid;
            Pointd coord; Vec3 norm; Color color;
            int c, f;
            cg3::deserialize(id, binaryFile);
            coord.deserialize(binaryFile);
            norm.deserialize(binaryFile);
            cg3::deserialize(color, binaryFile);
            cg3::deserialize(heid, binaryFile);
            cg3::deserialize(c, binaryFile);
            cg3::deserialize(f, binaryFile);

            Dcel::Vertex* v = tmp.addVertex(id);
            v->setCardinality(c);
            v->setCoordinate(coord);
            v->setNormal(norm);
            v->setFlag(f);
            vert[id] = heid;
        }
        //HalfEdges
        tmp.halfEdges.resize(tmp.nHalfEdges+tmp.unusedHeids.size(), nullptr);
        std::map<int, std::array<int, 6> > edges;

        for (unsigned int i = 0; i < tmp.nHalfEdges; i++){
            int id, fv, tv, tw, prev, next, face, flag;
            cg3::deserialize(id, binaryFile);
            cg3::deserialize(fv, binaryFile);
            cg3::deserialize(tv, binaryFile);
            cg3::deserialize(tw, binaryFile);
            cg3::deserialize(prev, binaryFile);
            cg3::deserialize(next, binaryFile);
            cg3::deserialize(face, binaryFile);
            cg3::deserialize(flag, binaryFile);
            Dcel::HalfEdge* he = tmp.addHalfEdge(id);
            he->setFlag(flag);
            edges[id] = {fv, tv, tw, prev, next, face};
        }

        //Faces
        tmp.faces.resize(tmp.nFaces+tmp.unusedFids.size(), nullptr);
        #ifdef NDEBUG
        tmp.faceNormals.resize(tmp.nFaces+tmp.unusedFids.size(), Vec3());
        tmp.faceColors.resize(tmp.nFaces+tmp.unusedFids.size(), Color());
        #endif
        for (unsigned int i = 0; i < tmp.nFaces; i++){
            int id, ohe, /*cr, cg, cb,*/ flag, nihe;
            double /*nx, ny, nz,*/ area;
            Color color;
            Vec3 norm;
            cg3::deserialize(id, binaryFile);
            cg3::deserialize(ohe, binaryFile);
            norm.deserialize(binaryFile);
            cg3::deserialize(color, binaryFile);
            cg3::deserialize(area, binaryFile);
            cg3::deserialize(flag, binaryFile);
            cg3::deserialize(nihe, binaryFile);


            Dcel::Face* f = tmp.addFace(id);
            f->setColor(color);
            f->setNormal(norm);
            f->setArea(area);
            f->setFlag(flag);
            f->setOuterHalfEdge(tmp.halfEdge(ohe));
            for (int j = 0; j < nihe; j++){
                int idhe;
                cg3::deserialize(idhe, binaryFile);
                f->addInnerHalfEdge(tmp.halfEdge(idhe));
            }
        }

        for (Dcel::Vertex* v : tmp.vertexIterator()){
            v->setIncidentHalfEdge(tmp.halfEdge(vert[v->id()]));
        }
        for (Dcel::HalfEdge* he : tmp.halfEdgeIterator()){
            std::array<int, 6> a = edges[he->id()];
            he->setFromVertex(tmp.vertex(a[0]));
            he->setToVertex(tmp.vertex(a[1]));
            he->setTwin(tmp.halfEdge(a[2]));
            he->setPrev(tmp.halfEdge(a[3]));
            he->setNext(tmp.halfEdge(a[4]));
            he->setFace(tmp.face(a[5]));
        }

        *this = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        cg3::restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom cg3::Dcel"));
    }
    catch(...){
        cg3::restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of cg3::Dcel");
    }
}

/**
 * \~Italian
 * @brief Operatore di assegnamento della Dcel.
 *
 * Assegna alla Dcel this un'altra Dcel dcel.
 * Elimina la dcel precedentemente contenuta e successivamente ne fa una copia, che funziona
 * esattamente come il costruttore di copia Dcel(Dcel d):
 * crea una nuova Dcel a partire dalla Dcel passata in input, creando nuove istanze
 * di tutti i vertici, gli half edge e le facce contenute in dcel, e settando di conseguenza
 * tutte le relazioni tra essi.
 * @param[in] dcel: dcel da cui verrà creata la Dcel this
 * @return La Dcel appena assegnata
 */
Dcel& Dcel::operator = (Dcel dcel)
{
    swap(dcel);
    return *this;
}

/*********************
 * Protected Methods *
 ********************/

/**
 * \~Italian
 * @brief Aggiunge un vertice avente l'id passato come parametro alla Dcel e ne restituisce il puntatore.
 *
 * Il Dcel::Vertex è inizializzato col costruttore vuoto, e viene settato l'id passato come parametro.
 *
 * @param[in] id: l'id del vertice che verrà creato.
 * @return Il puntatore al vertice appena inserito nella Dcel
 */
Dcel::Vertex*Dcel::addVertex(int id)
{
    #ifdef NDEBUG
    Vertex* last= new Vertex(*this);
    #else
    Vertex* last= new Vertex();
    #endif
    last->setId(id);
    vertices[id] = last;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge un half edge avente l'id passato come parametro alla Dcel e ne restituisce il puntatore.
 *
 * Il Dcel::HalfEdge è inizializzato col costruttore vuoto, e viene settato l'id passato come parametro.
 *
 * @param[in] id: l'id dell'half edge che verrà creato.
 * @return Il puntatore all'half edge appena inserito nella Dcel
 */
Dcel::HalfEdge*Dcel::addHalfEdge(int id)
{
    #ifdef NDEBUG
    HalfEdge* last = new HalfEdge(*this);
    #else
    HalfEdge* last = new HalfEdge();
    #endif
    last->setId(id);
    halfEdges[id] = last;
    return last;
}

/**
 * \~Italian
 * @brief Aggiunge una faccia avente l'id passato come parametro alla Dcel e ne restituisce il puntatore.
 *
 * La Dcel::Face è inizializzata col costruttore vuoto, e viene settato l'id passato come parametro.
 *
 * @param[in] id: l'id della faccia che verrà creata.
 * @return Il puntatore alla faccia appena inserita nella Dcel
 */
Dcel::Face*Dcel::addFace(int id)
{
    #ifdef NDEBUG
    Face* last = new Face(*this);
    #else
    Face* last = new Face();
    #endif
    last->setId(id);
    faces[id] = last;
    return last;
}

/**
 * \~Italian
 * @brief Funzione che, data in ingresso una faccia avente dei buchi, restituisce una singola lista di vertici di una faccia avente dummy edge.
 * @param[in] f: faccia avente almeno un buco
 * @return Lista di vertice rappresentante una faccia senza buchi ma con dummy edge
 */
std::vector<const Dcel::Vertex*> Dcel::makeSingleBorder(const Face* f) const
{
    std::vector< std::vector<const Vertex*> > visited;
    std::vector< std::vector<const Vertex*> > notVisited;
    std::map< std::pair<int, int>, std::pair<int, int> > links;
    std::vector<const Vertex*> tmp;
    for (Face::ConstIncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(); heit != f->incidentHalfEdgeEnd(); ++heit){
        #ifdef DEBUG
        (*heit)->checkFromVertex();
        #endif
        tmp.push_back((*heit)->fromVertex());
    }
    visited.push_back(tmp);
    for (Face::ConstInnerHalfEdgeIterator iheit = f->innerHalfEdgeBegin(); iheit != f->innerHalfEdgeEnd(); ++iheit){
        tmp.clear();
        for (Face::ConstIncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(*iheit); heit != f->incidentHalfEdgeEnd(); ++heit){
            #ifdef DEBUG
            (*heit)->checkFromVertex();
            #endif
            tmp.push_back((*heit)->fromVertex());
        }
        notVisited.push_back(tmp);
    }
    while (notVisited.size() > 0) {
        // trova la coppia di punti tra visited e not_visited più vicina
        double dist = FLT_MAX;
        int visIndex = -1;
        int notvisIndex = -1;
        int visI = -1;
        int visJ = -1;
        for (unsigned int i=0; i<visited.size(); ++i){
            std::vector<const Vertex*> tmpVisited = visited[i];
            for (unsigned int j=0; j<notVisited.size(); ++j){
                std::vector<const Vertex*> tmpNotVisited = notVisited[j];
                for (unsigned int vi = 0; vi<tmpVisited.size(); ++vi){
                    for (unsigned int vj = 0; vj<tmpNotVisited.size(); ++vj){
                        if (((tmpVisited[vi])->dist(tmpNotVisited[vj])) < dist){
                            visIndex = vi;
                            notvisIndex = vj;
                            visI = i;
                            visJ = j;
                            dist = (tmpVisited[vi])->dist(tmpNotVisited[vj]);
                        }
                    }
                }
            }
        }
        std::pair<int, int> p1;
        p1.first = visI;
        p1.second = visIndex;
        std::pair<int, int> p2;
        p2.first = (int)visited.size();
        p2.second = notvisIndex;
        visited.push_back(notVisited[visJ]);
        notVisited.erase(notVisited.begin() + visJ);
        links[p1] = p2;
        links[p2] = p1;
    }
    std::vector<const Vertex*> border;
    const Vertex* start = visited[0][0];
    border.push_back(start);
    const Vertex* v = nullptr;
    int i = 0;
    int j = 0;
    while (v != start){
        std::pair<int, int> p;
        p.first = i;
        p.second = j;
        if (links.find(p) != links.end()){
            p = links[p];
            i = p.first;
            j = p.second;
            border.push_back(visited[i][j]);
        }
        j = (j + 1) % (visited[i]).size();
        border.push_back(visited[i][j]);
        v = visited[i][j];
    }
    return border;
}

void Dcel::toStdVectors(std::vector<double>& vertices, std::vector<double>& verticesNormals, std::vector<int>& faces, std::vector<unsigned int>& faceSizes, std::vector<float>& faceColors) const
{
    std::map<int, int> mapVertices;
    vertices.reserve(numberVertices()*3);
    verticesNormals.reserve(numberVertices()*3);
    faces.reserve(numberFaces()*3);
    faceSizes.reserve(numberFaces());
    faceColors.reserve(numberFaces()*3);

    int iv = 0;
    for (const Dcel::Vertex* v : vertexIterator()){
        vertices.push_back(v->coordinate().x());
        vertices.push_back(v->coordinate().y());
        vertices.push_back(v->coordinate().z());
        verticesNormals.push_back(v->normal().x());
        verticesNormals.push_back(v->normal().y());
        verticesNormals.push_back(v->normal().z());
        mapVertices[v->id()] = iv++;
    }
    for (const Dcel::Face* f : faceIterator()){
        unsigned int size = 0;
        if (f->numberInnerHalfEdges() == 0) {
            for (const Dcel::Vertex* v : f->incidentVertexIterator()){
                assert(mapVertices.find(v->id()) != mapVertices.end());
                faces.push_back(mapVertices[v->id()]);
                size++;
            }

        }
        else { // holes
            std::vector<const Vertex*> v = makeSingleBorder(f);
            for (unsigned int i = 0; i<v.size(); ++i) {
                assert(mapVertices.find(v[i]->id()) != mapVertices.end());
                faces.push_back(mapVertices[v[i]->id()]);
            }
            size = (unsigned int)v.size();
        }
        faceSizes.push_back(size);
        faceColors.push_back(f->color().redF());
        faceColors.push_back(f->color().greenF());
        faceColors.push_back(f->color().blueF());
    }
}

void Dcel::afterLoadFile(
        const std::list<double> &coords,
        const std::list<unsigned int> &faces,
        int mode,
        const std::list<double> &vnorm,
        const std::list<Color> &vcolor,
        const std::list<Color> &fcolor,
        const std::list<unsigned int> &fsizes)
{
    std::vector<Vertex*> vertices;

    std::map< std::pair<int,int>, HalfEdge* > edge;
    std::map< std::pair<int,int>, HalfEdge* >::iterator eiter;

    bool first = true;

    std::list<double>::const_iterator vnit = vnorm.begin();
    std::list<Color>::const_iterator vcit = vcolor.begin();
    for (std::list<double>::const_iterator it = coords.begin(); it != coords.end(); ){
        double x = *(it++), y = *(it++), z = *(it++);
        Pointd coord(x,y,z);
        if (first) {
            bBox.setMin(coord);
            bBox.setMax(coord);
            first = false;
        }
        bBox.min() = bBox.min().min(coord);
        bBox.max() = bBox.max().max(coord);

        Vertex* vid = addVertex(coord);

        vertices.push_back(vid);

        if (mode & io::NORMAL_VERTICES){
            Vec3 norm;
            norm.setX(*(vnit++));
            norm.setY(*(vnit++));
            norm.setZ(*(vnit++));
            vid->setNormal(norm);
        }
        if (mode & io::COLOR_VERTICES){
            vid->setColor(*(vcit++));
        }
    }

    std::list<unsigned int>::const_iterator fit = faces.begin();
    std::list<Color>::const_iterator fcit = fcolor.begin();
    for (std::list<unsigned int>::const_iterator fsit = fsizes.begin(); fsit != fsizes.end(); ++fsit){

        unsigned int thisSize = *fsit;
        std::vector<unsigned int> nid;
        nid.reserve(thisSize);
        for (unsigned int i = 0; i < thisSize; i++){
            nid.push_back(*(fit++));
        }
        nid.push_back(nid[0]);

        std::pair<int, int> p;
        HalfEdge* eid = nullptr;
        Face* fid = addFace();
        HalfEdge* prev = nullptr;
        HalfEdge* first = nullptr;

        for (unsigned int i=0; i<nid.size()-1; i++){
            eid = addHalfEdge();
            if (i==0) {
                first = eid;
                fid->setOuterHalfEdge(eid);
            }
            else {
                eid->setPrev(prev);
                prev->setNext(eid);
            }
            vertices[nid[i]]->setIncidentHalfEdge(eid);
            eid->setFromVertex(vertices[nid[i]]);
            vertices[nid[i]]->incrementCardinality();
            eid->setToVertex(vertices[nid[i+1]]);
            eid->setFace(fid);
            p.first = nid[i+1];
            p.second = nid[i];
            eiter = edge.find(p);
            if (eiter != edge.end()){
                HalfEdge* twin = edge[p];
                eid->setTwin(twin);
                twin->setTwin(eid);
                edge.erase(eiter);
            }
            else {
                p.first = nid[i];
                p.second = nid[i+1];
                edge[p] = eid;
            }
            prev = eid;
        }
        eid->setNext(first);
        first->setPrev(eid);

        if (mode & io::COLOR_FACES){
            Color c = *(fcit++);
            fid->setColor(c);
        }
        else
            fid->setColor(Color(128, 128, 128));

        fid->updateNormal();
        fid->updateArea();
    }

    if (! (mode & io::NORMAL_VERTICES))
        updateVertexNormals();
}

#ifdef  CG3_EIGENMESH_DEFINED
void Dcel::copyFrom(const SimpleEigenMesh& eigenMesh)
{
    clear();

    std::vector<Vertex*> vertices;

    std::map< std::pair<int,int>, HalfEdge* > edge;
    std::map< std::pair<int,int>, HalfEdge* >::iterator eiter;

    bool first = true;


    for (unsigned int i = 0; i < eigenMesh.numberVertices(); i++) {

        Pointd coord = eigenMesh.vertex(i);

        if (first) {
            bBox.setMin(coord);
            bBox.setMax(coord);
            first = false;
        }

        if (coord.x() < bBox.minX()) bBox.setMinX(coord.x());
        if (coord.y() < bBox.minY()) bBox.setMinY(coord.y());
        if (coord.z() < bBox.minZ()) bBox.setMinZ(coord.z());

        if (coord.x() > bBox.maxX()) bBox.setMaxX(coord.x());
        if (coord.y() > bBox.maxY()) bBox.setMaxY(coord.y());
        if (coord.z() > bBox.maxZ()) bBox.setMaxZ(coord.z());

        Vertex* vid = addVertex(coord);

        vertices.push_back(vid);
    }

    for (unsigned int i = 0; i < eigenMesh.numberFaces(); i++) {

        std::vector<int> nid;
        Pointi ff = eigenMesh.face(i);
        nid.push_back(ff.x());
        nid.push_back(ff.y());
        nid.push_back(ff.z());
        nid.push_back(nid[0]);
        std::pair<int, int> p;
        HalfEdge* eid = nullptr;
        Face* fid = addFace();
        HalfEdge* prev = nullptr;
        HalfEdge* first = nullptr;

        for (unsigned int i=0; i<nid.size()-1; i++){
            eid = addHalfEdge();
            if (i==0) {
                first = eid;
                fid->setOuterHalfEdge(eid);
            }
            else {
                eid->setPrev(prev);
                prev->setNext(eid);
            }
            vertices[nid[i]]->setIncidentHalfEdge(eid);
            eid->setFromVertex(vertices[nid[i]]);
            vertices[nid[i]]->incrementCardinality();
            eid->setToVertex(vertices[nid[i+1]]);
            eid->setFace(fid);
            p.first = nid[i+1];
            p.second = nid[i];
            eiter = edge.find(p);
            if (eiter != edge.end()){
                HalfEdge* twin = edge[p];
                eid->setTwin(twin);
                twin->setTwin(eid);
                edge.erase(eiter);
            }
            else {
                p.first = nid[i];
                p.second = nid[i+1];
                edge[p] = eid;
            }
            prev = eid;
        }
        eid->setNext(first);
        first->setPrev(eid);

        fid->setColor(Color(128, 128, 128));

        fid->updateNormal();
        fid->updateArea();
    }
}

void Dcel::copyFrom(const EigenMesh& eigenMesh)
{
    copyFrom((SimpleEigenMesh)eigenMesh);
    for (Dcel::Face* f : faceIterator()){
        f->setColor(eigenMesh.faceColor(f->id()));
        f->setNormal(eigenMesh.faceNormal(f->id()));
    }
    for (Dcel::Vertex* v : vertexIterator()){
        v->setNormal(eigenMesh.vertexNormal(v->id()));
        v->setColor(eigenMesh.vertexColor(v->id()));
    }
}
#endif // CG3_EIGENMESH_DEFINED

#ifdef CG3_CINOLIB_DEFINED
void Dcel::copyFrom(const cinolib::Trimesh<> &trimesh)
{
    clear();

    std::vector<Vertex*> vertices;

    std::map< std::pair<int,int>, HalfEdge* > edge;
    std::map< std::pair<int,int>, HalfEdge* >::iterator eiter;

    bool first = true;


    for (unsigned int i = 0; i < (unsigned int)trimesh.num_verts(); i++) {

        Pointd coord(trimesh.vert(i));

        if (first) {
            bBox.setMin(coord);
            bBox.setMax(coord);
            first = false;
        }

        if (coord.x() < bBox.minX()) bBox.setMinX(coord.x());
        if (coord.y() < bBox.minY()) bBox.setMinY(coord.y());
        if (coord.z() < bBox.minZ()) bBox.setMinZ(coord.z());

        if (coord.x() > bBox.maxX()) bBox.setMaxX(coord.x());
        if (coord.y() > bBox.maxY()) bBox.setMaxY(coord.y());
        if (coord.z() > bBox.maxZ()) bBox.setMaxZ(coord.z());

        Vertex* vid = addVertex(coord);

        vertices.push_back(vid);
    }

    for (unsigned int i = 0; i < (unsigned int)trimesh.num_polys(); i++) {

        std::vector<int> nid;
        Pointi ff(trimesh.poly_vert_id(i, 0), trimesh.poly_vert_id(i, 1), trimesh.poly_vert_id(i, 2));
        nid.push_back(ff.x());
        nid.push_back(ff.y());
        nid.push_back(ff.z());
        nid.push_back(nid[0]);
        std::pair<int, int> p;
        HalfEdge* eid = nullptr;
        Face* fid = addFace();
        HalfEdge* prev = nullptr;
        HalfEdge* first = nullptr;

        for (unsigned int i=0; i<nid.size()-1; i++){
            eid = addHalfEdge();
            if (i==0) {
                first = eid;
                fid->setOuterHalfEdge(eid);
            }
            else {
                eid->setPrev(prev);
                prev->setNext(eid);
            }
            vertices[nid[i]]->setIncidentHalfEdge(eid);
            eid->setFromVertex(vertices[nid[i]]);
            vertices[nid[i]]->incrementCardinality();
            eid->setToVertex(vertices[nid[i+1]]);
            eid->setFace(fid);
            p.first = nid[i+1];
            p.second = nid[i];
            eiter = edge.find(p);
            if (eiter != edge.end()){
                HalfEdge* twin = edge[p];
                eid->setTwin(twin);
                twin->setTwin(eid);
                edge.erase(eiter);
            }
            else {
                p.first = nid[i];
                p.second = nid[i+1];
                edge[p] = eid;
            }
            prev = eid;
        }
        eid->setNext(first);
        first->setPrev(eid);

        fid->setColor(Color(128, 128, 128));

        fid->updateNormal();
        fid->updateArea();
    }
}

#endif //CG3_CINOLIB_DEFINED

} //namespace cg3
