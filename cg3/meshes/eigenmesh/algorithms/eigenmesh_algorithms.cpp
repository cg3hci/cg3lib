/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "eigenmesh_algorithms.h"
#include <cg3/utilities/utils.h>
#include <cg3/geometry/transformations3.h>

namespace cg3 {

SimpleEigenMesh EigenMeshAlgorithms::makeBox(const BoundingBox3& bb, double minimumEdge)
{
    SimpleEigenMesh box;
    if (minimumEdge <= 0) {
        std::vector<Point3d> extremes;
        bb.extremes(extremes);
        box.resizeVertices(8);
        for (unsigned int i = 0; i < 8; i++){
			box.setVertex(i, bb[i]);
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
        nSubdX = bb.lengthX() / minimumEdge; nSubdX++;
        nSubdY = bb.lengthY() / minimumEdge; nSubdY++;
        nSubdZ = bb.lengthZ() / minimumEdge; nSubdZ++;
        double edgeLengthX = bb.lengthX() / nSubdX;
        double edgeLengthY = bb.lengthY() / nSubdY;
        double edgeLengthZ = bb.lengthZ() / nSubdZ;
        //creation vertices
        std::map<Point3i, Point3d> vertices;
        double x, y, z;
        unsigned int i, j , k;

        // fix z - k = 0;
        k = 0; z = bb.minZ();
        x = bb.minX();
        for (i = 0; i <= nSubdX; i++){
            y = bb.minY();
            for (j = 0; j <= nSubdY; j++){
                Point3i pi(i,j,k);
                Point3d pd(x,y,z);
                vertices[pi] = pd;
                y+=edgeLengthY;
            }
            x+=edgeLengthX;
        }
        // fix z - k = nSubdZ;
        k = nSubdZ; z = bb.maxZ();
        x = bb.minX();
        for (i = 0; i <= nSubdX; i++){
            y = bb.minY();
            for (j = 0; j <= nSubdY; j++){
                Point3i pi(i,j,k);
                Point3d pd(x,y,z);
                vertices[pi] = pd;
                y+=edgeLengthY;
            }
            x+=edgeLengthX;
        }
        // fix y - j = 0;
        j = 0; y = bb.minY();
        x = bb.minX();
        for (i = 0; i <= nSubdX; i++){
            z = bb.minZ();
            for (k = 0; k <= nSubdZ; k++){
                Point3i pi(i,j,k);
                Point3d pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            x+=edgeLengthX;
        }
        // fix y - j = nSubdY;
        j = nSubdY; y = bb.maxY();
        x = bb.minX();
        for (i = 0; i <= nSubdX; i++){
            z = bb.minZ();
            for (k = 0; k <= nSubdZ; k++){
                Point3i pi(i,j,k);
                Point3d pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            x+=edgeLengthX;
        }
        // fix x - i = 0;
        i = 0; x = bb.minX();
        y = bb.minY();
        for (j = 0; j <= nSubdY; j++){
            z = bb.minZ();
            for (k = 0; k <= nSubdZ; k++){
                Point3i pi(i,j,k);
                Point3d pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            y+=edgeLengthY;
        }
        // fix x - i = nSubdX;
        i = nSubdX; x = bb.maxX();
        y = bb.minY();
        for (j = 0; j <= nSubdY; j++){
            z = bb.minZ();
            for (k = 0; k <= nSubdZ; k++){
                Point3i pi(i,j,k);
                Point3d pd(x,y,z);
                vertices[pi] = pd;
                z+=edgeLengthZ;
            }
            y+=edgeLengthY;
        }

        std::map<Point3i, int> indices;
        int index = 0;
        box.resizeVertices((unsigned int)vertices.size());
        for (std::pair<Point3i, Point3d> pair : vertices) {
            indices[pair.first] = index;
            box.setVertex(index, pair.second.x(), pair.second.y(), pair.second.z());
            index++;

        }

        //triangles
        // fix z - k = 0;
        k = 0;
        for (i = 0; i < nSubdX; i++){
            for (j = 0; j < nSubdY; j++){
                Point3i pi1(i,j,k);
                Point3i pi2(i+1,j,k);
                Point3i pi3(i+1,j+1,k);
                Point3i pi4(i,j+1,k);
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
                Point3i pi1(i,j,k);
                Point3i pi2(i+1,j,k);
                Point3i pi3(i+1,j+1,k);
                Point3i pi4(i,j+1,k);
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
                Point3i pi1(i,j,k);
                Point3i pi2(i+1,j,k);
                Point3i pi3(i+1,j,k+1);
                Point3i pi4(i,j,k+1);
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
                Point3i pi1(i,j,k);
                Point3i pi2(i+1,j,k);
                Point3i pi3(i+1,j,k+1);
                Point3i pi4(i,j,k+1);
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
                Point3i pi1(i,j,k);
                Point3i pi2(i,j+1,k);
                Point3i pi3(i,j+1,k+1);
                Point3i pi4(i,j,k+1);
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
                Point3i pi1(i,j,k);
                Point3i pi2(i,j+1,k);
                Point3i pi3(i,j+1,k+1);
                Point3i pi4(i,j,k+1);
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
SimpleEigenMesh EigenMeshAlgorithms::makeSphere(
        const Point3d &center,
        float radius,
        unsigned nLatitude)
{
    SimpleEigenMesh sphere;
    const double DEGS_TO_RAD = M_PI/180.0f;
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

SimpleEigenMesh EigenMeshAlgorithms::makeCylinder(
        const Point3d &p1,
        const Point3d &p2,
        float radius,
        unsigned int subd)
{
    Vec3d vector = p2 - p1;
    vector.normalize();
    std::cerr << "vector cyl: " << vector << "\n";
    double angv = acos(vector.dot(Vec3d(0,0,1)));
    Vec3d vcrss = vector.cross(Vec3d(0,0,1));
    std::cerr << "ang: " << angv << "\n";
    std::cerr << "vcross: " << vcrss << "\n";
    Eigen::Matrix3d rot = rotationMatrix(vcrss, -angv);
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

    if (vector != Vec3d(0,0,1) && vector != Vec3d(0,0,-1))
        circle.rotate(rot);

    if (vector == Vec3d(0,0,-1))
        circle.translate(p2);
    else
        circle.translate(p1);

    return circle;
}

bool EigenMeshAlgorithms::isABox(const SimpleEigenMesh& mesh)
{
    std::array<double, 6> coords;
    std::array<bool, 6> init = {false};
    bool isABox = true;
    for (unsigned int i = 0; i < mesh.numberFaces() && isABox; i++){
        Vec3d n = mesh.faceNormal(i);
        bool found = false;
        for (unsigned int a = 0; a < cg3::AXIS.size() && !found; a++){
            if (epsilonEqual(n, cg3::AXIS[a])){
                found = true;
                if (init[a]){
                    if (! epsilonEqual(coords[a], mesh.vertex(mesh.face(i).x())[a%3]))
                        isABox = false;
                }
                else {
                    init[a] = true;
                    coords[a] = mesh.vertex(mesh.face(i).x())[a%3];
                }

            }
        }
        if (!found)
            isABox = false;
    }
    return isABox;
}

} //namespace cg3
