/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
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
 * @class Dcel
 *
 * Main Dcel Page: @ref DcelPage
 *
 * @brief Double Connected Edge List data structure.
 *
 * The Dcel class is composed by three main lists of:
 * - Dcel::Vertex*
 * - Dcel::HalfEdge*
 * - Dcel::Face*
 *
 * The data structure is half-edge based: all the local adjacence and incidence relations are stored inside the Dcel::HalfEdge.
 * It is possible to modify these relations by simply use set methods. Dcel::Vertex and Dcel::Face contain some pointers to incident
 * half edges (Dcel::Vertex contains an outgoing half edge, Dcel::Face contains an incident outer half edge and one inner half edge
 * for every hole of the face), all the other adjacent/incident relations can be obtained through the half edges.
 * Dcel allows to access all its elements through iterators. For example, we can iterate through all the vertices of a Dcel d in the
 * following way:
 * \code{.cpp}
 * for (Dcel::VertexIterator vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     // use v here
 * }
 * \endcode
 *
 * or:
 *
 * \code{.cpp}
 * for (Dcel::Vertex* v : d.vertexIterator()){
 *     // use v here
 * }
 * \endcode
 *
 * We can do the same thing with Dcel::HalfEdge and Dcel::Face. For const Dcel, you can use const iterators.
 * Dcel::Vertex and Dcel::Face classes have also other type of iterators (which are mostly circular iterators)
 * that allows to access to incident/adjacent elements. See the documentation for all the specific iterators.
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
