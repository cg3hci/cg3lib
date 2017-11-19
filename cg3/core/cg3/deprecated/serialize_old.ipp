#include "serialize_old.h"

#include <exception>

namespace cg3 {

inline void SerializerOld::restore(std::ifstream& binaryFile, const std::streampos& position) {
    binaryFile.clear();
    binaryFile.seekg(position);
}

/**
 * \~Italian
 * @brief
 *
 * \~English
 * @brief Serializer::serialize
 *
 * This function allows to serialize on a std::ofstream opened in binary mode:
 *
 * - All primitive types;
 * - All classes that have correctly implemented the abstract class SerializableObject
 *
 * This method will be called if there is not a specialized "serialize" method for the type of object
 * that you are passing as first parameter (see specialized methods below).
 *
 * @param[in] obj: object which we want serialize
 * @param[in] binaryFile: std::ofstream opened in binary mode on the file where we want to serialize
 */
template <typename T>
inline void SerializerOld::serialize(const T& obj, std::ofstream& binaryFile){
    if (std::is_base_of<SerializableObjectOld, T>::value){
        SerializableObjectOld* o =(SerializableObjectOld*) &obj;
        o->serializeOld(binaryFile);
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
inline bool SerializerOld::deserialize(T& obj, std::ifstream& binaryFile){
    if (std::is_base_of<SerializableObjectOld, T>::value){
        SerializableObjectOld* o =(SerializableObjectOld*) &obj;
        return o->deserializeOld(binaryFile);
    }
    else{
        std::streampos begin = binaryFile.tellg();
        if (binaryFile.read(reinterpret_cast<char*>(&obj), sizeof(T)))
            return true;
        else{
            restore(binaryFile, begin);
            return false;
        }
    }
}

#ifdef QT_CORE_LIB
/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] obj: QColor
 * @param binaryFile
 */
inline void SerializerOld::serialize(const QColor& obj, std::ofstream& binaryFile){
    int r = obj.red(), g = obj.green(), b = obj.blue(), a = obj.alpha();
    SerializerOld::serialize(r, binaryFile);
    SerializerOld::serialize(g, binaryFile);
    SerializerOld::serialize(b, binaryFile);
    SerializerOld::serialize(a, binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] obj: QColor
 * @param binaryFile
 */
inline bool SerializerOld::deserialize(QColor& obj, std::ifstream& binaryFile){
    int r, g, b, a;
    std::streampos begin = binaryFile.tellg();
    if (SerializerOld::deserialize(r, binaryFile) &&
        SerializerOld::deserialize(g, binaryFile) &&
        SerializerOld::deserialize(b, binaryFile) &&
        SerializerOld::deserialize(a, binaryFile)) {
            obj.setRgb(r,g,b,a);
            return true;
    }
    else{
        restore(binaryFile, begin);
        return false;
    }
}
#endif //QT_CORE_LIB

inline void SerializerOld::serialize(const std::string& str, std::ofstream& binaryFile){
    unsigned long int size=str.size();
    SerializerOld::serialize(size, binaryFile);
    binaryFile.write(&str[0],size);
}

inline bool SerializerOld::deserialize(std::string& str, std::ifstream& binaryFile){
    unsigned long int size;
    std::string tmp;
    std::streampos begin = binaryFile.tellg();
    if (SerializerOld::deserialize(size, binaryFile)){
        try {
            tmp.resize(size);
            if (binaryFile.read(&tmp[0], size)){
                str = std::move(tmp);
                return true;
            }
            else{
                restore(binaryFile, begin);
                return false;
            }
        }
        catch (...){
            restore(binaryFile, begin);
            return false;
        }
    }
    else{
        restore(binaryFile, begin);
        return false;
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void SerializerOld::serialize(const std::set<T, A...> &s, std::ofstream& binaryFile){
    unsigned long int size = s.size();
    SerializerOld::serialize(size, binaryFile);
    for (typename std::set<T, A...>::const_iterator it = s.begin(); it != s.end(); ++it)
        SerializerOld::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input set is an empty set.
 * @param[out] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline bool SerializerOld::deserialize(std::set<T, A...> &s, std::ifstream& binaryFile){
    std::set<T, A...> tmp;
    unsigned long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(size, binaryFile)){
            for (unsigned int it = 0; it < size; ++it){
                T obj;
                if(SerializerOld::deserialize(obj, binaryFile))
                    tmp.insert(obj);
                else{
                    restore(binaryFile, begin);
                    return false;
                }
            }
            s = std::move(tmp);
            return true;
        }
        else {
            restore(binaryFile, begin);
            return false;
        }
    }
    catch (...){
        restore(binaryFile, begin);
        return false;
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] v: std::vector of booleans
 * @param binaryFile
 */
template <typename ...A>
inline void SerializerOld::serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile){
    bool tmp;
    unsigned long int size = v.size();
    SerializerOld::serialize(size, binaryFile);
    for (typename std::vector<bool, A...>::const_iterator it = v.begin(); it != v.end(); ++it){
        if (*it) tmp = 1;
        else tmp = 0;
        SerializerOld::serialize(tmp, binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void SerializerOld::serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile){
    unsigned long int size = v.size();
    SerializerOld::serialize(size, binaryFile);
    for (typename std::vector<T, A...>::const_iterator it = v.begin(); it != v.end(); ++it)
        SerializerOld::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input vector is an empty vector (it will be overwritten)
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename ...A>
inline bool SerializerOld::deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile){
    unsigned long int size;
    std::vector<bool, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(size, binaryFile)){
            tmpv.resize(size);
            bool tmp;
            for (unsigned int it = 0; it < size; ++it){
                if (SerializerOld::deserialize(tmp, binaryFile))
                    tmpv[it] = tmp;
                else{
                    restore(binaryFile, begin);
                    return false;
                }
            }
            v = std::move(tmpv);
            return true;
        }
        else{
            restore(binaryFile, begin);
            return false;
        }
    }
    catch(...){
        restore(binaryFile, begin);
        return false;
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input vector is an empty vector (it will be overwritten)
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline bool SerializerOld::deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile){
    unsigned long int size;
    std::vector<T, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(size, binaryFile)){
            tmpv.resize(size);
            for (unsigned int it = 0; it < size; ++it){
                if (! SerializerOld::deserialize(tmpv[it], binaryFile)){
                    binaryFile.clear();
                    binaryFile.seekg(begin);
                    return false;
                }
            }
            v = std::move(tmpv);
            return true;
        }
        else{
            binaryFile.clear();
            binaryFile.seekg(begin);
            return false;
        }
    }
    catch(...){
        restore(binaryFile, begin);
        return false;
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void SerializerOld::serialize(const std::list<T, A...> &l, std::ofstream& binaryFile){
    unsigned long int size = l.size();
    SerializerOld::serialize(size, binaryFile);
    for (typename std::list<T, A...>::const_iterator it = l.begin(); it != l.end(); ++it)
        SerializerOld::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input list is an empty list
 * @param[out] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline bool SerializerOld::deserialize(std::list<T, A...> &l, std::ifstream& binaryFile){
    unsigned long int size;
    std::list<T, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(size, binaryFile)){
            for (unsigned int it = 0; it < size; ++it){
                T obj;
                if (SerializerOld::deserialize(obj, binaryFile))
                    tmp.push_back(obj);
                else{
                    binaryFile.clear();
                    binaryFile.seekg(begin);
                    return false;
                }
            }
            l = std::move(tmp);
            return true;
        }
        else{
            binaryFile.clear();
            binaryFile.seekg(begin);
            return false;
        }
    }
    catch (...){
        restore(binaryFile, begin);
        return false;
    }
}

/**
 * \~English
 * @brief Serializer::serialize
 * @param[out] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void SerializerOld::serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile){
    unsigned long int size = m.size();
    SerializerOld::serialize(size, binaryFile);
    for (typename std::map<T1, T2, A...>::const_iterator it = m.begin(); it != m.end(); ++it){
        SerializerOld::serialize((it->first), binaryFile);
        SerializerOld::serialize((it->second), binaryFile);
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input map is an empty map
 * @param[in] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline bool SerializerOld::deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile){
    unsigned long int size;
    std::map<T1, T2, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(size, binaryFile)) {

            for (unsigned int it = 0; it < size; ++it){
                T1 o1;
                T2 o2;

                if (SerializerOld::deserialize(o1, binaryFile) &&
                    SerializerOld::deserialize(o2, binaryFile))
                        tmp[std::move(o1)] = std::move(o2);
                else{
                    binaryFile.clear();
                    binaryFile.seekg(begin);
                    return false;
                }
            }
            m = std::move(tmp);
            return true;
        }
        else{
            binaryFile.clear();
            binaryFile.seekg(begin);
            return false;
        }
    }
    catch (...){
        restore(binaryFile, begin);
        return false;
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
inline void SerializerOld::serialize(const Eigen::Matrix<T, A...> &m, std::ofstream& binaryFile){
    unsigned long int row = m.rows(), col = m.cols();
    SerializerOld::serialize(row, binaryFile);
    SerializerOld::serialize(col, binaryFile);
    for (unsigned int i = 0; i < row; i++){
        for (unsigned int j = 0; j < col; ++j){
            SerializerOld::serialize(m(i,j), binaryFile);
        }
    }
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input set is an empty set.
 * @param[out] m: Eigen::Matrix
 * @param binaryFile
 */
template <typename T, int ...A>
inline bool SerializerOld::deserialize(Eigen::Matrix<T, A...> &m, std::ifstream& binaryFile){
    unsigned long int row, col;
    Eigen::Matrix<T, A...> tmp;
    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(row, binaryFile) && SerializerOld::deserialize(col, binaryFile)) {
            tmp.resize(row, col);

            for (unsigned int i = 0; i < row; i++){
                for (unsigned int j = 0; j < col; ++j){
                    if (! SerializerOld::deserialize(tmp(i,j), binaryFile)){
                        binaryFile.clear();
                        binaryFile.seekg(begin);
                        return false;
                    }
                }
            }
            m = std::move(tmp);
            return true;
        }
        else{
            binaryFile.clear();
            binaryFile.seekg(begin);
            return false;
        }
    }
    catch (...){
        restore(binaryFile, begin);
        return false;
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
inline void SerializerOld::serialize(const std::array<T, A...> &a, std::ofstream& binaryFile){
    unsigned long int size = a.size();
    SerializerOld::serialize(size, binaryFile);
    for (typename std::array<T, A...>::const_iterator it = a.begin(); it != a.end(); ++it)
        SerializerOld::serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @warning please make sure that the input set is an empty set.
 * @param[out] m: Eigen::Matrix
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline bool SerializerOld::deserialize(std::array<T, A...> &a, std::ifstream& binaryFile){
    unsigned long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        if (SerializerOld::deserialize(size, binaryFile) && size == a.size()){
            std::vector<T> tmp(size);
            for (unsigned int it = 0; it < size; ++it){
                if (! SerializerOld::deserialize(tmp[it], binaryFile)){
                    binaryFile.clear();
                    binaryFile.seekg(begin);
                    return false;
                }
            }
            std::copy_n(tmp.begin(), size, a.begin());
            return true;
        }
        else{
            binaryFile.clear();
            binaryFile.seekg(begin);
            return false;
        }
    }
    catch (...){
        restore(binaryFile, begin);
        return false;
    }
}

}
