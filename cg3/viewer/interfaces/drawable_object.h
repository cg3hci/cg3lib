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
#include <cg3/geometry/point.h>

namespace cg3 {

/**
 * \~English
 * @interface DrawableObject
 * @brief The DrawableObject Interface models a renderable model for a GLCanvas.
 *
 * It contains methods that must be implemented by the classes that inherit from a DrawableObject
 * to be rendered by a GLCanvas.
 *
 * @author Marco Livesu (marco.livesu@gmail.com)
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 *
 * \~Italian
 * @interface DrawableObject
 * @brief L'interfaccia DrawableObject modella un oggetto renderizzabile da una GLCanvas.
 *
 * Contiene dei metodi che devono essere implementati dalle classi che ereditano da DrawableObject
 * per essere renderizzate da una GLCanvas.
 *
 * @author Marco Livesu (marco.livesu@gmail.com)
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class DrawableObject
{
    public :

        DrawableObject() {}                      /**< \~Italian @brief Costruttore, vuoto
                                                      \~English @brief Empty constructor */

        virtual ~DrawableObject() {}

        virtual void  draw()          const = 0; /**< \~Italian @brief Disegna l'oggetto mediante chiamate OpenGL
                                                      \~English @brief Draws the object through OpenGL */
        virtual Pointd sceneCenter()  const = 0; /**< \~Italian @brief Restituisce la posizione del centro dell'oggetto
                                                      \~English @brief Returns the position of the center of the objetc */
        virtual double sceneRadius()  const = 0; /**< \~Italian @brief Restituisce il raggio della bounding sphere (o del bounding box) dell'oggetto
                                                      \~English @brief Returns the ray of the bounding sphere (or the bounding box)* of the object */
};

}

#endif // CG3_DRAWABLE_OBJECT_H
