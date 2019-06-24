/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DCEL_BUILDIER_H
#define CG3_DCEL_BUILDIER_H

#include <unordered_map>

#include "dcel.h"

namespace cg3 {

/**
 * @brief The DcelBuilder class
 * This class allows to create a cg3::Dcel mesh without caring of half edges, which are
 * automatically created and setted. Using this builder it is possible to create a Dcel
 * by insertion of vertices and facets only (like more simpler data structures).
 */
class DcelBuilder
{
public:
    DcelBuilder(cg3::Dcel startingDcel = cg3::Dcel());
    cg3::Dcel& dcel();
    unsigned int addVertex(
            const cg3::Point3d& p,
            const Vec3d& n = Vec3d(),
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(unsigned int vid1,
            unsigned int vid2,
            unsigned int vid3,
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(unsigned int vid1,
            unsigned int vid2,
            unsigned int vid3,
            unsigned int vid4,
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(const std::vector<uint> &vids,
                const Color &c = Color(128, 128, 128),
                int flag = 0);

    int addFace(
            const cg3::Point3d& p1,
            const cg3::Point3d& p2,
            const cg3::Point3d& p3,
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(
            const cg3::Point3d& p1,
            const cg3::Point3d& p2,
            const cg3::Point3d& p3,
            const cg3::Point3d& p4,
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(const std::vector<cg3::Point3d> &ps,
                const Color &c = Color(128, 128, 128),
                int flag = 0);

    void finalize();

    void setUpdateNormalOnInsertion(bool b = true);

protected:

    cg3::Dcel d;
    std::map<cg3::Point3d, unsigned int> mapVertices;
    std::map<std::pair<unsigned int, unsigned int>, unsigned int> mapHalfEdges;
    bool updateNormalOnInsertion;
};

} //namespace cg3

#ifndef CG3_STATIC
#define CG3_DCEL_BUILDIER_CPP "dcel_builder.cpp"
#include CG3_DCEL_BUILDIER_CPP
#undef CG3_DCEL_BUILDIER_CPP
#endif

#endif // CG3_DCEL_BUILDIER_H
