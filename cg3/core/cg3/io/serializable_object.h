#ifndef CG3_SERIALIZABLE_OBJECT_H
#define CG3_SERIALIZABLE_OBJECT_H

#include <fstream>

namespace cg3 {

/**
 * \~English
 * @interface SerializableObject
 *
 * @brief The SerializableObject interface
 *
 *
 * If an class implements this interface, it becames "Serializable".
 * In that case, rules for serialization and deserialization of that class are given on
 * SerializableObject::serialize() and SerializableObject::deserialize() methods.
 */
class SerializableObject {
    public:
        SerializableObject() {}
        virtual ~SerializableObject() {}

        /**
         * \~English
         * @brief serialize
         *
         * How to use:
         *
         * \code{.cpp}
         * std::ofstream myfile;
         * //overwrite:
         * myfile.open ("fileName", std::ios::out | std::ios::binary);
         * //or append:
         * myfile.open ("fileName", std::ios::out | std::ios::binary | std::ios::app);
         *
         * if (myfile.is_open()) {
         *     myobj.serialize(myfile);
         * }
         * myfile.close();
         * \endcode
         *
         * @param[in] binaryFile : ofstream where we want to serialize the object
         */
        virtual void serialize(std::ofstream& binaryFile) const = 0;

        /**
         * \~English
         * @brief deserialize
         *
         * How to use:
         *
         * \code{.cpp}
         * std::ifstream myfile;
         * myfile.open ("filename", std::ios::in | std::ios::binary);
         * if (myfile.is_open()) {
         *      if (myobj.deserialize(myfile))
         *          std::cout << "Object deserialized\n";
         *      else
         *          std::cout << "Object not serialized\n";
         * }
         * myfile.close();
         * \endcode
         *
         * @param[in] binaryFile : ifstream where we want to deserialize the object
         */
        virtual bool deserialize(std::ifstream& binaryFile) = 0;
};

}

#endif // COMMON_MODULE_SERIALIZABLE_OBJECT_H
