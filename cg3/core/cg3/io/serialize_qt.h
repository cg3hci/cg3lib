#ifndef CG3_SERIALIZE_QT_H
#define CG3_SERIALIZE_QT_H

#ifdef QT_CORE_LIB
#include <QColor>
#endif //QT_CORE_LIB

namespace cg3 {
namespace Serializer {

#ifdef QT_CORE_LIB
void serialize(const QColor& obj, std::ofstream& binaryFile);

void deserialize(QColor& obj, std::ifstream& binaryFile);
#endif

}
}

#include "serialize_qt.tpp"

#endif // CG3_SERIALIZE_QT_H
