/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "simpleeigenmesh.h"

#include <cg3/io/load_save_file.h>

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef TRIMESH_DEFINED
#include "trimesh/trimesh.h"
#endif

namespace cg3 {

#ifdef  CG3_DCEL_DEFINED
SimpleEigenMesh::SimpleEigenMesh(const Dcel& dcel)
{
    clear();
    V.resize(dcel.numberVertices(), 3);
    F.resize(dcel.numberFaces(), 3);
    std::map<int, int> vids;
    unsigned int i = 0;
    for (Dcel::ConstVertexIterator vit = dcel.vertexBegin(); vit != dcel.vertexEnd(); ++vit){
        const Dcel::Vertex* v = *vit;
        vids[v->id()] = i;
        Pointd p = v->coordinate();
        V(i,0) = p.x(); V(i,1) = p.y(); V(i,2) = p.z();
        i++;
    }
    i = 0;
    for (Dcel::ConstFaceIterator fit = dcel.faceBegin(); fit != dcel.faceEnd(); ++fit){
        const Dcel::Face* f = *fit;
        F(i, 0) = vids[f->vertex1()->id()]; F(i, 1) = vids[f->vertex2()->id()]; F(i, 2) = vids[f->vertex3()->id()];
        i++;
    }
}
#endif // CG3_DCEL_DEFINED

#ifdef CG3_CINOLIB_DEFINED
SimpleEigenMesh::SimpleEigenMesh(const cinolib::Trimesh<>& trimesh)
{
    resizeVertices(trimesh.num_verts());
    resizeFaces(trimesh.num_polys());
    for (unsigned int i = 0; i <trimesh.num_verts(); i++){
        cinolib::vec3d v = trimesh.vert(i);
        setVertex(i, v.x(), v.y(), v.z());
    }
    for (unsigned int i = 0; i < trimesh.num_polys(); i++){
        setFace(i, trimesh.poly_vert_id(i,0), trimesh.poly_vert_id(i,1), trimesh.poly_vert_id(i,2));
    }
}
#endif

Vec3 SimpleEigenMesh::getFaceNormal(unsigned int f) const
{
    Pointi vertices = getFace(f);
    Vec3 normal = (getVertex(vertices.y()) - getVertex(vertices.x())).cross(getVertex(vertices.z()) - getVertex(vertices.x()));
    normal.normalize();
    return normal;
}

bool SimpleEigenMesh::isDegenerateTriangle(unsigned int f, double epsilon) const
{
    assert(f < F.rows());
    return getFaceArea(f) <= epsilon;
}

void SimpleEigenMesh::removeDegenerateTriangles(double epsilon)
{
    for (unsigned int i = 0; i < F.rows(); i++){
        if (isDegenerateTriangle(i, epsilon)){
            this->removeFace(i);
            i--;
        }
    }
}

bool SimpleEigenMesh::loadFromObj(const std::string& filename)
{
    return loadTriangleMeshFromObj(filename, V, F);
}

bool SimpleEigenMesh::loadFromPly(const std::string& filename)
{
    return loadTriangleMeshFromPly(filename, V, F);
}

bool SimpleEigenMesh::loadFromFile(const std::string& filename)
{
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    if(ext == "obj" || ext == "OBJ") { //obj file
        return loadFromObj(filename);
    }
    else if(ext == "ply" || ext == "PLY") { //ply file
        return loadFromPly(filename);
    }
    else
        return false;
}

bool SimpleEigenMesh::saveOnPly(const std::string& filename) const
{
    return saveMeshOnPly(filename, V.rows(), F.rows(), V.data(), F.data());
}

bool SimpleEigenMesh::saveOnObj(const std::string& filename) const
{
    return saveMeshOnObj(filename, V.rows(), F.rows(), V.data(), F.data());
}

void SimpleEigenMesh::translate(const Pointd& p)
{
    Eigen::RowVector3d v;
    v << p.x(), p.y(), p.z();
    V.rowwise() += v;
}

void SimpleEigenMesh::translate(const Eigen::Vector3d& p)
{
    V.rowwise() += p.transpose();
}

void SimpleEigenMesh::rotate(const Eigen::Matrix3d& m, const Eigen::Vector3d& centroid)
{
    V.rowwise() -= centroid.transpose();
    for (unsigned int i = 0; i < V.rows(); i++){
        V.row(i) =  m * V.row(i).transpose();
    }
    V.rowwise() += centroid.transpose();
}

void SimpleEigenMesh::scale(const BoundingBox& newBoundingBox)
{
    BoundingBox boundingBox = getBoundingBox();
    Pointd oldCenter = boundingBox.center();
    Pointd newCenter = newBoundingBox.center();
    Pointd deltaOld = boundingBox.max() - boundingBox.min();
    Pointd deltaNew = newBoundingBox.max() - newBoundingBox.min();
    for (int i = 0; i < V.rows(); i++){
        Pointd coord = getVertex(i);
        coord -= oldCenter;
        coord *= deltaNew / deltaOld;
        coord += newCenter;
        setVertex(i, coord);
    }
}

void SimpleEigenMesh::scale(const BoundingBox& oldBoundingBox, const BoundingBox& newBoundingBox)
{
    Pointd oldCenter = oldBoundingBox.center();
    Pointd newCenter = newBoundingBox.center();
    Pointd deltaOld = oldBoundingBox.max() - oldBoundingBox.min();
    Pointd deltaNew = newBoundingBox.max() - newBoundingBox.min();
    for (int i = 0; i < V.rows(); i++){
        Pointd coord = getVertex(i);
        coord -= oldCenter;
        coord *= deltaNew / deltaOld;
        coord += newCenter;
        setVertex(i, coord);
    }
}

void SimpleEigenMesh::scale(const Vec3& scaleFactor)
{
    if (scaleFactor.x() > 0 && scaleFactor.y() > 0 && scaleFactor.z() > 0){
        for (unsigned int i = 0; i < V.rows(); i++){
            V.row(i) = Eigen::Vector3d(V(i,0) * scaleFactor.x(),
                                       V(i,1) * scaleFactor.y(),
                                       V(i,2) * scaleFactor.z());
        }
    }
}

void SimpleEigenMesh::scale(double scaleFactor)
{
    scale(cg3::Vec3(scaleFactor, scaleFactor, scaleFactor));
}

void SimpleEigenMesh::merge(SimpleEigenMesh &result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2)
{
    result.V.resize(m1.V.rows()+m2.V.rows(), 3);
    result.V << m1.V,
            m2.V;
    result.F = m1.F;
    int start = m1.getNumberVertices();
    for (unsigned int i = 0; i < m2.getNumberFaces(); i++){
        Pointi fi =m2.getFace(i);
        result.addFace(fi.x()+start, fi.y()+start, fi.z()+start);
    }
}

SimpleEigenMesh SimpleEigenMesh::merge(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2)
{
    SimpleEigenMesh result;
    result.V.resize(m1.V.rows()+m2.V.rows(), 3);
    result.V << m1.V,
            m2.V;
    result.F = m1.F;
    int start = m1.getNumberVertices();
    for (unsigned int i = 0; i < m2.getNumberFaces(); i++){
        Pointi fi =m2.getFace(i);
        result.addFace(fi.x()+start, fi.y()+start, fi.z()+start);
    }
    return result;
}

} //namespace cg3
