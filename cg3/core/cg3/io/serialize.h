/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SERIALIZE_H
#define CG3_SERIALIZE_H

#include "serializable_object.h"

#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <typeinfo>
#include <type_traits> // To use 'std::integral_constant'.

namespace cg3 {

    template <typename... Args>
    void serializeObjectAttributes(const std::string& s, std::ofstream& binaryFile, const Args&... args);

    template <typename... Args>
    void deserializeObjectAttributes(const std::string& s, std::ifstream& binaryFile, Args&... args);

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
 */
namespace serializer {

    std::streampos getPosition(std::ifstream& binaryFile);

    void restorePosition(std::ifstream& binaryFile, const std::streampos& position);

    template <typename T>
    void serialize(const T& obj, std::ofstream& binaryFile, typename std::enable_if<std::is_pointer<T>::value >::type* = 0);

    template <typename T>
    void serialize(const T& obj, std::ofstream& binaryFile, typename std::enable_if<!std::is_pointer<T>::value >::type* = 0);

    template <typename T>
    void deserialize(T& obj, std::ifstream& binaryFile, typename std::enable_if<std::is_pointer<T>::value >::type* = 0);

    template <typename T>
    void deserialize(T& obj, std::ifstream& binaryFile, typename std::enable_if<!std::is_pointer<T>::value >::type* = 0);

    void serialize(const char * str, std::ofstream& binaryFile);

    void serialize(const std::string& str, std::ofstream& binaryFile);

    void deserialize(std::string& str, std::ifstream& binaryFile);

    template <typename T1, typename T2>
    void serialize(const std::pair<T1, T2>& p, std::ofstream& binaryFile);

    template <typename T1, typename T2>
    void deserialize(std::pair<T1, T2>& p, std::ifstream& binaryFile);

    template <typename T, typename ...A>
    void serialize(const std::set<T, A...> &s, std::ofstream& binaryFile);

    template <typename T, typename ...A> void
    deserialize(std::set<T, A...> &s, std::ifstream& binaryFile);

    template <typename T, typename ...A>
    void serialize(const std::unordered_set<T, A...> &s, std::ofstream& binaryFile);

    template <typename T, typename ...A> void
    deserialize(std::unordered_set<T, A...> &s, std::ifstream& binaryFile);

    template <typename ...A> void
    serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile);

    template <typename T, typename ...A> void
    serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile);

    template <typename ...A> void
    deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile);

    template <typename T, typename ...A> void
    deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile);

    template <typename T, typename ...A> void
    serialize(const std::list<T, A...> &l, std::ofstream& binaryFile);

    template <typename T, typename ...A> void
    deserialize(std::list<T, A...> &l, std::ifstream& binaryFile);

    template <typename T1, typename T2, typename ...A>
    void serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile);

    template <typename T1, typename T2, typename ...A>
    void deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile);

    template <typename T, unsigned long int ...A>
    void serialize(const std::array<T, A...> &a, std::ofstream& binaryFile);

    template <typename T, unsigned long int ...A>
    void deserialize(std::array<T, A...> &a, std::ifstream& binaryFile);

    namespace internal {
        template <typename T>
        std::string typeName(bool specifyIfConst = true, bool specifyIfVolatile = true, bool specifyIfReference = true);

        void serializeAttribute(std::ofstream& binaryFile);

        template<typename T, typename... Args>
        void serializeAttribute(std::ofstream& binaryFile, const T& t, const Args&... args);

        void deserializeAttribute(std::ifstream& binaryFile);

        template<typename T, typename... Args>
        void deserializeAttribute(std::ifstream& binaryFile, T& t, Args&... args);
    }

}

}

#include "serialize_eigen.h"
#include "serialize_qt.h"

#include "serialize.tpp"

#endif // CG3_SERIALIZE_H
