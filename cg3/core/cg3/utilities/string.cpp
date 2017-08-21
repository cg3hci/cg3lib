#include "string.h"

#include <iomanip>
#include <sstream>

namespace cg3 {

/**
 * @brief Common::toStringWithPrecision
 * @param value
 * @param precision
 * @link https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
 * @return
 */
template<typename T>
std::string toStringWithPrecision(const T& value, unsigned int precision) {
    std::ostringstream out;
    out << std::setprecision(precision) << value;
    return out.str();
}

/**
 * @brief Common::separateExtensionFromFilename
 * @param fullname
 * @param rawname
 * @param extension
 * @link https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
 */
inline void separateExtensionFromFilename(const std::string& fullname, std::string& rawname, std::string& extension) {
    size_t lastindex = fullname.find_last_of(".");
    rawname = fullname.substr(0, lastindex);
    extension = fullname.substr(lastindex, fullname.size());
}

inline void separateFilenameFromPath(const std::string &fullpath, std::string &path, std::string &filename) {
    size_t lastindex = fullpath.find_last_of("/");
    path = fullpath.substr(0, lastindex);
    filename = fullpath.substr(lastindex, fullpath.size());
}

}
