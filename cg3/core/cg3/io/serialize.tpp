/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "serialize.h"

#include <exception>
#include <memory>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif

namespace cg3 {

/**
 * @brief serializeObjectAttributes
 *
 * Allows an easy serialization of a series of arguments in a binary file.
 * The arguments will be serialized in the order they are passed, after the first input string,
 * which is used as id.
 *
 * @param[in] s: a string which discriminates the set of arguments which are going to be serialized.
 * @param[in] binaryFile: the file in which the arguments are going to be serialized
 * @param[in] args: a variable number of arguments of different types
 */
template<typename... Args>
inline void serializeObjectAttributes(const std::string& s, std::ofstream& binaryFile, const Args&... args) {
    serializer::serialize(s, binaryFile);
    serializer::internal::serializeAttribute(binaryFile, args...);
}

/**
 * @brief deserializeObjectAttributes
 *
 * Allows an easy deserialization of a series of arguments from a binary file.
 * The arguments will be deserialized in the order they are passed, after the first input string,
 * which is deserialized and checked as id.
 * If the data deserialized doesn't match with the arguments passed, an exception is thrown
 * and the initial position of the binary file restored as it was when the function was called.
 * The position of the binary file will change only if all arguments will deserialized correctly.
 *
 * @param[in] s: a string which should match with the first deserialized string on the file.
 * @param[in] binaryFile: the file from which the arguments are going to be deserialized
 * @param[out] args: a variable number of arguments of different types
 * @throws std::ios_base::failure exception if the arguments don't match with the data
 * deserialized from the binary file.
 */
template<typename... Args>
inline void deserializeObjectAttributes(const std::string& s, std::ifstream& binaryFile, Args&... args) {
    std::string tmp;
    std::streampos begin = binaryFile.tellg();
    try {

        serializer::deserialize(tmp, binaryFile);
        if (tmp != s)
            throw std::ios_base::failure("Mismatching String: " + tmp + " != " + s);
        serializer::internal::deserializeAttribute(binaryFile, args...);

    }
    catch(std::ios_base::failure& e){
        serializer::restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom ") + s);
    }
    catch(...){
        serializer::restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of " + s);
    }
}

/**
 * @brief Serializer::getPosition
 * @param[in] binaryFile
 * @return the position of the stream
 */
inline std::streampos serializer::getPosition(std::ifstream& binaryFile) {
    return binaryFile.tellg();
}

/**
 * @brief Serializer::restorePosition
 * restores the current position of the stream
 * @param[out] binaryFile: the file with the new position
 * @param[in] position: the desired position on the file
 */
inline void serializer::restorePosition(std::ifstream& binaryFile, const std::streampos& position) {
    binaryFile.clear();
    binaryFile.seekg(position);
}

/**
 * \~English
 * @brief Serializer::serialize
 *
 * This function allows to serialize on a std::ofstream opened in binary mode:
 *
 * - All primitive types;
 * - All classes that have correctly implemented the abstract class SerializableObject
 *
 * For pointers, see the dedicated specialization.
 * This method will be called if there is not a specialized "serialize" function for the type of object
 * that you are passing as first parameter (see specialized methods).
 *
 * @param[in] obj: object which we want serialize
 * @param[in] binaryFile: std::ofstream opened in binary mode on the file where we want to serialize
 */
template <typename T>
inline void serializer::serialize(const T& obj, std::ofstream& binaryFile, typename std::enable_if<!std::is_pointer<T>::value >::type*){
    #ifndef CG3_IGNORE_TYPESAFE_SERIALIZATION_CHECK
    static_assert(std::is_base_of<SerializableObject, T>::value || std::is_fundamental<T>::value, "Please provide cg3::Serializer::serialize specialization for this type!");
    #endif
    if (std::is_base_of<SerializableObject, T>::value){
        SerializableObject* o =(SerializableObject*) &obj;
        o->serialize(binaryFile);
    }
    else{ //primitive type serialization
        binaryFile.write(reinterpret_cast<const char*>(&obj), sizeof(T));
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 *
 * This function allows to serialize on a std::ofstream opened in binary mode:
 *
 * - All pointers to primitive types;
 * - All pointers classes that have correctly implemented the abstract class SerializableObject
 *
 * It will serialize automatically the pointed object saving also the fact that it was a pointer to the object.
 * This method will be called if there is not a specialized "serialize" function for the type of pointer
 * that you are passing as first parameter (see specialized methods).
 *
 * @warning this method is meant to be used only for pointers that are "unique". The deserialization of a pointer will result in a
 * new dynamically allocated object. Example: if you pass three times a pointer to the same object, in the file will be stored three different
 * istances of that object. The deserialization will create three different istances to the object and therefore three different pointers.
 * @param[in] obj: object which we want serialize
 * @param[in] binaryFile: std::ofstream opened in binary mode on the file where we want to serialize
 */
template <typename T>
inline void serializer::serialize(const T& obj, std::ofstream& binaryFile, typename std::enable_if<std::is_pointer<T>::value >::type*){
    if (obj == nullptr)
        serialize("cg3nullptr", binaryFile);
    else {
        serialize("cg3p", binaryFile);
        serialize(*obj, binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 *
 * This function allows to deserialize on a std::ifstream opened in binary mode:
 *
 * - All primitive types
 * - All classes that have correctly implemented the abstract class SerializableObject
 *
 * For pointers, see the dedicated specialization.
 * All you have to do is to call all the deserialize methods in the same order of the methods
 * serialize.
 *
 * This method will be called if there is not a specialized "deserialize" method for the type of object
 * that you are passing as first parameter (see specialized methods below).
 *
 * @param[out] obj: the object that we want to load
 * @param[in] binaryFile: std::ifstream opened in binary mode on the file we want to deserialize
 */
template <typename T>
inline void serializer::deserialize(T& obj, std::ifstream& binaryFile, typename std::enable_if<!std::is_pointer<T>::value >::type*){
    #ifndef CG3_IGNORE_TYPESAFE_SERIALIZATION_CHECK
    static_assert(std::is_base_of<SerializableObject, T>::value || std::is_fundamental<T>::value, "Please provide cg3::Serializer::deserialize specialization for this type!");
    #endif
    std::streampos begin = binaryFile.tellg();
    if (std::is_base_of<SerializableObject, T>::value){
        SerializableObject* o =(SerializableObject*) &obj;
        try {
            o->deserialize(binaryFile);
        }
        catch (std::ios_base::failure& e){
            restorePosition(binaryFile, begin);
            throw std::ios_base::failure(e.what() + std::string("\nFrom ") + internal::typeName<decltype(obj)>(false, false, false));
        }
        catch(...){
            restorePosition(binaryFile, begin);
            throw std::ios_base::failure("Deserialization failed of " + internal::typeName<decltype(obj)>(false, false, false));
        }
    }
    else{ //primitive type deserialization
        if (! binaryFile.read(reinterpret_cast<char*>(&obj), sizeof(T))){
            restorePosition(binaryFile, begin);
            throw std::ios_base::failure("Deserialization failed of " + internal::typeName<decltype(obj)>(false, false, false));
        }
    }
}

/**
 * \~English
 * @brief Serializer::deserialize - specialization for pointers
 *
 * This function allows to deserialize on a std::ifstream opened in binary mode:
 *
 * - All pointers to primitive types
 * - All pointers to classes that have correctly implemented the abstract class SerializableObject
 *
 * It allocates dynamic memory for every object which is deserialized. The pointer will point to the
 * dynamically allocated object that has been deserialized.
 *
 * All you have to do is to call all the deserialize methods in the same order of the methods
 * serialize.
 *
 * This method will be called if there is not a specialized "deserialize" method for the type of pointer
 * that you are passing as first parameter (see specialized methods below).
 *
 * @warning this method is meant to be used only for pointers that are "unique". The deserialization of a pointer will result in a
 * new dynamically allocated object. Example: if you pass three times a pointer to the same object, in the file will be stored three different
 * istances of that object. The deserialization will create three different istances to the object and therefore three different pointers.
 * @param[out] obj: the object that we want to load
 * @param[in] binaryFile: std::ifstream opened in binary mode on the file we want to deserialize
 */
template <typename T>
inline void serializer::deserialize(T& obj, std::ifstream& binaryFile, typename std::enable_if<std::is_pointer<T>::value >::type*){
    std::streampos begin = binaryFile.tellg();
    T tmp = nullptr;
    try {
        std::string s;
        deserialize(s, binaryFile);
        if (s == "cg3nullptr"){
            obj = nullptr;
        }
        else if (s == "cg3p"){
            tmp = new typename std::remove_pointer<T>::type ();
            deserialize(*tmp, binaryFile);
            obj = tmp;
        }
        else
            throw std::ios_base::failure("Mismatching String: expected a pointer.\n");
    }
    catch(std::ios_base::failure& e){
        if (tmp != nullptr) delete tmp;
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom " + internal::typeName<decltype(obj)>(false, false, false)));
    }
    catch(...){
        if (tmp != nullptr) delete tmp;
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of " + internal::typeName<decltype(obj)>(false, false, false));
    }
}

/**
 * @brief Serializer::serialize
 *
 * Specialization for literal strings. A serialized literal string can be deserialized in a std::string.
 *
 * @param str
 * @param binaryFile
 */
inline void serializer::serialize(const char * str, std::ofstream& binaryFile){
    unsigned long long int size = std::strlen(str);
    serializer::serialize(size, binaryFile);
    binaryFile.write(str, size);
}

/**
 * @brief Serializer::serialize
 *
 * Specialization for std::string
 *
 * @param str
 * @param binaryFile
 */
inline void serializer::serialize(const std::string& str, std::ofstream& binaryFile){
    unsigned long long int size = str.size();
    serializer::serialize(size, binaryFile);
    binaryFile.write(&str[0],size);
}

/**
 * @brief Serializer::deserialize
 *
 * Specialization for std::string.
 * If there were an error on reading the object, it will restore the position of the stream
 * BEFORE the reading was started, and an exception will be thrown.
 *
 * @throws std::ios_base::failure if there were an error on reading the string.
 * @param str
 * @param binaryFile
 */
inline void serializer::deserialize(std::string& str, std::ifstream& binaryFile){
    unsigned long long int size;
    std::string tmp;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(size, binaryFile);
        tmp.resize(size);
        if (binaryFile.read(&tmp[0], size)){
            str = std::move(tmp);
        }
        else{
            throw std::exception();
        }
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::string"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::string");
    }

}

template<typename T1, typename T2>
inline void serializer::serialize(const std::pair<T1, T2>& p, std::ofstream& binaryFile) {
    serializer::serialize(p.first, binaryFile);
    serializer::serialize(p.second, binaryFile);
}

template<typename T1, typename T2>
inline void serializer::deserialize(std::pair<T1, T2>& p, std::ifstream& binaryFile) {
    std::streampos begin = binaryFile.tellg();
    std::pair<T1, T2> tmp;
    try {
        serializer::deserialize(tmp.first, binaryFile);
        serializer::deserialize(tmp.second, binaryFile);
        p = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::pair"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::pair");
    }

}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::serialize(const std::set<T, A...> &s, std::ofstream& binaryFile){
    unsigned long long int size = s.size();
    serializer::serialize("stdset", binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::set<T, A...>::const_iterator it = s.begin(); it != s.end(); ++it)
        serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::deserialize(std::set<T, A...> &s, std::ifstream& binaryFile){
    std::string str;
    std::set<T, A...> tmp;
    unsigned long long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(str, binaryFile);
        if (str != "stdset")
            throw std::ios_base::failure("Mismatching String: " + str + " != stdset");
        serializer::deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            serializer::deserialize(obj, binaryFile);
            tmp.insert(obj);
        }
        s = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::set"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::set");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] s: std::unordered_set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::serialize(const std::unordered_set<T, A...> &s, std::ofstream& binaryFile){
    unsigned long long int size = s.size();
    serializer::serialize("stdunorderedset", binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::unordered_set<T, A...>::const_iterator it = s.begin(); it != s.end(); ++it)
        serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] s: std::unordered_set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::deserialize(std::unordered_set<T, A...> &s, std::ifstream& binaryFile){
    std::string str;
    std::unordered_set<T, A...> tmp;
    unsigned long long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(str, binaryFile);
        if (str != "stdunorderedset")
            throw std::ios_base::failure("Mismatching String: " + str + " != stdset");
        serializer::deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            serializer::deserialize(obj, binaryFile);
            tmp.insert(obj);
        }
        s = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::set"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::set");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] v: std::vector of booleans
 * @param binaryFile
 */
template <typename ...A>
inline void serializer::serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile){
    bool tmp;
    unsigned long long int size = v.size();
    serializer::serialize("stdvectorBool", binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::vector<bool, A...>::const_iterator it = v.begin(); it != v.end(); ++it){
        if (*it) tmp = 1;
        else tmp = 0;
        serializer::serialize(tmp, binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile){
    unsigned long long int size = v.size();
    serializer::serialize(std::string("stdvector"), binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::vector<T, A...>::const_iterator it = v.begin(); it != v.end(); ++it)
        serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename ...A>
inline void serializer::deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile){
    unsigned long long int size;
    std::string s;
    std::vector<bool, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(s, binaryFile);
        if (s != "stdvectorBool")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdvectorBool");
        serializer::deserialize(size, binaryFile);
        tmpv.resize(size);
        bool tmp;
        for (unsigned int it = 0; it < size; ++it){
            serializer::deserialize(tmp, binaryFile);
            tmpv[it] = tmp;
        }
        v = std::move(tmpv);
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::vector<bool>"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::set");
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile){
    unsigned long long int size;
    std::string s;
    std::vector<T, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(s, binaryFile);
        if (s != "stdvector")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdvector");
        serializer::deserialize(size, binaryFile);
        tmpv.resize(size);
        for (unsigned int it = 0; it < size; ++it){
            serializer::deserialize(tmpv[it], binaryFile);
        }
        v = std::move(tmpv);

    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::vector"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::vector");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::serialize(const std::list<T, A...> &l, std::ofstream& binaryFile){
    unsigned long long int size = l.size();
    serializer::serialize("stdlist", binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::list<T, A...>::const_iterator it = l.begin(); it != l.end(); ++it)
        serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serializer::deserialize(std::list<T, A...> &l, std::ifstream& binaryFile){
    unsigned long long int size;
    std::string s;
    std::list<T, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(s, binaryFile);
        if (s != "stdlist")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdlist");
        serializer::deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            serializer::deserialize(obj, binaryFile);
            tmp.push_back(obj);
        }
        l = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::list"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::list");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[out] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void serializer::serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile){
    unsigned long long int size = m.size();
    serializer::serialize("stdmap", binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::map<T1, T2, A...>::const_iterator it = m.begin(); it != m.end(); ++it){
        serializer::serialize((it->first), binaryFile);
        serializer::serialize((it->second), binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[in] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void serializer::deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile){
    unsigned long long int size;
    std::string s;
    std::map<T1, T2, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(s, binaryFile);
        if (s != "stdmap")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdmap");
        serializer::deserialize(size, binaryFile);

        for (unsigned int it = 0; it < size; ++it){
            T1 o1;
            T2 o2;

            serializer::deserialize(o1, binaryFile);
            serializer::deserialize(o2, binaryFile);
            tmp[std::move(o1)] = std::move(o2);
        }
        m = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::map"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::map");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] m: std::array
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline void serializer::serialize(const std::array<T, A...> &a, std::ofstream& binaryFile){
    unsigned long long int size = a.size();
    serializer::serialize("stdarray", binaryFile);
    serializer::serialize(size, binaryFile);
    for (typename std::array<T, A...>::const_iterator it = a.begin(); it != a.end(); ++it)
        serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input set is an empty set.
 * @param[out] m: std::array
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline void serializer::deserialize(std::array<T, A...> &a, std::ifstream& binaryFile){
    unsigned long long int size;
    std::string s;
    std::streampos begin = binaryFile.tellg();
    try {
        serializer::deserialize(s, binaryFile);
        if (s != "stdarray")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdarray");
        serializer::deserialize(size, binaryFile);
        if (size != a.size())
            throw std::ios_base::failure(std::string("Mismatching std::array size: ") + std::to_string(size) + " != " + std::to_string(a.size()));
        std::vector<T> tmp(size);
        for (unsigned int it = 0; it < size; ++it){
            serializer::deserialize(tmp[it], binaryFile);
        }
        std::copy_n(tmp.begin(), size, a.begin());
    }
    catch(std::ios_base::failure& e){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::array"));
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::array");
    }
}

template<typename T>
inline std::string serializer::internal::typeName(bool specifyIfConst, bool specifyIfVolatile, bool specifyIfReference) {
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

inline void serializer::internal::serializeAttribute(std::ofstream& binaryFile){
    CG3_SUPPRESS_WARNING(binaryFile);
}

template<typename T, typename ...Args>
inline void serializer::internal::serializeAttribute(std::ofstream& binaryFile, const T& t, const Args&... args) {
    serializer::serialize(t, binaryFile);
    serializeAttribute(binaryFile, args...);
}

inline void serializer::internal::deserializeAttribute(std::ifstream& binaryFile){
    CG3_SUPPRESS_WARNING(binaryFile);
}

template<typename T, typename ...Args>
inline void serializer::internal::deserializeAttribute(std::ifstream& binaryFile, T& t, Args&... args) {
    T tmp;
    serializer::deserialize(tmp, binaryFile);
    deserializeAttribute(binaryFile, args...);
    t = std::move(tmp);
}

}
