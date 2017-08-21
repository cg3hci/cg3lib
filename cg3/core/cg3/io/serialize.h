/*
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef CG3_SERIALIZE_H
#define CG3_SERIALIZE_H

#include "serializable_object.h"

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#ifdef QT_CORE_LIB
#include <QColor>
#endif //QT_CORE_LIB
#include <typeinfo>
#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif //COMMON_WITH_EIGEN
#include <array>

#include <type_traits> // To use 'std::integral_constant'.

namespace cg3 {

/**
 * \~English
 * @namespace Serializer
 *
 * @brief Please, if you can, add serialize/deserialize methods for all types you need that don't work
 * with the standard "serialize"/"deserialize" methods!
 *
 * \~Italian
 * @namespace Serializer
 * @brief Supporta la serializzazione/deserializzazione di tutti i tipi primitivi più:
 * - QColor
 * - std::string
 * - std::set<T,...> dove :
 *         T è un tipo primitivo o un SerializableObject (NON puntatore a SerializableObject)
 * - std::vector<T,...> dove :
 *         T è un tipo primitivo o un SerializableObject (NON puntatore a SerializableObject)
 * - std::list<T,...> dove :
 *         T è un tipo primitivo o un SerializableObject (NON puntatore a SerializableObject)
 * - std::map<T1,T2,...> dove:
 *         T1 è un tipo primitivo o un SerializableObject (NON puntatore a SerializableObject)
 *         T2 è un tipo primitivo o un SerializableObject (NON puntatore a SerializableObject)
 * - std::array<T,size_t,...> dove:
 *         T è un tipo primitivo o un SerializableObject (NON puntatore a SerializableObject)
 *         size_t è la dimensione dell'array
 */
namespace Serializer {

    void restore(std::ifstream& binaryFile, const std::streampos& position);

    template <typename T> void serialize(const T& obj, std::ofstream& binaryFile);

    template <typename T> bool deserialize(T& obj, std::ifstream& binaryFile);

    #ifdef QT_CORE_LIB
    void serialize(const QColor& obj, std::ofstream& binaryFile);

    bool deserialize(QColor& obj, std::ifstream& binaryFile);
    #endif

    void serialize(const std::string& str, std::ofstream& binaryFile);

    bool deserialize(std::string& str, std::ifstream& binaryFile);

    template <typename T, typename ...A> void serialize(const std::set<T, A...> &s, std::ofstream& binaryFile);

    template <typename T, typename ...A> bool deserialize(std::set<T, A...> &s, std::ifstream& binaryFile);

    template <typename ...A> void serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile);

    template <typename T, typename ...A> void serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile);

    template <typename ...A> bool deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile);

    template <typename T, typename ...A> bool deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile);

    template <typename T, typename ...A> void serialize(const std::list<T, A...> &l, std::ofstream& binaryFile);

    template <typename T, typename ...A> bool deserialize(std::list<T, A...> &l, std::ifstream& binaryFile);

    template <typename T1, typename T2, typename ...A> void serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile);

    template <typename T1, typename T2, typename ...A> bool deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile);

    #ifdef CG3_EIGEN
    template <typename T, int ...A> void serialize(const Eigen::Matrix<T, A...> &m, std::ofstream& binaryFile);

    template <typename T, int ...A> bool deserialize(Eigen::Matrix<T, A...> &m, std::ifstream& binaryFile);
    #endif //COMMON_WITH_EIGEN

    template <typename T, unsigned long int ...A> void serialize(const std::array<T, A...> &a, std::ofstream& binaryFile);

    template <typename T, unsigned long int ...A> bool deserialize(std::array<T, A...> &a, std::ifstream& binaryFile);
}

}

#include "serialize.cpp"

#endif // CG3_SERIALIZE_H
