/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "point3.h"

#include <assert.h>
#include <iostream>
#include <cmath>

/****************
 * Constructors *
 ****************/

namespace cg3 {

/**
 * @brief Constructor, initializes the point with the input values
 * @param[in] x: value of \c x component, default 0
 * @param[in] y: value of \c y component, default 0
 * @param[in] z: value of \c z component, default 0
 */
template <class T>
inline Point3<T>::Point3(T x, T y, T z) :
    xCoord(x),
    yCoord(y),
    zCoord(z)
{
}

#ifdef  CG3_WITH_EIGEN
template <class T>
Point3<T>::Point3(const Eigen::VectorXd& v) :
    xCoord(v(0)),
    yCoord(v(1)),
    zCoord(v(2))
{
}
#endif

#ifdef CG3_CINOLIB_DEFINED
template <class T>
Point3<T>::Point3(const cinolib::vec3<T>& v) :
    xCoord(v.x()),
    yCoord(v.y()),
    zCoord(v.z())
{
}
#endif


/*************************
* Public Inline Methods *
*************************/

/**
 * @brief Returns the \c x component of the point/vector
 * @return \c x component
 */
template <class T>
inline const T& Point3<T>::x() const
{
    return this->xCoord;
}

/**
 * @brief Returns the \c y component of the point/vector
 * @return \c y component
 */
template <class T>
inline const T& Point3<T>::y() const
{
    return this->yCoord;
}

/**
 * @brief Returns the \c z component of the point/vector
 * @return \c z component
 */
template <class T>
inline const T& Point3<T>::z() const
{
    return this->zCoord;
}

/**
 * @brief Function that calculates the euclidean distance between two points
 * @param[in] otherPoint: point on which is calculated the distance
 * @return The distance between the point and \c otherPoint
 */
template <class T>
inline double Point3<T>::dist(const Point3<T>& otherPoint) const
{
    return sqrt ( std::pow((xCoord - otherPoint.xCoord), 2) +
                  std::pow((yCoord - otherPoint.yCoord), 2) +
                  std::pow((zCoord - otherPoint.zCoord), 2) );
}

/**
 * @brief Function that calculates the dot product between two vectors
 * @param[in] otherVector: vector on which is calculated the dot product
 * @return The dot product between this and \c otherVector
 */
template <class T>
inline double Point3<T>::dot(const Point3<T>& otherVector) const
{
    return xCoord * otherVector.xCoord +
           yCoord * otherVector.yCoord +
            zCoord * otherVector.zCoord;
}

/**
 * @brief Function that calculates the angle in radians between the two vectors
 * @param[in] otherVector: vector on which is calculated the angle
 * @return The angle in radians between this and \c otherVector
 */
template<class T>
inline double Point3<T>::angleRAD(const Point3<T>& otherVector) const
{
	Point3<T> u = *this; u.normalize();
	Point3<T> v = otherVector;    v.normalize();
    double dot   = std::min( 1.0, u.dot(v));
           dot   = std::max(-1.0, dot);
    double angle = acos(dot);
    assert(!std::isnan(angle));
    return angle;
}

/**
 * @brief Function that calculates the angle in degrees between the two vectors
 * @param[in] otherVector: vector on which is calculated the angle
 * @return The angle in degrees between this and \c otherVector
 */
template<class T>
inline double Point3<T>::angleDEG(const Point3<T>& otherVector) const
{
    return angleRAD(otherVector)*180.0/M_PI;
}

/**
 * @brief Function which calculates the cross product between two vectors
 * @param[in] otherVector: vector on which is calculated the cross product
 * @return The cross product between this and \c otherVector
 */
template <class T>
inline Point3<T> Point3<T>::cross(const Point3<T>& otherVector) const
{
	return Point3<T>(yCoord * otherVector.zCoord - zCoord * otherVector.yCoord,
                 zCoord * otherVector.xCoord - xCoord * otherVector.zCoord,
                 xCoord * otherVector.yCoord - yCoord * otherVector.xCoord);
}

/**
 * @brief Function which calculated the length of the vector
 * @return The length of the vector
 */
template <class T>
inline double Point3<T>::length() const
{
    return sqrt( xCoord*xCoord + yCoord*yCoord + zCoord*zCoord );
}

/**
 * \~Italian
 * @brief Operatore per il calcolo della lunghezza al quadrato di un vettore
 * @return La lunghezza al quadrato del vettore this
 */
template <class T>
inline double Point3<T>::lengthSquared() const
{
    return xCoord * xCoord + yCoord * yCoord + zCoord * zCoord;
}

template<class T>
inline Point3<T> Point3<T>::orthogonalVector() const
{
    if ((fabs(yCoord) >= 0.9 * fabs(xCoord)) && (fabs(zCoord) >= 0.9 * fabs(xCoord)))
		return Point3<T>(0.0, -zCoord, yCoord);
    else if ((fabs(xCoord) >= 0.9 * fabs(yCoord)) && (fabs(zCoord) >= 0.9 * fabs(yCoord)))
		return Point3<T>(-zCoord, 0.0, xCoord);
    else
		return Point3<T>(-yCoord, xCoord, 0.0);
}

/**
 * \~Italian
 * @brief Funzione di minimo tra punti/vettori.
 *
 * Ogni componente del punto/vettore restituito sarà uguale alla corrispondente componente minore tra il punto/vettore
 * this e otherPoint.
 *
 * @param[in] otherPoint: punto/vettore con cui viene calcolata la funzione di minimo
 *
 * @return Il punto/vettore dei minimi
 */
template <class T>
inline Point3<T> Point3<T>::min(const Point3<T>& otherPoint) const
{
	return Point3<T>(std::min(x(), otherPoint.x()),
                    std::min(y(), otherPoint.y()),
                    std::min(z(), otherPoint.z()));
}

/**
 * \~Italian
 * @brief Funzione di massimo tra punti/vettori.
 *
 * Ogni componente del punto/vettore restituito sarà uguale alla corrispondente componente maggiore tra il punto/vettore
 * this e otherPoint.
 *
 * @param[in] otherPoint: punto/vettore con cui viene calcolata la funzione di massimo
 *
 * @return Il punto/vettore dei massimi
 */
template <class T>
inline Point3<T> Point3<T>::max(const Point3<T>& otherPoint) const
{
	return Point3<T>(std::max(x(), otherPoint.x()),
                    std::max(y(), otherPoint.y()),
                    std::max(z(), otherPoint.z()));
}

template <class T>
inline const T& Point3<T>::operator[](unsigned int i) const
{
    assert(i < 3);
    switch (i){
        case 0: return xCoord;
        case 1: return yCoord;
        case 2: return zCoord;
    }
    return xCoord;
}

template <class T>
inline const T& Point3<T>::operator()(unsigned int i) const
{
    assert(i < 3);
    switch (i){
        case 0: return xCoord;
        case 1: return yCoord;
        case 2: return zCoord;
    }
    return xCoord;
}

/**
 * \~Italian
 * @brief Operatore di uguaglianza tra punti/vettori.
 *
 * Due punti/vettori sono considerati uguali se tutte e tre le loro componenti sono uguali.
 *
 * @param[in] otherPoint: punto/vettore con cui viene verificata l'uguaglianza
 * @return True se il punto e otherPoint sono uguali, false altrimenti
 */
template <class T>
inline bool Point3<T>::operator == (const Point3<T>& otherPoint) const
{
    if ( otherPoint.xCoord != xCoord )	return false;
    if ( otherPoint.yCoord != yCoord )	return false;
    if ( otherPoint.zCoord != zCoord )	return false;
    return true;
}

/**
 * \~Italian
 * @brief Operatore di disuguaglianza tra punti/vettori.
 *
 * Due punti/vettori sono considerati diversi se almeno una delle loro componenti è diversa.
 *
 * @param[in] otherPoint: punto/vettore con cui viene verificata la disuguaglianza
 * @return True se il punto e otherPoint sono diversi, false altrimenti
 */
template <class T>
inline bool Point3<T>::operator != (const Point3<T>& otherPoint) const
{
    if ( otherPoint.xCoord != xCoord )	return true;
    if ( otherPoint.yCoord != yCoord )	return true;
    if ( otherPoint.zCoord != zCoord )	return true;
    return false;
}

/**
 * \~Italian
 * @brief Operatore di minore tra punti/vettori.
 *
 * In questo contesto, il punto/vettore è minore di otherPoint se la sua componente x
 * è minore di quella di otherPoint; in caso di uguaglianza si verifica la componente y
 * e in caso di ultieriore uguaglianza la componente z.
 *
 * @param[in] otherPoint: altro punto/vettore
 * @return True se il punto/vettore this è minore di otherPoint, false altrimenti
 */
template <class T>
inline bool Point3<T>::operator < (const Point3<T>& otherPoint) const
{
    if (this->xCoord < otherPoint.xCoord) return true;
    if (this->xCoord > otherPoint.xCoord) return false;
    if (this->yCoord < otherPoint.yCoord) return true;
    if (this->yCoord > otherPoint.yCoord) return false;
    if (this->zCoord < otherPoint.zCoord) return true;
    return false;
}

/**
 * \~Italian
 * @brief Operatore prefisso di negazione, restituisce il punto/vettore negato
 * @return Il punto/vettore negato
 */
template <class T>
inline Point3<T> Point3<T>::operator - () const
{
	return Point3<T>(-xCoord, -yCoord, -zCoord);
}

template <class T>
inline Point3<T> Point3<T>::operator +(const T& scalar) const
{
	return Point3<T>(xCoord + scalar,
                    yCoord + scalar,
                    zCoord + scalar);
}

/**
 * \~Italian
 * @brief Operatore di somma tra punti/vettori
 * @param[in] otherPoint: punto/vettore con cui verrà sommato il punto/vettore this
 * @return Il punto/vettore risultato della somma, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator + (const Point3<T>& otherPoint) const
{
	return Point3<T>(xCoord + otherPoint.xCoord,
                    yCoord + otherPoint.yCoord,
                    zCoord + otherPoint.zCoord);
}

template <class T>
inline Point3<T> Point3<T>::operator -(const T& scalar) const
{
	return Point3<T>(xCoord - scalar,
                    yCoord - scalar,
                    zCoord - scalar);
}

/**
 * \~Italian
 * @brief Operatore di sottrazione tra punti/vettori
 * @param[in] otherPoint: punto/vettore che verrà sottratto al punto/vettore this
 * @return Il punto/vettore risultato della differenza, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator - (const Point3<T>& otherPoint) const
{
	return Point3<T>(xCoord - otherPoint.xCoord,
                    yCoord - otherPoint.yCoord,
                    zCoord - otherPoint.zCoord);
}

/**
 * \~Italian
 * @brief Operatore di prodotto scalare tra un punto/vettore e uno scalare
 * @param[in] scalar: scalare con cui verrà eseguito il prodotto scalare
 * @return Il punto/vettore risultato del prodotto scalare tra tra il punto/vettore this e scalar
 */
template <class T>
inline Point3<T> Point3<T>::operator * (const T& scalar) const
{
	return Point3<T>(xCoord * scalar, yCoord * scalar, zCoord * scalar);
}

/**
 * \~Italian
 * @brief Operatore di prodotto, componente per componente, tra punti/vettori
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il prodotto
 * @return Il punto/vettore risultato del prodotto, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator * (const Point3<T>& otherPoint) const
{
	return Point3<T>(xCoord * otherPoint.xCoord, yCoord * otherPoint.yCoord, zCoord * otherPoint.zCoord);
}

/**
 * \~Italian
 * @brief Operatore di quoziente scalare tra un punto/vettore e uno scalare
 * @param[in] scalar: scalare con cui verrà eseguito il quoziente scalare
 * @return Il punto/vettore risultato del quoziente scalare tra il punto/vettore this e scalar
 */
template <class T>
inline Point3<T> Point3<T>::operator / (const T& scalar) const
{
	return Point3<T>(xCoord / scalar, yCoord / scalar, zCoord / scalar);
}

/**
 * \~Italian
 * @brief Operatore di quoziente, componente per componente, tra punti/vettori
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il quoziente
 * @return Il punto/vettore risultato del quoziente, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator / (const Point3<T>& otherPoint) const
{
	return Point3<T>(xCoord / otherPoint.xCoord, yCoord / otherPoint.yCoord, zCoord / otherPoint.zCoord);
}

/**
 * @brief Returns the \c x component of the point/vector
 * @return \c x component
 */
template <class T>
inline T& Point3<T>::x()
{
    return this->xCoord;
}

/**
 * @brief Returns the \c y component of the point/vector
 * @return \c y component
 */
template <class T>
inline T& Point3<T>::y()
{
    return this->yCoord;
}

/**
 * @brief Returns the \c z component of the point/vector
 * @return \c z component
 */
template <class T>
inline T& Point3<T>::z()
{
    return this->zCoord;
}

/**
 * \~Italian
 * @brief Modifica la componente x del punto/vettore this
 * @param[in] x: valore settato come componente x
 */
template <class T>
inline void Point3<T>::setX(const T& x)
{
    xCoord = x;
}

/**
 * \~Italian
 * @brief Modifica la componente y del punto/vettore this
 * @param[in] y: valore settato come componente y
 */
template <class T>
inline void Point3<T>::setY(const T& y)
{
    yCoord = y;
}

/**
 * \~Italian
 * @brief Modifica la componente z del punto/vettore this
 * @param[in] z: valore settato come componente z
 */
template <class T>
inline void Point3<T>::setZ(const T& z)
{
    zCoord = z;
}

/**
 * \~Italian
 * @brief Modifica le componenti del punto/vettore this
 * @param[in] x: valore settato come componente x
 * @param[in] y: valore settato come componente y
 * @param[in] z: valore settato come componente z
 */
template <class T>
inline void Point3<T>::set(const T& x, const T& y, const T& z)
{
    xCoord = x;
    yCoord = y;
    zCoord = z;
}

/**
 * \~Italian
 * @brief Funzione di normalizzazione di un vettore, in modo tale che la sua lunghezza sia pari a 1
 * @return La lunghezza precedente del vettore prima di essere normalizzato
 */
template <class T>
inline double Point3<T>::normalize()
{
    double len = length();
    xCoord /= len;
    yCoord /= len;
    zCoord /= len;
    return len;
}

/**
 * @brief Returns the normalized vector, such that its length is 1
 * @return
 */
template<class T>
Point3<T> Point3<T>::normalized() const
{
	double len = length();
	return Point3<T>(xCoord/len, yCoord/len, zCoord/len);
}

#ifdef CG3_WITH_EIGEN
template <class T>
Eigen::Vector3d Point3<T>::toEigenVector() const
{
    return Eigen::Vector3d(xCoord, yCoord, zCoord);
}


template <class T>
void Point3<T>::rotate(const Eigen::Matrix3d& matrix, const Point3<T>& centroid)
{
    *this -= centroid;
    *this = mul(matrix, *this);
    *this += centroid;
}
#endif //CG3_WITH_EIGEN

/**
 * \~Italian
 * @brief Applica una matrice di rotazione 3x3 ad un punto/vettore
 * @param[in] m: matrice di rotazione 3x3
 * @param[in] centroid: punto centroide della rotazione, di default (0,0,0)
 */
template <class T>
inline void Point3<T>::rotate(double matrix[3][3], const Point3<T>& centroid)
{
    *this -= centroid;
    *this = mul(matrix, *this);
    *this += centroid;
}

template<class T>
void Point3<T>::serialize(std::ofstream& binaryFile) const
{
    serializeObjectAttributes("cg3Point3D", binaryFile, xCoord, yCoord, zCoord);
}

template<class T>
void Point3<T>::deserialize(std::ifstream& binaryFile)
{
    deserializeObjectAttributes("cg3Point3D", binaryFile, xCoord, yCoord, zCoord);
}

template <class T>
inline T& Point3<T>::operator[](unsigned int i)
{
    assert(i < 3);
    switch (i){
        case 0: return xCoord;
        case 1: return yCoord;
        case 2: return zCoord;
    }
    return xCoord;
}

template <class T>
inline T& Point3<T>::operator()(unsigned int i)
{
    assert(i < 3);
    switch (i){
        case 0: return xCoord;
        case 1: return yCoord;
        case 2: return zCoord;
    }
    return xCoord;
}

/**
 * \~Italian
 * @brief Operatore di somma e assegnamento tra punti/vettori.
 *
 * Il risultato della somma è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore con cui verrà sommato il punto/vettore this
 * @return Il punto/vettore risultato della somma, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator += (const Point3<T>& otherPoint)
{
    xCoord += otherPoint.xCoord;
    yCoord += otherPoint.yCoord;
    zCoord += otherPoint.zCoord;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di sottrazione e assegnamento tra punti/vettori.
 *
 * Il risultato della differenza è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore che verrà sottratto al punto/vettore this
 * @return Il punto/vettore risultato della differenza, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator -= (const Point3<T>& otherPoint)
{
    xCoord -= otherPoint.xCoord;
    yCoord -= otherPoint.yCoord;
    zCoord -= otherPoint.zCoord;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di prodotto scalare e assegnamento tra un punto/vettore e uno scalare.
 *
 * Il risultato del prodotto scalare è assegnato al punto/vettore this.
 *
 * @param[in] scalar: scalare con cui verrà eseguito il prodotto scalare
 * @return Il punto/vettore risultato del prodotto scalare tra tra il punto/vettore this e scalar
 */
template <class T>
inline Point3<T> Point3<T>::operator *= (const T& scalar)
{
    xCoord *= scalar;
    yCoord *= scalar;
    zCoord *= scalar;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di prodotto, componente per componente, e assegnamento tra punti/vettori.
 *
 * Il risultato del prodotto è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il prodotto
 * @return Il punto/vettore risultato del prodotto, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator *= (const Point3<T>& otherPoint)
{
    xCoord *= otherPoint.xCoord;
    yCoord *= otherPoint.yCoord;
    zCoord *= otherPoint.zCoord;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di quoziente scalare e assegnamento tra un punto/vettore e uno scalare.
 *
 * Il risultato del quoziente scalare è assegnato al punto/vettore this.
 *
 * @param[in] scalar: scalare con cui verrà eseguito il quoziente scalare
 * @return Il punto/vettore risultato del quoziente scalare tra il punto/vettore this e scalar
 */
template <class T>
inline Point3<T> Point3<T>::operator /= (const T& scalar)
{
    xCoord /= scalar;
    yCoord /= scalar;
    zCoord /= scalar;
    return *this;
}

/**
 * \~Italian
 * @brief Operatore di quoziente, componente per componente, e assegnamento tra punti/vettori.
 *
 * Il risultato del quoziente è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il quoziente
 * @return Il punto/vettore risultato del quoziente, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point3<T> Point3<T>::operator /= (const Point3<T>& otherPoint)
{
    xCoord /= otherPoint.xCoord;
    yCoord /= otherPoint.yCoord;
    zCoord /= otherPoint.zCoord;
    return *this;
}

/****************
* Other Methods *
*****************/
/**
 * \~Italian
 * @brief Operatore di prodotto scalare tra un punto/vettore e uno scalare
 * @param[in] scalar: scalare con cui verrà eseguito il prodotto scalare
 * @param[in] point: punto/vettore con cui verrà eseguito il prodotto scalare
 * @return Il punto/vettore risultato del prodotto scalare tra tra point e scalar
 */
template <class T>
inline Point3<T> operator * (const T& scalar, const Point3<T>& point)
{
	return Point3<T>(point.x() * scalar,
                    point.y() * scalar,
                    point.z() * scalar);
}

template <class T>
inline Point3<T> mul(const T m[][3], const Point3<T>& point)
{
	Point3<T> tmp = point;
    tmp.setX(m[0][0]*point.x() + m[0][1]*point.y() + m[0][2]*point.z());
    tmp.setY(m[1][0]*point.x() + m[1][1]*point.y() + m[1][2]*point.z());
    tmp.setZ(m[2][0]*point.x() + m[2][1]*point.y() + m[2][2]*point.z());
    return tmp;
}

#ifdef CG3_WITH_EIGEN
template <class T>
inline Point3<T> mul(const Eigen::Matrix3d &m, const Point3<T>& point)
{
	Point3<T> tmp = point;
    tmp.setX(m(0,0)*point.x() + m(0,1)*point.y() + m(0,2)*point.z());
    tmp.setY(m(1,0)*point.x() + m(1,1)*point.y() + m(1,2)*point.z());
    tmp.setZ(m(2,0)*point.x() + m(2,1)*point.y() + m(2,2)*point.z());
    return tmp;
}
#endif //CG3_WITH_EIGEN

/**
 * \~Italian
 * @brief Operatore di stram sul punto/vettore
 * @param[in] input_stream: stream di input
 * @return Lo stream di input a cui è stato accodato lo stream del punto/vettore
 */
template <class T>
inline std::ostream& operator<<(std::ostream& inputStream, const Point3<T>& p)
{
    inputStream << "[" << p.x() << ", " << p.y() << ", " << p.z() << "]";
    return inputStream;
}

template<class T>
inline std::string to_string(const Point3<T> &p)
{
    return std::string("[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ", " + std::to_string(p.z()) + "]");
}

} //namespace cg3

//hash specialization
template<typename T>
inline std::size_t std::hash<cg3::Point3<T> >::operator()(const cg3::Point3<T>& k) const
{
    std::size_t h=0;
    cg3::hashCombine(h, k.x(), k.y(), k.z());
    return h;
}
