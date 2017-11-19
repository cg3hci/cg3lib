#include "array2d.h"

namespace cg3 {

///
/// Array2D
///

/**
 * @brief Array2D<T>::Array2D
 * Initializes a 2D array with 0 rows and 0 columns
 */
template <class T>
inline Array2D<T>::Array2D() : sizeX(0), sizeY(0) {
    v.resize(0);
}

/**
 * @brief Array2D<T>::Array2D
 * Initializes a 2D array with sizeX rows and sizeY columns
 * All the velues of the array will be initialized to 0
 *
 * @param sizeX
 * @param sizeY
 */
template <class T>
inline Array2D<T>::Array2D(unsigned long int sizeX, unsigned long int sizeY) : sizeX(sizeX), sizeY(sizeY) {
    v.resize(sizeX*sizeY);
}

/**
 * @brief Array2D<T>::Array2D
 * Initializzes a 2D array with sizeX rows and sizeY columns.
 * All the values of the array will be initialized to the value passed as a parameter
 *
 * @param sizeX
 * @param sizeY
 * @param value
 */
template <class T>
inline Array2D<T>::Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value) : sizeX(sizeX), sizeY(sizeY) {
    v.resize(sizeX*sizeY, value);
}

/**
 * @brief Array2D<T>::operator ()
 * Access to the i,j element of the array
 *
 * @param i: row of the desired element
 * @param j: column of the desired element
 * @return a reference of the element in position i,j
 */
template <class T>
inline T& Array2D<T>::operator ()(unsigned long int i, unsigned long int j) {
    return v[getIndex(i,j)];
}

template <class T>
inline T Array2D<T>::operator ()(unsigned long int i, unsigned long int j) const {
    return v[getIndex(i,j)];
}

template <class T>
inline const T* Array2D<T>::operator ()(unsigned long int i) const{
    assert (i < sizeX);
    return &(v[sizeY*i]);
}

template <class T>
inline unsigned long int Array2D<T>::getSizeX() const {
    return sizeX;
}

template <class T>
inline unsigned long int Array2D<T>::getSizeY() const{
    return sizeY;
}

template <class T>
inline T&Array2D<T>::getMin() {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
const T&Array2D<T>::getMin() const {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
inline T&Array2D<T>::getMax() {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
const T&Array2D<T>::getMax() const {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
inline void Array2D<T>::setConstant(const T& c) {
    std::fill(v.begin(), v.end(), c);
}

template <class T>
inline void Array2D<T>::resize(unsigned long int x, unsigned long int y) {
    v.resize(x*y);
    sizeX = x;
    sizeY = y;
}

template <class T>
inline void Array2D<T>::resize(unsigned long int x, unsigned long int y, const T& value) {
    v.resize(x*y, value);
    sizeX = x;
    sizeY = y;
}

template<class T>
inline void Array2D<T>::conservativeResize(unsigned long x, unsigned long y) {
    std::vector<T> newVector(x*y);
    for (unsigned int i = 0; i < sizeX || i < x; i++){
        for (unsigned int j = 0; j < sizeY || j < y; j++){
            int newIndex = j + y*i;
            int oldIndex = getIndex(i,j);
            newVector[newIndex] = v[oldIndex];
        }
    }
    sizeX = x;
    sizeY = y;
    v = newVector;
}

template<class T>
inline void Array2D<T>::clear() {
    v.clear();
    sizeX = sizeY = 0;
}

template <class T>
inline void Array2D<T>::serializeOld(std::ofstream& binaryFile) const {
    SerializerOld::serialize(sizeX, binaryFile);
    SerializerOld::serialize(sizeY, binaryFile);
    for (unsigned int i = 0; i < v.size(); ++i)
        SerializerOld::serialize(v[i], binaryFile);
}

template <class T>
inline bool Array2D<T>::deserializeOld(std::ifstream& binaryFile) {
    Array2D<T> tmp;
    int begin = binaryFile.tellg();
    if (SerializerOld::deserialize(tmp.sizeX, binaryFile) &&
            SerializerOld::deserialize(tmp.sizeY, binaryFile)) {
        tmp.v.resize(tmp.sizeX*tmp.sizeY);
        for (unsigned int i = 0; i < tmp.v.size(); ++i){
            if (! SerializerOld::deserialize(tmp.v[i], binaryFile)){
                binaryFile.seekg(begin);
                return false;
            }
        }
        *this = std::move(tmp);
        return true;
    }
    else{
        binaryFile.clear();
        binaryFile.seekg(begin);
        return false;
    }
}

template<class T>
inline void Array2D<T>::serialize(std::ofstream& binaryFile) const {
    Serializer::serializeObjectAttributes("cg3Array2D", binaryFile, sizeX, sizeY, v);
}

template<class T>
inline void Array2D<T>::deserialize(std::ifstream& binaryFile) {
    Serializer::deserializeObjectAttributes("cg3Array2D", binaryFile, sizeX, sizeY, v);
}

template <class T>
inline unsigned long int Array2D<T>::getIndex(unsigned long int i, unsigned long int j) const {
    assert (i < sizeX);
    assert (j < sizeY);
    return j + sizeY*i;
}

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a) {
    for (unsigned int i = 0; i < a.getSizeX(); i++){
        for (unsigned int j = 0; j < a.getSizeY(); j++){
            inputStream << std::setw(4) <<a(i,j) << " ";
        }
        inputStream << "\n";
    }
    return inputStream;
}

}
