/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_STRUCT_H
#define CG3_DCEL_STRUCT_H

#include <cg3/geometry/bounding_box3.h>
#include <cg3/utilities/color.h>
#include <cg3/meshes/mesh.h>
#include <cg3/io/file_commons.h>
#include "dcel_data.h"
#include "dcel_iterators.h"

#ifdef  CG3_EIGENMESH_DEFINED
namespace cg3 {
    class SimpleEigenMesh;
    class EigenMesh;
} //namespace cg3
#endif

#ifdef CG3_CINOLIB_DEFINED
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
#include <cinolib/meshes/trimesh.h>
#pragma GCC diagnostic pop
#else
#include <cinolib/meshes/trimesh.h>
#endif
#endif //CG3_CINOLIB_DEFINED

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
template <class V = Vertex, class HE = HalfEdge, class F = Face>
class TemplatedDcel : public SerializableObject, public internal::DcelData
{
public:

    /*********************
    * Associated Classes *
    **********************/

    /*class Vertex;
    class Face;
    class HalfEdge;*/
    using Vertex = V;
    using HalfEdge = HE;
    using Face = F;

    /************
    * Iterators *
    *************/

    using VertexIterator = internal::DcelIterator<Vertex>;
    using ConstVertexIterator = internal::ConstDcelIterator<Vertex>;
    using HalfEdgeIterator = internal::DcelIterator<HalfEdge>;
    using ConstHalfEdgeIterator = internal::ConstDcelIterator<HalfEdge>;
    using FaceIterator = internal::DcelIterator<Face>;
    using ConstFaceIterator = internal::ConstDcelIterator<Face>;
    class ConstVertexRangeBasedIterator;
    class ConstHalfEdgeRangeBasedIterator;
    class ConstFaceRangeBasedIterator;
    class VertexRangeBasedIterator;
    class HalfEdgeRangeBasedIterator;
    class FaceRangeBasedIterator;

    /***************
    * Constructors *
    ****************/

    TemplatedDcel();
    TemplatedDcel(const char* filename);
    TemplatedDcel(const std::string& filename);
    TemplatedDcel(const TemplatedDcel& dcel);
    TemplatedDcel(TemplatedDcel&& dcel);
    #ifdef  CG3_EIGENMESH_DEFINED
    TemplatedDcel(const cg3::SimpleEigenMesh &eigenMesh);
    TemplatedDcel(const cg3::EigenMesh &eigenMesh);
    #endif // CG3_EIGENMESH_DEFINED
    #ifdef CG3_CINOLIB_DEFINED
    TemplatedDcel(const cinolib::Trimesh<> &trimesh);
    #endif //CG3_CINOLIB_DEFINED
    ~TemplatedDcel();

    /************************
    * Public Inline Methods *
    *************************/

    const Vertex* vertex(unsigned int idVertex)          const;
    const HalfEdge* halfEdge(unsigned int idHalfEdge)    const;
    const Face* face(unsigned int idFace)                const;
	BoundingBox3 boundingBox()                            const;
    inline unsigned int numberVertices()        const;
    inline unsigned int numberHalfEdges()       const;
    inline unsigned int numberFaces()           const;
    inline bool contains(const Vertex* v)               const;
    inline bool contains(const HalfEdge* he)            const;
    inline bool contains(const Face* f)                 const;
    inline ConstVertexIterator vertexBegin()       const;
    inline ConstVertexIterator vertexEnd()         const;
    inline ConstHalfEdgeIterator halfEdgeBegin()   const;
    inline ConstHalfEdgeIterator halfEdgeEnd()     const;
    inline ConstFaceIterator faceBegin()           const;
    inline ConstFaceIterator faceEnd()             const;
    inline const ConstVertexRangeBasedIterator vertexIterator() const;
    inline const ConstHalfEdgeRangeBasedIterator halfEdgeIterator() const;
    inline const ConstFaceRangeBasedIterator faceIterator() const;

    Vertex* vertex(unsigned int idVertex);
    HalfEdge* halfEdge(unsigned int idHalfEdge);
    Face* face(unsigned int idFace);
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


    bool vertexBelongsToThis(const Vertex* v)               const;
    bool halfEdgeBelongsToThis(const HalfEdge* he)          const;
    bool faceBelongsToThis(const Face* f)                   const;
    bool isTriangleMesh()                                   const;
    double surfaceArea()                                 const;
    double volume()                                         const;
    Point3d barycenter()                                  const;
    double averageHalfEdgesLength()                      const;
    bool saveOnObj(const std::string& fileNameObj) const;
    bool saveOnObj(const std::string& fileNameObj, bool saveProperties)             const;
	bool saveOnPly(const std::string& fileNamePly, bool binary = true) const;
	bool saveOnPly(const std::string& fileNamePly, bool binary, io::FileMeshMode fm) const;
    void saveOnDcelFile(const std::string& fileNameDcel)           const;

    Vertex* addVertex(const Point3d& p = Point3d(), const Vec3d& n = Vec3d(), const Color &c = Color(128, 128, 128));
    HalfEdge* addHalfEdge();
    Face* addFace(const Vec3d& n = Vec3d(), const Color& c = Color(128,128,128));
    bool deleteVertex (Vertex* v);
    bool deleteVertex (unsigned int vid);
    bool deleteHalfEdge (HalfEdge* he);
    bool deleteHalfEdge (unsigned int heid);
    bool deleteFace (Face* f);
    bool deleteFace(unsigned int fid);
    void invertFaceOrientations();
    void deleteUnreferencedVertices();
    void deleteDuplicatedVertices();
    void updateFaceAreas();
    void updateFaceNormals();
    void updateVertexNormals();
	BoundingBox3 updateBoundingBox();
	void setFaceColors(const Color &c);
	void setFaceFlags(int flag);
	void setVertexColors(const Color &c);
	void setVertexFlags(int flag);
    void scale(double scaleFactor);
    void scale(const cg3::Vec3d& scaleVector);
	void scale(const BoundingBox3 &newBoundingBox);
    #ifdef CG3_WITH_EIGEN
    void rotate(const Eigen::Matrix3d& matrix);
    void rotate(const Eigen::Matrix3d& matrix, const Point3d& centroid);
    #endif
    void rotate(const Vec3d& axis, double angle, const Point3d& centroid = Point3d());
    void rotate(double matrix[3][3], const Point3d& centroid = Point3d());
    void translate(const Vec3d &c);
    void recalculateIds();
    void resetFaceColors();
    void clear();
    #ifdef  CG3_CGAL_DEFINED
    unsigned int triangulateFace(uint idf);
    void triangulate();
    #endif
    bool loadFromFile(const std::string& filename);
    bool loadFromObj(const std::string& filename);
    bool loadFromPly(const std::string& filename);
    bool loadFromDcelFile(const std::string& filename);

    void swap(TemplatedDcel& d);
    void merge(const TemplatedDcel& d);
    void merge(TemplatedDcel&& d);

    TemplatedDcel& operator= (TemplatedDcel dcel);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:

    /*************
    * Attributes *
    **************/

    std::vector<Vertex* >   vertices;
    std::vector<HalfEdge* > halfEdges;
    std::vector<Face* >     faces;
    std::set<int>           unusedVids;
    std::set<int>           unusedHeids;
    std::set<int>           unusedFids;
    unsigned int            nVertices;
    unsigned int            nHalfEdges;
    unsigned int            nFaces;
	BoundingBox3             bBox;

    /******************
    * Private Methods *
    *******************/

    Vertex* addVertex(int id);
    HalfEdge* addHalfEdge(int id);
    Face* addFace(int id);

    std::vector<const Vertex*> makeSingleBorder(const Face *f)     const;
    void toStdVectors(
            std::vector<double> &vertices,
            std::vector<double> &verticesNormals,
			std::vector<float> &verticesColors,
            std::vector<int> &faces,
			std::vector<double> &faceNormals,
            std::vector<unsigned int> &faceSizes,
            std::vector<float> &faceColors) const;

    void afterLoadFile(
            const std::list<double>& coords,
            const std::list<unsigned int>& faces,
			const io::FileMeshMode& fm,
			const std::list<double>& vnorm,
            const std::list<Color>& vcolor,
            const std::list<Color>& fcolor,
            const std::list<unsigned int>& fsizes);

    #ifdef  CG3_EIGENMESH_DEFINED
    void copyFrom(const SimpleEigenMesh &eigenMesh);
    void copyFrom(const EigenMesh &eigenMesh);
    #endif // CG3_EIGENMESH_DEFINED
    #ifdef CG3_CINOLIB_DEFINED
    void copyFrom(const cinolib::Trimesh<> &trimesh);
#endif //CG3_CINOLIB_DEFINED
};

template <class Vertex, class HalfEdge, class Face>
void swap(TemplatedDcel<Vertex, HalfEdge, Face>& d1, TemplatedDcel<Vertex, HalfEdge, Face>& d2);

template <class Vertex, class HalfEdge, class Face>
TemplatedDcel<Vertex, HalfEdge, Face> merge(const TemplatedDcel<Vertex, HalfEdge, Face>& d1, const TemplatedDcel<Vertex, HalfEdge, Face>& d2);

} //namespace cg3

#include "dcel_struct.cpp"

#endif // CG3_DCEL_STRUCT_H
