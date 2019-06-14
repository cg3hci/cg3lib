/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_DRAWABLE_VORONOI_DIAGRAM3_H
#define CG3_DRAWABLE_VORONOI_DIAGRAM3_H

#include <cg3/viewer/drawable_objects/drawable_objects_container.h>
#include <cg3/viewer/drawable_objects/drawable_dcel.h>
#include <cg3/data_structures/voronoi/voronoi_diagram3.h>

namespace cg3 {

class DrawableVoronoiCell3 : public VoronoiCell3, public DrawableObject {

public:
	DrawableVoronoiCell3(double sphereRadius = 1);
	DrawableVoronoiCell3(const VoronoiCell3& v, double sphereRadius = 1);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

protected:
    bool drawSite;
    bool drawLines;
    double sphereRadius;
};

class DrawableVoronoiDiagram3 : public VoronoiDiagram3, virtual public DrawableObjectsContainer<cg3::DrawableVoronoiCell3>
{
public:
	DrawableVoronoiDiagram3(const BoundingBox3& bb, uint nPoints = 100);
    template<class Container>
	DrawableVoronoiDiagram3(const Container& c);
    template<class Iterator>
	DrawableVoronoiDiagram3(Iterator begin, Iterator end);

    // DrawableObject interface
    void draw() const;
    Point3d sceneCenter() const;
    double sceneRadius() const;

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

    using VoronoiDiagram3::begin;
    using VoronoiDiagram3::end;
    using VoronoiDiagram3::clear;

protected:
    virtual void finalize();


};

template<class Container>
DrawableVoronoiDiagram3::DrawableVoronoiDiagram3(const Container &c) :
    VoronoiDiagram3 (c)
{
    finalize();
}

template<class Iterator>
DrawableVoronoiDiagram3::DrawableVoronoiDiagram3(Iterator begin, Iterator end) :
    VoronoiDiagram3 (begin, end)
{
    finalize();
}

} //namespace cg3

#endif // CG3_DRAWABLE_VORONOI_DIAGRAM3_H
