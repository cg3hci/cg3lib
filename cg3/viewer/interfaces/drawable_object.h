/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#ifndef CG3_DRAWABLE_OBJECT_H
#define CG3_DRAWABLE_OBJECT_H

#include <float.h>
#include <cg3/geometry/point3.h>

#ifdef CG3_VIEWER_DEFINED
namespace cg3 {
namespace viewer {
class GLCanvas;
}
#endif

class DrawableContainer;

/**
 * @ingroup cg3viewer
 * @interface DrawableObject
 * @brief The DrawableObject Interface models a renderable model for a GLCanvas.
 *
 * It contains methods that must be implemented in order to be rendered by the GLCanvas.
 *
 * \code{*.cpp}
 * class MyDrawableObject : public cg3::DrawableObject {
 *    //all the stuff of MyDrawableObject
 * }
 *
 * //usage
 * MyDrawableObject mdo; //some initialization here...
 * cg3::viewer::MainWindow mw;
 * mw.pushObj(&mdo, "My Drawable Object");
 * \endcode
 *
 * Be careful: a DrawableObject must live as long as its pointer is stored in the MainWindow.
 * Remember to call cg3::viewer::MainWindow::deleteObj() before the object goes out of scope or it is deleted.
 *
 */
class DrawableObject
{
public :
    #ifdef CG3_VIEWER_DEFINED
    friend class cg3::viewer::GLCanvas;
    #endif
    friend class cg3::DrawableContainer;

    DrawableObject() : visibility(true) {}                      /**< @brief Empty constructor */

    virtual ~DrawableObject() {}

    virtual void  draw() const = 0; /**< @brief This member function must draw the object through OpenGL calls.
                                                It will be called at every frame by the canvas. */

    virtual Point3d sceneCenter() const = 0; /**< @brief This member function is used to find a good camera position to visualize the rendered object.
                                                        It must return the position of the center of the object. */

    virtual double sceneRadius() const = 0; /**< @brief This member function is used to find a good camera position to visualize the rendered object.
                                                         It should return the ray of the bounding sphere of the object, but also half diagonal of the
                                                         bounding box of the object is a good approximation. Return -1 if the object shouldn't influence
                                                         the position of the camera. */
    inline virtual bool isVisible() const {
        return visibility;
    }

private:
    inline virtual void setVisibility(bool vis) const {
        visibility = vis;
    }

    mutable bool visibility;
};

} //namespace cg3

#endif // CG3_DRAWABLE_OBJECT_H
