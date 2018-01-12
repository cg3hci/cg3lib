/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "bounding_box.h"
#include "../io/load_save_file.h"

namespace cg3 {

/****************
 * Constructors *
 ****************/

/**
 * \~English
 * @brief Constructor, creates a bounding box and calls BoundingBox::reset() method
 *
 * \~Italian
 * @brief Costruttore, crea un bounding box e chiama il metodo BoundingBox::reset()
 */
inline BoundingBox::BoundingBox() {
    reset();
}

/**
 * \~English
 * @brief Constructor, creates a bounding box whith with minimum equal to the parameter \c min and maximum equal to the parameter \c max
 * @param[in] min: point setted as minimum point of the bounding box
 * @param[in] max: point setted as maximum point of the bounding box
 *
 * \~Italian
 * @brief Costruttore, crea un bounding box con limite minimo pari a \c min e limite massimo pari a \c max
 * @param[in] min: punto minimo che verrà settato
 * @param[in] max: punto massimo che verrà settato
 */
inline BoundingBox::BoundingBox(const Pointd& min, const Pointd& max) : minCoord(min), maxCoord(max) {
}

/*************************
* Public Inline Methods *
*************************/

/**
 * \~English
 * @brief Returns the minimum point of the bounding box
 * @return The minimum point
 *
 * \~Italian
 * @brief Restituisce il punto minimo del bounding box
 * @return Il punto minimo
 */
inline const Pointd& BoundingBox::getMin() const {
    return minCoord;
}

inline const Pointd& BoundingBox::min() const {
    return minCoord;
}

/**
 * \~English
 * @brief Returns the maximum point of the bounding box
 * @return The maximum point
 *
 * \~Italian
 * @brief Restituisce il punto massimo del bounding box
 * @return Il punto massimo
 */
inline const Pointd& BoundingBox::getMax() const {
    return maxCoord;
}

inline const Pointd& BoundingBox::max() const {
    return maxCoord;
}

/**
 * \~English
 * @brief Returns the x component of the minimum point of the bounding box
 * @return X component of the minimum point
 *
 * \~Italian
 * @brief Restituisce la componente x del punto minimo del bounding box
 * @return La componente x del punto minimo
 */
inline const double& BoundingBox::getMinX() const {
    return minCoord.x();
}

inline const double& BoundingBox::minX() const {
    return minCoord.x();
}

/**
 * \~English
 * @brief Returns the y component of the minimum point of the bounding box
 * @return Y component of the minimum point
 *
 * \~Italian
 * @brief Restituisce la componente y del punto minimo del bounding box
 * @return La componente y del punto minimo
 */
inline const double& BoundingBox::getMinY() const {
    return minCoord.y();
}

inline const double& BoundingBox::minY() const {
    return minCoord.y();
}

/**
 * \~English
 * @brief Returns the z component of the minimum point of the bounding box
 * @return Z component of the minimum point
 *
 * \~Italian
 * @brief Restituisce la componente z del punto minimo del bounding box
 * @return La componente z del punto minimo
 */
inline const double& BoundingBox::getMinZ() const {
    return minCoord.z();
}

inline const double& BoundingBox::minZ() const {
    return minCoord.z();
}

/**
 * \~English
 * @brief Returns the x component of the maximum point of the bounding box
 * @return X component of the maximum point
 *
 * \~Italian
 * @brief Restituisce la componente x del punto massimo del bounding box
 * @return La componente x del punto massimo
 */
inline const double& BoundingBox::getMaxX() const {
    return maxCoord.x();
}

inline const double& BoundingBox::maxX() const {
    return maxCoord.x();
}

/**
 * \~English
 * @brief Returns the y component of the maximum point of the bounding box
 * @return Y component of the maximum point
 *
 * \~Italian
 * @brief Restituisce la componente y del punto massimo del bounding box
 * @return La componente y del punto massimo
 */
inline const double& BoundingBox::getMaxY() const {
    return maxCoord.y();
}

inline const double& BoundingBox::maxY() const {
    return maxCoord.y();
}

/**
 * \~English
 * @brief Returns the Z component of the maximum point of the bounding box
 * @return Z component of the maximum point
 *
 * \~Italian
 * @brief Restituisce la componente z del punto massimo del bounding box
 * @return La componente z del punto massimo
 */
inline const double& BoundingBox::getMaxZ() const {
    return maxCoord.z();
}

inline const double& BoundingBox::maxZ() const {
    return maxCoord.z();
}

inline double BoundingBox::getLengthX() const {
    return maxCoord.x() - minCoord.x();
}

inline double BoundingBox::getLengthY() const {
    return maxCoord.y() - minCoord.y();
}

inline double BoundingBox::getLengthZ() const {
    return maxCoord.z() - minCoord.z();
}

/**
 * \~English
 * @brief Calculates the center of the bounding box
 * @return The point centered in the bounding box
 *
 * \~Italian
 * @brief Calcola il centro del bounding box
 * @return Il punto al centro del bounding box
 */
inline Pointd BoundingBox::center() const {
    return (minCoord + maxCoord) * 0.5;
}

/**
 * \~English
 * @brief Calculates the length of the diagonal of the bounding box
 * @return The length of the diagonal of the bounding box
 *
 * \~Italian
 * @brief Calcola la lunghezza della diagonale del bounding box
 * @return La lunghezza della diagonale del bounding box
 */
inline double BoundingBox::diag() const {
    return (minCoord - maxCoord).getLength();
}

inline bool BoundingBox::isValid() const {
    return minCoord.x() <= maxCoord.x() && minCoord.y() <= maxCoord.y() && minCoord.z() <= maxCoord.z();
}

inline bool BoundingBox::isStrictlyIntern(const Pointd &p) const {
    return (p.x() > minCoord.x() && p.y() > minCoord.y() && p.z() > minCoord.z() &&
            p.x() < maxCoord.x() && p.y() < maxCoord.y() && p.z() < maxCoord.z());
}

inline bool BoundingBox::isStrictlyInside(const Pointd& p) const {
    return isStrictlyIntern(p);
}

inline bool BoundingBox::isStrictlyIntern(double px, double py, double pz) const {
    return (px > minCoord.x() && py > minCoord.y() && pz > minCoord.z() &&
            px < maxCoord.x() && py < maxCoord.y() && pz < maxCoord.z());
}

inline bool BoundingBox::isStrictlyInside(double px, double py, double pz) const {
    return isStrictlyIntern(px, py, pz);
}

inline bool BoundingBox::isIntern(const Pointd &p) const {
    return (p.x() >= minCoord.x() && p.y() >= minCoord.y() && p.z() >= minCoord.z() &&
            p.x() <= maxCoord.x() && p.y() <= maxCoord.y() && p.z() <= maxCoord.z());
}

inline bool BoundingBox::isInside(const Pointd& p) const {
    return isIntern(p);
}

inline bool BoundingBox::isIntern(double px, double py, double pz) const {
    return (px >= minCoord.x() && py >= minCoord.y() && pz >= minCoord.z() &&
            px <= maxCoord.x() && py <= maxCoord.y() && pz <= maxCoord.z());
}

inline bool BoundingBox::isInside(double px, double py, double pz) const {
    return isIntern(px, py, pz);
}

inline bool BoundingBox::isEpsilonIntern(const Pointd& p, double epsilon) const {
    return (p.x() >= minCoord.x()-epsilon && p.y() >= minCoord.y()-epsilon && p.z() >= minCoord.z()-epsilon &&
            p.x() <= maxCoord.x()+epsilon && p.y() <= maxCoord.y()+epsilon && p.z() <= maxCoord.z()+epsilon);
}

inline bool BoundingBox::isEpsilonInside(const Pointd& p, double epsilon) const {
    return isEpsilonIntern(p, epsilon);
}

inline bool BoundingBox::isEpsilonIntern(double px, double py, double pz, double epsilon) const {
    return (px >= minCoord.x()-epsilon && py >= minCoord.y()-epsilon && pz >= minCoord.z()-epsilon &&
            px <= maxCoord.x()+epsilon && py <= maxCoord.y()+epsilon && pz <= maxCoord.z()+epsilon);
}

inline bool BoundingBox::isEpsilonInside(double px, double py, double pz, double epsilon) const {
    return isEpsilonIntern(px, py, pz, epsilon);
}

/**
 * @brief BoundingBox::intersect
 * @param[in] otherBox
 * @return true if otherBox overlaps this box
 * @link http://gamemath.com/2011/09/detecting-whether-two-boxes-overlap/
 */
inline bool BoundingBox::intersect(const BoundingBox& otherBox) {
    if (getMaxX() <= otherBox.getMinX()) return false; // a is left of b
    if (getMinX() >= otherBox.getMaxX()) return false; // a is right of b
    if (getMaxY() <= otherBox.getMinY()) return false; // a is above b
    if (getMinY() >= otherBox.getMaxY()) return false; // a is below b
    if (getMaxZ() <= otherBox.getMinZ()) return false; // a is behind b
    if (getMinZ() >= otherBox.getMaxZ()) return false; // a is in front b
    return true; //boxes overlap
}

/**
 * @brief BoundingBox::getExtremes
 * @param[out] extremes: a vector of 8 Pointd which are the extremes of the bounding box
 */
inline void BoundingBox::getExtremes(std::vector<Pointd>& extremes) const {
    extremes.resize(8);
    extremes[0] = minCoord;
    extremes[1].set(maxCoord.x(), minCoord.y(), minCoord.z());
    extremes[2].set(maxCoord.x(), minCoord.y(), maxCoord.z());
    extremes[3].set(minCoord.x(), minCoord.y(), maxCoord.z());
    extremes[4].set(minCoord.x(), maxCoord.y(), minCoord.z());
    extremes[5].set(maxCoord.x(), maxCoord.y(), minCoord.z());
    extremes[6] = maxCoord;
    extremes[7].set(minCoord.x(), maxCoord.y(), maxCoord.z());
}

/**
 * @brief BoundingBox::getExtremes
 * @return a vector of 8 Pointd which are the extremes of the bounding box
 */
inline std::vector<Pointd> BoundingBox::getExtremes() const {
    std::vector<Pointd> extremes;
    getExtremes(extremes);
    return extremes;
}

/**
 * @brief BoundingBox::operator ()
 * @param i
 * @return a double which is a coordinate of minCoord [0-2] or a coordinate of maxCoord[3-5]
 */
inline const double& BoundingBox::operator ()(unsigned int i) const {
    assert(i < 6);
    switch (i%6){
        case 0: return minCoord.x();
        case 1: return minCoord.y();
        case 2: return minCoord.z();
        case 3: return maxCoord.x();
        case 4: return maxCoord.y();
        case 5: return maxCoord.z();
    }
    return minCoord.x();
}

/**
 * @brief BoundingBox::operator []
 * @param i
 * @return a Pointd which is an extreme of the bounding box [0-7]
 */
inline Pointd BoundingBox::operator[](unsigned int i) const {
    assert(i < 8);
    switch (i%8){
        case 0: return minCoord;
        case 1: return Pointd(maxCoord.x(), minCoord.y(), minCoord.z());
        case 2: return Pointd(maxCoord.x(), minCoord.y(), maxCoord.z());
        case 3: return Pointd(minCoord.x(), minCoord.y(), maxCoord.z());
        case 4: return Pointd(minCoord.x(), maxCoord.y(), minCoord.z());
        case 5: return Pointd(maxCoord.x(), maxCoord.y(), minCoord.z());
        case 6: return maxCoord;
        case 7: return Pointd(minCoord.x(), maxCoord.y(), maxCoord.z());
    }
    return minCoord.x();
}

/**
 * @brief BoundingBox::saveOnObj
 *
 * It saves the bounding box as a quad mesh in the obj file saved on parameters.
 *
 * @param filename
 * @param c
 */
inline void BoundingBox::saveOnObj(const std::string& filename, const Color &c) const {
    std::vector<double> v {
        minCoord.x(), minCoord.y(), minCoord.z(),
        maxCoord.x(), minCoord.y(), minCoord.z(),
        maxCoord.x(), minCoord.y(), maxCoord.z(),
        minCoord.x(), minCoord.y(), maxCoord.z(),
        minCoord.x(), maxCoord.y(), minCoord.z(),
        maxCoord.x(), maxCoord.y(), minCoord.z(),
        maxCoord.x(), maxCoord.y(), maxCoord.z(),
        minCoord.x(), maxCoord.y(), maxCoord.z()
    };
    std::vector<int> f {
        0, 1, 2, 3,
        7, 6, 5, 4,
        2, 1, 5, 6,
        0, 3, 7, 4,
        3, 2, 6, 7,
        1, 0, 4, 5
    };
    int r = c.red(), g = c.green(), b = c.blue();
    std::vector<int> cl {
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b
    };
    loadSave::saveMeshOnObj(filename, 8, 6, v.data(), f.data(), loadSave::QUAD_MESH, loadSave::COLOR_FACES, loadSave::dummies::dummyVectorDouble.data(), loadSave::RGB, loadSave::dummies::dummyVectorFloat.data(), cl.data());
}

/**
 * \~English
 * @brief Modifies the minimum point of the bounding box
 * @param[in] min: point setted as minimum point
 *
 * \~Italian
 * @brief Modifica il punto minimo del bounding box
 * @param[in] min: punto settato come punto minimo
 */
inline void BoundingBox::setMin(const Pointd& min) {
    this->minCoord = min;
}

/**
 * @brief BoundingBox::min
 * @see setMin()
 */
inline Pointd&BoundingBox::min() {
    return minCoord;
}

/**
 * \~English
 * @brief Modifies the maximum point of the bounding box
 * @param[in] max: point setted as maximum point
 *
 * \~Italian
 * @brief Modifica il punto massimo del bounding box
 * @param[in] max: punto settato come punto massimo
 */
inline void BoundingBox::setMax(const Pointd& max) {
    this->maxCoord = max;
}

/**
 * @brief BoundingBox::max
 * @see setMax()
 */
inline Pointd& BoundingBox::max() {
    return maxCoord;
}

/**
 * \~English
 * @brief Modifies the minimum point of the bounding box
 * @param[in] x: value setted as \c x component of the minimum point
 * @param[in] y: value setted as \c y component of the minimum point
 * @param[in] z: value setted as \c z component of the minimum point
 *
 * \~Italian
 * @brief Modifica il punto minimo del bounding box
 * @param[in] x: valore settato come componente \c x del punto minimo
 * @param[in] y: valore settato come componente \c y del punto minimo
 * @param[in] z: valore settato come componente \c z del punto minimo
 */
inline void BoundingBox::setMin(double x, double y, double z) {
    minCoord.set(x, y, z);
}

/**
 * \~English
 * @brief Modifies the maximum point of the bounding box
 * @param[in] x: value setted as \c x component of the maximum point
 * @param[in] y: value setted as \c y component of the maximum point
 * @param[in] z: value setted as \c z component of the maximum point
 *
 * \~Italian
 * @brief Modifica il punto massimo del bounding box
 * @param[in] x: valore settato come componente \c x del punto massimo
 * @param[in] y: valore settato come componente \c y del punto massimo
 * @param[in] z: valore settato come componente \c z del punto massimo
 */
inline void BoundingBox::setMax(double x, double y, double z) {
    maxCoord.set(x, y, z);
}

/**
 * \~English
 * @brief Modifies the \c x component of the minimum point of the bounding box
 * @param[in] x: value that will be setted as \c x component of the minimum point
 *
 * \~Italian
 * @brief Modifica la componente \c x del punto minimo del bounding box
 * @param[in] x: valore settato come componente \c x del punto minimo
 */
inline void BoundingBox::setMinX(double x) {
    minCoord.setX(x);
}

inline double& BoundingBox::minX() {
    return minCoord.x();
}

/**
 * \~English
 * @brief Modifies the \c y component of the minimum point of the bounding box
 * @param[in] y: value that will be setted as \c y component of the minimum point
 *
 * \~Italian
 * @brief Modifica la componente \c y del punto minimo del bounding box
 * @param[in] y: valore settato come componente \c y del punto minimo
 */
inline void BoundingBox::setMinY(double y) {
    minCoord.setY(y);
}

inline double& BoundingBox::minY() {
    return minCoord.y();
}

/**
 * \~English
 * @brief Modifies the \c z component of the minimum point of the bounding box
 * @param[in] z: value that will be setted as \c z component of the minimum point
 *
 * \~Italian
 * @brief Modifica la componente \c z del punto minimo del bounding box
 * @param[in] z: valore settato come componente \c z del punto minimo
 */
inline void BoundingBox::setMinZ(double z) {
    minCoord.setZ(z);
}

inline double& BoundingBox::minZ() {
    return minCoord.z();
}

/**
 * \~English
 * @brief Modifies the \c x component of the maximum point of the bounding box
 * @param[in] x: value that will be setted as \c x component of the maximum point
 *
 * \~Italian
 * @brief Modifica la componente \c x del punto massimo del bounding box
 * @param[in] x: valore settato come componente \c x del punto massimo
 */
inline void BoundingBox::setMaxX(double x) {
    maxCoord.setX(x);
}

inline double&BoundingBox::maxX() {
    return maxCoord.x();
}

/**
 * \~English
 * @brief Modifies the \c y component of the maximum point of the bounding box
 * @param[in] y: value that will be setted as \c y component of the maximum point
 *
 * \~Italian
 * @brief Modifica la componente \c y del punto massimo del bounding box
 * @param[in] y: valore settato come componente \c y del punto massimo
 */
inline void BoundingBox::setMaxY(double y) {
    maxCoord.setY(y);
}

inline double&BoundingBox::maxY() {
    return maxCoord.y();
}

/**
 * \~English
 * @brief Modifies the \c z component of the maximum point of the bounding box
 * @param[in] z: value that will be setted as \c z component of the maximum point
 *
 * \~Italian
 * @brief Modifica la componente \c z del punto massimo del bounding box
 * @param[in] z: valore settato come componente \c z del punto massimo
 */
inline void BoundingBox::setMaxZ(double z) {
    maxCoord.setZ(z);
}

inline double& BoundingBox::maxZ() {
    return maxCoord.z();
}

/**
 * \~English
 * @brief Resets the bounding box.
 *
 * Sets the three components of minimum to +std::numeric_limits<double>::max() and the three components of maximum to -std::numeric_limits<double>::max().
 * In this way, it is faster to create a new bounding box (every number is greater than -std::numeric_limits<double>::max() and every number is lower
 * than std::numeric_limits<double>::max()).
 *
 * \~Italian
 * @brief Resetta il bounding box.
 *
 * Setta le tre componenti del punto minimo a std::numeric_limits<double>::max() e del punto massimo a -std::numeric_limits<double>::max().
 * In questo modo, è più veloce creare un nuovo bounding box (ogni numero è maggiore di -std::numeric_limits<double>::max() e ogni numero è minore di
 * std::numeric_limits<double>::max()).
 */
inline void BoundingBox::reset() {
    minCoord = Pointd( std::numeric_limits<double>::max(),  std::numeric_limits<double>::max(),  std::numeric_limits<double>::max());
    maxCoord = Pointd(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
}

inline double& BoundingBox::operator()(unsigned int i) {
    assert(i < 6);
    switch (i%6){
        case 0: return minCoord.x();
        case 1: return minCoord.y();
        case 2: return minCoord.z();
        case 3: return maxCoord.x();
        case 4: return maxCoord.y();
        case 5: return maxCoord.z();
    }
    return minCoord.x();
}

inline void BoundingBox::serialize(std::ofstream& binaryFile) const {
    serializeObjectAttributes("cg3BoundingBox", binaryFile, minCoord, maxCoord);
}

inline void BoundingBox::deserialize(std::ifstream& binaryFile) {
    deserializeObjectAttributes("cg3BoundingBox", binaryFile, minCoord, maxCoord);
}

}

//hash specialization
inline std::size_t std::hash<cg3::BoundingBox>::operator()(const cg3::BoundingBox &k) const{
    std::size_t h = 0;
    cg3::hashCombine(h, k.min(), k.max());
    return h;
}
