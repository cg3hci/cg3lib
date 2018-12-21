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
            const cg3::Pointd& p,
            const Vec3& n = Vec3(),
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(unsigned int vid1,
            unsigned int vid2,
            unsigned int vid3,
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(const std::vector<uint> &vids,
                const Color &c = Color(128, 128, 128),
                int flag = 0);

    int addFace(
            const cg3::Pointd& p1,
            const cg3::Pointd& p2,
            const cg3::Pointd& p3,
            const Color &c = Color(128, 128, 128),
            int flag = 0);

    int addFace(const std::vector<cg3::Pointd> &ps,
                const Color &c = Color(128, 128, 128),
                int flag = 0);

    void finalize();

protected:

    cg3::Dcel d;
    std::map<cg3::Pointd, unsigned int> mapVertices;
    std::map<std::pair<unsigned int, unsigned int>, unsigned int> mapHalfEdges;
};

} //namespace cg3

#endif // CG3_DCEL_BUILDIER_H
