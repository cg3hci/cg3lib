/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_BOUNDING_BOX_H
#define CG3_BOUNDING_BOX_H

#include <float.h>
#include "point.h"
#include "../utilities/color.h"

namespace cg3 {

/**
 * \~English
 * @class BoundingBox
 * @brief The BoundingBox class models a Bounding Box which contains a 3D mesh.
 *
 *        It is composed of two 3D points representing the minimum and maximum coordinates that generates the bounding box.
 *        The class provides methods like for obtaining the center or the diagonal of the bounding box.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 *
 * \~Italian
 * @class BoundingBox
 * @brief La classe BoundingBox modella un Bounding Box contenente una mesh 3D.
 *
 *        Essa è caratterizzata da due punti contenenti le tre coordinate minime e massime che generano il bounding box.
 *        La classe fornisce metodi come il calcolo del centro e il calcolo della diagonale.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */
class BoundingBox : public SerializableObject {
    public:

        /****************
         * Constructors *
         ****************/

        BoundingBox();
        BoundingBox(const Pointd& min, const Pointd& max);

        /************************
        * Public Inline Methods *
        *************************/

        const Pointd& getMin()     const;
        const Pointd& min()        const;
        const Pointd& getMax()     const;
        const Pointd& max()        const;
        const double& getMinX()    const;
        const double& minX()       const;
        const double& getMinY()    const;
        const double& minY()       const;
        const double& getMinZ()    const;
        const double& minZ()       const;
        const double& getMaxX()    const;
        const double& maxX()       const;
        const double& getMaxY()    const;
        const double& maxY()       const;
        const double& getMaxZ()    const;
        const double& maxZ()       const;
        double getLengthX()        const;
        double getLengthY()        const;
        double getLengthZ()        const;

        Pointd  center()    const;
        double diag()       const;
        bool isValid() const;
        bool isStrictlyIntern(const Pointd& p)     const;
        bool isStrictlyInside(const Pointd& p)     const;
        bool isStrictlyIntern(double px, double py, double pz)     const;
        bool isStrictlyInside(double px, double py, double pz)     const;
        bool isIntern(const Pointd& p)     const;
        bool isInside(const Pointd& p)     const;
        bool isIntern(double px, double py, double pz)     const;
        bool isInside(double px, double py, double pz)     const;
        bool isEpsilonIntern(const Pointd& p, double epsilon = 1e-6)     const;
        bool isEpsilonInside(const Pointd& p, double epsilon = 1e-6)     const;
        bool isEpsilonIntern(double px, double py, double pz, double epsilon = 1e-6)     const;
        bool isEpsilonInside(double px, double py, double pz, double epsilon = 1e-6)     const;
        bool intersect(const BoundingBox& otherBox);
        void getExtremes(std::vector<Pointd> &extremes) const;
        std::vector<Pointd> getExtremes() const;

        //Operators
        const double &operator ()(unsigned int i) const;
        Pointd operator[](unsigned int i)                 const;

        void saveOnObj(const std::string &filename, const Color& c = Color(128, 128, 128)) const;

        void setMin(const Pointd& min);
        Pointd& min();
        void setMax(const Pointd& max);
        Pointd& max();
        void setMin(double x, double y, double z);
        void setMax(double x, double y, double z);
        void setMinX(double x);
        double& minX();
        void setMinY(double y);
        double& minY();
        void setMinZ(double z);
        double& minZ();
        void setMaxX(double x);
        double& maxX();
        void setMaxY(double y);
        double& maxY();
        void setMaxZ(double z);
        double& maxZ();
        void reset();

        //Operators
        double& operator()(unsigned int i);

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    protected:

        /**************
        * Attributes *
        **************/

        Pointd minCoord; /**< \~English @brief Minimum point of the bounding box
                         \~Italian @brief Punto minimo del bounding box*/
        Pointd maxCoord; /**< \~English @brief Maximum point of the bounding box
                         \~Italian @brief Punto massimo del bounding box*/
};

typedef BoundingBox Box;

}

//hash specialization
namespace std {

template <>
struct hash<cg3::BoundingBox> {
    size_t operator()(const cg3::BoundingBox& k) const;
};

}

#include "bounding_box.tpp"

#endif // CG3_BOUNDING_BOX_H
