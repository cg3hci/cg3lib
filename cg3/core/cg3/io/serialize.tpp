#include "serialize.h"

#include <exception>
#include <type_traits>

namespace cg3 {

/**
 * @brief Serializer::getPosition
 * @param[in] binaryFile
 * @return the position of the stream
 */
inline std::streampos Serializer::getPosition(std::ifstream& binaryFile) {
    return binaryFile.tellg();
}

/**
 * @brief Serializer::restorePosition
 * restores the current position of the stream
 * @param[out] binaryFile: the file with the new position
 * @param[in] position: the desired position on the file
 */
inline void Serializer::restorePosition(std::ifstream& binaryFile, const std::streampos& position) {
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
 * This method will be called if there is not a specialized "serialize" function for the type of object
 * that you are passing as first parameter (see specialized methods).
 *
 * @param[in] obj: object which we want serialize
 * @param[in] binaryFile: std::ofstream opened in binary mode on the file where we want to serialize
 */
template <typename T>
inline void Serializer::serialize(const T& obj, std::ofstream& binaryFile){
    if (std::is_base_of<SerializableObject, T>::value){
        SerializableObject* o =(SerializableObject*) &obj;
        o->serialize(binaryFile);
    }
    else{
        binaryFile.write(reinterpret_cast<const char*>(&obj), sizeof(T));
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
inline void Serializer::deserialize(T& obj, std::ifstream& binaryFile){
    std::streampos begin = binaryFile.tellg();
    if (std::is_base_of<SerializableObject, T>::value){
        SerializableObject* o =(SerializableObject*) &obj;
        try {
            o->deserialize(binaryFile);
        }
        catch (...){
            restorePosition(binaryFile, begin);
            throw std::ios_base::failure("");
        }
    }
    else{ // primitive type or type which doesn't exist a "deserialize" implementation
        if (! binaryFile.read(reinterpret_cast<char*>(&obj), sizeof(T))){
            restorePosition(binaryFile, begin);
            throw std::ios_base::failure("");
        }
    }
}

/**
 * @brief Serializer::serializeObjectAttributes
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
inline void Serializer::serializeObjectAttributes(const std::string& s, std::ofstream& binaryFile, const Args&... args) {
    Serializer::serialize(s, binaryFile);
    Serializer::internal::serializeAttribute(binaryFile, args...);
}

/**
 * @brief Serializer::deserializeObjectAttributes
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
inline void Serializer::deserializeObjectAttributes(const std::string& s, std::ifstream& binaryFile, Args&... args) {
    std::string tmp;
    std::streampos begin = binaryFile.tellg();
    try {

        Serializer::deserialize(tmp, binaryFile);
        if (tmp != s)
            throw std::ios_base::failure("");
        Serializer::internal::deserializeAttribute(binaryFile, args...);

    }
    catch(...){
        Serializer::restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading " + s);
    }
}

#ifdef QT_CORE_LIB
/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] obj: QColor
 * @param binaryFile
 */
inline void Serializer::serialize(const QColor& obj, std::ofstream& binaryFile){
    int r = obj.red(), g = obj.green(), b = obj.blue(), a = obj.alpha();
    Serializer::serializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] obj: QColor
 * @param binaryFile
 */
inline void Serializer::deserialize(QColor& obj, std::ifstream& binaryFile){
    int r, g, b, a;
    Serializer::deserializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
    obj.setRgb(r,g,b,a);
}
#endif //QT_CORE_LIB

inline void Serializer::serialize(const char * str, std::ofstream& binaryFile){
    unsigned long int size=std::strlen(str);
    Serializer::serialize(size, binaryFile);
    binaryFile.write(str, size);
}

inline void Serializer::serialize(const std::string& str, std::ofstream& binaryFile){
    unsigned long int size=str.size();
    Serializer::serialize(size, binaryFile);
    binaryFile.write(&str[0],size);
}

inline void Serializer::deserialize(std::string& str, std::ifstream& binaryFile){
    unsigned long int size;
    std::string tmp;
    std::streampos begin = binaryFile.tellg();
    Serializer::deserialize(size, binaryFile);
    tmp.resize(size);
    if (binaryFile.read(&tmp[0], size)){
        str = std::move(tmp);
    }
    else{
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::string");
    }

}

template<typename T1, typename T2>
inline void Serializer::serialize(const std::pair<T1, T2>& p, std::ofstream& binaryFile) {
    Serializer::serialize(p.first, binaryFile);
    Serializer::serialize(p.second, binaryFile);
}

template<typename T1, typename T2>
inline void Serializer::deserialize(std::pair<T1, T2>& p, std::ifstream& binaryFile) {
    std::streampos begin = binaryFile.tellg();
    std::pair<T1, T2> tmp;
    try {
        Serializer::deserialize(tmp.first, binaryFile);
        Serializer::deserialize(tmp.second, binaryFile);
        p = std::move(tmp);
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::pair");
    }

}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void Serializer::serialize(const std::set<T, A...> &s, std::ofstream& binaryFile){
    unsigned long int size = s.size();
    Serializer::serialize("stdset", binaryFile);
    Serializer::serialize(size, binaryFile);
    for (typename std::set<T, A...>::const_iterator it = s.begin(); it != s.end(); ++it)
        Serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void Serializer::deserialize(std::set<T, A...> &s, std::ifstream& binaryFile){
    std::string str;
    std::set<T, A...> tmp;
    unsigned long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(str, binaryFile);
        if (str != "stdset")
            throw std::ios_base::failure("");
        Serializer::deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            Serializer::deserialize(obj, binaryFile);
            tmp.insert(obj);
        }
        s = std::move(tmp);
    }
    catch (...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::set");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] v: std::vector of booleans
 * @param binaryFile
 */
template <typename ...A>
inline void Serializer::serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile){
    bool tmp;
    unsigned long int size = v.size();
    Serializer::serialize("stdvectorBool", binaryFile);
    Serializer::serialize(size, binaryFile);
    for (typename std::vector<bool, A...>::const_iterator it = v.begin(); it != v.end(); ++it){
        if (*it) tmp = 1;
        else tmp = 0;
        Serializer::serialize(tmp, binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void Serializer::serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile){
    unsigned long int size = v.size();
    Serializer::serialize(std::string("stdvector"), binaryFile);
    Serializer::serialize(size, binaryFile);
    for (typename std::vector<T, A...>::const_iterator it = v.begin(); it != v.end(); ++it)
        Serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename ...A>
inline void Serializer::deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile){
    unsigned long int size;
    std::string s;
    std::vector<bool, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "stdvectorBool")
            throw std::ios_base::failure("");
        Serializer::deserialize(size, binaryFile);
        tmpv.resize(size);
        bool tmp;
        for (unsigned int it = 0; it < size; ++it){
            Serializer::deserialize(tmp, binaryFile);
            tmpv[it] = tmp;
        }
        v = std::move(tmpv);
    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::vector<bool>");
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void Serializer::deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile){
    unsigned long int size;
    std::string s;
    std::vector<T, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "stdvector")
            throw std::ios_base::failure("");
        Serializer::deserialize(size, binaryFile);
        tmpv.resize(size);
        for (unsigned int it = 0; it < size; ++it){
            Serializer::deserialize(tmpv[it], binaryFile);
        }
        v = std::move(tmpv);

    }
    catch(...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::vector");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void Serializer::serialize(const std::list<T, A...> &l, std::ofstream& binaryFile){
    unsigned long int size = l.size();
    Serializer::serialize("stdlist", binaryFile);
    Serializer::serialize(size, binaryFile);
    for (typename std::list<T, A...>::const_iterator it = l.begin(); it != l.end(); ++it)
        Serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void Serializer::deserialize(std::list<T, A...> &l, std::ifstream& binaryFile){
    unsigned long int size;
    std::string s;
    std::list<T, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "stdlist")
            throw std::ios_base::failure("");
        Serializer::deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            Serializer::deserialize(obj, binaryFile);
            tmp.push_back(obj);
        }
        l = std::move(tmp);
    }
    catch (...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::list");
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[out] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void Serializer::serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile){
    unsigned long int size = m.size();
    Serializer::serialize("stdmap", binaryFile);
    Serializer::serialize(size, binaryFile);
    for (typename std::map<T1, T2, A...>::const_iterator it = m.begin(); it != m.end(); ++it){
        Serializer::serialize((it->first), binaryFile);
        Serializer::serialize((it->second), binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[in] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void Serializer::deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile){
    unsigned long int size;
    std::string s;
    std::map<T1, T2, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "stdmap")
            throw std::ios_base::failure("");
        Serializer::deserialize(size, binaryFile);

        for (unsigned int it = 0; it < size; ++it){
            T1 o1;
            T2 o2;

            Serializer::deserialize(o1, binaryFile);
            Serializer::deserialize(o2, binaryFile);
            tmp[std::move(o1)] = std::move(o2);
        }
        m = std::move(tmp);
        return true;
    }
    catch (...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::list");
    }
}

#ifdef CG3_WITH_EIGEN
/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] m: Eigen::Matrix
 * @param binaryFile
 */
template <typename T, int ...A>
inline void Serializer::serialize(const Eigen::Matrix<T, A...> &m, std::ofstream& binaryFile){
    unsigned long int row = m.rows(), col = m.cols();
    Serializer::serialize("EigenMatrix", binaryFile);
    Serializer::serialize(row, binaryFile);
    Serializer::serialize(col, binaryFile);
    for (unsigned int i = 0; i < row; i++){
        for (unsigned int j = 0; j < col; ++j){
            Serializer::serialize(m(i,j), binaryFile);
        }
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] m: Eigen::Matrix
 * @param binaryFile
 */
template <typename T, int ...A>
inline void Serializer::deserialize(Eigen::Matrix<T, A...> &m, std::ifstream& binaryFile){
    unsigned long int row, col;
    std::string s;
    Eigen::Matrix<T, A...> tmp;
    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "EigenMatrix")
            throw std::ios_base::failure("");
        Serializer::deserialize(row, binaryFile);
        Serializer::deserialize(col, binaryFile);
        tmp.resize(row, col);

        for (unsigned int i = 0; i < row; i++){
            for (unsigned int j = 0; j < col; ++j){
                Serializer::deserialize(tmp(i,j), binaryFile);
            }
        }
        m = std::move(tmp);
    }
    catch (...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading Eigen::Matrix");
    }
}
#endif //CG3_WITH_EIGEN

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] m: Eigen::Matrix
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline void Serializer::serialize(const std::array<T, A...> &a, std::ofstream& binaryFile){
    unsigned long int size = a.size();
    Serializer::serialize("stdarray", binaryFile);
    Serializer::serialize(size, binaryFile);
    for (typename std::array<T, A...>::const_iterator it = a.begin(); it != a.end(); ++it)
        Serializer::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input set is an empty set.
 * @param[out] m: Eigen::Matrix
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline void Serializer::deserialize(std::array<T, A...> &a, std::ifstream& binaryFile){
    unsigned long int size;
    std::string s;
    std::streampos begin = binaryFile.tellg();
    try {
        Serializer::deserialize(s, binaryFile);
        if (s != "stdarray")
            throw std::ios_base::failure("");
        Serializer::deserialize(size, binaryFile);
        if (size != a.size())
            throw std::ios_base::failure("");
        std::vector<T> tmp(size);
        for (unsigned int it = 0; it < size; ++it){
            Serializer::deserialize(tmp[it], binaryFile);
        }
        std::copy_n(tmp.begin(), size, a.begin());
    }
    catch (...){
        restorePosition(binaryFile, begin);
        throw std::ios_base::failure("Failure reading std::array");
    }
}

inline void Serializer::internal::serializeAttribute(std::ofstream& binaryFile){
    CG3_SUPPRESS_WARNING(binaryFile);
}

template<typename T, typename ...Args>
inline void Serializer::internal::serializeAttribute(std::ofstream& binaryFile, const T& t, const Args&... args) {
    Serializer::serialize(t, binaryFile);
    serializeAttribute(binaryFile, args...);
}

inline void Serializer::internal::deserializeAttribute(std::ifstream& binaryFile){
    CG3_SUPPRESS_WARNING(binaryFile);
}

template<typename T, typename ...Args>
inline void Serializer::internal::deserializeAttribute(std::ifstream& binaryFile, T& t, Args&... args) {
    T tmp;
    Serializer::deserialize(tmp, binaryFile);
    deserializeAttribute(binaryFile, args...);
    t = std::move(tmp);
}

}
