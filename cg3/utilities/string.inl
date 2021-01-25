/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "string.h"

#include <iomanip>
#include <sstream>

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief toStringWithPrecision
 * @param value
 * @param precision
 * @link https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
 * @return
 */
template<typename T>
std::string toStringWithPrecision(
        const T& value,
        unsigned int precision)
{
    std::ostringstream out;
    out << std::setprecision(precision) << value;
    return out.str();
}

/**
 * @ingroup cg3core
 * @brief extracts the extension of a string that contains a filename.
 *
 * \code{.cpp}
 * std::string fullname = "/usr/bin/foo.sh";
 * std::string filename, extension;
 * cg3::separateExtensionFromFilename(fullname, filename, extension);
 * //filename = "/usr/bin/foo"
 * //extension = ".sh"
 * \endcode
 *
 * To separate the path from the filename, see cg3::separateFilenameFromPath
 *
 * @param fullname
 * @param rawname
 * @param extension
 * @link https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
 */
inline void separateExtensionFromFilename(
        const std::string& fullname,
        std::string& rawname,
        std::string& extension)
{
    size_t lastindex = fullname.find_last_of(".");
	if (lastindex != std::string::npos){
		rawname = fullname.substr(0, lastindex);
		extension = fullname.substr(lastindex, fullname.size());
	}
	else {
		rawname = "";
		extension = "";
	}
}

/**
 * @ingroup cg3core
 * @brief extracts the filename (extension included) of a string that contains a fullpath.
 *
 * \code{.cpp}
 * std::string fullname = "/usr/bin/foo.sh";
 * std::string path, filename;
 * cg3::separateExtensionFromFilename(fullname, path, filename);
 * //path = "/usr/bin"
 * //filename = "foo.sh"
 * \endcode
 *
 * @param fullpath
 * @param path
 * @param filename
 */
inline void separateFilenameFromPath(
        const std::string &fullpath,
        std::string &path,
        std::string &filename)
{
    size_t lastindex = fullpath.find_last_of("/");
	if (lastindex != std::string::npos){
		path = fullpath.substr(0, lastindex);
		filename = fullpath.substr(lastindex+1, fullpath.size());
	}
	else {
		path = "";
		filename = "";
	}
}

/**
 * @ingroup cg3core
 * @brief pathWithoutFilename
 *
 * \code{.cpp}
 * std::string fullname = "/usr/bin/foo.sh";
 * std::string path = cg3::pathWithoutFilename(fullname);
 * //path = "/usr/bin/"
 * \endcode
 *
 * @param fullpath
 * @return
 */
inline std::string pathWithoutFilename(const std::string& fullpath)
{
    std::string path, filename;
    separateFilenameFromPath(fullpath, path, filename);
    return path + "/";
}

/**
 * @ingroup cg3core
 * @brief filenameWithExtension
 *
 * \code{.cpp}
 * std::string fullname = "/usr/bin/foo.sh";
 * std::string filename = cg3::filenameWithExtension(fullname);
 * //filename = "foo.sh"
 * \endcode
 *
 * @param fullpath
 * @return
 */
inline std::string filenameWithExtension(const std::string& fullpath)
{
    std::string filename, path, ext;
    separateFilenameFromPath(fullpath, path, filename);
    return filename;
}

/**
 * @ingroup cg3core
 * @brief filenameWithoutExtension
 *
 * \code{.cpp}
 * std::string fullname = "/usr/bin/foo.sh";
 * std::string filename = cg3::filenameWithoutExtension(fullname);
 * //filename = "foo"
 * \endcode
 *
 * @param fullpath
 * @return
 */
inline std::string filenameWithoutExtension(const std::string& fullpath)
{
    std::string filename = filenameWithExtension(fullpath), ext;
    separateExtensionFromFilename(filename, filename, ext);
    return filename;
}



} //namespace cg3
