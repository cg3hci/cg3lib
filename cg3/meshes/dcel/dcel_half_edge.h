/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef DCEL_HALF_EDGE_H
#define DCEL_HALF_EDGE_H

#include "dcel_struct.h"

namespace cg3 {

/**
 * \~Italian
 * @class Dcel::HalfEdge
 * @brief Classe rappresentante un half edge della Dcel.
 *
 * La classe Dcel::HalfEdge implementa un half edge della Dcel.\n
 * L'half-edge è un segmento \e orientato, che parte da un vertice di origine
 * identificato come \b fromVertex e arriva ad un vertice di destinazione detto \b toVertex.
 * Ogni half edge è caratterizzato dall'avere un half-edge gemello, identificato
 * come \b twin half edge, che ha orientamento opposto rispetto all'half-edge originale.
 * L'half-edge inoltre possiede i riferimenti agli half edge \b next e \b prev, che rappresentano
 * rispettivamente l'half-edge successivo e l'half-edge precedente seguendo la direzione indicata
 * dall'half edge stesso, e il riferimento alla faccia incidente \b face.
 *
 * Per una corretta gestione della Dcel, devono essere rispettate le seguenti regole:
 *
 * - Ogni half edge \c e ha un twin \c t, e il suo twin \c t ha come twin l'half edge \c e.
 * - Ogni half edge ha from vertex uguale al to vertex del suo twin, e viceversa.
 * - Partendo da un half edge \c e, una serie di operazioni di next (3 se si ha una Dcel di triangoli) riporta all'half edge \c e, tutti questi half edge hanno la stessa faccia incidente.
 * - Partendo da un half edge \c e, una serie di operazioni di prev (3 se si ha una Dcel di triangoli) riporta all'half edge \c e, tutti questi half edge hanno la stessa faccia incidente.
 * - Il to vertex di un half edge corrisponde al from vertex del suo next;
 * - Il from vertex di un half edge corrisponde al to vertex del suo prev.
 * - Partendo da un half edge \c e, una serie di operazioni di twin e next riporta all'half edge \c e.
 * - Partendo da un half edge \c e, una serie di operazioni di prev e twin riporta all'half edge \c e.
 *
 *
 * Le altre componenti che compongono l'half edge sono:
 * - id: intero senza segno univoco all'interno della lista degli half edge della Dcel,
 *   non modificabile dall'utente. Può essere usato per identificare la faccia all'interno
 *   della Dcel (in modo meno efficiente rispetto all'utilizzo di un puntatore);\n
 * - flag: intero personalizzabile dall'utente. \n
 *
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::HalfEdge
{
        friend class Dcel;

    public:

        /************************
        * Public Inline Methods *
        *************************/

        unsigned int getId()                                const;
        int getFlag()                                       const;
        const Dcel::Vertex* getFromVertex()                 const;
        const Dcel::Vertex* getToVertex()                   const;
        const Dcel::HalfEdge* getTwin()                     const;
        const Dcel::HalfEdge* getPrev()                     const;
        const Dcel::HalfEdge* getNext()                     const;
        const Dcel::Face* getFace()                         const;
        bool operator == (const HalfEdge& otherHalfEdge)    const;
        bool operator != (const HalfEdge& otherHalfEdge)    const;
        #ifdef DEBUG
        void checkFromVertex()                              const;
        void checkToVertex()                                const;
        void checkTwin()                                    const;
        void checkPrev()                                    const;
        void checkNext()                                    const;
        void checkFace()                                    const;
        #endif
        bool isConvex()                                     const;

        void setFlag();
        void setFlag(int new_flag);
        void resetFlag();
        Dcel::Vertex* getFromVertex();
        Dcel::Vertex* getToVertex();
        Dcel::HalfEdge* getTwin();
        Dcel::HalfEdge* getPrev();
        Dcel::HalfEdge* getNext();
        Dcel::Face* getFace();
        void setFromVertex(Dcel::Vertex* newFromVertex);
        void setToVertex(Dcel::Vertex* newToVertex);
        void setTwin(Dcel::HalfEdge* newTwin);
        void setPrev(Dcel::HalfEdge* newPrev);
        void setNext(Dcel::HalfEdge* newNext);
        void setFace(Dcel::Face* newFace);

        /*****************
        * Public Methods *
        ******************/

        bool isOuterComponent() const;
        float getLength()       const;
        std::string toString()  const;


    protected:

        /***************
        * Constructors *
        ****************/

        #ifdef NDEBUG
        HalfEdge(Dcel &parent);
        #else
        HalfEdge();
        #endif
        //HalfEdge(Dcel::Vertex* from, Dcel::Vertex* to);
        //HalfEdge(Dcel::Vertex* from, Dcel::Vertex* to, Dcel::HalfEdge* twin, Dcel::HalfEdge* prev, Dcel::HalfEdge* next, Dcel::Face* face);
        ~HalfEdge();

        /**************
        * Attributes *
        **************/

        #ifdef NDEBUG
        Dcel* parent;
        #endif
        Dcel::Vertex* 	fromVertex; /**< \~Italian @brief Vertice di origine dell'half edge */
        Dcel::Vertex* 	toVertex;   /**< \~Italian @brief Vertice di destinazione dell'half edge */
        Dcel::HalfEdge* twin;       /**< \~Italian @brief Half edge gemello dell'half edge */
        Dcel::HalfEdge*	prev;       /**< \~Italian @brief Half edge precendente all'half edge */
        Dcel::HalfEdge*	next;       /**< \~Italian @brief Half edge successivo all'half edge */
        Dcel::Face* 	face;       /**< \~Italian @brief Faccia incidente all'half edge */
        unsigned int    id;         /**< \~Italian @brief Id univoco, all'interno della Dcel, associato all'a faccia'half edge */
        int             flag;       /**< \~Italian @brief Flag personalizzabile, associato all'half edge */

        /***************************
        * Protected Inline Methods *
        ****************************/

        void setId(unsigned int id);
};

}

#include "dcel_half_edge_inline.tpp"


#endif // DCEL_HALF_EDGE_H
