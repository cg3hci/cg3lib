#include "eigenmesh_algorithms.h"
#include <cg3/utilities/utils.h>

#ifdef  CG3_LIBIGL_DEFINED
#include <igl/decimate.h>
#include <igl/facet_components.h>
#include <igl/remove_unreferenced.h>
#include <igl/remove_duplicates.h>
#include <igl/is_edge_manifold.h>
#include <igl/is_vertex_manifold.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/extract_manifold_patches.h>
#endif //IGL_DEFINED

namespace cg3 {

SimpleEigenMesh EigenMeshAlgorithms::makeBox(const BoundingBox& bb, double minimumEdge) {
    SimpleEigenMesh box;
    if (minimumEdge <= 0) {
        std::vector<Pointd> extremes;
        bb.getExtremes(extremes);
        box.resizeVertices(8);
        for (unsigned int i = 0; i < 8; i++){
            box.setVertex(i, extremes[i].x(), extremes[i].y(), extremes[i].z());
        }
        box.resizeFaces(12);
        box.setFace(0, 0,1,2);
        box.setFace(1, 0,2,3);
        box.setFace(2, 2,1,5);
        box.setFace(3, 2,5,6);
        box.setFace(4, 5,1,0);
        box.setFace(5, 5,0,4);
        box.setFace(6, 6,5,4);
        box.setFace(7, 6,4,7);
        box.setFace(8, 7,4,0);
        box.setFace(9, 7,0,3);
        box.setFace(10, 7,3,2);
        box.setFace(11, 7,2,6);
    }
    else {
        unsigned int nSubdX, nSubdY, nSubdZ;
        //minimumEdge /= std::sqrt(2.f);
        nSubdX = bb.getLengthX() / minimumEdge; nSubdX++;
        nSubdY = bb.getLengthY() / minimumEdge; nSubdY++;
        nSubdZ = bb.getLengthZ() / minimumEdge; nSubdZ++;
        double edgeLengthX = bb.getLengthX() / nSubdX;
        double edgeLengthY = bb.getLengthY() / nSubdY;
        double edgeLengthZ = bb.getLengthZ() / nSubdZ;
        //creation vertices
        std::map<Pointi, Pointd> vertices;
        double x, y, z;
        unsigned int i, j , k;

        // fix z - k = 0;
        k = 0; z = bb.getMinZ();
        x = bb.getMinX();
        for (i = 0; i <= nSubdX; i++){
            y = bb.getMinY();
            for (j = 0; j <= nSubdY; j++){
                Pointi pi(i,j,k);
                Pointd pd(x,y,z);
                vertices[pi] = pd;
                y+=edgeLengthY;
            }
            x+=edgeLengthX;
        }
        // fix z - k = nSubdZ;
        k = nSubdZ; z = bb.getMaxZ();
        x = bb.getMinX();
        for (i = 0; i <= nSubdX; i++){
            y = bb.getMinY();
            for (j = 0; j <= nSubdY; j++){
                Pointi pi(i,j,k);
                Pointd pd(x,y,z);
                vertices[pi] = pd;
                y+=edgeLengthY;
            }
            x+=edgeLengthX;
        }
        // fix y - j = 0;
        j = 0; y = bb.getMinY();
        x = bb.getMinX();
        for (i = 0; i <= nSubdX; i++){
            z = bb.getMinZ();
            for (k = 0; k <= nSubdZ; k++){
                Pointi pi(i,j,k);
                Pointd pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            x+=edgeLengthX;
        }
        // fix y - j = nSubdY;
        j = nSubdY; y = bb.getMaxY();
        x = bb.getMinX();
        for (i = 0; i <= nSubdX; i++){
            z = bb.getMinZ();
            for (k = 0; k <= nSubdZ; k++){
                Pointi pi(i,j,k);
                Pointd pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            x+=edgeLengthX;
        }
        // fix x - i = 0;
        i = 0; x = bb.getMinX();
        y = bb.getMinY();
        for (j = 0; j <= nSubdY; j++){
            z = bb.getMinZ();
            for (k = 0; k <= nSubdZ; k++){
                Pointi pi(i,j,k);
                Pointd pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            y+=edgeLengthY;
        }
        // fix x - i = nSubdX;
        i = nSubdX; x = bb.getMaxX();
        y = bb.getMinY();
        for (j = 0; j <= nSubdY; j++){
            z = bb.getMinZ();
            for (k = 0; k <= nSubdZ; k++){
                Pointi pi(i,j,k);
                Pointd pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            y+=edgeLengthY;
        }

        std::map<Pointi, int> indices;
        int index = 0;
        box.resizeVertices(vertices.size());
        for (std::pair<Pointi, Pointd> pair : vertices) {
            indices[pair.first] = index;
            box.setVertex(index, pair.second.x(), pair.second.y(), pair.second.z());
            index++;

        }

        //triangles
        // fix z - k = 0;
        k = 0;
        for (i = 0; i < nSubdX; i++){
            for (j = 0; j < nSubdY; j++){
                Pointi pi1(i,j,k);
                Pointi pi2(i+1,j,k);
                Pointi pi3(i+1,j+1,k);
                Pointi pi4(i,j+1,k);
                assert(indices.find(pi1) != indices.end());
                assert(indices.find(pi2) != indices.end());
                assert(indices.find(pi3) != indices.end());
                assert(indices.find(pi4) != indices.end());
                int i1 = indices[pi1], i2 = indices[pi2], i3 = indices[pi3], i4 = indices[pi4];
                box.addFace(i2, i1, i3);
                box.addFace(i3, i1, i4);
            }
        }
        // fix z - k = nSubdZ;
        k = nSubdZ;
        for (i = 0; i < nSubdX; i++){
            for (j = 0; j < nSubdY; j++){
                Pointi pi1(i,j,k);
                Pointi pi2(i+1,j,k);
                Pointi pi3(i+1,j+1,k);
                Pointi pi4(i,j+1,k);
                assert(indices.find(pi1) != indices.end());
                assert(indices.find(pi2) != indices.end());
                assert(indices.find(pi3) != indices.end());
                assert(indices.find(pi4) != indices.end());
                int i1 = indices[pi1], i2 = indices[pi2], i3 = indices[pi3], i4 = indices[pi4];
                box.addFace(i1, i2, i3);
                box.addFace(i1, i3, i4);
            }
        }
        // fix y - j = 0;
        j = 0;
        for (i = 0; i < nSubdX; i++){
            for (k = 0; k < nSubdZ; k++){
                Pointi pi1(i,j,k);
                Pointi pi2(i+1,j,k);
                Pointi pi3(i+1,j,k+1);
                Pointi pi4(i,j,k+1);
                assert(indices.find(pi1) != indices.end());
                assert(indices.find(pi2) != indices.end());
                assert(indices.find(pi3) != indices.end());
                assert(indices.find(pi4) != indices.end());
                int i1 = indices[pi1], i2 = indices[pi2], i3 = indices[pi3], i4 = indices[pi4];
                box.addFace(i1, i2, i3);
                box.addFace(i1, i3, i4);
            }
        }
        // fix y - j = nSubdY;
        j = nSubdY;
        for (i = 0; i < nSubdX; i++){
            for (k = 0; k < nSubdZ; k++){
                Pointi pi1(i,j,k);
                Pointi pi2(i+1,j,k);
                Pointi pi3(i+1,j,k+1);
                Pointi pi4(i,j,k+1);
                assert(indices.find(pi1) != indices.end());
                assert(indices.find(pi2) != indices.end());
                assert(indices.find(pi3) != indices.end());
                assert(indices.find(pi4) != indices.end());
                int i1 = indices[pi1], i2 = indices[pi2], i3 = indices[pi3], i4 = indices[pi4];
                box.addFace(i2, i1, i3);
                box.addFace(i3, i1, i4);
            }
        }
        // fix x - i = 0;
        i = 0;
        for (j = 0; j < nSubdY; j++){
            for (k = 0; k < nSubdZ; k++){
                Pointi pi1(i,j,k);
                Pointi pi2(i,j+1,k);
                Pointi pi3(i,j+1,k+1);
                Pointi pi4(i,j,k+1);
                assert(indices.find(pi1) != indices.end());
                assert(indices.find(pi2) != indices.end());
                assert(indices.find(pi3) != indices.end());
                assert(indices.find(pi4) != indices.end());
                int i1 = indices[pi1], i2 = indices[pi2], i3 = indices[pi3], i4 = indices[pi4];
                box.addFace(i2, i1, i3);
                box.addFace(i3, i1, i4);
            }
        }
        // fix x - i = nSubdX;
        i = nSubdX;
        for (j = 0; j < nSubdY; j++){
            for (k = 0; k < nSubdZ; k++){
                Pointi pi1(i,j,k);
                Pointi pi2(i,j+1,k);
                Pointi pi3(i,j+1,k+1);
                Pointi pi4(i,j,k+1);
                assert(indices.find(pi1) != indices.end());
                assert(indices.find(pi2) != indices.end());
                assert(indices.find(pi3) != indices.end());
                assert(indices.find(pi4) != indices.end());
                int i1 = indices[pi1], i2 = indices[pi2], i3 = indices[pi3], i4 = indices[pi4];
                box.addFace(i1, i2, i3);
                box.addFace(i1, i3, i4);
            }
        }
    }
    return box;
}

/**
 * @brief EigenMeshAlgorithms::makeSphere
 * @link http://www.andrewnoske.com/wiki/Generating_a_sphere_as_a_3D_mesh
 * @param center
 * @param radius
 * @param nLatitude
 * @return
 */
SimpleEigenMesh EigenMeshAlgorithms::makeSphere(const Pointd &center, float radius, unsigned nLatitude) {
    SimpleEigenMesh sphere;
    float DEGS_TO_RAD = M_PI/180.0f;
    int i, j;
    float x, y, z, out;
    const unsigned int nPitch = nLatitude/2 + 1;

    float pitchInc = (180. / (float)nPitch) * DEGS_TO_RAD;
    float rotInc   = (360. / (float)nLatitude) * DEGS_TO_RAD;

    //## PRINT VERTICES:

    sphere.addVertex(center.x(), center.y()+radius, center.z());// Top vertex.
    sphere.addVertex(center.x(), center.y()-radius, center.z());// Bottom vertex.

    for(unsigned int p=1; p<nPitch; p++) {     // Generate all "intermediate vertices":
        out = radius * sin((float)p * pitchInc);
        if(out < 0) out = -out;    // abs() command won't work with all compilers
        y   = radius * cos(p * pitchInc);
        //printf("OUT = %g\n", out);    // bottom vertex
        //printf("nPitch = %d\n", nPitch);    // bottom vertex
        for(unsigned int s=0; s<nLatitude; s++) {
            x = out * cos(s * rotInc);
            z = out * sin(s * rotInc);

            sphere.addVertex(x+center.x(), y+center.y(), z+center.z());
        }
    }

    //## PRINT SQUARE FACES BETWEEN INTERMEDIATE POINTS:

    for(unsigned int p=1; p<nPitch-1; p++) {
        for(unsigned int s=0; s<nLatitude; s++) {
            i = p*nLatitude + s;
            j = (s==nLatitude-1) ? i-nLatitude : i;
            sphere.addFace((i+1-nLatitude)+1, (j+2-nLatitude)+1, (j+2)+1);
            sphere.addFace((i+1-nLatitude)+1, (j+2)+1, (i+1)+1);
        }
    }

    //## PRINT TRIANGLE FACES CONNECTING TO TOP AND BOTTOM VERTEX:

    int offLastVerts  = 2 + (nLatitude * (nLatitude/2-1));
    for(unsigned int s=0; s<nLatitude; s++)
    {
        j = (s==nLatitude-1) ? -1 : s;
        sphere.addFace(0, (j+2)+1,        (s+1)+1);
        sphere.addFace(1,   (s)+offLastVerts, (j+1)+offLastVerts);
    }

    return sphere;
}

SimpleEigenMesh EigenMeshAlgorithms::makeCylinder(const Pointd &p1, const Pointd &p2, float radius, unsigned int subd) {
    Vec3 vector = p2 - p1;
    vector.normalize();
    std::cerr << "vector cyl: " << vector << "\n";
    double angv = acos(vector.dot(Vec3(0,0,1)));
    Vec3 vcrss = vector.cross(Vec3(0,0,1));
    std::cerr << "ang: " << angv << "\n";
    std::cerr << "vcross: " << vcrss << "\n";
    Eigen::Matrix3d rot = Common::getRotationMatrix(vcrss, -angv);
    std::cerr << "rot: \n" << rot << "\n";
    SimpleEigenMesh circle;
    double dist = p1.dist(p2);
    double angle = (2* M_PI) / subd;
    for (unsigned int i = 0; i < subd; i++){
        circle.addVertex(radius * cos(angle), radius * sin(angle), 0);
        angle += (2* M_PI) / subd;
    }
    circle.addVertex(0,0,0);
    for (unsigned int i = 0; i < subd; i++){
        circle.addVertex(radius * cos(angle), radius * sin(angle), dist);
        angle += (2* M_PI) / subd;
    }
    circle.addVertex(0,0,dist);
    for (unsigned int i = 0; i < subd; i++){
        circle.addFace((i+1)%subd, i, subd);
    }
    int base = subd +1;
    for (unsigned int i = 0; i < subd; i++){
        circle.addFace(i+base, (i+1)%subd+base, subd+base);
    }

    for (unsigned int i = 0; i < subd; i++){
        circle.addFace(i, (i+1)%subd, i+base);
        circle.addFace((i+1)%subd, (i+1)%subd + base, i+base);
    }

    if (vector != Vec3(0,0,1) && vector != Vec3(0,0,-1))
        circle.rotate(rot);

    if (vector == Vec3(0,0,-1))
        circle.translate(p2);
    else
        circle.translate(p1);

    return circle;
}

bool EigenMeshAlgorithms::isABox(const SimpleEigenMesh& mesh) {
    std::array<double, 6> coords;
    std::array<bool, 6> init = {false};
    bool isABox = true;
    for (unsigned int i = 0; i < mesh.getNumberFaces() && isABox; i++){
        Vec3 n = mesh.getFaceNormal(i);
        bool found = false;
        for (unsigned int a = 0; a < Common::AXIS.size() && !found; a++){
            if (Common::epsilonEqual(n, Common::AXIS[a])){
                found = true;
                if (init[a]){
                    if (! Common::epsilonEqual(coords[a], mesh.getVertex(mesh.getFace(i).x())[a%3]))
                        isABox = false;
                }
                else {
                    init[a] = true;
                    coords[a] = mesh.getVertex(mesh.getFace(i).x())[a%3];
                }

            }
        }
        if (!found)
            isABox = false;
    }
    return isABox;
}

#ifdef  CG3_LIBIGL_DEFINED
SimpleEigenMesh EigenMeshAlgorithms::decimateMesh(const SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
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

EigenMesh EigenMeshAlgorithms::decimateMesh(const EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
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

void EigenMeshAlgorithms::decimateMesh(SimpleEigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
    /**
     * @todo Pull request
     */
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    igl::decimate(m.V, m.F, numberDesiredFaces, VV, FF, mapping);
    m.V = VV;
    m.F = FF;
}

void EigenMeshAlgorithms::decimateMesh(EigenMesh& m, int numberDesiredFaces, Eigen::VectorXi& mapping) {
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

#ifdef  CG3_CGAL_DEFINED
igl::copyleft::cgal::CSGTree EigenMeshAlgorithms::eigenMeshToCSGTree(const SimpleEigenMesh& m) {
    return igl::copyleft::cgal::CSGTree(m.V, m.F);
}

SimpleEigenMesh EigenMeshAlgorithms::CSGTreeToEigenMesh(const igl::copyleft::cgal::CSGTree& tree) {
    SimpleEigenMesh result;
    result.V = tree.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = tree.F();
    return result;
}

void EigenMeshAlgorithms::intersection(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"i"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshAlgorithms::intersection(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    SimpleEigenMesh sres;
    EigenMeshAlgorithms::intersection(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
}

SimpleEigenMesh EigenMeshAlgorithms::intersection(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    SimpleEigenMesh result;
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"i"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
    return result;
}

EigenMesh EigenMeshAlgorithms::intersection(const EigenMesh& m1, const EigenMesh& m2) {
    EigenMesh result;
    SimpleEigenMesh sres;
    EigenMeshAlgorithms::intersection(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
    return result;
}

void EigenMeshAlgorithms::intersection(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    result = {m1,{m2.V,m2.F},"i"};
}

igl::copyleft::cgal::CSGTree EigenMeshAlgorithms::intersection(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    return {m1,{m2.V,m2.F},"i"};
}

void EigenMeshAlgorithms::intersection(SimpleEigenMesh& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {m1,{m2.V,m2.F},"i"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshAlgorithms::difference(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"m"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshAlgorithms::difference(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    SimpleEigenMesh sres;
    EigenMeshAlgorithms::difference(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
}

SimpleEigenMesh EigenMeshAlgorithms::difference(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    SimpleEigenMesh result;
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"m"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
    return result;
}

EigenMesh EigenMeshAlgorithms::difference(const EigenMesh& m1, const EigenMesh& m2) {
    EigenMesh result;
    SimpleEigenMesh sres;
    EigenMeshAlgorithms::difference(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
    return result;
}

void EigenMeshAlgorithms::difference(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    result = {m1,{m2.V,m2.F},"m"};
}

igl::copyleft::cgal::CSGTree EigenMeshAlgorithms::difference(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    return {m1,{m2.V,m2.F},"m"};
}

void EigenMeshAlgorithms::union_(SimpleEigenMesh& result, const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"u"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
}

void EigenMeshAlgorithms::union_(EigenMesh& result, const EigenMesh& m1, const EigenMesh& m2) {
    SimpleEigenMesh sres;
    EigenMeshAlgorithms::union_(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
}

SimpleEigenMesh EigenMeshAlgorithms::union_(const SimpleEigenMesh& m1, const SimpleEigenMesh& m2) {
    SimpleEigenMesh result;
    igl::copyleft::cgal::CSGTree M;
    M = {{m1.V,m1.F},{m2.V,m2.F},"u"};
    result.V = M.cast_V<Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor> >();
    result.F = M.F();
    return result;
}

EigenMesh EigenMeshAlgorithms::union_(const EigenMesh& m1, const EigenMesh& m2) {
    EigenMesh result;
    SimpleEigenMesh sres;
    EigenMeshAlgorithms::union_(sres, SimpleEigenMesh(m1.V, m1.F), SimpleEigenMesh(m2.V, m2.F));
    result = EigenMesh(sres);
    return result;
}

void EigenMeshAlgorithms::union_(igl::copyleft::cgal::CSGTree& result, const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    result = {m1,{m2.V,m2.F},"u"};
}

igl::copyleft::cgal::CSGTree EigenMeshAlgorithms::union_(const igl::copyleft::cgal::CSGTree& m1, const SimpleEigenMesh& m2) {
    return {m1,{m2.V,m2.F},"u"};
}

void EigenMeshAlgorithms::removeUnreferencedVertices(SimpleEigenMesh& input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I) {
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

void EigenMeshAlgorithms::removeDuplicateVertices(SimpleEigenMesh& input, double epsilon) {
    Eigen::VectorXi I;
    removeDuplicateVertices(input, I, epsilon);
}

void EigenMeshAlgorithms::removeDuplicateVertices(SimpleEigenMesh& input, Eigen::Matrix<int, Eigen::Dynamic, 1>& I, double epsilon) {
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

void EigenMeshAlgorithms::removeDuplicateVertices(EigenMesh& input, double epsilon) {
    Eigen::VectorXi I;
    removeDuplicateVertices(input, I, epsilon);
}

void EigenMeshAlgorithms::removeDuplicateVertices(EigenMesh& input, Eigen::Matrix<int, Eigen::Dynamic, 1>& I, double epsilon) {
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

bool EigenMeshAlgorithms::isEdgeManifold(const SimpleEigenMesh& input) {
    return igl::is_edge_manifold(input.F);
}

bool EigenMeshAlgorithms::isVertexManifold(const SimpleEigenMesh& input, Eigen::Matrix<bool, Eigen::Dynamic, 1>& B) {
    return igl::is_vertex_manifold(input.V, B);
}

std::vector<SimpleEigenMesh> EigenMeshAlgorithms::getConnectedComponents(const SimpleEigenMesh& mm) {
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

Eigen::MatrixXi EigenMeshAlgorithms::getFaceAdjacences(const SimpleEigenMesh& m) {
    Eigen::MatrixXi TT;
    //igl::triangle_triangle_adjacency(F, TT);
    /**
     * @todo Pull request libigl
     */
    Eigen::MatrixXi FF = m.F;
    igl::triangle_triangle_adjacency(FF, TT);
    return TT;
}
#endif // CG3_CGAL_DEFINED

unsigned int EigenMeshAlgorithms::extractManifoldPatches(const SimpleEigenMesh& m, Eigen::Matrix<int, Eigen::Dynamic, 1>& I) {
    return igl::extract_manifold_patches(m.F, I);
}
#endif // CG3_LIBIGL_DEFINED

}
