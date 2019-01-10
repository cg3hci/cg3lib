/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_VORONOI_DIAGRAM_H
#define CG3_DRAWABLE_VORONOI_DIAGRAM_H

#include <cg3/viewer/drawable_objects/drawable_objects_container.h>
#include <cg3/viewer/drawable_objects/drawable_dcel.h>
#include <cg3/data_structures/voronoi/voronoi_diagram.h>

namespace cg3 {

class DrawableVoronoiCell : public VoronoiCell, public DrawableObject {

public:
    DrawableVoronoiCell(double sphereRadius = 1);
    DrawableVoronoiCell(const VoronoiCell& v, double sphereRadius = 1);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

protected:
    bool drawSite;
    bool drawLines;
    double sphereRadius;
};

class DrawableVoronoiDiagram : virtual public VoronoiDiagram, virtual public DrawableObjectsContainer<cg3::DrawableVoronoiCell>
{
public:
    DrawableVoronoiDiagram(const BoundingBox& bb, uint nPoints = 100);
    template<class Container>
    DrawableVoronoiDiagram(const Container& c);
    template<class Iterator>
    DrawableVoronoiDiagram(Iterator begin, Iterator end);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    using VoronoiDiagram::begin;
    using VoronoiDiagram::end;
    using VoronoiDiagram::clear;

protected:
    virtual void finalize();


};

template<class Container>
DrawableVoronoiDiagram::DrawableVoronoiDiagram(const Container &c) :
    VoronoiDiagram (c)
{
    finalize();
}

template<class Iterator>
DrawableVoronoiDiagram::DrawableVoronoiDiagram(Iterator begin, Iterator end) :
    VoronoiDiagram (begin, end)
{
    finalize();
}

} //namespace cg3

#endif // CG3_DRAWABLE_VORONOI_DIAGRAM_H
