/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_libigl_algorithms.h"

#include <igl/decimate.h>
#include <igl/facet_components.h>
#include <igl/remove_unreferenced.h>
#include <igl/remove_duplicates.h>
#include <igl/is_edge_manifold.h>
#include <igl/is_vertex_manifold.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/extract_manifold_patches.h>

namespace cg3 {

namespace libigl {

namespace internal {

SimpleEigenMesh EigenMeshLibIglAlgorithms::decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
    SimpleEigenMesh output;

    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);

    output.V = VV;
    output.F = FF;
    return output;
}

EigenMesh EigenMeshLibIglAlgorithms::decimateMesh(const EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
    EigenMesh output;

    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);

    output.V = VV;
    output.F = FF;
    output.updateFaceNormals();
    output.updateVerticesNormals();
    output.CV = Eigen::MatrixXf::Constant(output.V.rows(), 3, 0.5);
    output.CF.resize(output.F.rows(), 3);
    for (unsigned int i = 0; i < output.F.rows(); i++){
        output.CF(i,0) = m.CF(mapping(i), 0);
        output.CF(i,1) = m.CF(mapping(i), 1);
        output.CF(i,2) = m.CF(mapping(i), 2);
    }
    output.updateBoundingBox();

    return output;
}

void EigenMeshLibIglAlgorithms::decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);
    m.V = VV;
    m.F = FF;
}

void EigenMeshLibIglAlgorithms::decimateMesh(EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);
    m.V = VV;
    m.F = FF;

    m.CV = Eigen::MatrixXf::Constant(m.V.rows(), 3, 0.5);
    Eigen::MatrixXf tmp = m.CF;
    m.CF.resize(m.F.rows(), 3);
    for (int i = FF.rows()-1; i>= 0; i--){
        m.CF(i,0) = tmp(mapping(i), 0);
        m.CF(i,1) = tmp(mapping(i), 1);
        m.CF(i,2) = tmp(mapping(i), 2);
    }

    m.updateBoundingBox();
}

void EigenMeshLibIglAlgorithms::removeUnreferencedVertices(SimpleEigenMesh& input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I) {
    //Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> NV;
    //Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor> NF;
    //igl::remove_unreferenced(V,F, NV, NF, I);

    /**
      @todo Pull request
    */
    ///
    /// If IGL Static (pull request problem)
    Eigen::MatrixXd VV = input.V, NV;
    Eigen::MatrixXi FF = input.F, NF;
    igl::remove_unreferenced(VV,FF, NV, NF, I);
    ///

    input.V = NV;
    input.F = NF;
}

void EigenMeshLibIglAlgorithms::removeDuplicateVertices(SimpleEigenMesh& input, double epsilon) {
    Eigen::VectorXi I;
    removeDuplicateVertices(input, I, epsilon);
}

void EigenMeshLibIglAlgorithms::removeDuplicateVertices(SimpleEigenMesh& input, Eigen::Matrix<int, Eigen::Dynamic, 1>& I, double epsilon) {
    /**
      @todo Pull request
    */
    ///
    /// If IGL Static (pull request problem)
    Eigen::MatrixXd VV = input.V, NV;
    Eigen::MatrixXi FF = input.F, NF;
    igl::remove_duplicates( VV,FF, NV, NF, I,epsilon );
    ///

    input.V = NV;
    input.F = NF;
}

void EigenMeshLibIglAlgorithms::removeDuplicateVertices(EigenMesh& input, double epsilon) {
    Eigen::VectorXi I;
    removeDuplicateVertices(input, I, epsilon);
}

void EigenMeshLibIglAlgorithms::removeDuplicateVertices(EigenMesh& input, Eigen::Matrix<int, Eigen::Dynamic, 1>& I, double epsilon) {
    /**
      @todo Reimplement this WITHOUT LBIGL (see resizing color faces)
    */
    ///
    /// If IGL Static (pull request problem)
    Eigen::MatrixXd VV = input.V, NV;
    Eigen::MatrixXi FF = input.F, NF;
    igl::remove_duplicates( VV,FF, NV, NF, I,epsilon );
    ///

    input.V = NV;
    input.F = NF;

    Eigen::MatrixXd NNV(NV.rows(), 3);
    Eigen::MatrixXf NCV(NV.rows(), 3);
    for (unsigned int i = 0; i < VV.rows(); i++){
        NNV.row(I(i)) = input.NV.row(i);
        NCV.row(I(i)) = input.CV.row(i);
    }
    input.NV = NNV;
    input.CV = NCV;
    input.CF.conservativeResize(input.F.rows(), Eigen::NoChange);
    input.updateFaceNormals();
    //input.updateFacesAndVerticesNormals();
    //input.updateColorSizes();
}

bool EigenMeshLibIglAlgorithms::isEdgeManifold(const SimpleEigenMesh& input) {
    return igl::is_edge_manifold(input.F);
}

bool EigenMeshLibIglAlgorithms::isVertexManifold(const SimpleEigenMesh& input, Eigen::Matrix<bool, Eigen::Dynamic, 1>& B) {
    return igl::is_vertex_manifold(input.V, B);
}

std::vector<SimpleEigenMesh> EigenMeshLibIglAlgorithms::getConnectedComponents(const SimpleEigenMesh& mm) {
    std::vector<SimpleEigenMesh> connectedComponents;
    Eigen::VectorXi C;
    //igl::facet_components(F, C);

    /**
      @todo Pull request
    */
    ///If IGL Static (pull request problem)
    Eigen::MatrixXi FF = mm.F;
    igl::facet_components(FF, C);
    ///
    for (unsigned int i = 0; i < C.size(); i++){
        if (C(i) >= (int)connectedComponents.size()){
            assert(C(i) == (int)connectedComponents.size());
            SimpleEigenMesh m;
            m.V = mm.V;
            connectedComponents.push_back(m);
        }
        connectedComponents[C(i)].addFace(mm.F.row(i));
    }
    for (unsigned int i = 0; i < connectedComponents.size(); i++){
        Eigen::Matrix<int, Eigen::Dynamic, 1> I;
        removeUnreferencedVertices(connectedComponents[i], I);
    }
    return connectedComponents;
}

Eigen::MatrixXi EigenMeshLibIglAlgorithms::getFaceAdjacences(const SimpleEigenMesh& m) {
    Eigen::MatrixXi TT;
    //igl::triangle_triangle_adjacency(F, TT);
    /**
     * @todo Pull request libigl
     */
    Eigen::MatrixXi FF = m.F;
    igl::triangle_triangle_adjacency(FF, TT);
    return TT;
}

unsigned int EigenMeshLibIglAlgorithms::extractManifoldPatches(const SimpleEigenMesh& m, Eigen::Matrix<int, Eigen::Dynamic, 1>& I) {
    return igl::extract_manifold_patches(m.F, I);
}

#ifdef  CG3_CGAL_DEFINED
igl::copyleft::cgal::CSGTree EigenMeshLibIglAlgorithms::eigenMeshToCSGTree(const SimpleEigenMesh& m) {
    return igl::copyleft::cgal::CSGTree(m.V, m.F);
}

SimpleEigenMesh EigenMeshLibIglAlgorithms::CSGTreeToEigenMesh(const igl::copyleft::cgal::CSGTree& tree) {
    SimpleEigenMesh result;
    result.V = tree.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = tree.F();
    return result;
}

void EigenMeshLibIglAlgorithms::intersection(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"i"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshLibIglAlgorithms::intersection(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    SimpleEigenMesh sres;
    EigenMeshLibIglAlgorithms::intersection(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
}

SimpleEigenMesh EigenMeshLibIglAlgorithms::intersection(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    SimpleEigenMesh result;
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"i"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
    return result;
}

EigenMesh EigenMeshLibIglAlgorithms::intersection(const EigenMesh& m1, const EigenMesh& m2) {
    EigenMesh result;
    SimpleEigenMesh sres;
    EigenMeshLibIglAlgorithms::intersection(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
    return result;
}

void EigenMeshLibIglAlgorithms::intersection(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    result = {m1,{m2.V,m2.F},"i"};
}

igl::copyleft::cgal::CSGTree EigenMeshLibIglAlgorithms::intersection(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    return {m1,{m2.V,m2.F},"i"};
}

void EigenMeshLibIglAlgorithms::intersection(SimpleEigenMesh& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {m1,{m2.V,m2.F},"i"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshLibIglAlgorithms::difference(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"m"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshLibIglAlgorithms::difference(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    SimpleEigenMesh sres;
    EigenMeshLibIglAlgorithms::difference(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
}

SimpleEigenMesh EigenMeshLibIglAlgorithms::difference(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    SimpleEigenMesh result;
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"m"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
    return result;
}

EigenMesh EigenMeshLibIglAlgorithms::difference(const EigenMesh& m1, const EigenMesh& m2) {
    EigenMesh result;
    SimpleEigenMesh sres;
    EigenMeshLibIglAlgorithms::difference(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
    return result;
}

void EigenMeshLibIglAlgorithms::difference(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    result = {m1,{m2.V,m2.F},"m"};
}

igl::copyleft::cgal::CSGTree EigenMeshLibIglAlgorithms::difference(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    return {m1,{m2.V,m2.F},"m"};
}

void EigenMeshLibIglAlgorithms::union_(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"u"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshLibIglAlgorithms::union_(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    SimpleEigenMesh sres;
    EigenMeshLibIglAlgorithms::union_(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
}

SimpleEigenMesh EigenMeshLibIglAlgorithms::union_(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    SimpleEigenMesh result;
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"u"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
    return result;
}

EigenMesh EigenMeshLibIglAlgorithms::union_(const EigenMesh& m1, const EigenMesh& m2) {
    EigenMesh result;
    SimpleEigenMesh sres;
    EigenMeshLibIglAlgorithms::union_(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
    return result;
}

void EigenMeshLibIglAlgorithms::union_(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    result = {m1,{m2.V,m2.F},"u"};
}

igl::copyleft::cgal::CSGTree EigenMeshLibIglAlgorithms::union_(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    return {m1,{m2.V,m2.F},"u"};
}
#endif // CG3_CGAL_DEFINED

}

}

}
