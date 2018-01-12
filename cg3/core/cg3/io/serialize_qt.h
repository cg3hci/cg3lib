/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SERIALIZE_QT_H
#define CG3_SERIALIZE_QT_H

#include "serialize.h"

#ifdef QT_CORE_LIB
#include <QColor>
#endif //QT_CORE_LIB

namespace cg3 {
namespace serializer {

#ifdef QT_CORE_LIB
void serialize(const QColor& obj, std::ofstream& binaryFile);

void deserialize(QColor& obj, std::ifstream& binaryFile);
#endif

}
}

#include "serialize_qt.tpp"

#endif // CG3_SERIALIZE_QT_H
