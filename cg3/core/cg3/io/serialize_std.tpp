/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "serialize_std.h"

namespace cg3 {

template<typename T1, typename T2>
inline void serialize(const std::pair<T1, T2>& p, std::ofstream& binaryFile)
{
    serialize(p.first, binaryFile);
    serialize(p.second, binaryFile);
}

template<typename T1, typename T2>
inline void deserialize(std::pair<T1, T2>& p, std::ifstream& binaryFile)
{
    std::streampos begin = binaryFile.tellg();
    std::pair<T1, T2> tmp;
    try {
        deserialize(tmp.first, binaryFile);
        deserialize(tmp.second, binaryFile);
        p = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::pair"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::pair");
    }

}

/**
 * \~English
 * @brief serialize
 * @param[in] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serialize(const std::set<T, A...> &s, std::ofstream& binaryFile)
{
    unsigned long long int size = s.size();
    serialize("stdset", binaryFile);
    serialize(size, binaryFile);
    for (typename std::set<T, A...>::const_iterator it = s.begin(); it != s.end(); ++it)
        serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief deserialize
 * @param[out] s: std::set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void deserialize(std::set<T, A...> &s, std::ifstream& binaryFile)
{
    std::string str;
    std::set<T, A...> tmp;
    unsigned long long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(str, binaryFile);
        if (str != "stdset")
            throw std::ios_base::failure("Mismatching String: " + str + " != stdset");
        deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            deserialize(obj, binaryFile);
            tmp.insert(obj);
        }
        s = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::set"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::set");
    }
}

/**
 * \~English
 * @brief serialize
 * @param[in] s: std::unordered_set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serialize(const std::unordered_set<T, A...> &s, std::ofstream& binaryFile)
{
    unsigned long long int size = s.size();
    serialize("stdunorderedset", binaryFile);
    serialize(size, binaryFile);
    for (typename std::unordered_set<T, A...>::const_iterator it = s.begin(); it != s.end(); ++it)
        serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief deserialize
 * @param[out] s: std::unordered_set
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void deserialize(std::unordered_set<T, A...> &s, std::ifstream& binaryFile)
{
    std::string str;
    std::unordered_set<T, A...> tmp;
    unsigned long long int size;
    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(str, binaryFile);
        if (str != "stdunorderedset")
            throw std::ios_base::failure("Mismatching String: " + str + " != stdset");
        deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            deserialize(obj, binaryFile);
            tmp.insert(obj);
        }
        s = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::set"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::set");
    }
}

/**
 * \~English
 * @brief serialize
 * @param[in] v: std::vector of booleans
 * @param binaryFile
 * @link https://stackoverflow.com/questions/29623605/how-to-dump-stdvectorbool-in-a-binary-file
 */
template <typename ...A>
inline void serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile)
{
    //bool tmp;
    unsigned long long int size = v.size();
    serialize("stdvectorBool", binaryFile);
    serialize(size, binaryFile);

    for(typename std::vector<bool, A...>::size_type i = 0; i < size;) {
        unsigned char aggr = 0;
        for(unsigned char mask = 1; mask > 0 && i < size; ++i, mask <<= 1)
            if(v.at(i))
                aggr |= mask;
        binaryFile.write((const char*)&aggr, sizeof(unsigned char));
    }
}

/**
 * \~English
 * @brief serialize
 * @param[in] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile)
{
    unsigned long long int size = v.size();
    serialize(std::string("stdvector"), binaryFile);
    serialize(size, binaryFile);
    for (typename std::vector<T, A...>::const_iterator it = v.begin(); it != v.end(); ++it)
        serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief deserialize
 * @param[out] v: std::vector
 * @param binaryFile
 * @link https://stackoverflow.com/questions/29623605/how-to-dump-stdvectorbool-in-a-binary-file
 */
template <typename ...A>
inline void deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile)
{
    unsigned long long int size;
    std::string s;
    std::vector<bool, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(s, binaryFile);
        if (s != "stdvectorBool")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdvectorBool");
        deserialize(size, binaryFile);
        tmpv.resize(size);

        for(typename std::vector<bool, A...>::size_type i = 0; i < size;) {
            unsigned char aggr;
            binaryFile.read((char*)&aggr, sizeof(unsigned char));
            for(unsigned char mask = 1; mask > 0 && i < size; ++i, mask <<= 1)
                tmpv.at(i) = aggr & mask;
        }
        v = std::move(tmpv);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::vector<bool>"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::set");
    }
}

/**
 * \~English
 * @brief deserialize
 * @param[out] v: std::vector
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile)
{
    unsigned long long int size;
    std::string s;
    std::vector<T, A...> tmpv;
    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(s, binaryFile);
        if (s != "stdvector")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdvector");
        deserialize(size, binaryFile);
        tmpv.resize(size);
        for (unsigned int it = 0; it < size; ++it){
            deserialize(tmpv[it], binaryFile);
        }
        v = std::move(tmpv);

    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::vector"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::vector");
    }
}

/**
 * \~English
 * @brief serialize
 * @param[in] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void serialize(const std::list<T, A...> &l, std::ofstream& binaryFile)
{
    unsigned long long int size = l.size();
    serialize("stdlist", binaryFile);
    serialize(size, binaryFile);
    for (typename std::list<T, A...>::const_iterator it = l.begin(); it != l.end(); ++it)
        serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief deserialize
 * @param[out] l: std::list
 * @param binaryFile
 */
template <typename T, typename ...A>
inline void deserialize(std::list<T, A...> &l, std::ifstream& binaryFile)
{
    unsigned long long int size;
    std::string s;
    std::list<T, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(s, binaryFile);
        if (s != "stdlist")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdlist");
        deserialize(size, binaryFile);
        for (unsigned int it = 0; it < size; ++it){
            T obj;
            deserialize(obj, binaryFile);
            tmp.push_back(obj);
        }
        l = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::list"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::list");
    }
}

/**
 * \~English
 * @brief serialize
 * @param[out] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile)
{
    unsigned long long int size = m.size();
    serialize("stdmap", binaryFile);
    serialize(size, binaryFile);
    for (typename std::map<T1, T2, A...>::const_iterator it = m.begin(); it != m.end(); ++it){
        serialize((it->first), binaryFile);
        serialize((it->second), binaryFile);
    }
}

/**
 * \~English
 * @brief deserialize
 * @param[in] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile)
{
    unsigned long long int size;
    std::string s;
    std::map<T1, T2, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(s, binaryFile);
        if (s != "stdmap")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdmap");
        deserialize(size, binaryFile);

        for (unsigned int it = 0; it < size; ++it){
            T1 o1;
            T2 o2;

            deserialize(o1, binaryFile);
            deserialize(o2, binaryFile);
            tmp[std::move(o1)] = std::move(o2);
        }
        m = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::map"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::map");
    }
}

/**
 * \~English
 * @brief serialize
 * @param[out] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void serialize(const std::unordered_map<T1, T2, A...> &m, std::ofstream& binaryFile)
{
    unsigned long long int size = m.size();
    serialize("stdunorderedmap", binaryFile);
    serialize(size, binaryFile);
    for (typename std::unordered_map<T1, T2, A...>::const_iterator it = m.begin(); it != m.end(); ++it){
        serialize((it->first), binaryFile);
        serialize((it->second), binaryFile);
    }
}

/**
 * \~English
 * @brief deserialize
 * @param[in] m: std::map
 * @param binaryFile
 */
template <typename T1, typename T2, typename ...A>
inline void deserialize(std::unordered_map<T1, T2, A...> &m, std::ifstream& binaryFile)
{
    unsigned long long int size;
    std::string s;
    std::unordered_map<T1, T2, A...> tmp;

    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(s, binaryFile);
        if (s != "stdunorderedmap")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdunorderedmap");
        deserialize(size, binaryFile);

        for (unsigned int it = 0; it < size; ++it){
            T1 o1;
            T2 o2;

            deserialize(o1, binaryFile);
            deserialize(o2, binaryFile);
            tmp[std::move(o1)] = std::move(o2);
        }
        m = std::move(tmp);
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::map"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::map");
    }
}

/**
 * \~English
 * @brief serialize
 * @param[in] m: std::array
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline void serialize(const std::array<T, A...> &a, std::ofstream& binaryFile)
{
    unsigned long long int size = a.size();
    serialize("stdarray", binaryFile);
    serialize(size, binaryFile);
    for (typename std::array<T, A...>::const_iterator it = a.begin(); it != a.end(); ++it)
        serialize((*it), binaryFile);
}

/**
 * \~English
 * @brief deserialize
 * @warning please make sure that the input set is an empty set.
 * @param[out] m: std::array
 * @param binaryFile
 */
template <typename T, unsigned long int ...A>
inline void deserialize(std::array<T, A...> &a, std::ifstream& binaryFile)
{
    unsigned long long int size;
    std::string s;
    std::streampos begin = binaryFile.tellg();
    try {
        deserialize(s, binaryFile);
        if (s != "stdarray")
            throw std::ios_base::failure("Mismatching String: " + s + " != stdarray");
        deserialize(size, binaryFile);
        if (size != a.size())
            throw std::ios_base::failure(std::string("Mismatching std::array size: ") + std::to_string(size) + " != " + std::to_string(a.size()));
        std::vector<T> tmp(size);
        for (unsigned int it = 0; it < size; ++it){
            deserialize(tmp[it], binaryFile);
        }
        std::copy_n(tmp.begin(), size, a.begin());
    }
    catch(std::ios_base::failure& e){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure(e.what() + std::string("\nFrom std::array"));
    }
    catch(...){
        restoreFilePosition(binaryFile, begin);
        throw std::ios_base::failure("Deserialization failed of std::array");
    }
}

}
