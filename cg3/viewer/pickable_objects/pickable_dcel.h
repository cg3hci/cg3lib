/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@gmail.com)
 */

#ifndef CG3_PICKABLE_DCEL_H
#define CG3_PICKABLE_DCEL_H

#include "../drawable_objects/drawable_dcel.h"
#include <cg3/viewer/interfaces/pickable_object.h>

namespace cg3 {

/**
 * \~Italian
 * @class PickableDcel
 */
class PickableDcel : public DrawableDcel, public PickableObject
{
    public:
        PickableDcel();
        PickableDcel(const Dcel &d);
        void drawWithNames() const;
        void draw() const;
        void setSelectedFacesContour(std::vector<Dcel::HalfEdge*> selected_faces_contour);
        void setSelectionColor(Color color);
        void setSelectionWidth(int value);

    protected:
        void drawFace(const Face* f) const;
        std::vector<int> obtainFaceTriangles(const Face* f) const;

        std::vector<Dcel::HalfEdge*> selected_faces_contour;
        Color selection_color;
        int selection_width;
};

}

#endif // CG3_PICKABLE_DCEL_H
