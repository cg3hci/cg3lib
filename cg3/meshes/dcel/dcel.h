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
 * @page Dcel
 * \~Italian
 * # 1 Introduzione
 * Questa libreria è stata progettata per poter sviluppare degli algoritmi su mesh tridimensionali utilizzando una struttura dati
 * comoda e funzionale, avente tutti gli strumenti necessari per poter effettuare le operazioni di navigazione di base e anche avanzata.
 * Rispetto alle strutture dati presenti nelle librerie più utilizzate (CGAL, OpenMesh), questra struttura dati permette di gestire
 * mesh composte da poligoni generici che possono avere anche buchi.
 * È organizzata per essere utilizzata mediante puntatori, in modo da avere i riferimenti diretti ad ogni oggetto si voglia manipolare,
 * e fornisce una serie funzioni e metodi che sono sviluppati per lavorare su mesh manifold e chiuse. \n
 * Non mi assumo alcuna responsabilità riguardo la correttezza del codice; tuttavia, nel caso in cui fossero trovati dei bug, per
 * favore segnalateli al mio indirizzo email (muntoni.alessandro@gmail.com) in modo tale che possano essere corretti.
 * La libreria è rilasciata sotto licenza GNU GPL.\n
 *
 *
 * # 2 Installazione
 * La Dcel è stata sviluppata utilizzando un ambiente QT per gestirne la visualizzazione in un'applicazione semplice e intuitiva,
 * tuttavia può essere anche utilizzata in modo standalone.
 * Per compilare, la Dcel richiede l'installazione di:
 * - GCC (≥ 4.8) (flag C++11);
 * - QT (≥ 5.2);
 * - Boost (≥ 1.54).
 *
 *
 * È inoltre possibile usufruire di alcune funzionalità aggiuntive nel caso in cui sia installata la libreria CGAL.
 * Tali funzionalità sono molto utili soprattutto quando si ha intenzione di gestire una mesh composta da poligoni generici.
 * In questo caso, è sufficiente aggiungere la definizione della costante letterale CGAL_DEFINED per abilitare tali funzionalità.
 * Nel caso si voglia utilizzare anche il visualizzatore che permette di visualizzare e interagire con la Dcel mediante le classi
 * DrawableDcel e PickableDcel, è necessario installare anche la libreria libQGLViewer.
 *
 *
 * # 3 Overview
 * La Double-Connected Edge-List (Dcel)  è una struttura dati che si occupa di implementare e gestire gli elementi necessari a modellare
 * una mesh tridimensionale, in modo tale che tutte le informazioni di adiacenza e incidenza tra le componenti siano accessibili in tempo
 * costante. Una Dcel è composta da:
 * - Vertici (Dcel::Vertex);
 * - Mezzi Spigoli (Dcel::HalfEdge);
 * - Facce (Dcel::Face).
 *
 *
 * I Vertici sono composti da:
 * - Coordinate: punti definiti in uno spazio tridimensionale (vedi classe Point);
 * - Vettore Normale: solitamente è definito come la media delle normali alle facce incidenti sul vertice;
 * - Incident Half Edge: puntatore ad uno degli half edge incidenti sul vertice;
 * - Cardinalità: numero degli spigoli (non degli half edge!) incidenti sul vertice.
 * - Flag: valore associato alla faccia assegnabile a piacimento dall'utente.
 *
 *
 * Gli Half Edge sono composti da:
 * - From Vertex: puntatore al vertice da cui l'half edge è uscente;
 * - To Vertex: puntatore al vertice su cui l'half edge è entrante;
 * - Twin Half Edge: puntatore all'half edge gemello;
 * - Previous Half Edge: puntatore all'half edge precedente;
 * - Next Half Edge: puntatore all'half edge successivo;
 * - Incident Face: puntatore alla faccia incidente all'half edge.
 * - Flag: valore associato alla faccia assegnabile a piacimento dall'utente.
 *
 *
 * Le Facce sono composte da:
 * - Half Edge Esterno: puntatore ad uno degli half edge sul bordo esterno della faccia;
 * - Lista di Half Edge Interni: per ogni buco presente nella faccia (se ce ne sono), vi è il puntatore ad uno degli half edge sul suo bordo interno.
 * - Vettore Normale: vettore normale alla faccia;
 * - Area: area della faccia;
 * - Colore: colore associato alla faccia;
 * - Flag: valore associato alla faccia assegnabile a piacimento dall'utente.
 *
 *
 * Il compito della classe Dcel è quello di mettere insieme tutti i componenti, modellarne le relazioni di adiacenza e topologia sulla
 * base di quanto specificato dall'utente, rendere disponibili, quando necessario, le informazioni relative a un singolo componente (sia
 * esso un vertice, un half-edge o una faccia) e consentirne la modifica ed eventualmente la rimozione.
 * Il modello di ispirazione è quello classico, presentato anche in Computational  Geometry: Algorithms and Applications; i vertici, gli
 * half-edge e le facce sono inserite in tre array separati (non accessibili direttamente), e i collegamenti tra elementi appartenenti
 * agli array (es: un vertice che funge da origine per l'half-edge) sono gestiti utilizzando puntatori.
 * Le operazioni di inserimento, modifica e cancellazione di vertici, half edge e facce sono effettuate in tempo costante.
 *
 *
 * # 4 Come usare la Dcel
 *
 * In questa sezione viene data una piccola introduzione all'utilizzo della Dcel. Verranno fatti degli esempi di utilizzo sui vertici, ma
 * questi potranno poi essere estesi anche a half edge e facce. \n
 * Una istanza di una Dcel può essere semplicemente creata come segue:\n
 *
 * \code{.cpp}
 * Dcel d;
 * \endcode
 *
 * Una mesh può essere caricata da file:
 *
 * \code{.cpp}
 * d.loadFromObjFile("mesh.obj");
 * d.loadFromPlyFile("mesh.ply");
 * \endcode
 *
 * e successivamente salvata su file:
 *
 * \code{.cpp}
 * d.saveOnObjFile("mesh.obj");
 * d.saveOnPlyFile("mesh.ply");
 * \endcode
 *
 * Questi formati sono supportati in modalità testuale.
 * Vi è anche la possibilità di salvare e caricare una Dcel utilizzando un formato appositamente creato per la stessa.
 *
 * \code{.cpp}
 * d.loadFromDcelFile("mesh.dcel");
 * //some operations
 * d.saveOnDcelFile("newmesh.dcel");
 * \endcode
 *
 * È anche possibile caricare manualmente tutte le componenti nella Dcel:
 *
 * \code{.cpp}
 * Dcel::Vertex* v = d.addVertex(); // v è un puntatore al vertice appena inserito nella Dcel
 * v->setCoordinate(Pointd(0.0, 0.1, 0.2)); // setto le coordinate del vertice
 * Dcel::HalfEdge* he = d.addHalfEdge(); // he è un puntatore all'half edge appena inserito nella Dcel
 * he->setFromVertex(v); // v diventa il from vertex di he
 * Dcel::Face* f = d.addFace(); // f è un puntatore alla faccia appena inserita nella Dcel
 * f->setOuterHalfEdge(he); // he diventa l'half edge sul bordo esterno della faccia
 * he->setFace(f); // f diventa la faccia incidente all'half edge he
 * \endcode
 *
 * Nel momento in cui viene eseguito il metodo \c add_vertex() , viene inserito un vertice nella Dcel. Viene restituito un \c Dcel::Vertex* ,
 * ossia un puntatore al vertice presente nella Dcel. Dal momento in cui viene inserito, per poter manipolare il vertice presente sulla Dcel
 * bisognerà usare il puntatore \c v . Ovviamente, il discorso è invariato anche per quanto riguarda gli half edge e le facce.
 * Al momento dell'inserimento di un oggetto nella Dcel viene assegnato ad esso anche un ID univoco e non modificabile che permette una facile identificazione
 * delle componenti della Dcel  da parte dell'utente. Tale ID è valido solamente nel periodo in cui il vertice si trova nella Dcel. Ciò significa che,
 * nel caso in cui il vertice venga eliminato dalla Dcel, il suo ID potrà essere riutilizzato per altri vertici che verranno inseriti.
 *
 * Si noti come è necessario utilizzare il puntatore di un oggetto già inserito precedentemente nella Dcel per settare i campi degli oggetti Dcel::Vertex, Dcel::HalfEdge e Dcel::Face.
 * Quando viene creato un oggetto \c Dcel::Vertex , \c Dcel::HalfEdge o \c Dcel::Face , le sue componenti che dovrebbero fare riferimento ad
 * altri oggetti presenti nella Dcel (per esempio la componente \c incidentHalfEdge nella classe \c Dcel::Vertex ) vengono inizializzate a
 * \c nullptr e dovrebbero essere modificate non appena si possiede il riferimento all'oggetto stesso nella Dcel. Nel momento in cui si eseguono dei
 * metodi che necessitano di queste componenti, nel caso in cui le componenti stesse siano ancora settate a \c nullptr o contengano degli elementi non
 * disponibili (per esempio, elementi eliminati dalla Dcel senza averne aggiornato anche i riferimenti), allora si genera un errore di \e Segmentation \e Fault,
 * che non può essere gestito.\n
 * Per l'eliminazione di un elemento della Dcel, è disponibile il metodo:\n
 *
 * \code{.cpp}
 * d.deleteVertex(v);
 * \endcode
 *
 * Nel metodo \c deleteVertex(v) viene eliminato il vertice puntato da \c v dalla Dcel (viene gestita automaticamente l'allocazione dinamica
 * dell'oggetto). Inoltre, il metodo va a sostituire i riferimenti a v con \c nullptr \e dove \e è \e supposto \e che \e ci \e siano.
 * Per esempio, se stiamo eliminando \c v, il metodo controlla se è presente un riferimento a \c v in tutti i suoi
 * half edge uscenti (campo \c fromVertex ) e in tutti i sui half edge entranti (campo \c toVertex). Se questi campi contengono
 * \c v, allora vengono settati a nullptr.
 * Effettuare una qualsiasi operazione su \c v dopo la \c deleteVertex() comporterà
 * un errore di Segmentation Fault e di conseguenza un crash dell'applicazione.\n
 *
 * È possibile inoltre resettare una Dcel:
 *
 * \code{.cpp}
 * d.reset();
 * \endcode
 *
 * Il metodo reset si occupa di eliminare tutte le componenti della Dcel. Alla fine di tale metodo, \c d conterrà 0 vertici, 0 half edge e 0 facce.
 *
 *
 * # 5 Iteratori
 *
 * È possibile scorrere gli elementi della Dcel utilizzando gli iteratori (di cui vi sono anche i relativi iteratori \c const):\n
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
 * Si possono, per esempio, scorrere e modificare tutte le coordinate dei vertici della Dcel nel seguente modo:\n
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
 * L'insieme di vertici (come anche quello degli half edge e delle facce) è gestito mediante un array. L'id di ogni vertice rappresenta la posizione
 * stessa del vertice all'interno dell'array. Non è possibile tuttavia ciclare direttamente su questo array per via della gestione dell'eliminazione
 * degli elementi. Nel momento in cui in vertice viene eliminato, la sua posizione verrà settata nullptr. Gli iteratori permettono di saltare automaticamente
 * queste posizioni.
 *
 * Vi sono inoltre degli iteratori che permettono di navigare la mesh utilizzando le relazioni di adiacenza/incidenza degli elementi.
 * Per esempio, per scorrere e modificare tutti i vertici adiacenti a \c vid :\n
 *
 * \code{.cpp}
 * Dcel::Vertex::AdjacentVertexIterator avid;
 * for (avid = vid->adjacentVertexBegin(); avid != vid->adjacentVertexEnd(); ++avid)
 *     (*avid)->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 * I vertici verranno visitati ordinatamente, in base al senso degli half edge sulle facce (senso antiorario). Nel caso si voglia scorrere i vertici in senso opposto, è possibile
 * scrivere la seguente porzione di codice:\n
 *
 * \code{.cpp}
 * Dcel::Vertex::AdjacentVertexIterator avid;\n
 * for (avid = vid->adjacentVertexBegin(); avid != vid->adjacentVertexEnd(); --avid)
 *     (*avid)->setCoordinate(Pointd(0.1, 0.2, 0.3));
 * \endcode
 *
 * Questi iteratori necessitano di lavorare su una mesh manifold e chiusa. Infatti, gli iteratori non fanno altro che utilizzare i riferimenti contenuti in Dcel::Vertex, Dcel::HalfEdge e Dcel::Face.
 * In caso di mesh non-manifold o non chiusa, è possibile che molti riferimenti rimangano settati a nullptr. Nel momento in cui vi sono degli errori sui riferimenti (soprattutto nelle relazioni
 * di prev, next e twin degli half edge), o la Dcel non è utilizzata correttamente, è possibile che gli iteratori causino Segmentation Fault o anche loop infiniti. Se, per esempio,
 * si deve lavorare con mesh non chiuse, è consigliabile navigare manualmente la Dcel senza utilizzare gli iteratori (che non sono in grado di gestire tutti i possibili casi
 * che possono verificarsi in mesh di questo tipo).\n
 * Talvolta questi iteratori sono usati anche all'interno di alcuni metodi presenti nella Dcel, in quanto sono dei metodi pensati per lavorare su mesh chiuse e manifold. \n
 * Per Dcel chiusa e manifold, si intende una Dcel che rispetta le seguenti caratteristiche:
 * - Ogni half edge \c e ha un twin \c t, e il suo twin \c t ha come twin l'half edge \c e.
 * - Ogni half edge ha from vertex uguale al to vertex del suo twin, e viceversa.
 * - Partendo da un half edge \c e, una serie di operazioni di next (3 se si ha una Dcel di triangoli) riporta all'half edge \c e, tutti questi half edge hanno la stessa faccia incidente.
 * - Partendo da un half edge \c e, una serie di operazioni di prev (3 se si ha una Dcel di triangoli) riporta all'half edge \c e, tutti questi half edge hanno la stessa faccia incidente.
 * - Il to vertex di un half edge corrisponde al from vertex del suo next;
 * - Il from vertex di un half edge corrisponde al to vertex del suo prev.
 * - Partendo da un half edge \c e, una serie di operazioni di twin e next riporta all'half edge \c e.
 * - Partendo da un half edge \c e, una serie di operazioni di prev e twin riporta all'half edge \c e.
 * - Non esistono due vertici che hanno le stesse coordinate. \n
 * - Ogni vertice \c v ha come half edge uscente un half edge che ha come from vertex \c v.
 * - Ogni faccia \c f ha come outer half edge e inner half edges degli edge che hanno \c f come faccia incidente.
 *
 *
 * Per le funzioni avanzate della Dcel, vedere la documentazione relativa alle classi: \n
 * - Dcel \n
 * - Dcel::Vertex \n
 * - Dcel::HalfEdge \n
 * - Dcel::Face \n
 *
 *
 * \~English
 * # 1 Introduction
 * This library has been designed to allow the developemento of algorithms on three-dimensional meshes using a data structure
 * preactical and easy, having all the necessary tools to make all the basic and advanced operations of navigation on the mesh.
 *
 **/

#endif // CG3_DCEL_H
