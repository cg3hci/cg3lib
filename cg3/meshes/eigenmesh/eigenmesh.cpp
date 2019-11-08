/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh.h"
#include <cg3/io/load_save_file.h>

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef TRIMESH_DEFINED
#include "trimesh/trimesh.h"
#endif

namespace cg3 {

EigenMesh::EigenMesh() {
}

EigenMesh::EigenMesh(const char* filename) :
	SimpleEigenMesh(filename)
{
	updateColorSizes();
	updateFaceNormals();
	updateVerticesNormals();
	updateBoundingBox();
}

EigenMesh::EigenMesh(const SimpleEigenMesh& m) :
    SimpleEigenMesh(m)
{
    updateColorSizes();
    updateFaceNormals();
    updateVerticesNormals();
    updateBoundingBox();
}

EigenMesh::EigenMesh(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F) :
    SimpleEigenMesh(V,F)
{
    updateColorSizes();
    updateFaceNormals();
    updateVerticesNormals();
    updateBoundingBox();
}

EigenMesh::EigenMesh(
        const Eigen::MatrixXd& V,
        const Eigen::MatrixXi& F,
        const Eigen::MatrixXf& CV,
        const Eigen::MatrixXf& CF) :
    SimpleEigenMesh(V,F), CV(CV), CF(CF)
{
    updateFaceNormals();
    updateVerticesNormals();
    updateBoundingBox();
}

#ifdef  CG3_DCEL_DEFINED
EigenMesh::EigenMesh(const Dcel& dcel)
{
    clear();
    V.resize(dcel.numberVertices(), 3);
    F.resize(dcel.numberFaces(), 3);
    CF.resize(F.rows(), 3);
    updateVertexColorsSize();
    NV.resize(V.rows(), 3);
    NF.resize(F.rows(), 3);
    std::map<int, int> vids;
    bb = dcel.boundingBox();
    unsigned int i = 0;
    for (Dcel::ConstVertexIterator vit = dcel.vertexBegin(); vit != dcel.vertexEnd(); ++vit){
        const Dcel::Vertex* v = *vit;
        vids[v->id()] = i;
        Point3d p = v->coordinate();
        Vec3d n = v->normal();
        n.normalize();
        V(i,0) = p.x(); V(i,1) = p.y(); V(i,2) = p.z();
        NV(i,0) = n.x(); NV(i,1) = n.y(); NV(i,2) = n.z();
        i++;
    }
    i = 0;
    for (Dcel::ConstFaceIterator fit = dcel.faceBegin(); fit != dcel.faceEnd(); ++fit){
        const Dcel::Face* f = *fit;
        F(i, 0) = vids[f->vertex1()->id()]; F(i, 1) = vids[f->vertex2()->id()]; F(i, 2) = vids[f->vertex3()->id()];
        Color c = f->color();
        Vec3d n = f->normal();
        CF(i,0) = c.redF(); CF(i,1) = c.greenF(); CF(i,2) = c.blueF();
        NF(i,0) = n.x(); NF(i,1) = n.y(); NF(i,2) = n.z();
        i++;
    }
}
#endif

bool EigenMesh::loadFromObj(const std::string& filename)
{
    clear();
	io::FileMeshMode mode;
    bool b = loadTriangleMeshFromObj(filename, V, F, mode, NV, CV, CF);
    updateBoundingBox();

    if (b){
        updateFaceNormals();
		if (!(mode.hasVertexNormals())){
            updateVerticesNormals();
        }
        else
            NV.rowwise().normalize();
		if (!(mode.hasVertexColors())){
            updateVertexColorsSize();
        }
		if (!(mode.hasFaceColors())){
            updateFaceColorsSize();
        }
    }
    return b;
}

bool EigenMesh::loadFromPly(const std::string& filename)
{
    clear();
	io::FileMeshMode mode;
    bool b = loadTriangleMeshFromPly(filename, V, F, mode, NV, CV, CF);
    updateBoundingBox();

    if (b){
        updateFaceNormals();
		if (!(mode.hasVertexNormals())){
            updateVerticesNormals();
        }
        else
            NV.rowwise().normalize();
		if (!(mode.hasVertexColors())){
            updateVertexColorsSize();
        }
		if (!(mode.hasFaceColors())){
            updateFaceColorsSize();
        }
    }
    return b;
}

void EigenMesh::setFaceColor(const Color& c, int f)
{
    setFaceColor(c.redF(), c.greenF(), c.blueF(), f);
}

void EigenMesh::setFaceColor(int red, int green, int blue, int f)
{
    setFaceColor(red/255.0, green/255.0, blue/255.0, f);
}

void EigenMesh::setFaceColor(double red, double green, double blue, int f)
{
    if (f < 0){
        if (CF.rows() != F.rows())
            CF.resize(F.rows(), 3);
        for (unsigned int i = 0; i < (unsigned int)CF.rows(); i++)
            CF.row(i) << red, green, blue;
    }
    else{
        assert(f < F.rows());
        CF.row(f) << red, green, blue;
    }
}

void EigenMesh::setVertexColor(const Color &c, int v)
{
    setVertexColor(c.redF(), c.greenF(), c.blueF(), v);
}

void EigenMesh::setVertexColor(int red, int green, int blue, int v)
{
    setVertexColor(red/255.0, green/255.0, blue/255.0, v);
}

void EigenMesh::setVertexColor(double red, double green, double blue, int v)
{
    if (v < 0){
        if (CV.rows() != V.rows())
            CV.resize(V.rows(), 3);
        for (unsigned int i = 0; i < (unsigned int)CV.rows(); i++)
            CV.row(i) << red, green, blue;
    }
    else{
        assert(v < V.rows());
        CV.row(v) << red, green, blue;
    }
}

void EigenMesh::setVertexNormal(const Vec3d &n, unsigned int v)
{
    assert(v < (unsigned int)V.rows());
    NV.row(v) << n.x(), n.y(), n.z();
}

BoundingBox3 EigenMesh::boundingBox() const
{
    return bb;
}

void EigenMesh::translate(const Point3d &p)
{
    SimpleEigenMesh::translate(p);
    updateBoundingBox();
}

void EigenMesh::translate(const Eigen::Vector3d &p)
{
    SimpleEigenMesh::translate(p);
    updateBoundingBox();
}

void EigenMesh::rotate(const Eigen::Matrix3d &m, const Eigen::Vector3d &centroid)
{
    SimpleEigenMesh::rotate(m, centroid);
    updateBoundingBox();
    for (unsigned int i = 0; i < (unsigned int)NF.rows(); i++){
        NF.row(i) =  m * NF.row(i).transpose();
    }
    for (unsigned int i = 0; i < (unsigned int)NV.rows(); i++){
        NV.row(i) =  m * NV.row(i).transpose();
    }
}

void EigenMesh::scale(const BoundingBox3& newBoundingBox)
{
    SimpleEigenMesh::scale(newBoundingBox);
    bb = newBoundingBox;
}

void EigenMesh::scale(const BoundingBox3& oldBoundingBox, const BoundingBox3& newBoundingBox)
{
    SimpleEigenMesh::scale(oldBoundingBox, newBoundingBox);
    bb = newBoundingBox;
}

void EigenMesh::scale(const Vec3d& scaleFactor)
{
    SimpleEigenMesh::scale(scaleFactor);
    updateBoundingBox();
}

Eigen::MatrixXf EigenMesh::verticesColorMatrix() const
{
    return CV;
}

Eigen::MatrixXf EigenMesh::facesColorMatrix() const
{
    return CF;
}

void EigenMesh::updateFaceNormals()
{
    Eigen::Matrix<double,3,1> Z(0,0,0);
    NF.resize(F.rows(),3);
    int nf = F.rows();
    //#pragma omp parallel for
    for(int i = 0; i < nf; i++) {
        const Eigen::Matrix<double, 1, 3, Eigen::RowMajor> v1 = V.row(F(i,1)) - V.row(F(i,0));
        const Eigen::Matrix<double, 1, 3, Eigen::RowMajor> v2 = V.row(F(i,2)) - V.row(F(i,0));
        Point3d p1(v1(0,0),v1(0,1),v1(0,2));
        Point3d p = p1.cross(Point3d(v2(0,0),v2(0,1),v2(0,2)));
        //NF.row(i) = v1.cross(v2);//.normalized(); //eigen probelm
        NF(i,0) = p.x(); NF(i,1) = p.y(); NF(i,2) = p.z();
        double r = NF.row(i).norm();
        if(r == 0) {
            NF.row(i) = Z;
        }
        else {
            NF.row(i) /= r;
        }
    }
}

void EigenMesh::updateVerticesNormals()
{
    NV = Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>::Zero(V.rows(), 3);
    // loop over faces
    for(int i = 0;i<F.rows();i++) {
        // throw normal at each corner
        for(int j = 0; j < 3;j++) {
            NV.row(F(i,j)) += NF.row(i);
        }
    }
    NV.rowwise().normalize();
}

void EigenMesh::removeDegenerateTriangles(double epsilon) {
    for (unsigned int i = 0; i < (unsigned int)F.rows(); i++){
        if (isDegenerateTriangle(i, epsilon)){
            this->removeFace(i);
            i--;
        }
    }
}

std::pair<int, int> EigenMesh::commonVertices(unsigned int f1, unsigned int f2) const
{
    for (unsigned int i = 0; i < 3; i++){
        for (unsigned int j = 0; j < 3; j++){
            if (F(f1, i) == F(f2,(j+1)%3) && F(f1,(i+1)%3) == F(f2, j))
                return std::pair<int, int>(F(f1, i), F(f1,(i+1)%3));
        }
    }
    return std::pair<int, int>(-1, -1);
}

bool EigenMesh::saveOnPly(const std::string &filename, bool binary) const
{
	io::FileMeshMode mode;
	mode.setVertexNormals();
	mode.setVertexColors();
	mode.setFaceColors();
    if (F.cols() == 3)
		mode.setTriangleMesh();
    else if (F.cols() == 4)
		mode.setQuadMesh();
    else
		mode.setPolygonMesh();
    io::FileColorMode colorMode = io::RGB;
	return saveMeshOnPly(filename, V.rows(), F.rows(), V.data(), F.data(),
						 binary, mode, NV.data(), NF.data(), colorMode,
						 CV.data(), CF.data());
}

bool EigenMesh::saveOnObj(const std::string& filename) const
{
	io::FileMeshMode mode;
	mode.setVertexNormals();
	mode.setVertexColors();
	mode.setFaceColors();
	if (F.cols() == 3)
		mode.setTriangleMesh();
	else if (F.cols() == 4)
		mode.setQuadMesh();
	else
		mode.setPolygonMesh();
	io::FileColorMode colorMode = io::RGB;
	return saveMeshOnObj(filename, V.rows(), F.rows(), V.data(), F.data(), mode,
						 NV.data(), colorMode, CV.data(), CF.data());
}

void EigenMesh::merge(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2)
{
    SimpleEigenMesh::merge(result, m1, m2);
    result.CF.resize(m1.CF.rows()+m2.CF.rows(), 3);
    result.CF << m1.CF,
            m2.CF;
    result.CV.resize(m1.CV.rows()+m2.CV.rows(), 3);
    result.CV << m1.CV,
            m2.CV;
    result.NV.resize(m1.NV.rows()+m2.NV.rows(), 3);
    result.NV << m1.NV,
            m2.NV;
    result.NF.resize(m1.NF.rows()+m2.NF.rows(), 3);
    result.NF << m1.NF,
            m2.NF;
    result.updateBoundingBox();
}

EigenMesh EigenMesh::merge(const EigenMesh& m1, const EigenMesh& m2)
{
    EigenMesh result;
    SimpleEigenMesh::merge(result, m1, m2);
    result.CF.resize(m1.CF.rows()+m2.CF.rows(), 3);
    result.CF << m1.CF,
            m2.CF;
    result.CV.resize(m1.CV.rows()+m2.CV.rows(), 3);
    result.CV << m1.CV,
            m2.CV;
    result.NV.resize(m1.NV.rows()+m2.NV.rows(), 3);
    result.NV << m1.NV,
            m2.NV;
    result.NF.resize(m1.NF.rows()+m2.NF.rows(), 3);
    result.NF << m1.NF,
            m2.NF;
    result.updateBoundingBox();
    return result;
}

#ifdef  CG3_DCEL_DEFINED
EigenMesh& EigenMesh::operator=(const Dcel& dcel)
{
    clear();
    V.resize(dcel.numberVertices(), 3);
    F.resize(dcel.numberFaces(), 3);
    CF.resize(F.rows(), 3);
    CV = Eigen::MatrixXf::Constant(V.rows(), 3, 0.5);
    NV.resize(V.rows(), 3);
    NF.resize(F.rows(), 3);
    std::map<int, int> vids;
    bb = dcel.boundingBox();
    unsigned int i = 0;
    for (Dcel::ConstVertexIterator vit = dcel.vertexBegin(); vit != dcel.vertexEnd(); ++vit){
        const Dcel::Vertex* v = *vit;
        vids[v->id()] = i;
        Point3d p = v->coordinate();
        Vec3d n = v->normal();
        V(i,0) = p.x(); V(i,1) = p.y(); V(i,2) = p.z();
        NV(i,0) = n.x(); NV(i,1) = n.y(); NV(i,2) = n.z();
        i++;
    }
    i = 0;
    for (Dcel::ConstFaceIterator fit = dcel.faceBegin(); fit != dcel.faceEnd(); ++fit){
        const Dcel::Face* f = *fit;
        F(i, 0) = vids[f->vertex1()->id()]; F(i, 1) = vids[f->vertex2()->id()]; F(i, 2) = vids[f->vertex3()->id()];
        Color c = f->color();
        Vec3d n = f->normal();
        CF(i,0) = c.redF(); CF(i,1) = c.greenF(); CF(i,2) = c.blueF();
        NF(i,0) = n.x(); NF(i,1) = n.y(); NF(i,2) = n.z();
        i++;
    }
    return *this;
}
#endif

void EigenMesh::updateFaceColorsSize()
{
    CF.conservativeResizeLike(Eigen::MatrixXf::Constant(F.rows(), 3, 0.5));
}

void EigenMesh::updateVertexColorsSize()
{
    CV.conservativeResizeLike(Eigen::MatrixXf::Constant(V.rows(), 3, 0.5));
}

void EigenMesh::updateColorSizes()
{
    updateFaceColorsSize();
    updateVertexColorsSize();
}

} //namespace cg3
