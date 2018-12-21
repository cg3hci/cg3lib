/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_voronoi_diagram.h"

namespace cg3 {

//DrawableVoronoiCell
DrawableVoronoiCell::DrawableVoronoiCell(double sphereRadius) :
    VoronoiCell (), drawSite(true), drawLines(true), sphereRadius(sphereRadius)
{
}

DrawableVoronoiCell::DrawableVoronoiCell(const VoronoiCell &v, double sphereRadius) :
    VoronoiCell(v), sphereRadius(sphereRadius)
{
}

void DrawableVoronoiCell::draw() const
{
    if (drawSite)
        cg3::opengl::drawSphere(_site, sphereRadius, cg3::RED);
    if (drawLines){
        for (const std::vector<uint>& f : faces){
            for (uint i = 0; i < f.size(); ++i){
                cg3::opengl::drawLine(_coords[f[i]], _coords[f[(i+1)%f.size()]], cg3::BLACK);
            }
        }
    }
}

Pointd DrawableVoronoiCell::sceneCenter() const
{
    return bb.center();
}

double DrawableVoronoiCell::sceneRadius() const
{
    return bb.diag() / 2;
}

//DrawableVoronoiDiagram
DrawableVoronoiDiagram::DrawableVoronoiDiagram(const BoundingBox &bb, uint nPoints) :
    VoronoiDiagram (bb, nPoints)
{
    finalize();
}

void DrawableVoronoiDiagram::draw() const
{
    DrawableObjectsContainer<DrawableVoronoiCell>::draw();
}

Pointd DrawableVoronoiDiagram::sceneCenter() const
{
    return bb.center();
}

double DrawableVoronoiDiagram::sceneRadius() const
{
    return bb.diag() / 2;
}

void DrawableVoronoiDiagram::finalize()
{
    VoronoiDiagram::finalize();
    double sphereRadius = bb.diag() / 100;
    for (const VoronoiCell& cell : *this){
        pushBack(DrawableVoronoiCell(cell, sphereRadius), "Cell " + std::to_string(cell.id()));
    }
}

}
