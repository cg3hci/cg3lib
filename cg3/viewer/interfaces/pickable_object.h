/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_PICKABLE_OBJECT_H
#define CG3_PICKABLE_OBJECT_H

#include "drawable_object.h"

namespace cg3 {
namespace viewer {

class GLCanvas;

} //namespace cg3::viewer

/**
 * @ingroup cg3viewer
 * @interface PickableObject
 * @brief The PickableObject Interface models a pickable model by click for a GLCanvas.
 *
 * It contains methods that must be implemented by the classes that inherit from a PickableObject
 * to be picked by click on a GLCanvas.
 *
 * In order to make an element "pickable" from the GLCanvas, you should draw the element
 * in the following way:
 * \code{.cpp}
 * unsigned int idElement;
 * //set idElement with an univoque id for the element inside the Object.
 * glPushName(idElement); //note: this is a PickableObject member function
 *                        //that calls opengl's glPushName
 * // opengl code that draws the element
 * glPopName();
 * \endcode
 *
 * The static value PickableObject::objectBits controls how many PickableObjects and how
 * many elements per PickableObject can be supported by viewer::GlCanvas.
 * Default value is 8, which means that 8 bits are used for the objects (2^8 : max 256
 * Pickable Objects) and 32-8=24 bits are used for the elements for every object (2^24 :
 * max xxx pickable elements for every PickableObject pushed in the canvas).
 * If you need different values, be sure to change PickableObject::objectBits BEFORE
 * pushing a PickableObject to the GLCanvas.
 */
class PickableObject : public virtual DrawableObject
{
public:
    friend class viewer::GLCanvas;

    PickableObject();
    virtual ~PickableObject() {}

    virtual void drawWithNames() const = 0; /**< @brief Draws all the pickable objects of the object */

protected:
    static void setMeshBits(unsigned int nBits);
    void glPushName(unsigned int idElement) const;

private:
    static void getIdsFromIdName(unsigned int idName, unsigned int& idObject, unsigned int &idElement);

    static unsigned int objectBits; //default is 8 bit -> initialized in pickable_object.cpp

	static uint oBits(int nBits);
    mutable unsigned int id = 0; //member reserved for GLCanvas
};

} //namespace cg3

//no way to use static members declared in headers in a header only class (only c++17)
//#ifndef CG3_STATIC
//#define CG3_PICKABLE_OBJECT_CPP "pickable_object.cpp"
//#include CG3_PICKABLE_OBJECT_CPP
//#undef CG3_PICKABLE_OBJECT_CPP
//#endif //CG3_STATIC

#endif // CG3_PICKABLE_OBJECT_H
