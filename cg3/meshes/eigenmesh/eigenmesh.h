/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_EIGENMESH_H
#define CG3_EIGENMESH_H

#include "simpleeigenmesh.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

#ifdef CG3_LIBIGL_DEFINED
namespace libigl {
namespace internal {

class EigenMeshLibIglAlgorithms;

} //namespace cg3::libigl::internal
} //namespace cg3::libigl
#endif

class EigenMesh : public SimpleEigenMesh
{
    friend class EigenMeshAlgorithms;

    #ifdef CG3_LIBIGL_DEFINED
    friend class libigl::internal::EigenMeshLibIglAlgorithms;
    #endif

public:
    EigenMesh();
	EigenMesh(const char* filename);
    EigenMesh(const std::string& filename);
    EigenMesh(const SimpleEigenMesh &m);
    EigenMesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F);
    EigenMesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F, const Eigen::MatrixXf& CV, const Eigen::MatrixXf& CF);
    #ifdef  CG3_DCEL_DEFINED
    EigenMesh(const Dcel& dcel);
    #endif
    #ifdef TRIMESH_DEFINED
    template<typename T>
    EigenMesh(const Trimesh<T>& trimesh);
    #endif

    const Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>& getVerticesNormalsMatrix() const;
    const Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>& getFacesNormalsMatrix() const;
    const Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor>& getVerticesColorsMatrix() const;
    const Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor>& getFacesColorsMatrix() const;

    virtual void resizeVertices(unsigned int nv);
    virtual void resizeFaces(unsigned int nf);
    void updateBoundingBox();
    virtual void clear();
    virtual unsigned int addFace(const Eigen::VectorXi &f);
    virtual unsigned int addFace(unsigned int t1, unsigned int t2, unsigned int t3);
    virtual unsigned int addVertex(const Eigen::VectorXd &p);
    virtual unsigned int addVertex(const Point3d &p);
    virtual unsigned int addVertex(double x, double y, double z);
    virtual void removeFace(unsigned int f);
    virtual bool loadFromObj(const std::string &filename);
    virtual bool loadFromPly(const std::string &filename);
    void setFaceColor(const Color &c, int f = -1);
    void setFaceColor(int red, int green, int blue, int f = -1);
    void setFaceColor(double red, double green, double blue, int f = -1);
    Vec3d faceNormal(unsigned int f) const;
    void setVertexColor(const Color& c, int v = -1);
    void setVertexColor(int red, int green, int blue, int v = -1);
    void setVertexColor(double red, double green, double blue, int v = -1);
    Vec3d vertexNormal(unsigned int v) const;
    void setVertexNormal(const Vec3d& n, unsigned int v);
    Color faceColor(unsigned int f) const;
    Color vertexColor(unsigned int v) const;
    virtual void boundingBox(Eigen::RowVector3d &BBmin, Eigen::RowVector3d &BBmax) const;
    virtual BoundingBox3 boundingBox() const;
    virtual void translate(const Point3d &p);
    virtual void translate(const Eigen::Vector3d &p);
    virtual void rotate(const Eigen::Matrix3d &m, const Eigen::Vector3d& centroid = Eigen::Vector3d::Zero());
    virtual void scale(const BoundingBox3& newBoundingBox);
    virtual void scale(const BoundingBox3& oldBoundingBox, const BoundingBox3& newBoundingBox);
    virtual void scale(const Vec3d &scaleFactor);
    Eigen::MatrixXf verticesColorMatrix() const;
    Eigen::MatrixXf facesColorMatrix() const;
    void updateFaceNormals();
    void updateVerticesNormals();
    void updateFacesAndVerticesNormals();

    virtual void removeDegenerateTriangles(double epsilon = CG3_EPSILON);
	template <typename T, int ...A> void setVerticesColorMatrix(const Eigen::PlainObjectBase<T>& CV);
	template <typename U, int ...A> void setFacesColorMatrix(const Eigen::PlainObjectBase<U>& CF);

    std::pair<int, int> commonVertices(unsigned int f1, unsigned int f2) const;

	virtual bool saveOnPly(const std::string &filename, bool binary = true) const;
    virtual bool saveOnObj(const std::string &filename) const;

    static void merge(EigenMesh &result, const EigenMesh &m1, const EigenMesh &m2);
    static EigenMesh merge(const EigenMesh &m1, const EigenMesh &m2);

    #ifdef  CG3_DCEL_DEFINED
    EigenMesh& operator= (const Dcel& dcel);
    #endif

    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:

    void updateFaceColorsSize();
    void updateVertexColorsSize();
    void updateColorSizes();

    //Eigen::RowVector3d BBmin, BBmax;
    BoundingBox3 bb;
    Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> NV;
    Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> NF;
    Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> CV;
    Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> CF;
};



/**
  * EigenMesh
  */

#ifdef TRIMESH_DEFINED
template <typename T>
inline EigenMesh::EigenMesh(const Trimesh<T>& trimesh) :
    SimpleEigenMesh(trimesh)
{
    CF = Eigen::MatrixXd::Constant(F.rows(), 3, 0.5);
    NV.resize(V.rows(), 3);
    NF.resize(F.rows(), 3);
    updateFaceNormals();
    updateVerticesNormals();
    updateBoundingBox();
}
#endif

inline EigenMesh::EigenMesh(const std::string &filename)
{
    loadFromFile(filename);
}

inline const Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>& EigenMesh::getVerticesNormalsMatrix() const
{
    return NV;
}

inline const Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>& EigenMesh::getFacesNormalsMatrix() const
{
    return NF;
}

inline const Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor>& EigenMesh::getVerticesColorsMatrix() const
{
    return CV;
}

inline const Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor>& EigenMesh::getFacesColorsMatrix() const
{
    return CF;
}

inline void EigenMesh::resizeVertices(unsigned int nv)
{
    SimpleEigenMesh::resizeVertices(nv);
    NV.conservativeResize(nv, Eigen::NoChange);
}

inline void EigenMesh::resizeFaces(unsigned int nf)
{
    SimpleEigenMesh::resizeFaces(nf);
    NF.conservativeResize(nf, Eigen::NoChange);
    CF.conservativeResize(nf, Eigen::NoChange);
}

inline void EigenMesh::updateBoundingBox()
{
    if (V.rows() > 0){
        Eigen::RowVector3d min = V.colwise().minCoeff(), max = V.colwise().maxCoeff();
        bb.min().x() = min(0); bb.min().y() = min(1); bb.min().z() = min(2);
        bb.max().x() = max(0); bb.max().y() = max(1); bb.max().z() = max(2);
    }
}

inline void EigenMesh::clear()
{
    V.resize(0,Eigen::NoChange);
    F.resize(0,Eigen::NoChange);
    CF.resize(0,Eigen::NoChange);
    NV.resize(0,Eigen::NoChange);
    NF.resize(0,Eigen::NoChange);
}

inline unsigned int EigenMesh::addFace(const Eigen::VectorXi& f)
{
    SimpleEigenMesh::addFace(f);
    NF.conservativeResize(F.rows(), Eigen::NoChange);
    Vec3d n = SimpleEigenMesh::faceNormal(F.rows()-1);
    for (unsigned int i = 0; i < 3; i++)
        NF(F.rows()-1, i) = n(i);
    CF.conservativeResize(F.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        CF(F.rows()-1, i) = 0.5;
    return (unsigned int)F.rows()-1;
}

inline unsigned int EigenMesh::addFace(unsigned int t1, unsigned int t2, unsigned int t3)
{
    SimpleEigenMesh::addFace(t1, t2, t3);
    NF.conservativeResize(F.rows(), Eigen::NoChange);
    Vec3d n = SimpleEigenMesh::faceNormal(F.rows()-1);
    for (unsigned int i = 0; i < 3; i++)
        NF(F.rows()-1, i) = n(i);
    CF.conservativeResize(F.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        CF(F.rows()-1, i) = 0.5;
    return (unsigned int)F.rows()-1;
}

inline unsigned int EigenMesh::addVertex(const Eigen::VectorXd& p)
{
    SimpleEigenMesh::addVertex(p);
    NV.conservativeResize(V.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        NV(V.rows()-1, i) = 0;
    CV.conservativeResize(V.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        CV(V.rows()-1, i) = 0.5;
    return (unsigned int)V.rows()-1;
}

inline unsigned int EigenMesh::addVertex(const Point3d &p)
{
    SimpleEigenMesh::addVertex(p);
    NV.conservativeResize(V.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        NV(V.rows()-1, i) = 0;
    CV.conservativeResize(V.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        CV(V.rows()-1, i) = 0.5;
    return (unsigned int)V.rows()-1;
}

inline unsigned int EigenMesh::addVertex(double x, double y, double z)
{
    SimpleEigenMesh::addVertex(x,y,z);
    NV.conservativeResize(V.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        NV(V.rows()-1, i) = 0;
    CV.conservativeResize(V.rows(), Eigen::NoChange);
    for (unsigned int i = 0; i < 3; i++)
        CV(V.rows()-1, i) = 0.5;
    return (unsigned int)V.rows()-1;
}

inline void EigenMesh::removeFace(unsigned int f)
{
    SimpleEigenMesh::removeFace(f);
    cg3::removeRowFromEigenMatrix(NF, f);
    cg3::removeRowFromEigenMatrix(CF, f);
}

inline Vec3d EigenMesh::faceNormal(unsigned int f) const
{
    assert (f < (unsigned int)F.rows());
    return Vec3d(NF(f,0), NF(f,1), NF(f,2));
}

inline Vec3d EigenMesh::vertexNormal(unsigned int v) const
{
    assert (v < (unsigned int)V.rows());
    return Vec3d(NV(v,0), NV(v,1), NV(v,2));
}

inline Color EigenMesh::faceColor(unsigned int f) const
{
    assert (f < (unsigned int)F.rows());
    Color c;
    c.setRedF((float)CF(f,0));
    c.setGreenF((float)CF(f,1));
    c.setBlueF((float)CF(f,2));
    return c;
}

inline Color EigenMesh::vertexColor(unsigned int v) const
{
    assert (v < (unsigned int)V.rows());
    Color c;
    c.setRedF((float)CV(v,0));
    c.setGreenF((float)CV(v,1));
    c.setBlueF((float)CV(v,2));
    return c;
}

inline void EigenMesh::boundingBox(Eigen::RowVector3d& BBmin, Eigen::RowVector3d& BBmax) const
{
    BBmin(0) = bb.minX(); BBmin(1) = bb.minY(); BBmin(2) = bb.minZ();
    BBmax(0) = bb.maxX(); BBmax(1) = bb.maxY(); BBmax(2) = bb.maxZ();
}

inline void EigenMesh::updateFacesAndVerticesNormals()
{
    updateFaceNormals();
    updateVerticesNormals();
}

template <typename T, int ...A>
void EigenMesh::setVerticesColorMatrix(const Eigen::PlainObjectBase<T>& CV)
{
	this->CV = CV;
}

template <typename U, int ...A>
void EigenMesh::setFacesColorMatrix(const Eigen::PlainObjectBase<U>& CF)
{
	this->CF = CF;
}

inline void EigenMesh::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3EigenMesh", binaryFile, V, F, bb, NV, NF, CV, CF);
}

inline void EigenMesh::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3EigenMesh", binaryFile, V, F, bb, NV, NF, CV, CF);
}

} //namespace cg3

#endif // CG3_EIGENMESH_H
