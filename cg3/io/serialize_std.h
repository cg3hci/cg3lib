/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_SERIALIZE_STD_H
#define CG3_SERIALIZE_STD_H

#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <typeinfo>
#include <algorithm>

#include "serialize.h"

namespace cg3 {

template <typename T1, typename T2>
void serialize(const std::pair<T1, T2>& p, std::ofstream& binaryFile);

template <typename T1, typename T2>
void deserialize(std::pair<T1, T2>& p, std::ifstream& binaryFile);

template <typename T, typename ...A>
void serialize(const std::set<T, A...> &s, std::ofstream& binaryFile);

template <typename T, typename ...A>
void deserialize(std::set<T, A...> &s, std::ifstream& binaryFile);

template <typename T, typename ...A>
void serialize(const std::unordered_set<T, A...> &s, std::ofstream& binaryFile);

template <typename T, typename ...A>
void deserialize(std::unordered_set<T, A...> &s, std::ifstream& binaryFile);

template <typename ...A>
void serialize(const std::vector<bool, A...> &v, std::ofstream& binaryFile);

template <typename T, typename ...A>
void serialize(const std::vector<T, A...> &v, std::ofstream& binaryFile);

template <typename ...A>
void deserialize(std::vector<bool, A...> &v, std::ifstream& binaryFile);

template <typename T, typename ...A>
void deserialize(std::vector<T, A...> &v, std::ifstream& binaryFile);

template <typename T, typename ...A>
void serialize(const std::list<T, A...> &l, std::ofstream& binaryFile);

template <typename T, typename ...A>
void deserialize(std::list<T, A...> &l, std::ifstream& binaryFile);

template <typename T1, typename T2, typename ...A>
void serialize(const std::map<T1, T2, A...> &m, std::ofstream& binaryFile);

template <typename T1, typename T2, typename ...A>
void deserialize(std::map<T1, T2, A...> &m, std::ifstream& binaryFile);

template <typename T1, typename T2, typename ...A>
void serialize(const std::unordered_map<T1, T2, A...> &m, std::ofstream& binaryFile);

template <typename T1, typename T2, typename ...A>
void deserialize(std::unordered_map<T1, T2, A...> &m, std::ifstream& binaryFile);

template <typename T, unsigned long int ...A>
void serialize(const std::array<T, A...> &a, std::ofstream& binaryFile);

template <typename T, unsigned long int ...A>
void deserialize(std::array<T, A...> &a, std::ifstream& binaryFile);

} //namespace cg3

#endif // CG3_SERIALIZE_STD_H
