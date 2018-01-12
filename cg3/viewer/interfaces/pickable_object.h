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
 * \~English
 * @interface PickableObject
 * @brief The PickableObject Interface models a pickable model by click for a GLCanvas.
 *
 * It contains methods that must be implemented by the classes that inherit from a PickableObject
 * to be picked by click on a GLCanvas.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 *
 * \~Italian
 * @interface PickableObject
 * @brief L'interfaccia PickableObject modella un oggetto "catturabile" mediante click da una GLCanvas.
 *
 * Contiene dei metodi che devono essere implementati dalle classi che ereditano da PickableObject
 * per essere catturate da un click in una GLCanvas.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class PickableObject
{
    public:
        PickableObject() {}   /**< \~English @brief Empty constructor
                                   \~Italian @brief Costruttore, vuoto */
        virtual ~PickableObject() {}

        virtual void drawWithNames() const = 0; /**< \~English @brief Disegna tutti gli oggetti cliccabili dell'oggetto
                                                     \~Italian @brief Draws all the pickable objects of the object */
};

}

#endif // CG3_PICKABLE_OBJECT_H
