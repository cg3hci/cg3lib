#ifndef CG3_SERIALIZE_H
#define CG3_SERIALIZE_H

#include "serializable_object.h"

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <typeinfo>
#include <type_traits> // To use 'std::integral_constant'.
#ifdef QT_CORE_LIB
#include <QColor>
#endif //QT_CORE_LIB
#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif //CG3_WITH_EIGEN


namespace cg3 {

/**
 * \~English
 * @namespace Serializer
 *
 * @brief
 * The Serializer namespace contains some functions for serialization/deserialization of standard
 * classes (vectors, sets, maps, etc).
 *
 * Please, if you can, add serialize/deserialize methods for all types you need that don't work
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

    std::streampos getPosition(std::ifstream& binaryFile);

    void restorePosition(std::ifstream& binaryFile, const std::streampos& position);

    template <typename T> void serialize(const T& obj, std::ofstream& binaryFile);

    template <typename T> void deserialize(T& obj, std::ifstream& binaryFile);

    template <typename... Args> void serializeObjectAttributes(const std::string& s, std::ofstream& binaryFile, const Args&... args);

    template <typename... Args> void deserializeObjectAttributes(const std::string& s, std::ifstream& binaryFile, Args&... args);

    #ifdef QT_CORE_LIB
    void serialize(const QColor& obj, std::ofstream& binaryFile);

    void deserialize(QColor& obj, std::ifstream& binaryFile);
    #endif

    void serialize(const char * str, std::ofstream& binaryFile);

    void serialize(const std::string& str, std::ofstream& binaryFile);

    void deserialize(std::string& str, std::ifstream& binaryFile);

    template <typename T1, typename T2> void serialize(const std::pair<T1, T2>& p, std::ofstream& binaryFile);

    template <typename T1, typename T2> void deserialize(std::pair<T1, T2>& p, std::ifstream& binaryFile);

    template <typename T, typename ...A> void serialize(const std::set<T, A...> &s, std::ofstream& binaryFile);

    template <typename T, typename ...A> void deserialize(std::set<T, A...> &s, std::ifstream& binaryFile);

    template <typename ...A> void serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile);

    template <typename T, typename ...A> void serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile);

    template <typename ...A> void deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile);

    template <typename T, typename ...A> void deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile);

    template <typename T, typename ...A> void serialize(const std::list<T, A...> &l, std::ofstream& binaryFile);

    template <typename T, typename ...A> void deserialize(std::list<T, A...> &l, std::ifstream& binaryFile);

    template <typename T1, typename T2, typename ...A> void serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile);

    template <typename T1, typename T2, typename ...A> void deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile);

    #ifdef CG3_WITH_EIGEN
    template <typename T, int ...A> void serialize(const Eigen::Matrix<T, A...> &m, std::ofstream& binaryFile);

    template <typename T, int ...A> void deserialize(Eigen::Matrix<T, A...> &m, std::ifstream& binaryFile);
    #endif //CG3_WITH_EIGEN

    template <typename T, unsigned long int ...A> void serialize(const std::array<T, A...> &a, std::ofstream& binaryFile);

    template <typename T, unsigned long int ...A> void deserialize(std::array<T, A...> &a, std::ifstream& binaryFile);

    namespace internal {
        template <typename T>
        std::string typeName(bool specifyIfConst = true, bool specifyIfVolatile = true, bool specifyIfReference = true);

        void serializeAttribute(std::ofstream& binaryFile);
        template<typename T, typename... Args> void serializeAttribute(std::ofstream& binaryFile, const T& t, const Args&... args);

        void deserializeAttribute(std::ifstream& binaryFile);
        template<typename T, typename... Args> void deserializeAttribute(std::ifstream& binaryFile, T& t, Args&... args);
    }

}

}

#include "serialize.tpp"

#endif // CG3_SERIALIZE_H
