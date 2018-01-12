/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "serialize_qt.h"

namespace cg3 {

#ifdef QT_CORE_LIB
/**
 * \~English
 * @brief Serializer::serialize
 * @param[in] obj: QColor
 * @param binaryFile
 */
inline void serializer::serialize(const QColor& obj, std::ofstream& binaryFile){
    int r = obj.red(), g = obj.green(), b = obj.blue(), a = obj.alpha();
    cg3::serializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
}

/**
 * \~English
 * @brief Serializer::deserialize
 * @param[out] obj: QColor
 * @param binaryFile
 */
inline void serializer::deserialize(QColor& obj, std::ifstream& binaryFile){
    int r, g, b, a;
    cg3::deserializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
    obj.setRgb(r,g,b,a);
}
#endif //QT_CORE_LIB

}
