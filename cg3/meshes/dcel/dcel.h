/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@tiscali.it)
 */

#ifndef CG3_DCEL_H
#define CG3_DCEL_H

#include "dcel_vertex.h"
#include "dcel_face.h"
#ifndef CG3_STATIC
#define CG3_DCEL_FACE_CPP "dcel_face.cpp"
#include CG3_DCEL_FACE_CPP
#undef CG3_DCEL_FACE_CPP

#define CG3_DCEL_VERTEX_CPP "dcel_vertex.cpp"
#include CG3_DCEL_VERTEX_CPP
#undef CG3_DCEL_VERTEX_CPP


#define DCEL_HALF_EDGE_CPP "dcel_half_edge.cpp"
#include DCEL_HALF_EDGE_CPP
#undef DCEL_HALF_EDGE_CPP
#endif
#include "dcel_struct.h"

namespace cg3 {

class Dcel : public TemplatedDcel<Vertex, HalfEdge, Face>
{
public:
    Dcel() : TemplatedDcel() {}
    Dcel(const TemplatedDcel<Vertex, HalfEdge, Face>& t) : TemplatedDcel(t) {}
    Dcel(TemplatedDcel<Vertex, HalfEdge, Face>&& t) : TemplatedDcel(t) {}
    using TemplatedDcel<Vertex, HalfEdge, Face>::TemplatedDcel; //inherits constructors
    using TemplatedDcel<Vertex, HalfEdge, Face>::operator=; //inherits assignment operators
};

}

/**
 * @page DcelPage The cg3::Dcel Data Structure
 *
 * # 1 Introduction
 * The cg3::Dcel data structure has been designed to allow the a practical and easy
 * developement of algorithms with a double connected half edge list, providing useful and
 * powerful tools for a fast navigation of surfaces. It is designed to be used with
 * pointers, allowing to manipulate directly all the elements that compose the surface.
 * The base cg3::Dcel supports perfectly triangle meshes. It supports also polygonal
 * meshes (polygons can also have holes), but for these you will need to enable the
 * cg3::cgal module.
 *
 * # 2 Overview
 * The Double-Connected Edge-List (Dcel) is a data structures that implements and
 * manages elements in order to model a 3D surface mesh, in order that all the adjacency
 * and incidency informations between the components will be accessibile in a constant
 * time. The Dcel is composed of:
 * - Vertices (Dcel::Vertex)
 * - Half Edges (Dcel::HalfEdge)
 * - Faces (Dcel::Face)
 *
 * Vertices are composed of:
 * - Coordinate: a 3D point (cg3::Point);
 * - Normal: a 3D vector which represent the normal to the vertex (cg3::Point);
 * - Incident Half Edge: a pointer to one of the incident outgoing half edges from the
 * vertex;
 * - Cardinality: number of edges (not half edges!) incident to the vertex;
 * - Flag: an integer value assignable by the user to the vertex.
 *
 * Half Edges are composed of:
 * - From Vertex: pointer to the from vertex;
 * - To Vertex: pointer to the to vertex;
 * - Twin Half Edge: pointer to the half edge twin (same incident vertices, opposite
 * direction);
 * - Previous Half Edge: pointer to the previous half edge in the incident face;
 * - Next Half Edge: pointer to the next half edge in the incident face;
 * - Incident Face: pointer to the incident face;
 * - Flag: an integer value assignable by the user to the half edge.
 *
 * Faces are composed of:
 * - Outer Half Edge: Pointer to one of the half edges on the border of the face;
 * - Inner Half Edges: list of inner half edges of the face, one for every hole of the
 * face;
 * - Normal: a 3D vector which represent the normal to the face (cg3::Point);
 * - Area: area of the face;
 * - Color: color associated to the face;
 * - Flag: an integer value assignable by the user to the face.
 *
 * The main purpose of the Dcel class is to put together three lists of components above
 * and link them together, in order to have an efficient access to all the adjacencies and
 * incidences between the components. The class allows to have access to the single
 * components of every Vertex, Half Edge and Face, and also to make global operations on
 * the surface stored in the Dcel, allowing efficient insertion, modification and deletion
 * of every component. The class is inspired to the classic DCEL model described in
 * Computational  Geometry: Algorithms and Applications; vertices, half edges and faces
 * are stored in three different lists, and the links between the components are made
 * using pointers.
 *
 * # 3 How to use cg3::Dcel
 *
 * A cg3::Dcel istance can be created as a simple variable: \n
 *
 * \code{.cpp}
 * cg3::Dcel d;
 * \endcode
 *
 * A dcel can be loaded from file, using a constructor a the method Dcel::loadFromFile:
 *
 * \code{.cpp}
 * cg3::Dcel d("mesh.ply");
 * d.loadFromObj("mesh.obj");
 * d.loadFromPly("mesh2.ply");
 * \endcode
 *
 * A Dcel can be also stored on file, using methods for the supported formats:
 *
 * \code{.cpp}
 * d.saveOnObj("mesh.obj");
 * d.saveOnPly("mesh.ply");
 * \endcode
 *
 * It exists also a specified format "dcel" for cg3::Dcel meshes:
 *
 * \code{.cpp}
 * d.loadFromDcelFile("mesh.dcel"); // or d.loadFromFile("mesh.dcel");
 * //some operations
 * d.saveOnDcelFile("newmesh.dcel");
 * \endcode
 *
 * It is also possible to create and load manually all the components to the Dcel:
 *
 * \code{.cpp}
 * cg3::Dcel::Vertex* v = d.addVertex(); // v is a pointer to the vertex of the Dcel
 * v->setCoordinate(Pointd(0.0, 0.1, 0.2)); // setting the coordinate of the vertex
 * cg3::Dcel::HalfEdge* he = d.addHalfEdge(); // he is a pointer to the inserted half
 *                                            // edge of the Dcel
 * he->setFromVertex(v); // v becomes the "from vertex" of he
 * cg3::Dcel::Face* f = d.addFace(); // f is a pointer to the inserted face of the Dcel
 * f->setOuterHalfEdge(he); // he becomes the outer half edge of the face f
 * he->setFace(f); // f becomes the incident face of he
 * \endcode
 *
 * When the method \c addVertex() is exectued, a new vertex is added to the Dcel. The
 * method returns a  \c cg3::Dcel::Vertex*. After adding the vertex, it will be necessary
 * to use its pointer \c v to manipulate it. The same is valid for cg3::Dcel::HalfEdge and
 * cg3::Dcel::Face. After the element is inserted in the Dcel, an unique and non-mutable
 * ID will be assigned to it. This ID allows to easily identify the elements.
 * Elements can be also extracted from the Dcel using the ID:
 *
 * \code{.cpp}
 * cg3::Dcel::Vertex* v = d.vertex(12); // v is a pointer to the vertex with ID = 12
 * \endcode
 *
 * This ID is unique and valid only in the time when the vertex is stored in the Dcel. If
 * a vertex with some ID is deleted from the Dcel, its ID can be used for some other
 * vertices that will be added to the Dcel after.
 *
 * When an element in the Dcel is created, all the links will be initialized with \c
 * nullptr value. If, for example, a cg3::Dcel::HalfEdge has its twin with value \c
 * nullptr, it means that the half edge has no twin. Before using pointer fields of the
 * Dcel elements, be careful and check if they are different from \c nullptr.
 * To delete an element from the Dcel, it is possible to use the following method :\n
 *
 * \code{.cpp}
 * d.deleteVertex(v);
 * \endcode
 *
 * In the \c deleteVertex(v) method, the vertex pointed by \c v is deleted from the Dcel.
 * Furthermore, the method sets the references to \c v to \c nullptr \e where \e they \e are
 * \e supposed \e to \e be: in all its outgoing half edges and incoming half edges. If these
 * field where setted to \c v, they will cointain \c nullptr value after \c delteVertex(v).
 * Doing any operation on \c v after the execution of \c deleteVertex(v) causes an
 * undefined behavior. The same goes for \c deleteHalfEdge(he) and \c deleteFace(f). \n
 *
 * To reset a Dcel, it is possible to use the following method:
 *
 * \code{.cpp}
 * d.clear();
 * \endcode
 *
 * # 4 Iterators
 *
 * It is possible to iterate along the elements of the Dcel using its iterators:
 *
 * \code{.cpp}
 * Dcel::VertexIterator vit;
 * Dcel::HalfEdgeIterator heit;
 * Dcel::FaceIterator fit;
 * Dcel::ConstVertexIterator cvit;
 * Dcel::ConstHalfEdgeIterator cheit;
 * Dcel::ConstFaceIterator cfit;
 * \endcode
 *
 * It is possible, for example, to iterate and modify all the vertex coordinates of the
 * Dcel \c d in the following way:\n
 *
 * \code{.cpp}
 * for (vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     v->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * }
 * \endcode
 *
 * or using the range for iterator:\n
 *
 * \code{.cpp}
 * for (Dcel::Vertex* v : d.vertexIterator()){
 *     v->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * }
 * \endcode
 *
 * Vertices, HalfEdges and Faces are stored in the Dcel using an std::vector. Ids of every
 * element of the Dcel represents their position in the vector. If an element is deleted
 * from the Dcel, its position in the vector is setted to \c nullptr. No compacting of
 * the vector is  performed, and iterators will skip automatically these positions.
 *
 * There are also iterators that allows to navigate the mesh using adjacency/incidence
 * relations between elements. For exaple, it is possible to iterate along the adjacent
 * vertices of a given vertex \c v:
 *
 * \code{.cpp}
 * Dcel::Vertex::AdjacentVertexIterator avid;
 * for (avid = v->adjacentVertexBegin(); avid != v->adjacentVertexEnd(); ++avid)
 *     (*avid)->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 * Alternatively, it is possible to use the range for:
 *
 * \code{.cpp}
 * for (Dcel::Vertex* av : v.adjacentVertexIterator())
 *     av->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 *
 *
 * The vertices will be visited in counterclockwise order (next vertex is obtained performing
 * operations of prev and then twin of the outgoing half edge of the vertex, amd then
 * toVertex). To iterate in the opposite order, it is possible to use the operator --
 * (no range for):
 *
 * \code{.cpp}
 * Dcel::Vertex::AdjacentVertexIterator avid;\n
 * for (avid = vid->adjacentVertexBegin(); avid != vid->adjacentVertexEnd(); --avid)
 *     (*avid)->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 * These iterators need to work on manifold and preferably watertight meshes, where
 * relations between elements make actually sense. If used in meshes where relations are
 * not correct, it is undefined behavior (segmentation fault, infinite loops). In these
 * cases, it is recommended to navigate manually the mesh. \n
 *
 * Some Dcel methods use these methods because they actually make sense only on manifold
 * meshes. A manifold and watertight Dcel is a Dcel that satisfies the follwing constraints:
 * - Every half hadge \c e has a twin \c t, and its twin \c t has, as twin, \c e.
 * - Every half edge has from vertex equal to the to vertex of its twin, and viceversa.
 * - Starting from an half edge \c e, a series of next operations (3 for Triangle Dcel)
 *   goes back to half edge \c e, and all the visited half edges have the same incident
 *   face. The same goes for prev operations.
 * - To vertex of an half edge corresponds to the from vertex of its next;
 * - From vertex of an half edge corresponts to the to vertex of its prev.
 * - Starting from an half edge \c e, a series of operations of twin and next goes back
 * to half edge \c e.
 * - Starting from an half edge \c e, a series of operations of prev and twin goes back
 * to half edge \c e.
 * - Two vartices with same coordinates cannot exist inside the same Dcel. \n
 * - Every vertex \c v has as outgoing half edge an half edge that has as from vertex \c v.
 * - Every face \c f has as outer half edge and inner half edges some edges that have
 * \c f as incident face.
 *
 *
 * For advanced operation on the Dcel, please see the documentation of the following classes: \n
 * - Dcel \n
 * - Dcel::Vertex \n
 * - Dcel::HalfEdge \n
 * - Dcel::Face \n
 **/

#endif // CG3_DCEL_H
