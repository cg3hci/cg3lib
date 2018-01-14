/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "utils.h"

namespace cg3 {

/**
     * \~English
     * @brief This function computes an equality between two parameters considering an epsilon offset
     * @param[in] x: first parameter
     * @param[in] v: second parameter
     * @param[in] epsilon: offset for equality, default value 0.0000001
     * @return true if the two parameters are equals on the epsilon interval, false otherwise
     *
     * \~Italian
     * @brief Questa funzione calcola l'uguaglianza tra due parametri tenendo conto di un possibile offset pari a epsilon
     * @param[in] x: primo parametro
     * @param[in] v: secondo parametro
     * @param[in] epsilon: offset di uguaglianza, valore di default 0.0000001
     * @return true se i due parametri sono uguali a meno del valore di epsilon, falso altrimenti
     */
template <typename T>
inline bool epsilonEqual(T x, T v, double epsilon) {
    if (std::abs(x-v) < epsilon) return true;
    return false;
}

/**
 * \~English
 * @brief This function computes an equality between two Points considering an epsilon offset
 * @param[in] x: first Point parameter
 * @param[in] v: second Point parameter
 * @param[in] epsilon: offset for equality, default value 0.0000001
 * @return true if the two Points are equals on the epsilon interval, false otherwise
 *
 * \~Italian
 * @brief Questa funzione calcola l'uguaglianza tra due Point tenendo conto di un possibile offset pari a epsilon
 * @param[in] x: primo parametro Point
 * @param[in] v: secondo parametro Point
 * @param[in] epsilon: offset di uguaglianza, valore di default 0.0000001
 * @return true se i due Point sono uguali a meno del valore di epsilon, falso altrimenti
 */
template <typename T>
inline bool epsilonEqual(const Point<T> &x, const Point<T> &v, double epsilon) {
    if ((epsilonEqual(x.x(), v.x(), epsilon)) && (epsilonEqual(x.y(), v.y(), epsilon)) && (epsilonEqual(x.z(), v.z(), epsilon))) return true;
    else return false;
}

/**
 * \~English
 * @brief This function computes an equality between two Point2D considering an epsilon offset
 * @param[in] x: first Point parameter
 * @param[in] v: second Point parameter
 * @param[in] epsilon: offset for equality, default value 0.0000001
 * @return true if the two Points are equals on the epsilon interval, false otherwise
 *
 * \~Italian
 * @brief Questa funzione calcola l'uguaglianza tra due Point2D tenendo conto di un possibile offset pari a epsilon
 * @param[in] x: primo parametro Point2D
 * @param[in] v: secondo parametro Point2D
 * @param[in] epsilon: offset di uguaglianza, valore di default 0.0000001
 * @return true se i due Point2D sono uguali a meno del valore di epsilon, falso altrimenti
 */
template <typename T>
inline bool epsilonEqual(const Point2D<T> &x, const Point2D<T> &v, double epsilon) {
    if ((epsilonEqual(x.x(), v.x(), epsilon)) && (epsilonEqual(x.y(), v.y(), epsilon))) return true;
    else return false;
}



inline double truncate(double d, unsigned int numberOfDecimalDigitsToKeep) {
    int tmp = (int)((10*numberOfDecimalDigitsToKeep)*d);
    if (numberOfDecimalDigitsToKeep > 0)
        return (double) tmp / (10*numberOfDecimalDigitsToKeep);
    else return d;
}



template <typename T>
inline bool isInBounds(const T& value, const T& low, const T& high) {
    return !(value < low) && !(high < value);
}

template <typename T, typename R, typename Comparator>
inline bool isInBounds(const T& value, const R& low, const R& high, Comparator comp) {
    return !comp(value, low) && !comp(high, value);
}


template <typename T, typename AdjComparator>
inline std::map<T, Color> smartColoring(const std::vector<T> &elements, AdjComparator comp, const std::vector<Color> &colors) {
    std::set<T> colored;
    std::map<T, Color> colorMap;
    for (const T i : elements){
        if (colored.find(i) == colored.end()){
            std::set<Color> adjColors;
            std::set<T> adjacences = comp.getAdjacences(i);
            for (T adj : adjacences){
                if (colored.find(adj) != colored.end())
                    adjColors.insert(colorMap[adj]);
            }

            Color color;
            bool finded = false;
            for (unsigned int k = 0; k < colors.size() && !finded; k++){
                if (adjColors.find(colors[k]) == adjColors.end()){
                    finded = true;
                    color = colors[k];
                }
            }
            if (finded){
                colorMap[i] = color;
                colored.insert(i);
            }
            else
                colorMap[i] = Color(0,0,0);
        }
    }
    return colorMap;
}

/**
 * @brief typeName
 * Returns the type of T as a std::string
 *
 * Example.\n
 * \code{.cpp}
 * int i;
 * std::cout << "Type of i is " << typeName<decltype(i)>() << "\n";
 * \endcode
 *
 * @link https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
 * @return the type of T as a std::string
 */
template<typename T>
inline std::string typeName(bool specifyIfConst, bool specifyIfVolatile, bool specifyIfReference) {
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own(
    #ifndef _MSC_VER
                    abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
    #else
                    nullptr,
    #endif
                    std::free);
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value && specifyIfConst)
        r += " const";
    if (std::is_volatile<TR>::value && specifyIfVolatile)
        r += " volatile";
    if (specifyIfReference){
        if (std::is_lvalue_reference<T>::value)
            r += "&";
        else if (std::is_rvalue_reference<T>::value)
            r += "&&";
    }
    return r;
}

}
