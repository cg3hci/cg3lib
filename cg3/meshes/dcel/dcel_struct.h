/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_STRUCT_H
#define CG3_DCEL_STRUCT_H

#include <cg3/geometry/bounding_box.h>
#include <cg3/utilities/color.h>

#ifdef  CG3_EIGENMESH_DEFINED
namespace cg3 {
    class SimpleEigenMesh;
    class EigenMesh;
}
#endif

#ifdef CG3_CINOLIB_DEFINED
namespace  cinolib{
    class Trimesh;
}
#endif

namespace cg3 {

/**
 * \~Italian
 * @class Dcel
 * @brief Struttura dati Double Conntected Edge List.
 *
 * La classe Dcel è composta principalmente da tre liste di:
 * - Dcel::Vertex*
 * - Dcel::HalfEdge*
 * - Dcel::Face*
 *
 *
 * La struttura è Half-Edge based: tutte le relazioni di adiacenza e incidenza locali di un half edge sono contenuti
 * all'interno della classe Dcel::HalfEdge, ci si può accedere mediante semplici operazioni di get e si possono modificare
 * mediante semplici operazioni di set. Dcel::Vertex e Dcel::Face hanno invece dei riferimenti ad alcuni degli half edge incidenti
 * (nel caso del Dcel::Vertex solo uno, nel caso della Dcel::Face uno esterno e uno per ogni buco), e le restanti adiacenze/incidenze
 * sono reperibili mediante le operazioni messe a disposizione da Dcel::HalfEdge.
 * La Dcel mette a disposizione degli iteratori per poter accedere a tutti i Vertici, Half Edge e Facce contenunti in essa
 * e non permette di poter accedere direttamente ai vettori che li contengono, per poter preservare quelli che sono i dettagli
 * implementativi che permettono al programmatore di utilizzare una struttura dati il più sicura possibile.
 *
 * Si può ciclare, per esempio, su tutti i vertici contenuti nella Dcel con l'iteratore sui vertici:
 *
 * \code{.cpp}
 * for (Dcel::VertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     // operazioni su v
 * }
 * \endcode
 *
 * La stessa cosa si può fare con Dcel::HalfEdgeIterator e Dcel::FaceIterator. Per ciclare su const Dcel, invece, ci sono gli iteratori
 * Dcel::ConstVertexIterator, Dcel::ConstHalfEdgeIterator e Dcel::ConstFaceIterator.
 * La classi Dcel::Vertex e Dcel::Face mettono a disposizione altri iteratori (vedere le relative pagine), tuttavia i loro iteratori sono
 * completamente diversi rispetto a questi. Gli iteratori della Dcel servono per ciclare su tutti gli elementi contenuti nella Dcel, senza
 * tenere conto di nessuna relazione di adiacenza o incidenza.
 *
 * Gli iteratori presenti in Dcel::Vertex e Dcel::Face invece servono solo ed esclusivamente a visitare tutte le componenti adiacenti o incidenti
 * ad un Dcel::Vertex o una Dcel::Face. Non vi sono iteratori nella classe Dcel::HalfEdge in quanto tutte le relazioni di incidenza/adiacenza
 * sono ottenibili mediante operazioni di get.
 */

class Dcel : public SerializableObject {

    public:

        /*********************
        * Associated Classes *
        **********************/

        class Vertex;
        class Face;
        class HalfEdge;

        /************
        * Iterators *
        *************/

        class VertexIterator;
        class ConstVertexIterator;
        class HalfEdgeIterator;
        class ConstHalfEdgeIterator;
        class FaceIterator;
        class ConstFaceIterator;
        class ConstVertexRangeBasedIterator;
        class ConstHalfEdgeRangeBasedIterator;
        class ConstFaceRangeBasedIterator;
        class VertexRangeBasedIterator;
        class HalfEdgeRangeBasedIterator;
        class FaceRangeBasedIterator;

        /***************
        * Constructors *
        ****************/

        Dcel();
        Dcel(const char* filename);
        Dcel(const std::string& filename);
        Dcel(const Dcel& dcel);
        Dcel(Dcel&& dcel);
        #ifdef  CG3_EIGENMESH_DEFINED
        Dcel(const cg3::SimpleEigenMesh &eigenMesh);
        Dcel(const cg3::EigenMesh &eigenMesh);
        #endif // CG3_EIGENMESH_DEFINED
        #ifdef CG3_CINOLIB_DEFINED
        Dcel(const cinolib::Trimesh &trimesh);
        #endif //CG3_CINOLIB_DEFINED
        ~Dcel();

        /************************
        * Public Inline Methods *
        *************************/

        const Vertex* getVertex(unsigned int idVertex)          const;
        const HalfEdge* getHalfEdge(unsigned int idHalfEdge)    const;
        const Face* getFace(unsigned int idFace)                const;
        BoundingBox getBoundingBox()                            const;
        inline unsigned int getNumberVertices()        const;
        inline unsigned int getNumberHalfEdges()       const;
        inline unsigned int getNumberFaces()           const;
        inline ConstVertexIterator vertexBegin()       const;
        inline ConstVertexIterator vertexEnd()         const;
        inline ConstHalfEdgeIterator halfEdgeBegin()   const;
        inline ConstHalfEdgeIterator halfEdgeEnd()     const;
        inline ConstFaceIterator faceBegin()           const;
        inline ConstFaceIterator faceEnd()             const;
        inline const ConstVertexRangeBasedIterator vertexIterator() const;
        inline const ConstHalfEdgeRangeBasedIterator halfEdgeIterator() const;
        inline const ConstFaceRangeBasedIterator faceIterator() const;

        Vertex* getVertex(unsigned int idVertex);
        HalfEdge* getHalfEdge(unsigned int idHalfEdge);
        Face* getFace(unsigned int idFace);
        VertexIterator deleteVertex(const VertexIterator& vit);
        HalfEdgeIterator deleteHalfEdge(const HalfEdgeIterator& heit);

        FaceIterator deleteFace(const FaceIterator& fit);
        inline VertexIterator vertexBegin();
        inline VertexIterator vertexEnd();
        inline HalfEdgeIterator halfEdgeBegin();
        inline HalfEdgeIterator halfEdgeEnd();
        inline FaceIterator faceBegin();
        inline FaceIterator faceEnd();
        inline VertexRangeBasedIterator vertexIterator();
        inline HalfEdgeRangeBasedIterator halfEdgeIterator();
        inline FaceRangeBasedIterator faceIterator();

        /*****************
        * Public Methods *
        ******************/

        bool deleteVertex (Vertex* v);
        bool isTriangleMesh()                                   const;
        double getSurfaceArea()                                 const;
        Pointd getBarycenter()                                  const;
        double getAverageHalfEdgesLength()                      const;
        void saveOnObjFile(std::string fileNameObj)             const;
        void saveOnPlyFile(std::string fileNamePly)             const;
        void saveOnDcelFile(std::string fileNameDcel)           const;

        Vertex* addVertex(const Pointd& p = Pointd(), const Vec3& n = Vec3(), const Color &c = Color(128, 128, 128));
        HalfEdge* addHalfEdge();
        Face* addFace(const Vec3& n = Vec3(), const Color& c = Color(128,128,128));
        bool deleteHalfEdge (HalfEdge* he);
        bool deleteFace (Face* f);
        void updateFaceNormals();
        void updateVertexNormals();
        BoundingBox updateBoundingBox();
        void setColor(const Color &c);
        void scale(const BoundingBox &newBoundingBox);
        #ifdef CG3_WITH_EIGEN
        void rotate(const Eigen::Matrix3d& matrix);
        void rotate(const Eigen::Matrix3d& matrix, const Pointd& centroid);
        #endif
        void rotate(double matrix[3][3], const Pointd& centroid = Pointd());
        void translate(const Pointd &c);
        void recalculateIds();
        void resetFaceColors();
        void clear();
        #ifdef  CG3_CGAL_DEFINED
        unsigned int triangulateFace(Dcel::Face* f);
        void triangulate();
        #endif
        bool loadFromFile(const std::string& filename);
        bool loadFromObjFile(const std::string& filename);
        bool loadFromPlyFile(const std::string& filename);
        bool loadFromDcelFile(const std::string& filename);

        void swap(Dcel& d);

        Dcel& operator= (Dcel dcel);

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:

        /*************
        * Attributes *
        **************/

        std::vector<Vertex* >   vertices;       /**< \~Italian @brief Lista di vertici della Dcel. */
        std::vector<HalfEdge* > halfEdges;      /**< \~Italian @brief Lista di half edge della Dcel. */
        std::vector<Face* >     faces;          /**< \~Italian @brief Lista di facce della Dcel. */
        std::set<int>           unusedVids;     /**< \~Italian @brief Insieme degli id dei vertici non utilizzati (nullptr). */
        std::set<int>           unusedHeids;    /**< \~Italian @brief Insieme degli id degli half edge non utilizzati (nullptr). */
        std::set<int>           unusedFids;     /**< \~Italian @brief Insieme degli id delle facce non utilizzati (nullptr). */
        unsigned int            nVertices;      /**< \~Italian @brief Prossimo id del vertice. */
        unsigned int            nHalfEdges;     /**< \~Italian @brief Prossimo id dell'half edge. */
        unsigned int            nFaces;         /**< \~Italian @brief Prossimo id della faccia. */
        BoundingBox             boundingBox;    /**< \~Italian @brief Bounding box della mesh. */

        //Data
        #ifdef NDEBUG
        std::vector<Pointd> vertexCoordinates;
        std::vector<Vec3> vertexNormals;
        std::vector<Color> vertexColors;
        std::vector<Vec3> faceNormals;
        std::vector<Color> faceColors;
        #endif

        /******************
        * Private Methods *
        *******************/

        Vertex* addVertex(int id);
        HalfEdge* addHalfEdge(int id);
        Face* addFace(int id);

        std::vector<const Vertex*> makeSingleBorder(const Face *f)     const;
        void toStdVectors(std::vector<double> &vertices, std::vector<double> &verticesNormals, std::vector<int> &faces, std::vector<unsigned int> &faceSizes, std::vector<float> &faceColors) const;

        void afterLoadFile(const std::list<double>& coords, const std::list<unsigned int>& faces, int mode, const std::list<double>& vnorm, const std::list<Color>& vcolor, const std::list<Color>& fcolor, const std::list<unsigned int>& fsizes);

        #ifdef  CG3_EIGENMESH_DEFINED
        void copyFrom(const SimpleEigenMesh &eigenMesh);
        void copyFrom(const EigenMesh &eigenMesh);
        #endif // CG3_EIGENMESH_DEFINED
        #ifdef CG3_CINOLIB_DEFINED
        void copyFrom(const cinolib::Trimesh &trimesh);
        #endif //CG3_CINOLIB_DEFINED
};

void swap(Dcel& d1, Dcel& d2);

}

#include "dcel_inline.tpp"

#endif // CG3_DCEL_STRUCT_H
