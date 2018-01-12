/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "array.h"

template<class T, size_t N>
inline cg3::Array<T, N>::Array() : v(0){
    sizes.fill(0);
}

template<class T, size_t N>
constexpr unsigned long int cg3::Array<T, N>::dimensions() const {
    return N;
}

template<class T, size_t N>
template<typename... Sizes>
cg3::Array<T, N>::Array(Sizes... s) {
    static_assert(sizeof...(s) == N, "Wrong number of constructor arguments for Array.");
    unsigned long int args[N] = { static_cast<unsigned long int>(s)... };
    unsigned long int totalSize = 1;
    for (unsigned int i = 0; i < N; i++){
        sizes[i] = args[i];
        totalSize*=args[i];
    }
    v.resize(totalSize);
}

template<class T, size_t N>
template<typename... I>
T& cg3::Array<T, N>::operator ()(I... indices) {
    static_assert(sizeof...(indices) == N, "Wrong number of arguments for operator().");
    unsigned long int args[N] = { static_cast<unsigned long int>(indices)... };
    return v[getIndex(args)];
}

template<class T, size_t N>
template<typename... I>
T cg3::Array<T, N>::operator ()(I... indices) const{
    static_assert(sizeof...(indices) == N, "Wrong number of arguments for operator().");
    unsigned long int args[N] = { static_cast<unsigned long int>(indices)... };
    return v[getIndex(args)];
}

template<class T, size_t N>
template<typename... I>
const T* cg3::Array<T, N>::cArray(I... indices) const {
    static_assert(sizeof...(indices) < N, "Wrong number of arguments for operator cArray().");
    const unsigned long int n = sizeof...(indices);
    unsigned long int args[] = { static_cast<unsigned long int>(indices)... };
    unsigned long int ind = args[0];
    assert(args[0] < sizes[0]);
    unsigned int i;
    for (i = 1; i < n; i++){
        assert(args[i] < sizes[i]);
        ind*=sizes[i];
        ind+=args[i];
    }
    for (; i < N; i++){
        ind*=sizes[i];
    }
    return &v[ind];
}

template<class T, size_t N>
void cg3::Array<T, N>::fill(const T& t) {
    std::fill(v.begin(), v.end(), t);
}

template<class T, size_t N>
unsigned long int cg3::Array<T, N>::size(unsigned long dim) const {
    assert(dim < N);
    return sizes[dim];
}

template<class T, size_t N>
T& cg3::Array<T, N>::min() {
    return *(std::min_element(v.begin(), v.end()));
}

template<class T, size_t N>
const T& cg3::Array<T, N>::min() const {
    return *(std::min_element(v.begin(), v.end()));
}

template<class T, size_t N>
T& cg3::Array<T, N>::max() {
    return *(std::max_element(v.begin(), v.end()));
}

template<class T, size_t N>
const T& cg3::Array<T, N>::max() const {
    return *(std::max_element(v.begin(), v.end()));
}

template<class T, size_t N>
template<typename... Sizes>
void cg3::Array<T, N>::resize(Sizes... s) {
    static_assert(sizeof...(s) == N, "Wrong number of resize arguments for Array.");
    unsigned long int args[N] = { static_cast<unsigned long int>(s)... };
    unsigned long int totalSize = 1;
    for (unsigned int i = 0; i < N; i++){
        sizes[i] = args[i];
        totalSize*=args[i];
    }
    v.resize(totalSize);
}

template<class T, size_t N>
template<typename... Sizes>
void cg3::Array<T, N>::conservativeResize(Sizes... s) {
    static_assert(sizeof...(s) == N, "Wrong number of resize arguments for Array.");
    unsigned long int newSizes[N] = { static_cast<unsigned long int>(s)... };
    unsigned long int newTotalSize = 1;
    for (unsigned int i = 0; i < N; i++)
        newTotalSize*=newSizes[i];
    std::vector<T> newVector(newTotalSize);

    for (unsigned long int i = 0; i < v.size() || i < newTotalSize; i++){
        std::array<unsigned long int, N> indices = reverseIndex(i);
        bool outOfBound = false;
        for (unsigned long int j = 0; j < N; j++)
            if (indices[j] >= newSizes[j])
                outOfBound = true;
        if (!outOfBound){
            newVector[getIndex(indices.data(), newSizes)] = v[i];
        }
    }

    for (unsigned long int i = 0; i < sizes.size(); i++){
        sizes[i] = newSizes[i];
    }

    v = std::move(newVector);
}

template<class T, size_t N>
void cg3::Array<T, N>::clear() {
    v.clear();
    for (unsigned int i = 0; i < N; i++)
        sizes[i] = 0;
}

template<class T, size_t N>
void cg3::Array<T, N>::serialize(std::ofstream &binaryFile) const {
    cg3::serializeObjectAttributes("cg3Array" + std::to_string(N) + "D", binaryFile, sizes, v);
}

template<class T, size_t N>
void cg3::Array<T, N>::deserialize(std::ifstream &binaryFile) {
    cg3::deserializeObjectAttributes("cg3Array"  + std::to_string(N)+ "D", binaryFile, sizes, v);
}

template<class T, size_t N>
unsigned long int cg3::Array<T, N>::getIndex(const unsigned long indices[]) const {
    unsigned long int ind = indices[0];
    assert(indices[0] < sizes[0]);
    for (unsigned int i = 1; i < N; i++){
        assert(indices[i] < sizes[i]);
        ind*=sizes[i];
        ind+=indices[i];
    }
    return ind;
}

template<class T, size_t N>
std::array<unsigned long int, N> cg3::Array<T, N>::reverseIndex(unsigned int index) {
    std::array<unsigned long int, N> indices;
    for (long int i = N-1; i >= 0; i--){
        indices[i] = index%sizes[i];
        index/= sizes[i];
    }
    return indices;
}

template<class T, size_t N>
unsigned long cg3::Array<T, N>::getIndex(const unsigned long indices[], const unsigned long sizes[]) {
    unsigned long int ind = indices[0];
    assert(indices[0] < sizes[0]);
    for (unsigned int i = 1; i < N; i++){
        assert(indices[i] < sizes[i]);
        ind*=sizes[i];
        ind+=indices[i];
    }
    return ind;
}
