/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_VERTEX_H
#define CG3_DCEL_VERTEX_H

#include "dcel_struct.h"

namespace cg3 {

/**
 * \~Italian
 * @class Dcel::Vertex
 * @brief Classe rappresentante un vertice della DCEL.
 *
 * All'interno della Dcel, le sue componenti fondamentali sono:
 * - coordinate: Pointd contenente la posizione in uno spazio 3D del vertice; \n
 * - incicentHalfEdge: uno degli half edge \b uscenti incidenti al vertice, ossia
 *   half edge che ha come from vertex il vertice stesso. \n
 *
 *
 * Per una corretta gestione della Dcel, ogni Dcel::Vertex \c v deve avere un \c incidentHalfEdge.
 * Tale halfEdge deve avere come fromVertex il vertice \c v, e il suo twin deve avere \c v come toVertex.
 * Devono poi essere rispettate le regole degli halfEdge e dei loro vertici incidenti sulle relazioni di
 * prev e next.
 *
 * Le altre componenti che compongono il vertice sono:
 * - normal: vettore 3D rappresentante la normale del vertice, che solitamente è la
 *   media delle normali delle facce incidenti;\n
 * - cardinality: numero di edge (ossia la metà del numero di half edge) incidenti sul vertice;\n
 * - id: intero senza segno univoco all'interno della lista dei vertici della Dcel,
 *   non modificabile dall'utente. Può essere usato per identificare il vertice all'interno
 *   della Dcel (in modo meno efficiente rispetto all'utilizzo di un puntatore);\n
 * - flag: intero personalizzabile dall'utente. \n
 *
 *
 * @todo color: colore associato al vertice;\n
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Dcel::Vertex
{
    friend class Dcel;

public:

    /************
    * Iterators *
    *************/

    class AdjacentVertexIterator;
    class ConstAdjacentVertexIterator;
    class OutgoingHalfEdgeIterator;
    class ConstOutgoingHalfEdgeIterator;
    class IncomingHalfEdgeIterator;
    class ConstIncomingHalfEdgeIterator;
    class IncidentHalfEdgeIterator;
    class ConstIncidentHalfEdgeIterator;
    class IncidentFaceIterator;
    class ConstIncidentFaceIterator;
    class ConstAdjacentVertexRangeBasedIterator;
    class ConstOutgoingHalfEdgeRangeBasedIterator;
    class ConstIncomingHalfEdgeRangeBasedIterator;
    class ConstIncidentHalfEdgeRangeBasedIterator;
    class ConstIncidentFaceRangeBasedIterator;
    class AdjacentVertexRangeBasedIterator;
    class OutgoingHalfEdgeRangeBasedIterator;
    class IncomingHalfEdgeRangeBasedIterator;
    class IncidentHalfEdgeRangeBasedIterator;
    class IncidentFaceRangeBasedIterator;

    /************************
    * Public Inline Methods *
    *************************/

    unsigned int id()                                const;
    int flag()                                       const;
    Vec3 normal()                                    const;
    const Pointd& coordinate()                       const;
    Color color()                                    const;
    int cardinality()                                const;
    const Dcel::HalfEdge* incidentHalfEdge()         const;
    double dist(const Dcel::Vertex* otherVertex)     const;
    bool checkIncidentHalfEdge()                     const;

    void setFlag();
    void setFlag(int newFlag);
    void resetFlag();
    void setNormal(const Vec3& newNormal);
    void setCoordinate(const Pointd& newCoordinate);
    void setCardinality(int newCardinality);
    void setColor(const Color &c);
    int decrementCardinality();
    int incrementCardinality();
    Dcel::HalfEdge* incidentHalfEdge();
    void setIncidentHalfEdge(Dcel::HalfEdge* newIncidentHalfEdge);

    /*****************
    * Public Methods *
    ******************/

    int numberIncidentHalfEdges()                                                                            const;
    int numberIncidentFaces()                                                                                const;
    int numberAdjacentVertices()                                                                             const;
    const Dcel::HalfEdge* findSharedHalfEdge(const Dcel::Vertex* vertex)                                        const;
    std::string toString()                                                                                      const;
    ConstAdjacentVertexIterator adjacentVertexBegin()                                                           const;
    ConstAdjacentVertexIterator adjacentVertexEnd()                                                             const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const Dcel::HalfEdge* start)                                const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end)     const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const Dcel::Vertex* start)                                  const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const Dcel::Vertex* start, const Dcel::Vertex* end)         const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeBegin()                                                       const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeEnd()                                                         const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeBegin(const Dcel::HalfEdge* start)                            const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end) const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeBegin()                                                       const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeEnd()                                                         const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeBegin(const Dcel::HalfEdge* start)                            const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end) const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin()                                                       const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeEnd()                                                         const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(const Dcel::HalfEdge* start)                            const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end) const;
    ConstIncidentFaceIterator incidentFaceBegin()                                                               const;
    ConstIncidentFaceIterator incidentFaceEnd()                                                                 const;
    ConstIncidentFaceIterator incidentFaceBegin(const Dcel::HalfEdge* start)                                    const;
    ConstIncidentFaceIterator incidentFaceBegin(const Dcel::HalfEdge* start, const Dcel::HalfEdge* end)         const;

    Vec3 updateNormal();
    unsigned int updateCardinality();
    Dcel::HalfEdge* findSharedHalfEdge(const Dcel::Vertex* vertex);
    AdjacentVertexIterator adjacentVertexBegin();
    AdjacentVertexIterator adjacentVertexEnd();
    AdjacentVertexIterator adjacentVertexBegin(Dcel::HalfEdge* start);
    AdjacentVertexIterator adjacentVertexBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end);
    AdjacentVertexIterator adjacentVertexBegin(Dcel::Vertex* start);
    AdjacentVertexIterator adjacentVertexBegin(Dcel::Vertex* start, Dcel::Vertex* end);
    OutgoingHalfEdgeIterator outgoingHalfEdgeBegin();
    OutgoingHalfEdgeIterator outgoingHalfEdgeEnd();
    OutgoingHalfEdgeIterator outgoingHalfEdgeBegin(Dcel::HalfEdge* start);
    OutgoingHalfEdgeIterator outgoingHalfEdgeBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end);
    IncomingHalfEdgeIterator incomingHalfEdgeBegin();
    IncomingHalfEdgeIterator incomingHalfEdgeEnd();
    IncomingHalfEdgeIterator incomingHalfEdgeBegin(Dcel::HalfEdge* start);
    IncomingHalfEdgeIterator incomingHalfEdgeBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end);
    IncidentHalfEdgeIterator incidentHalfEdgeBegin();
    IncidentHalfEdgeIterator incidentHalfEdgeEnd();
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(Dcel::HalfEdge* start);
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end);
    IncidentFaceIterator incidentFaceBegin();
    IncidentFaceIterator incidentFaceEnd();
    IncidentFaceIterator incidentFaceBegin(Dcel::HalfEdge* start);
    IncidentFaceIterator incidentFaceBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end);

    const ConstAdjacentVertexRangeBasedIterator adjacentVertexIterator() const;
    AdjacentVertexRangeBasedIterator adjacentVertexIterator();
    const ConstOutgoingHalfEdgeRangeBasedIterator outgoingHalfEdgeIterator() const;
    OutgoingHalfEdgeRangeBasedIterator outgoingHalfEdgeIterator();
    const ConstIncomingHalfEdgeRangeBasedIterator incomingHalfEdgeIterator() const;
    IncomingHalfEdgeRangeBasedIterator incomingHalfEdgeIterator();
    const ConstIncidentHalfEdgeRangeBasedIterator incidentHalfEdgeIterator() const;
    IncidentHalfEdgeRangeBasedIterator incidentHalfEdgeIterator();
    const ConstIncidentFaceRangeBasedIterator incidentFaceIterator() const;
    IncidentFaceRangeBasedIterator incidentFaceIterator();

    #ifdef CG3_OLD_NAMES_COMPATIBILITY
    inline unsigned int getId() const {return id();}
    inline int getFlag() const {return flag();}
    inline Vec3 getNormal() const {return normal();}
    inline const Pointd& getCoordinate() const {return coordinate();}
    inline Color getColor() const {return color();}
    inline int getCardinality() const {return cardinality();}
    inline const Dcel::HalfEdge* getIncidentHalfEdge() const {return incidentHalfEdge();}
    inline Dcel::HalfEdge* getIncidentHalfEdge() {return incidentHalfEdge();}
    inline int getNumberIncidentHalfEdges() const {return numberIncidentHalfEdges();}
    inline int getNumberIncidentFaces() const {return numberIncidentFaces();}
    inline int getNumberAdjacentVertices() const {return numberAdjacentVertices();}
    #endif

protected:

    class GenericIterator;
    class ConstGenericIterator;

    /***************
    * Constructors *
    ****************/

    #ifdef NDEBUG
    Vertex(Dcel& parent);
    #else
    Vertex();
    #endif
    //Vertex(Dcel& parent, const Pointd& p);
    //Vertex(Dcel& parent, const Pointd& p, Dcel::HalfEdge* halfEdge);
    //Vertex(Dcel& parent, const Pointd& p, Dcel::HalfEdge* halfEdge, int cardinality);
    ~Vertex();

    /*************
    * Attributes *
    **************/

    #ifdef NDEBUG
    Dcel* parent;
    #else
    Pointd          _coordinate;         /**< \~Italian @brief Punto nello spazio 3D rappresentante la posizione del vertice */
    Vec3            _normal;             /**< \~Italian @brief Vettore normale al vertice */
    Color           _color;              /**< \~Italian @brief Colore associato al vertice */
    #endif
    Dcel::HalfEdge* _incidentHalfEdge;   /**< \~Italian @brief Uno degli half edge uscenti incidenti sul vertice */
    unsigned int    _cardinality;        /**< \~Italian @brief Numero di edge (metà degli half edge) incidenti sul vertice */
    unsigned int    _id;                 /**< \~Italian @brief Id univoco, all'interno della Dcel, associato al vertice */
    int             _flag;               /**< \~Italian @brief Flag personalizzabile, associato al vertice */

    /***************************
    * Protected Inline Methods *
    ****************************/

    void setId(unsigned int _id);
};

} //namespace cg3

#include "dcel_vertex_inline.tpp"

#endif // CG3_DCEL_VERTEX_H
