/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_PICKABLE_OBJECT_H
#define CG3_PICKABLE_OBJECT_H

namespace cg3 {

/**
 * @ingroup cg3viewer
 * @interface PickableObject
 * @brief The PickableObject Interface models a pickable model by click for a GLCanvas.
 *
 * It contains methods that must be implemented by the classes that inherit from a PickableObject
 * to be picked by click on a GLCanvas.
 *
 */
class PickableObject
{
public:
    PickableObject() {}   /**< \~English @brief Empty constructor */
    virtual ~PickableObject() {}

    virtual void drawWithNames() const = 0; /**< \~English @brief Draws all the pickable objects of the object */
};

} //namespace cg3

#endif // CG3_PICKABLE_OBJECT_H
