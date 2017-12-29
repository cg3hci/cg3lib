/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */
#include "cgal_voronoi2d.h"

namespace cg3 {

namespace cgal {

namespace voronoi2d {

void printEndpoint(Halfedge_handle e, bool is_src) {
    std::cout << "\t";
    if ( is_src ) {
        if ( e->has_source() )  std::cout << e->source()->point() << std::endl;
        else  std::cout << "point at infinity" << std::endl;
    } else {
        if ( e->has_target() )  std::cout << e->target()->point() << std::endl;
        else  std::cout << "point at infinity" << std::endl;
    }
}

std::vector<std::vector<cg3::Point2Dd> > computeVoronoiDiagram(const std::vector<cg3::Point2Dd>& sites) {

    std::vector<std::vector<cg3::Point2Dd> > voronoi;

    VD vd;
    for (const Point2Dd& p : sites) {
        Site_2 t(p.x(), p.y());
        vd.insert(t);
    }
    assert( vd.is_valid() );

    for (VD::Face_iterator fit = vd.faces_begin(); fit != vd.faces_end(); ++fit){
        VD::Face f = *fit;

        if (!f.is_unbounded()) {
            std::vector<cg3::Point2Dd> face;
            VD::Face::Ccb_halfedge_circulator start = f.ccb();
            VD::Face::Ccb_halfedge_circulator curr = start;
            do {
                VD::Halfedge he = *curr;
                if (he.has_source()){
                    Point2Dd p;
                    p.x() = (*he.source()).point().x();
                    p.y() = (*he.source()).point().y();
                    face.push_back(p);
                }
            } while (++curr != start);
            voronoi.push_back(face);
        }
    }
    return voronoi;
}

}

}

}
