/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_DCEL_FACE_H
#define CG3_DCEL_FACE_H

#include "dcel_struct.h"
#include <cg3/utilities/color.h>

namespace cg3 {

/**
 * \~Italian
 * @class Dcel::Face
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
 * - Dcel::Face::InnerHalfEdgeIterator
 * - Dcel::Face::ConstInnerHalfEdgeIterator
 *
 *
 * Sono messi a disposizione anche i seguenti iteratori per navigare sulle componenti
 * incidenti alla faccia:
 * - Dcel::Face::IncidentHalfEdgeIterator
 * - Dcel::Face::IncidentVertexIterator
 * - Dcel::Face::ConstIncidentHalfEdgeIterator
 * - Dcel::Face::ConstIncidentVertexIterator
 *
 * Per navigare su tutti gli half edge di un buco adiacenti alla faccia, è possibile usare
 * l'iteratore sugli half edge incidenti:
 *
 * \code{.cpp}
 * Dcel::HalfEdge* firstInnerHalfEdge;
 * if (f->getNumberInnerHalfEdges() > 0){
 *     firstInnerHalfEdge = *(f->innerHalfEdgeBegin()); //primo inner half edge della faccia
 *     for (Dcel::Face::IncidentHalfEdgeIterator heit = f->incidentHalfEdgeBegin(firstInnerHalfEdge);
 *          heit!=f->incidentHalfEdgeEnd();
 *          ++heit) {
 *         Dcel::HalfEdge* inner = *heit;
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
class Dcel::Face {

    friend class Dcel;

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
     * std::vector. Per esempio, data una faccia Dcel::Face* f:
     *
     * \code{.cpp}
     * for (Dcel::Face::InnerHalfEdgeIterator heit = f->innerHalfEgeBegin();
     *      heit != f->innerHalfEdgeEnd();
     *      ++heit) {
     *     Dcel::HalfEdge* he = *heit;
     *     // operazioni su he
     * }
     * \endcode
     *
     * Questo iteratore non garantisce l'immutabilità della faccia e quindi della Dcel a
     * cui appartiene, e quindi non è possibile utilizzarlo su const Dcel::Face. Per
     * const Dcel::Face, vedere Dcel::Face::ConstInnerHalfEdgeIterator.
     */
    typedef std::vector<Dcel::HalfEdge*>::iterator InnerHalfEdgeIterator;
    class ConstInnerHalfEdgeIterator;
    class AdjacentFaceIterator;
    class ConstAdjacentFaceIterator;
    class IncidentHalfEdgeIterator;
    class ConstIncidentHalfEdgeIterator;
    class IncidentVertexIterator;
    class ConstIncidentVertexIterator;
    class ConstAdjacentFaceRangeBasedIterator;
    class ConstIncidentHalfEdgeRangeBasedIterator;
    class ConstIncidentVertexRangeBasedIterator;
    class AdjacentFaceRangeBasedIterator;
    class IncidentHalfEdgeRangeBasedIterator;
    class IncidentVertexRangeBasedIterator;

    /************************
    * Public Inline Methods *
    *************************/

    unsigned int id()                            const;
    const Dcel::Vertex* vertex1()                const;
    const Dcel::Vertex* vertex2()                const;
    const Dcel::Vertex* vertex3()                const;
    int flag()                                   const;
    Vec3 normal()                                const;
    double area()                                const;
    Color color()                                const;
    const Dcel::HalfEdge* outerHalfEdge()        const;
    unsigned int numberInnerHalfEdges()          const;
    bool hasHoles()                                 const;
    bool checkOuterHalfEdge()                       const;


    Dcel::Vertex* vertex1();
    Dcel::Vertex* vertex2();
    Dcel::Vertex* vertex3();
    void setFlag();
    void setFlag(int newFlag);
    void resetFlag();
    void setNormal(const Vec3& newNormal);
    void setArea(double newArea);
    void setColor(const Color& newColor);
    Dcel::HalfEdge* outerHalfEdge();
    void setOuterHalfEdge(Dcel::HalfEdge* newOuterHalfEdge);
    void addInnerHalfEdge(Dcel::HalfEdge* newInnerHalfEdge);


    /*****************
    * Public Methods *
    ******************/

    bool isTriangle()                                                               const;
    bool isAdjacentTo(const Dcel::Face* ad)                                         const;
    bool isIncidentTo(const Dcel::Vertex* v)                                        const;
    int numberIncidentVertices()                                                 const;
    int numberIncidentHalfEdges()                                                const;
    Pointd barycenter()                                                          const;
    #ifdef CG3_CGAL_DEFINED
    void triangulation(
            std::vector<std::array<const Dcel::Vertex*, 3> >& triangles)            const;
    #endif
    std::string toString()                                                          const;
    ConstAdjacentFaceIterator adjacentFaceBegin()                                   const;
    ConstAdjacentFaceIterator adjacentFaceEnd()                                     const;
    ConstInnerHalfEdgeIterator innerHalfEdgeBegin()                                 const;
    ConstInnerHalfEdgeIterator innerHalfEdgeEnd()                                   const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin()                           const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeEnd()                             const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(
            const Dcel::HalfEdge* start)                                            const;
    ConstIncidentHalfEdgeIterator incidentHalfEdgeBegin(
            const Dcel::HalfEdge* start,
            const Dcel::HalfEdge* end)                                              const;
    ConstIncidentVertexIterator incidentVertexBegin()                               const;
    ConstIncidentVertexIterator incidentVertexEnd()                                 const;
    ConstIncidentVertexIterator incidentVertexBegin(const Dcel::HalfEdge* start)    const;
    ConstIncidentVertexIterator incidentVertexBegin(
            const Dcel::HalfEdge* start,
            const Dcel::HalfEdge* end)                                              const;
    ConstIncidentVertexIterator incidentVertexBegin(const Dcel::Vertex* start)      const;
    ConstIncidentVertexIterator incidentVertexBegin(
            const Dcel::Vertex* start,
            const Dcel::Vertex* end)                                                const;
    ConstAdjacentFaceRangeBasedIterator adjacentFaceIterator()                      const;
    ConstIncidentHalfEdgeRangeBasedIterator incidentHalfEdgeIterator()              const;
    ConstIncidentVertexRangeBasedIterator incidentVertexIterator()                  const;

    Vec3 updateNormal();
    double updateArea();
    void removeInnerHalfEdge(const InnerHalfEdgeIterator& iterator);
    bool removeInnerHalfEdge(const Dcel::HalfEdge* halfEdge);
    void removeAllInnerHalfEdges();
    AdjacentFaceIterator adjacentFaceBegin();
    AdjacentFaceIterator adjacentFaceEnd();
    InnerHalfEdgeIterator innerHalfEdgeBegin();
    InnerHalfEdgeIterator innerHalfEdgeEnd();
    IncidentHalfEdgeIterator incidentHalfEdgeBegin();
    IncidentHalfEdgeIterator incidentHalfEdgeEnd();
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(Dcel::HalfEdge* start);
    IncidentHalfEdgeIterator incidentHalfEdgeBegin(
            Dcel::HalfEdge* start,
            Dcel::HalfEdge* end);
    IncidentVertexIterator incidentVertexBegin();
    IncidentVertexIterator incidentVertexEnd();
    IncidentVertexIterator incidentVertexBegin(Dcel::HalfEdge* start);
    IncidentVertexIterator incidentVertexBegin(Dcel::HalfEdge* start, Dcel::HalfEdge* end);
    IncidentVertexIterator incidentVertexBegin(Dcel::Vertex* start);
    IncidentVertexIterator incidentVertexBegin(Dcel::Vertex* start, Dcel::Vertex* end);
    AdjacentFaceRangeBasedIterator adjacentFaceIterator();
    IncidentHalfEdgeRangeBasedIterator incidentHalfEdgeIterator();
    IncidentVertexRangeBasedIterator incidentVertexIterator();

    #ifdef CG3_OLD_NAMES_COMPATIBILITY
    inline unsigned int getId() const {return id();}
    inline const Dcel::Vertex* getVertex1() const {return vertex1();}
    inline const Dcel::Vertex* getVertex2() const {return vertex2();}
    inline const Dcel::Vertex* getVertex3() const {return vertex3();}
    inline Dcel::Vertex* getVertex1() {return vertex1();}
    inline Dcel::Vertex* getVertex2() {return vertex2();}
    inline Dcel::Vertex* getVertex3() {return vertex3();}
    inline int getFlag() const {return flag();}
    inline Vec3 getNormal() const {return normal();}
    inline double getArea() const {return area();}
    inline Color getColor() const {return color();}
    inline const Dcel::HalfEdge* getOuterHalfEdge() const {return outerHalfEdge();}
    inline Dcel::HalfEdge* getOuterHalfEdge() {return outerHalfEdge();}
    inline unsigned int getNumberInnerHalfEdges() const {return numberInnerHalfEdges();}
    inline int getNumberIncidentVertices() const {return numberIncidentVertices();}
    inline int getNumberIncidentHalfEdges() const {return numberIncidentHalfEdges();}
    inline Pointd getBarycenter() const {return barycenter();}
    #ifdef CG3_CGAL_DEFINED
    inline void getTriangulation(std::vector<std::array<const Dcel::Vertex*, 3> >& t) const {return triangulation(t);}
    #endif
    #endif

protected:

    class GenericIterator;
    class ConstGenericIterator;

    /***************
    * Constructors *
    ****************/

    #ifdef NDEBUG
    Face(Dcel &parent);
    #else
    Face();
    #endif
    ~Face();

    /*************
    * Attributes *
    **************/

    #ifdef NDEBUG
    Dcel *parent;
    #else
    Vec3                            _normal;
    Color                           _color;
    #endif
    Dcel::HalfEdge*                 _outerHalfEdge;
    std::vector<Dcel::HalfEdge*>    _innerHalfEdges;
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
};

std::ostream& operator<< (std::ostream& inputStream, const Dcel::Face* f);

} //namespace cg3

#include "dcel_face_inline.tpp"

#endif // CG3_DCEL_FACE_H
