/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_COMPARATORS_H
#define CG3_COMPARATORS_H

#include "../geometry/point.h"

namespace cg3 {

/**
 * \~English
 * @struct cmpUnorderedStdPair
 * @brief la struttura cmpUnorderedStdPair implementa un comparatore per la classe std::pair<T,T>
 *
 * It compares a couple of elements and decides if one is less than the other without taking account on the elements order.
 * It can be used if you need a set of unordered couples, where you can't have couples with inverted elements.
 *
 * Example: the couple (0,2) is not less than (2,0), and viceversa.
 *
 * Example: the couple (2,0) is less than the couple (0,3).
 *
 * Example of usage: std::set<std::pair<int, int>, cmpUnorderedStdPair<int> > set;
 * Note that the type of the elements of the pair must be the same, and must match to the comparator type.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 *
 * \~Italian
 * @struct cmpUnorderedStdPair
 * @brief The cmpUnorderedStdPair structure implements a comparator for the std::pair<T,T> class.
 *
 * Confronta una coppia di elementi e stabilisce se una è minore dell'altra senza tener conto dell'ordine
 * degli elementi.
 * Può essere utile se si vuole fare in modo che in un insieme di coppie non si possano avere due coppie
 * con gli stessi elementi invertiti.
 *
 * Esempio: La coppia (0,2) non risulta essere minore della coppia (2,0), e viceversa.
 *
 * Esempio: la coppia (2,0) risulta essere minore della coppia (0,3).
 *
 * Esempio: std::set<std::pair<int, int>, cmpUnorderedStdPair<int> > set;
 * Si noti che il tipo dei due elementi della coppia deve essere lo stesso, e deve coincidere con quello del comparator.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class T>
struct cmpUnorderedStdPair {
    bool operator()(const std::pair<T,T>& a, const std::pair<T,T>& b) const {
        T amin, bmin, amax, bmax;
        if (a.first < a.second) {
            amin = a.first;
            amax = a.second;
        }
        else {
            amin = a.second;
            amax = a.first;
        }
        if (b.first < b.second){
            bmin = b.first;
            bmax = b.second;
        }
        else {
            bmin = b.second;
            bmax = b.first;
        }
        if (amin < bmin) return true;
        else if (amin == bmin) return (amax < bmax);
        return false;
    }
};

/**
 * \~English
 * @struct cmpPointY
 * @brief The cmpPointY structure implements a comparator for the Point class using Y coordinate first.
 *
 * It defines another minus operator on Point class, ordering on the components y, x and z. It can be used, for example,
 * when you need to store Point on ordered containers like std::set or std::map, and you want to order them using the y coordinate.
 *
 * Example: std::map<Pointd, int, cmpPointY<double>> map;
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 *
 * \~Italian
 * @struct cmpPointY
 * @brief La struttura cmpPointY implementa un comparatore per classe Point usanto la coordinata Y per prima.
 *
 * È in grado di stabilire se un Point è minore di un altro o meno, ordinando rispettivamente per componente
 * y, poi x e poi z. Può essere utilizzato come parametro nel caso in cui si voglia usare un Point su
 * una struttura dati che necessita di un ordinamento.
 *
 * Esempio: std::map<Point<double>, int, cmpPointY<double>> map;
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class T>
struct cmpPointY {
    bool operator()(const Point<T>& a, const Point<T>& b) const {
        if (a == b) return false;
        if (a.y() == b.y() && a.x() == b.x()) return (a.z() < b.z());
        if (a.y() == b.y()) return (a.x() < b.x());
        return (a.y() < b.y());
    }
};

/**
 * \~English
 * @struct cmpPointZ
 * @brief The cmpPointZ structure implements a comparator for the Point class using Z coordinate first.
 *
 * It defines another minus operator on Point class, ordering on the components z, x and y. It can be used, for example,
 * when you need to store Point on ordered containers like std::set or std::map, and you want to order them using the z coordinate.
 *
 * Example: std::map<Pointd, int, cmpPointZ<double>> map;
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 *
 * \~Italian
 * @struct cmpPointZ
 * @brief La struttura cmpPointZ implementa un comparatore per classe Point usanto la coordinata Z per prima.
 *
 * È in grado di stabilire se un Point è minore di un altro o meno, ordinando rispettivamente per componente
 * z, poi x e poi y. Può essere utilizzato come parametro nel caso in cui si voglia usare un Point su
 * una struttura dati che necessita di un ordinamento.
 *
 * Esempio: std::map<Point<double>, int, cmpPointZ<double>> map;
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class T>
struct cmpPointZ {
    bool operator()(const Point<T>& a, const Point<T>& b) const {
        if (a == b) return false;
        if (a.z() == b.z() && a.x() == b.x()) return (a.y() < b.y());
        if (a.z() == b.z()) return (a.x() < b.x());
        return (a.z() < b.z());
    }
};

typedef cmpPointY<int> cmpPointiY;
typedef cmpPointY<float> cmpPointfY;
typedef cmpPointY<double> cmpPointdY;
typedef cmpPointY<double> cmpVec3Y;

typedef cmpPointZ<int> cmpPointiZ;
typedef cmpPointZ<float> cmpPointfZ;
typedef cmpPointZ<double> cmpPointdZ;
typedef cmpPointZ<double> cmpVec3Z;

}

#endif // CG3_COMPARATORS_H

