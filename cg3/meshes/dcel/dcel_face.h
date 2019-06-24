/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_FACE_H
#define CG3_DCEL_FACE_H

#include "dcel_half_edge.h"
#include <cg3/geometry/point3.h>
#include <cg3/utilities/color.h>

namespace cg3 {

/**
 * \~Italian
 * @class Face
 * @brief Classe rappresentante una faccia della Dcel.
 *
 * All'interno della Dcel, le sue componenti fondamentali sono:
 * - outerHalfEdge: un half edge incidente esterno, ossia che si trova sul bordo
 * esterno della faccia (tutti gli altri half edge dello stesso tipo saranno individuabili
 *   mediante operazioni di next e prev dell'half edge);\n
 * - innerHalfEdges: lista di half edge incidenti interni, ossia sul bordo di un buco
 * interno alla faccia, un inner half edge per ogni buco della faccia (tutti gli altri
 *   half edge dello stesso tipo saranno individuabili mediante operazioni di next e prev
 * dell'half edge).\n
 *
 *
 * Per una gestione corretta della Dcel, ogni faccia \c f deve avere un \c outerHalfEdge
 * e 0 o più \c innerHalfEdge.
 * Ognuno di questi questi half edge, e tutti quelli raggiungibili mediante operazioni di
 * next e prev, devono avere come incidentFace \c f.
 *
 * Le altre componenti che compongono la faccia sono:
 * - normal: vettore 3D rappresentante la normale alla faccia;\n
 * - area: superficie della faccia;\n
 * - color: colore associato alla faccia;\n
 * - id: intero senza segno univoco all'interno della lista delle facce della Dcel, non
 * modificabile dall'utente. Può essere usato per identificare la faccia all'interno
 *   della Dcel (in modo meno efficiente rispetto all'utilizzo di un puntatore);\n
 * - flag: intero personalizzabile dall'utente. \n
 *
 *
 * Sono messi a disposizione i seguenti iteratori per navigare sugli inner half edge
 * (uno per ogni buco):
 * - Face::InnerHalfEdgeIterator
 * - Face::ConstInnerHalfEdgeIterator
 *
 *
 * Sono messi a disposizione anche i seguenti iteratori per navigare sulle componenti
 * incidenti alla faccia:
 * - Face::IncidentHalfEdgeIterator
 * - Face::IncidentVertexIterator
 * - Face::ConstIncidentHalfEdgeIterator
 * - Face::ConstIncidentVertexIterator
 *
 * Per navigare su tutti gli half edge di un buco adiacenti alla faccia, è possibile usare
 * l'iteratore sugli half edge incidenti:
 *
 * \code{.cpp}
 * HalfEdge* firstInnerHalfEdge;
 * if (f->getNumberInnerHalfEdges() > 0){
 *     firstInnerHalfEdge = *(f->innerHalfEdgeBegin()); //primo inner half edge della faccia
 *     for (Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(firstInnerHalfEdge);
 *          heit!=f->incidentHalfEdgeEnd();
 *          ++heit) {
 *         HalfEdge* inner = *heit;
 *         // operazioni su inner
 *     }
 * }
 * \endcode
 *
 * Il controllo sull' \c if verifica che la faccia \c f abbia almeno un inner half edge
 * (ossia abbia almeno un buco). A questo punto, \c firstInnerHalfEdge viene fatto puntare
 * ad un inner half edge, e viene fatto ciclare un iteratore sugli incident half edge di \c f
 * inizializzato con \c firstInnerHalfEdge.
 *
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
class Face : public cg3::SerializableObject {

    template <class V, class HE, class F>
    friend class cg3::TemplatedDcel;

public:

    /************
    * Iterators *
    *************/

    /**
     * \~Italian
     * @class InnerHalfEdgeIterator
     *
     * @brief Iteratore che permette di ciclare sul vettore degli inner half edge associati
     * alla faccia. Ogni inner half edge è associato ad un buco presente all'interno della
     * faccia. Una volta che si ha a disposizione un inner half edge, è possibile ciclare
     * sul bordo del buco mediante delle semplici operazioni di next, oppure utilizzando
     * un IncidentHalfEdgeIterator o ConstIncidentHalfEdgeIterator opportunamente
     * inizializzato.
     *
     * È possibile utilizzare l'iteratore esattamente come si utilizza un iteratore su un
     * std::vector. Per esempio, data una faccia Face* f:
     *
     * \code{.cpp}
     * for (Face::InnerHalfEdgeIterator heit = f->innerHalfEgeBegin();
     *      heit != f->innerHalfEdgeEnd();
     *      ++heit) {
     *     HalfEdge* he = *heit;
     *     // operazioni su he
     * }
     * \endcode
     *
     * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a
     * cui appartiene, e quindi non è possibile utilizzarlo su const Face. Per
     * const Face, vedere Face::ConstInnerHalfEdgeIterator.
     */

    typedef std::vector<HalfEdge*>::iterator InnerHalfEdgeIterator;
    class ConstInnerHalfEdgeIterator;
    class AdjacentFaceIterator;
    class ConstAdjacentFaceIterator;
    class IncidentHalfEdgeIterator;
    class ConstIncidentHalfEdgeIterator;
    class IncidentVertexIterator;
    class ConstIncidentVertexIterator;

    class ConstInnerHalfEdgeRangeBasedIterator;
    class ConstAdjacentFaceRangeBasedIterator;
    class ConstIncidentHalfEdgeRangeBasedIterator;
    class ConstIncidentVertexRangeBasedIterator;
    class InnerHalfEdgeRangeBasedIterator;
    class AdjacentFaceRangeBasedIterator;
    class IncidentHalfEdgeRangeBasedIterator;
    class IncidentVertexRangeBasedIterator;

    /************************
    * Public Inline Methods *
    *************************/

    unsigned int id()                            const;
    const Vertex* vertex1()                const;
    const Vertex* vertex2()                const;
    const Vertex* vertex3()                const;
    int flag()                                   const;
    cg3::Vec3d normal()                                const;
    double area()                                const;
    Color color()                                const;
    const HalfEdge* outerHalfEdge()        const;
    unsigned int numberInnerHalfEdges()          const;
    bool hasHoles()                                 const;
    bool checkOuterHalfEdge()                       const;


    Vertex* vertex1();
    Vertex* vertex2();
    Vertex* vertex3();
    void setFlag();
    void setFlag(int newFlag);
    void resetFlag();
    void setNormal(const Vec3d& newNormal);
    void setArea(double newArea);
    void setColor(const Color& newColor);
    HalfEdge* outerHalfEdge();
    void setOuterHalfEdge(HalfEdge* newOuterHalfEdge);
    void addInnerHalfEdge(HalfEdge* newInnerHalfEdge);


    /*****************
    * Public Methods *
    ******************/

    bool isTriangle()                                                               const;
    bool isAdjacentTo(const Face* ad)                                         const;
    bool isIncidentTo(const Vertex* v)                                        const;
    int numberIncidentVertices()                                                 const;
    int numberIncidentHalfEdges()                                                const;
    Point3d barycenter()                                                          const;
    #ifdef CG3_CGAL_DEFINED
    void triangulation(
            std::vector<std::array<const Vertex*, 3> >& triangles)            const;
    #endif
    std::string toString()                                                          const;
    ConstAdjacentFaceIterator adjacentFaceBegin()                                   const;
    ConstAdjacentFaceIterator adjacentFaceEnd()                                     const;
    ConstInnerHalfEdgeIterator innerHalfEdgeBegin()                                 const;
    ConstInnerHalfEdgeIterator innerHalfEdgeEnd()                                   const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin()                           const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeEnd()                             const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(
            const HalfEdge* start)                                            const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(
            const HalfEdge* start,
            const HalfEdge* end)                                              const;
    ConstIncidentVertexIterator incidentVertexBegin()                               const;
    ConstIncidentVertexIterator incidentVertexEnd()                                 const;
    ConstIncidentVertexIterator incidentVertexBegin(const HalfEdge* start)    const;
    ConstIncidentVertexIterator incidentVertexBegin(
            const HalfEdge* start,
            const HalfEdge* end)                                              const;
    ConstIncidentVertexIterator incidentVertexBegin(const Vertex* start)      const;
    ConstIncidentVertexIterator incidentVertexBegin(
            const Vertex* start,
            const Vertex* end)                                                const;
    ConstInnerHalfEdgeRangeBasedIterator innerHalfEdgeIterator()                    const;
    ConstAdjacentFaceRangeBasedIterator adjacentFaceIterator()                      const;
    ConstIncidentHalfEdgeRangeBasedIterator incidentHalfEdgeIterator()              const;
    ConstIncidentVertexRangeBasedIterator incidentVertexIterator()                  const;

    Vec3d updateNormal();
    double updateArea();
    void removeInnerHalfEdge(const InnerHalfEdgeIterator& iterator);
    bool removeInnerHalfEdge(const HalfEdge* halfEdge);
    void removeAllInnerHalfEdges();
    void invertOrientation();
    AdjacentFaceIterator adjacentFaceBegin();
    AdjacentFaceIterator adjacentFaceEnd();
    InnerHalfEdgeIterator innerHalfEdgeBegin();
    InnerHalfEdgeIterator innerHalfEdgeEnd();
    IncidentHalfEdgeIterator incidentHalfEdgeBegin();
    IncidentHalfEdgeIterator incidentHalfEdgeEnd();
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(HalfEdge* start);
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(
            HalfEdge* start,
            HalfEdge* end);
    IncidentVertexIterator incidentVertexBegin();
    IncidentVertexIterator incidentVertexEnd();
    IncidentVertexIterator incidentVertexBegin(HalfEdge* start);
    IncidentVertexIterator incidentVertexBegin(HalfEdge* start, HalfEdge* end);
    IncidentVertexIterator incidentVertexBegin(Vertex* start);
    IncidentVertexIterator incidentVertexBegin(Vertex* start, Vertex* end);
    InnerHalfEdgeRangeBasedIterator innerHalfEdgeIterator();
    AdjacentFaceRangeBasedIterator adjacentFaceIterator();
    IncidentHalfEdgeRangeBasedIterator incidentHalfEdgeIterator();
    IncidentVertexRangeBasedIterator incidentVertexIterator();

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
    Face(internal::DcelData &parent);
    #else
    Face();
    #endif
    virtual ~Face();

    /*************
    * Attributes *
    **************/

    #ifdef NDEBUG
    internal::DcelData *parent;
    #else
    Vec3d                            _normal;
    Color                           _color;
    #endif
    HalfEdge*                 _outerHalfEdge;
    std::vector<HalfEdge*>    _innerHalfEdges;
    double                          _area;
    unsigned int                    _id;
    int                             _flag;

    /***************************
    * Protected Inline Methods *
    ****************************/

    void setId(unsigned int id);

    /********************
    * Protected Methods *
    *********************/

    std::string innerComponentsToString() const;
    double signedVolume() const;
};

std::ostream& operator<< (std::ostream& inputStream, const Face* f);

} //namespace cg3

#include "dcel_face_iterators.h"

#endif // CG3_DCEL_FACE_H
