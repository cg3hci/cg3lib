/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_VERTEX_H
#define CG3_DCEL_VERTEX_H

#include <cg3/geometry/point3.h>
#include <cg3/utilities/color.h>
#include "dcel_half_edge.h"

namespace cg3 {

/**
 * \~Italian
 * @class Vertex
 * @brief Classe rappresentante un vertice della DCEL.
 *
 * All'interno della Dcel, le sue componenti fondamentali sono:
 * - coordinate: Pointd contenente la posizione in uno spazio 3D del vertice; \n
 * - incicentHalfEdge: uno degli half edge \b uscenti incidenti al vertice, ossia
 *   half edge che ha come from vertex il vertice stesso. \n
 *
 *
 * Per una corretta gestione della Dcel, ogni Vertex \c v deve avere un \c incidentHalfEdge.
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
class Vertex : public cg3::SerializableObject
{
    template <class V, class HE, class F>
    friend class cg3::TemplatedDcel;

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
    cg3::Vec3d normal()                                    const;
    const Point3d& coordinate()                       const;
    Color color()                                    const;
    int cardinality()                                const;
    const HalfEdge* incidentHalfEdge()         const;
    double dist(const Vertex* otherVertex)     const;
    bool checkIncidentHalfEdge()                     const;

    void setFlag();
    void setFlag(int newFlag);
    void resetFlag();
    void setNormal(const Vec3d& newNormal);
    void setCoordinate(const Point3d& newCoordinate);
    void setCardinality(int newCardinality);
    void setColor(const Color &c);
    int decrementCardinality();
    int incrementCardinality();
    HalfEdge* incidentHalfEdge();
    void setIncidentHalfEdge(HalfEdge* newIncidentHalfEdge);

    /*****************
    * Public Methods *
    ******************/

    int numberIncidentHalfEdges()                                                                            const;
    int numberIncidentFaces()                                                                                const;
    int numberAdjacentVertices()                                                                             const;
    const HalfEdge* findSharedHalfEdge(const Vertex* vertex)                                        const;
    std::string toString()                                                                                      const;
    ConstAdjacentVertexIterator adjacentVertexBegin()                                                           const;
    ConstAdjacentVertexIterator adjacentVertexEnd()                                                             const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const HalfEdge* start)                                const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const HalfEdge* start, const HalfEdge* end)     const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const Vertex* start)                                  const;
    ConstAdjacentVertexIterator adjacentVertexBegin(const Vertex* start, const Vertex* end)         const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeBegin()                                                       const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeEnd()                                                         const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeBegin(const HalfEdge* start)                            const;
    ConstOutgoingHalfEdgeIterator outgoingHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeBegin()                                                       const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeEnd()                                                         const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeBegin(const HalfEdge* start)                            const;
    ConstIncomingHalfEdgeIterator incomingHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin()                                                       const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeEnd()                                                         const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(const HalfEdge* start)                            const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(const HalfEdge* start, const HalfEdge* end) const;
    ConstIncidentFaceIterator incidentFaceBegin()                                                               const;
    ConstIncidentFaceIterator incidentFaceEnd()                                                                 const;
    ConstIncidentFaceIterator incidentFaceBegin(const HalfEdge* start)                                    const;
    ConstIncidentFaceIterator incidentFaceBegin(const HalfEdge* start, const HalfEdge* end)         const;

    Vec3d updateNormal();
    unsigned int updateCardinality();
    HalfEdge* findSharedHalfEdge(const Vertex* vertex);
    AdjacentVertexIterator adjacentVertexBegin();
    AdjacentVertexIterator adjacentVertexEnd();
    AdjacentVertexIterator adjacentVertexBegin(HalfEdge* start);
    AdjacentVertexIterator adjacentVertexBegin(HalfEdge* start, HalfEdge* end);
    AdjacentVertexIterator adjacentVertexBegin(Vertex* start);
    AdjacentVertexIterator adjacentVertexBegin(Vertex* start, Vertex* end);
    OutgoingHalfEdgeIterator outgoingHalfEdgeBegin();
    OutgoingHalfEdgeIterator outgoingHalfEdgeEnd();
    OutgoingHalfEdgeIterator outgoingHalfEdgeBegin(HalfEdge* start);
    OutgoingHalfEdgeIterator outgoingHalfEdgeBegin(HalfEdge* start, HalfEdge* end);
    IncomingHalfEdgeIterator incomingHalfEdgeBegin();
    IncomingHalfEdgeIterator incomingHalfEdgeEnd();
    IncomingHalfEdgeIterator incomingHalfEdgeBegin(HalfEdge* start);
    IncomingHalfEdgeIterator incomingHalfEdgeBegin(HalfEdge* start, HalfEdge* end);
    IncidentHalfEdgeIterator incidentHalfEdgeBegin();
    IncidentHalfEdgeIterator incidentHalfEdgeEnd();
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(HalfEdge* start);
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(HalfEdge* start, HalfEdge* end);
    IncidentFaceIterator incidentFaceBegin();
    IncidentFaceIterator incidentFaceEnd();
    IncidentFaceIterator incidentFaceBegin(HalfEdge* start);
    IncidentFaceIterator incidentFaceBegin(HalfEdge* start, HalfEdge* end);

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

    // SerializableObject interface
    void serialize(std::ofstream& binaryFile) const;
    void deserialize(std::ifstream& binaryFile);

protected:

    class GenericIterator;
    class ConstGenericIterator;

    /***************
    * Constructors *
    ****************/

    #ifdef NDEBUG
    Vertex(internal::DcelData& parent);
    #else
    Vertex();
    #endif
    //Vertex(Dcel& parent, const Pointd& p);
    //Vertex(Dcel& parent, const Pointd& p, HalfEdge* halfEdge);
    //Vertex(Dcel& parent, const Pointd& p, HalfEdge* halfEdge, int cardinality);
    virtual ~Vertex();

    /*************
    * Attributes *
    **************/

    #ifdef NDEBUG
    internal::DcelData* parent;
    #else
    Point3d          _coordinate;         /**< \~Italian @brief Punto nello spazio 3D rappresentante la posizione del vertice */
    Vec3d            _normal;             /**< \~Italian @brief Vettore normale al vertice */
    Color           _color;              /**< \~Italian @brief Colore associato al vertice */
    #endif
    HalfEdge* _incidentHalfEdge;   /**< \~Italian @brief Uno degli half edge uscenti incidenti sul vertice */
    unsigned int    _cardinality;        /**< \~Italian @brief Numero di edge (metà degli half edge) incidenti sul vertice */
    unsigned int    _id;                 /**< \~Italian @brief Id univoco, all'interno della Dcel, associato al vertice */
    int             _flag;               /**< \~Italian @brief Flag personalizzabile, associato al vertice */

    /***************************
    * Protected Inline Methods *
    ****************************/

    void setId(unsigned int _id);
};

} //namespace cg3

#include "dcel_vertex_iterators.h"

#endif // CG3_DCEL_VERTEX_H
