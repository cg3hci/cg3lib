/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SERIALIZABLE_OBJECT_H
#define CG3_SERIALIZABLE_OBJECT_H

#include "../cg3lib.h"
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
 *
 * Iff your class is a simple class without manually managed resources, and all of its
 * attributes are SerializableObjects (or it exists a specialized function in the Serializer
 * namespace) you can easily use the helpers Serializer::serializeObjectAttributes() and
 * Serializer::deserializeObjectsAttributes();
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
         * The serialize function should serialize all the data of your class.
         * Iff your class is a simple class without manually managed resources, and all of its
         * attributes are SerializableObjects (or it exists a specialized function in the Serializer
         * namespace) you can easily use the helpers cg3::serializeObjectAttributes():
         *
         * \code{.cpp}
         * void serialize(std::ofstream& binaryFile){
         *     //"MyClass" should be a string containing the name of your class.
         *     cg3::serializeObjectAttributes("MyClass", binaryFile, attr1, attr2, attr3);
         * }
         * \endcode
         *
         * The helper function cg3::serializeObjectAttributes() accepts a variabile number of
         * arguments.
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
         *      try{
         *          myobj.deserialize(myfile);
         *          std::cout << "Object deserialized\n";
         *      }
         *      catch(...){
         *          std::cout << "Object not deserialized\n";
         *      }
         * }
         * myfile.close();
         * \endcode
         *
         * The deserialize function should:
         * - save the initial position of the input ifstream (see Serializer::getPosition());
         * - inside a try block read all the data of the class;
         * - if an exception is catched, the initial position of the input ifstream should be restore  (see Serializer::restorePosition())
         * and throw an std::ios_base::failure exception.
         *
         * Iff your class is a simple class without manually managed resources, and all of its
         * attributes are SerializableObjects (or it exists a specialized function in the Serializer
         * namespace) you can easily use the helpers cg3::deserializeObjectAttributes():
         *
         * \code{.cpp}
         * void deserialize(std::ifstream& binaryFile){
         *     //"MyClass" should be a string containing the name of your class.
         *     cg3::deserializeObjectAttributes("MyClass", binaryFile, attr1, attr2, attr3);
         * }
         * \endcode
         *
         * The helper function cg3::deserializeObjectAttributes() accepts a variabile number of
         * arguments. The argument passed should be exactly the same of the argument passed to the function
         * cg3::serializeObjectAttributes() in the serialize function.
         *
         * @param[in] binaryFile : ifstream where we want to deserialize the object
         */
        virtual void deserialize(std::ifstream& binaryFile) = 0;
};

}

#endif // CG3_SERIALIZABLE_OBJECT_H
