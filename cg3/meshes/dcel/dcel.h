/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Andreas Scalas (andreasscalas@tiscali.it)
 */

#ifndef CG3_DCEL_H
#define CG3_DCEL_H

#include "dcel_face_iterators.h"
#include "dcel_vertex_iterators.h"
#include "dcel_iterators.h"

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
 * d.loadFromObjFile("mesh.obj");
 * d.loadFromPlyFile("mesh2.ply");
 * \endcode
 *
 * A Dcel can be also stored on file, using methods for the supported formats:
 *
 * \code{.cpp}
 * d.saveOnObjFile("mesh.obj");
 * d.saveOnPlyFile("mesh.ply");
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
 * cg3::Dcel::Vertex* v = d.getVertex(12); // v is a pointer to the vertex with ID = 12
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
 * Nel metodo \c deleteVertex(v) viene eliminato il vertice puntato da \c v dalla Dcel
 * (viene gestita automaticamente l'allocazione dinamica dell'oggetto). Inoltre, il metodo
 * va a sostituire i riferimenti a v con \c nullptr \e dove \e è \e supposto \e che \e ci
 * \e siano. Per esempio, se stiamo eliminando \c v, il metodo controlla se è presente un
 * riferimento a \c v in tutti i suoi half edge uscenti (campo \c fromVertex ) e in tutti
 * i sui half edge entranti (campo \c toVertex). Se questi campi contengono \c v, allora
 * vengono settati a nullptr. Effettuare una qualsiasi operazione su \c v dopo la
 * \c deleteVertex() comporterà un errore di Segmentation Fault e di conseguenza un crash
 * dell'applicazione.\n
 *
 * È possibile inoltre resettare una Dcel:
 *
 * \code{.cpp}
 * d.clear();
 * \endcode
 *
 * Il metodo reset si occupa di eliminare tutte le componenti della Dcel. Alla fine di
 * tale metodo, \c d conterrà 0 vertici, 0 half edge e 0 facce.
 *
 *
 * # 4 Iterators
 *
 * È possibile scorrere gli elementi della Dcel utilizzando gli iteratori (di cui vi sono
 * anche i relativi iteratori \c const):\n
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
 * Si possono, per esempio, scorrere e modificare tutte le coordinate dei vertici della
 * Dcel nel seguente modo:\n
 *
 * \code{.cpp}
 * for (vit = d.vertexBegin(); vit != d.vertexEnd(); ++vit){
 *     Dcel::Vertex* v = *vit;
 *     v->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * }
 * \endcode
 *
 * oppure utilizzando il for compatto:\n
 *
 * \code{.cpp}
 * for (Dcel::Vertex* v : d.vertexIterator()){
 *     v->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * }
 * \endcode
 *
 * L'insieme di vertici (come anche quello degli half edge e delle facce) è gestito
 * mediante un array. L'id di ogni vertice rappresenta la posizione stessa del vertice
 * all'interno dell'array. Non è possibile tuttavia ciclare direttamente su questo array
 * per via della gestione dell'eliminazione degli elementi. Nel momento in cui in vertice
 * viene eliminato, la sua posizione verrà settata nullptr. Gli iteratori permettono di
 * saltare automaticamente queste posizioni.
 *
 * Vi sono inoltre degli iteratori che permettono di navigare la mesh utilizzando le
 * relazioni di adiacenza/incidenza degli elementi.
 * Per esempio, per scorrere e modificare tutti i vertici adiacenti a \c vid :\n
 *
 * \code{.cpp}
 * Dcel::Vertex::AdjacentVertexIterator avid;
 * for (avid = vid->adjacentVertexBegin(); avid != vid->adjacentVertexEnd(); ++avid)
 *     (*avid)->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 * I vertici verranno visitati ordinatamente, in base al senso degli half edge sulle facce
 * (senso antiorario). Nel caso si voglia scorrere i vertici in senso opposto, è possibile
 * scrivere la seguente porzione di codice:\n
 *
 * \code{.cpp}
 * Dcel::Vertex::AdjacentVertexIterator avid;\n
 * for (avid = vid->adjacentVertexBegin(); avid != vid->adjacentVertexEnd(); --avid)
 *     (*avid)->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 * Questi iteratori necessitano di lavorare su una mesh manifold e chiusa. Infatti, gli
 * iteratori non fanno altro che utilizzare i riferimenti contenuti in Dcel::Vertex,
 * Dcel::HalfEdge e Dcel::Face.
 * In caso di mesh non-manifold o non chiusa, è possibile che molti riferimenti rimangano
 * settati a nullptr. Nel momento in cui vi sono degli errori sui riferimenti
 * (soprattutto nelle relazioni di prev, next e twin degli half edge), o la Dcel non è
 * utilizzata correttamente, è possibile che gli iteratori causino Segmentation Fault o
 * anche loop infiniti. Se, per esempio, si deve lavorare con mesh non chiuse, è
 * consigliabile navigare manualmente la Dcel senza utilizzare gli iteratori (che non sono
 * in grado di gestire tutti i possibili casi che possono verificarsi in mesh di questo
 * tipo).\n
 * Talvolta questi iteratori sono usati anche all'interno di alcuni metodi presenti nella
 * Dcel, in quanto sono dei metodi pensati per lavorare su mesh chiuse e manifold. \n
 * Per Dcel chiusa e manifold, si intende una Dcel che rispetta le seguenti
 * caratteristiche:
 * - Ogni half edge \c e ha un twin \c t, e il suo twin \c t ha come twin l'half edge \c e.
 * - Ogni half edge ha from vertex uguale al to vertex del suo twin, e viceversa.
 * - Partendo da un half edge \c e, una serie di operazioni di next (3 se si ha una Dcel
 * di triangoli) riporta all'half edge \c e, tutti questi half edge hanno la stessa faccia
 * incidente.
 * - Partendo da un half edge \c e, una serie di operazioni di prev (3 se si ha una Dcel
 * di triangoli) riporta all'half edge \c e, tutti questi half edge hanno la stessa
 * faccia incidente.
 * - Il to vertex di un half edge corrisponde al from vertex del suo next;
 * - Il from vertex di un half edge corrisponde al to vertex del suo prev.
 * - Partendo da un half edge \c e, una serie di operazioni di twin e next riporta
 * all'half edge \c e.
 * - Partendo da un half edge \c e, una serie di operazioni di prev e twin riporta
 * all'half edge \c e.
 * - Non esistono due vertici che hanno le stesse coordinate. \n
 * - Ogni vertice \c v ha come half edge uscente un half edge che ha come from vertex \c v.
 * - Ogni faccia \c f ha come outer half edge e inner half edges degli edge che hanno
 * \c f come faccia incidente.
 *
 *
 * Per le funzioni avanzate della Dcel, vedere la documentazione relativa alle classi: \n
 * - Dcel \n
 * - Dcel::Vertex \n
 * - Dcel::HalfEdge \n
 * - Dcel::Face \n
 **/


#endif // CG3_DCEL_H
