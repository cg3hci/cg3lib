/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SIMPLEEIGENMESH_H
#define CG3_SIMPLEEIGENMESH_H

#include <Eigen/Core>

#include <cg3/geometry/point.h>
#include <cg3/geometry/bounding_box.h>
#include <cg3/utilities/color.h>
#include <cg3/utilities/const.h>
#include <cg3/utilities/eigen.h>

#ifdef CG3_CINOLIB_DEFINED
#include <cinolib/meshes/trimesh.h>
#endif

namespace cg3 {

#ifdef CG3_LIBIGL_DEFINED
namespace libigl {
namespace internal {

class EigenMeshLibIglAlgorithms;

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
#endif

#ifdef  CG3_DCEL_DEFINED
class Dcel;
#endif

#ifdef TRIMESH_DEFINED
template<typename T>
class Trimesh;
#endif

class EigenMeshAlgorithms;

class SimpleEigenMesh : public SerializableObject
{
    friend class EigenMeshAlgorithms;

    #ifdef CG3_LIBIGL_DEFINED
    friend class libigl::internal::EigenMeshLibIglAlgorithms;
    #endif

public:
    SimpleEigenMesh();
    SimpleEigenMesh(const std::string& filename);
    template <typename T, typename U> SimpleEigenMesh(const Eigen::PlainObjectBase<T> &V, const Eigen::PlainObjectBase<U> &F);
    #ifdef  CG3_DCEL_DEFINED
    SimpleEigenMesh(const Dcel& dcel);
    #endif
    #ifdef TRIMESH_DEFINED
    template<typename T> SimpleEigenMesh(const Trimesh<T>& trimesh);
    #endif
    #ifdef CG3_CINOLIB_DEFINED
    SimpleEigenMesh(const cinolib::Trimesh<> &trimesh);
    #endif

    const Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>& getVerticesMatrix() const;
    const Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>& getFacesMatrix() const;

    unsigned int getNumberVertices() const;
    unsigned int getNumberFaces() const;
    Pointd getVertex(unsigned int i) const;
    Pointi getFace(unsigned int i) const;
    double getFaceArea(unsigned int f) const;
    virtual Vec3 getFaceNormal(unsigned int f) const;
    virtual void getBoundingBox(Eigen::RowVector3d &BBmin, Eigen::RowVector3d &BBmax) const;
    virtual BoundingBox getBoundingBox() const;
    Pointd getBarycenter() const;

    virtual void clear();
    virtual void resizeVertices(unsigned int nv);
    void setVertex(unsigned int i, const Eigen::VectorXd &p);
    void setVertex(unsigned int i, const Pointd &p);
    void setVertex(unsigned int i, double x, double y, double z);
    virtual unsigned int addVertex(const Eigen::VectorXd &p);
    virtual unsigned int addVertex(const Pointd &p);
    virtual unsigned int addVertex(double x, double y, double z);
    virtual void resizeFaces(unsigned int nf);
    void setFace(unsigned int i, const Eigen::VectorXi &f);
    void setFace(unsigned int i, int t1, int t2, int t3);
    virtual unsigned int addFace(const Eigen::VectorXi &f);
    virtual unsigned int addFace(int t1, int t2, int t3);
    virtual void removeFace(unsigned int f);
    bool isDegenerateTriangle(unsigned int f, double epsilon = CG3_EPSILON) const;
    virtual void removeDegenerateTriangles(double epsilon = CG3_EPSILON);
    template <typename T, int ...A> void setVerticesMatrix(const Eigen::Matrix<T, A...>& V);
    template <typename U, int ...A> void setFacesMatrix(const Eigen::Matrix<U, A...>& F);

    virtual bool readFromObj(const std::string &filename);
    virtual bool readFromPly(const std::string &filename);
    virtual bool readFromFile(const std::string &filename);

    virtual bool saveOnPly(const std::string &filename) const;
    virtual bool saveOnObj(const std::string &filename) const;

    virtual void translate(const Pointd &p);
    virtual void translate(const Eigen::Vector3d &p);
    virtual void rotate(const Eigen::Matrix3d &m, const Eigen::Vector3d& centroid = Eigen::Vector3d::Zero());
    virtual void scale(const BoundingBox& newBoundingBox);
    virtual void scale(const BoundingBox& oldBoundingBox, const BoundingBox& newBoundingBox);
    virtual void scale(const Vec3 &scaleFactor);
    static void merge(SimpleEigenMesh &result, const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);
    static SimpleEigenMesh merge(const SimpleEigenMesh &m1, const SimpleEigenMesh &m2);

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);


protected:
    Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> V;
    Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor> F;
};

/**
 * SimpleEigenMesh
 */

inline SimpleEigenMesh::SimpleEigenMesh()
{
}

inline SimpleEigenMesh::SimpleEigenMesh(const std::string &filename)
{
    readFromFile(filename);
}

template <typename T, typename U>
SimpleEigenMesh::SimpleEigenMesh(const Eigen::PlainObjectBase<T> &V, const Eigen::PlainObjectBase<U> &F) : V(V), F(F)
{
}

#ifdef TRIMESH_DEFINED
template <typename T>
inline SimpleEigenMesh::SimpleEigenMesh(const Trimesh<T>& trimesh)
{
    int numV=trimesh.numVertices();
    int numF=trimesh.numTriangles();

    clear();
    V.resize(numV,3);
    F.resize(numF,3);

    for(int i=0;i<numV;++i) {
        V(i,0)=trimesh.vertex(i).x();
        V(i,1)=trimesh.vertex(i).y();
        V(i,2)=trimesh.vertex(i).z();
    }

    for(int i=0;i<numF;++i) {
        F(i,0)=trimesh.tri_vertex_id(i,0);
        F(i,1)=trimesh.tri_vertex_id(i,1);
        F(i,2)=trimesh.tri_vertex_id(i,2);
    }
}
#endif

inline const Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>& SimpleEigenMesh::getVerticesMatrix() const
{
    return V;
}

inline const Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>& SimpleEigenMesh::getFacesMatrix() const
{
    return F;
}

inline unsigned int SimpleEigenMesh::getNumberVertices() const
{
    return V.rows();
}

inline unsigned int SimpleEigenMesh::getNumberFaces() const
{
    return F.rows();
}

inline Pointd SimpleEigenMesh::getVertex(unsigned int i) const
{
    assert(i < (unsigned int)V.rows());
    return Pointd(V(i,0), V(i,1), V(i,2));
}

inline Pointi SimpleEigenMesh::getFace(unsigned int i) const
{
    assert (i < (unsigned int)F.rows());
    return Pointi(F(i,0), F(i,1), F(i,2));
}

inline double SimpleEigenMesh::getFaceArea(unsigned int f) const
{
    Pointd v1 = getVertex(F(f,0));
    return ((getVertex(F(f,2)) - v1).cross(getVertex(F(f,1)) - v1)).getLength() / 2;
}

inline void SimpleEigenMesh::getBoundingBox(Eigen::RowVector3d& BBmin, Eigen::RowVector3d& BBmax) const
{
    if (V.rows() > 0){
        BBmin = V.colwise().minCoeff();
        BBmax = V.colwise().maxCoeff();
    }
    else {
        BBmin = Eigen::RowVector3d();
        BBmax = Eigen::RowVector3d();
    }
}

inline BoundingBox SimpleEigenMesh::getBoundingBox() const
{
    BoundingBox  bb;
    if (V.rows() > 0){
        Eigen::RowVector3d BBmin, BBmax;
        BBmin = V.colwise().minCoeff();
        BBmax = V.colwise().maxCoeff();
        bb.setMin(BBmin(0), BBmin(1), BBmin(2));
        bb.setMax(BBmax(0), BBmax(1), BBmax(2));
    }
    return bb;
}

inline Pointd SimpleEigenMesh::getBarycenter() const
{
    Pointd bc(V.col(0).mean(), V.col(1).mean(), V.col(2).mean());
    return bc;
}

inline void SimpleEigenMesh::clear()
{
    V.resize(0,Eigen::NoChange);
    F.resize(0,Eigen::NoChange);
}

inline void SimpleEigenMesh::resizeVertices(unsigned int nv)
{
    V.conservativeResize(nv,Eigen::NoChange);
}

inline void SimpleEigenMesh::setVertex(unsigned int i, const Eigen::VectorXd& p)
{
    assert (i < (unsigned int)V.rows());
    assert (p.size() == 3);
    V.row(i) =  p;
}

inline void SimpleEigenMesh::setVertex(unsigned int i, const Pointd& p)
{
    assert (i < (unsigned int)V.rows());
    V(i,0) = p.x(); V(i,1) = p.y(); V(i,2) = p.z();
}

inline void SimpleEigenMesh::setVertex(unsigned int i, double x, double y, double z)
{
    assert (i < (unsigned int)V.rows());
    V(i, 0) = x; V(i, 1) = y; V(i, 2) = z;
}

inline unsigned int SimpleEigenMesh::addVertex(const Eigen::VectorXd& p)
{
    assert (p.size() == 3);
    V.conservativeResize(V.rows()+1, Eigen::NoChange);
    V.row(V.rows()-1) = p;
    return (unsigned int)V.rows()-1;
}

inline unsigned int SimpleEigenMesh::addVertex(const Pointd& p)
{
    V.conservativeResize(V.rows()+1, Eigen::NoChange);
    V(V.rows()-1, 0) = p.x(); V(V.rows()-1, 1) = p.y(); V(V.rows()-1, 2) = p.z();
    return (unsigned int)V.rows()-1;
}

inline unsigned int SimpleEigenMesh::addVertex(double x, double y, double z)
{
    V.conservativeResize(V.rows()+1, Eigen::NoChange);
    V(V.rows()-1, 0) = x; V(V.rows()-1, 1) = y; V(V.rows()-1, 2) = z;
    return (unsigned int)V.rows()-1;
}

inline void SimpleEigenMesh::resizeFaces(unsigned int nf)
{
    F.conservativeResize(nf,Eigen::NoChange);
}

inline void SimpleEigenMesh::setFace(unsigned int i, const Eigen::VectorXi& f)
{
    assert (i < (unsigned int)F.rows());
    assert (f.size() == 3);
    F.row(i) =  f;
}

inline void SimpleEigenMesh::setFace(unsigned int i, int t1, int t2, int t3)
{
    assert (i < (unsigned int)F.rows());
    F(i, 0) = t1; F(i, 1) = t2; F(i, 2) = t3;
}

inline unsigned int SimpleEigenMesh::addFace(const Eigen::VectorXi& f)
{
    assert (f.size() == 3);
    F.conservativeResize(F.rows()+1, Eigen::NoChange);
    F.row(F.rows()-1) = f;
    return (unsigned int)F.rows()-1;
}

inline unsigned int SimpleEigenMesh::addFace(int t1, int t2, int t3)
{
    F.conservativeResize(F.rows()+1, Eigen::NoChange);
    F(F.rows()-1, 0) = t1; F(F.rows()-1, 1) = t2; F(F.rows()-1, 2) = t3;
    return (unsigned int)F.rows()-1;
}

inline void SimpleEigenMesh::removeFace(unsigned int f)
{
    assert(f < (unsigned int)F.rows());
    cg3::removeRowFromEigenMatrix(F, f);
}


template <typename T, int ...A>
inline void SimpleEigenMesh::setVerticesMatrix(const Eigen::Matrix<T, A...>& V)
{
    this->V = V;
}

template <typename U, int ...A>
inline void SimpleEigenMesh::setFacesMatrix(const Eigen::Matrix<U, A...>& F)
{
    this->F = F;
}

inline void SimpleEigenMesh::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3SimpleEigenMesh", binaryFile, V, F);
}

inline void SimpleEigenMesh::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3SimpleEigenMesh", binaryFile, V, F);
}

} //namespace cg3

#endif // CG3_SIMPLEEIGENMESH_H
